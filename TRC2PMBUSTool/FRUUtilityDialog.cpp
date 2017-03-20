/**
 * @file FRUUtilityDialog.cpp
 */
#include "FRUUtilityDialog.h"

wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_WRITE_END, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_READ_END, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_WRITE_INTERRUPT, wxThreadEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_E2PROM_READ_INTERRUPT, wxThreadEvent);

#define FRU_WRITER_DIALOG_WIDTH   (800)
#define FRU_WRITER_DIALOG_HEIGHT  (480)

#define DEF_E2PROM_SLAVE_ADDR           wxT("AE")
#define DEF_E2PROM_ST_WIDTH                 160
#define DEF_E2PROM_TC_WIDTH                 420
#define DEF_E2PROM_SLAVE_ADDR_WIDTH          30

#define MAX_FRU_FILE_LOAD_LENGTH            256
#define MAX_FRU_FILE_WRITE_LENGTH           256
#define MAX_FRU_FILE_READ_LENGTH            256

#define MAX_RECV_BUFFER_LENGTH              256

#define WRITE_CMD_INTERVAL_TIME              10 // Millisecond
#define READ_CMD_INTERVAL_TIME               10 // Millisecond

#define MAX_E2PROM_WRITE_RETRY_TIMES          3
#define MAX_E2PROM_READ_RETRY_TIMES           3

#define DUMP_BINARY_CONTENT                 

FRUUtilityDialog::FRUUtilityDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO) : wxDialog(parent, wxID_ANY, wxString(wxT("FRU Utility")), wxDefaultPosition, wxSize(FRU_WRITER_DIALOG_WIDTH, FRU_WRITER_DIALOG_HEIGHT)){

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(E2PROM_16));

	this->SetIcon(icon);

	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

	this->outputLog = false;

	// Setup Text Validator
	DecCharIncludes = wxT("0123456789");
	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);

	m_decValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decValidator.SetCharIncludes(DecCharIncludes);

	// Initialize Sizer 
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_e2pROMSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("EEPROM Slave Address"));
	m_fruWriteSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("FRU WRITE"));
	m_fruReadSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("FRU READ"));
	m_logSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Operation Log"));
	m_e2pROMLine1Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_e2pROMLine2Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_btnSizer = new wxBoxSizer(wxHORIZONTAL);

	// Initilaize Components
	// FRU Slave Address 
	m_e2pROMSlaveAddrST = new wxStaticText(m_e2pROMSBS->GetStaticBox(), wxID_ANY, wxT("EEPROM Slave Address"), wxDefaultPosition, wxSize(DEF_E2PROM_ST_WIDTH, -1));
	m_e2pROMSlaveAddrTC = new wxTextCtrl(m_e2pROMSBS->GetStaticBox(), wxID_ANY, DEF_E2PROM_SLAVE_ADDR, wxDefaultPosition, wxSize(DEF_E2PROM_SLAVE_ADDR_WIDTH, -1));
	m_e2pROMSlaveAddrTC->SetValidator(m_hexValidator);
	m_e2pROMSlaveAddrTC->SetMaxLength(2);

	// FRU File
	m_fruFileST = new wxStaticText(m_fruWriteSBS->GetStaticBox(), wxID_ANY, wxT("FRU File"), wxDefaultPosition, wxSize(DEF_E2PROM_ST_WIDTH, -1));
	m_fruFileTC = new wxTextCtrl(m_fruWriteSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(DEF_E2PROM_TC_WIDTH, -1));
	m_fruFileTC->SetEditable(false);
	m_floppyLoadBB = new wxBitmapButton(m_fruWriteSBS->GetStaticBox(), CID_BTN_LOAD, wxBITMAP_PNG(FLOPPY_16));

	//m_stline1 = new wxStaticLine(this);
	//m_stline2 = new wxStaticLine(this);

	m_btnWRITE = new wxButton(m_fruWriteSBS->GetStaticBox(), CID_BTN_WRITE, wxT("WRITE To E2PROM"));
	m_btnWRITE->Enable(false);

	m_btnREAD = new wxButton(this, CID_BTN_READ, wxT("READ"));
	m_btnREAD->Enable(true);

	m_btnSaveAsFile = new wxButton(this, CID_BTN_SAVE_AS_FILE, wxT("Save As File"));
	m_btnSaveAsFile->Enable(false);

	m_logTC = new PMBUSLogTextCtrl(m_logSBS->GetStaticBox(), wxID_ANY);

	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	this->m_logTC->SetFont(font);


	// Add Components To Sizer
	m_e2pROMLine1Sizer->Add(m_e2pROMSlaveAddrST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMLine1Sizer->Add(m_e2pROMSlaveAddrTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMSBS->Add(m_e2pROMLine1Sizer);

	m_e2pROMLine2Sizer->Add(m_fruFileST, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMLine2Sizer->Add(m_fruFileTC, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMLine2Sizer->Add(m_floppyLoadBB, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_e2pROMLine2Sizer->Add(m_btnWRITE, wxSizerFlags().Align(wxALIGN_CENTER_VERTICAL).Border());
	m_fruWriteSBS->Add(m_e2pROMLine2Sizer);

	m_btnSizer->Add(m_btnREAD);
	m_btnSizer->Add(m_btnSaveAsFile);

	m_fruReadSBS->Add(m_btnSizer);

	m_logSBS->Add(m_logTC, wxSizerFlags(1).Expand().Border());

	m_topLevelSizer->Add(m_e2pROMSBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_fruWriteSBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_fruReadSBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_logSBS, wxSizerFlags(1).Expand().Border());

	memset(this->m_fruBinaryContent, 0x00, MAX_FRU_FILE_SIZE);
	memset(this->m_e2pRomContent,    0xFF, MAX_FRU_FILE_SIZE);

	SetSizer(m_topLevelSizer);
}

FRUUtilityDialog::~FRUUtilityDialog(){

	wxLog::SetActiveTarget(m_oldLog);
}

void FRUUtilityDialog::OnBtnLOAD(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	unsigned int readBytes = 0;

	// Load FRU Binary File
	wxFileDialog LoadBINFileDialog(this, L"Load FRU Binary File", "", "", "BIN Files (*.bin)|*.bin", wxFD_OPEN);

	LoadBINFileDialog.Centre();

	// If the user changed idea...
	if (LoadBINFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

	wxString path = LoadBINFileDialog.GetPath();
	PSU_DEBUG_PRINT(MSG_ALERT, "BINARY File Path : %s", path.c_str());

	// Update FRU File Path Static Text
	m_fruFileTC->SetValue(path);

	// Open Binary File
	wxFile *fruFile = new wxFile(path, wxFile::read);

	if (fruFile->IsOpened() != true){
		PSU_DEBUG_PRINT(MSG_ERROR, "Open BINARY File Failed");
		return;
	}

	// Load Conten Of FRU Buiary File
	PSU_DEBUG_PRINT(MSG_ALERT, "BINARY File Size is %lld Bytes", fruFile->Length());

	// If File Size Large Than 256, Should be a error
	if (fruFile->Length() > MAX_FRU_FILE_LOAD_LENGTH){
		PSU_DEBUG_PRINT(MSG_ERROR, "BINARY FILE Size Large Than %d", MAX_FRU_FILE_LOAD_LENGTH);
		wxDELETE(fruFile);
		return;
	}

	readBytes = fruFile->Read((void*)this->m_fruBinaryContent, MAX_FRU_FILE_LOAD_LENGTH);
	this->m_fruFileLength = readBytes;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Bytes Loaeded : %d", readBytes);

#ifdef DUMP_BINARY_CONTENT
	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------- BINARY FILE CONTENT -------------------");
	PMBUSHelper::PrintFRUContent(this->m_fruBinaryContent, readBytes);
#endif

#if 1
	// Parse FRU
	struct FRU_DATA *fru = NULL;
	fru = parse_FRU(this->m_fruBinaryContent);

	if (fru){

		if (fru->Product_Area){
			dump_PRODUCT(fru->Product_Area);
		}

		if (fru->MultiRecord_Area){
			dump_MULTIRECORD(fru->MultiRecord_Area);
		}

		free_FRU(fru);

		// Seems like No Error On FRU Binary File Content
		m_btnWRITE->Enable(true);
	}
#endif

	wxDELETE(fruFile);
}

void FRUUtilityDialog::OnBtnWRITE(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	// Disable Read/Write Button
	this->m_btnREAD->Enable(false);
	this->m_btnWRITE->Enable(false);

	// New E2PRomWriteDataTask To Write
	int count = TaskEx::GetCount(task_ID_E2PRomWriteDataTask);
	
	if (count > 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "Another E2PRomWriteDataTask is Running");
		return;
	}

	new(TP_E2PRomWriteDataTask) E2PRomWriteDataTask(this->m_ioaccess, this->m_currentIO, this->GetEventHandler(), (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()), this->m_fruBinaryContent, this->m_fruFileLength, &this->outputLog, WRITE_CMD_INTERVAL_TIME, READ_CMD_INTERVAL_TIME);

}

void FRUUtilityDialog::OnBtnREAD(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	//unsigned char e2pRomContent[MAX_FRU_FILE_SIZE] = { 0 };

	this->m_preWriteBTNEnable = this->m_btnWRITE->IsEnabled();

	this->m_btnREAD->Enable(false);
	this->m_btnWRITE->Enable(false);

	// New E2PRomReadDataTask To Write
	int count = TaskEx::GetCount(task_ID_E2PRomReadDataTask);

	if (count > 0){
		PSU_DEBUG_PRINT(MSG_ALERT, "Another E2PRomReadDataTask is Running");
		return;
	}

	new(TP_E2PRomReadDataTask) E2PRomReadDataTask(this->m_ioaccess, this->m_currentIO, this->GetEventHandler(), (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()), m_e2pRomContent, &this->outputLog, READ_CMD_INTERVAL_TIME);
	
}

void FRUUtilityDialog::OnBtnSaveAsFile(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	// Save FRU Binary File
	wxFileDialog SaveFRUBinaryFileDialog(this, L"Save FRU Binary File", "", "FRU.bin", "BIN Files (*.bin)|*.bin", wxFD_SAVE);

	SaveFRUBinaryFileDialog.Centre();

	// If the user changed idea...
	if (SaveFRUBinaryFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

	// Get Save Path
	wxString path = SaveFRUBinaryFileDialog.GetPath();
	PSU_DEBUG_PRINT(MSG_ALERT, "Save FRU Binary File To %s", path.c_str());

	// Start Save Binary File
	wxString SavePath = path;

	wxFFileOutputStream fileOutStream(SavePath);

	if (!fileOutStream.IsOk()){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can not Save Binary To %s", SavePath);
		return;
	}

	wxDataOutputStream dataOutputStream(fileOutStream);

	for (unsigned int idx = 0; idx < MAX_FRU_FILE_SIZE; idx++){

		wxUint8 u8(this->m_e2pRomContent[idx]);
		dataOutputStream.Write8(u8);

	}

	fileOutStream.Sync();
}

void FRUUtilityDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	this->EndModal(wxID_CANCEL);

}

void FRUUtilityDialog::OnE2PRomWriteEnd(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	// Enable Read/Write Button
	this->m_btnREAD->Enable(true);
	this->m_btnWRITE->Enable(true);

	wxMessageBox(wxT("Write & Verify E2PROM Success"),
		wxT("Write E2PROM Success"),  // caption
		wxOK | wxICON_INFORMATION);
}

void FRUUtilityDialog::OnE2PRomReadEnd(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	
	wxMessageBox(wxT("Read E2PROM Success"),
		wxT("Read E2PROM Success"),  // caption
		wxOK | wxICON_INFORMATION);
	
	this->m_btnREAD->Enable(true);
	if (this->m_preWriteBTNEnable == true){
		this->m_btnWRITE->Enable(true);
	}

	// Print Content of E2PROM
	PSU_DEBUG_PRINT(MSG_ALERT, "----------------------- E2PROM CONTENT ----------------------");
	PMBUSHelper::PrintFRUContent(this->m_e2pRomContent, 256);

	// Parse FRU
	struct FRU_DATA *fru = NULL;
	fru = parse_FRU(m_e2pRomContent);

	if (fru){
		if (fru->Product_Area){
			dump_PRODUCT(fru->Product_Area);
		}
		free_FRU(fru);

		m_btnSaveAsFile->Enable(true);
	}

}

void FRUUtilityDialog::OnE2PRomWriteInterrupt(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	// Enable Read/Write Button
	this->m_btnREAD->Enable(true);
	this->m_btnWRITE->Enable(true);

	wxMessageBox(wxT("Write & Verify E2PROM Failed"),
		wxT("Write E2PROM Failed"),  // caption
		wxOK | wxICON_ERROR);
}

void FRUUtilityDialog::OnE2PRomReadInterrupt(wxThreadEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);
	this->m_btnREAD->Enable(true);
	if (this->m_preWriteBTNEnable == true){
		this->m_btnWRITE->Enable(true);
	}

	wxMessageBox(wxT("Read E2PROM Failed"),
		wxT("Read E2PROM Failed"),  // caption
		wxOK | wxICON_ERROR);
}

void FRUUtilityDialog::dump_fru_field(const char * description, size_t offset, unsigned char * field){
	/* does field exist, and have length? */
	if (field) {
		//PSU_DEBUG_PRINT(MSG_ALERT, "%s : ", description);
		if (FIELD_LEN(field)) {
			if (TYPE_CODE(field) == FRU_STRING_ASCII || offset) {
				wxString str("");
				str += wxString::Format("%32s", description);

				for (int idx = 0; idx < FIELD_LEN(field); idx++){
					str += wxString::Format("%c", *&field[offset + 1 + idx]);
				}

				PSU_DEBUG_PRINT(MSG_ALERT, "%s", str.c_str());
			}
			else {
				PSU_DEBUG_PRINT(MSG_ALERT ,"Non-ASCII");
			}
		}
		else
			PSU_DEBUG_PRINT(MSG_ERROR, "Empty Field");
	}
}

void FRUUtilityDialog::dump_PRODUCT(struct PRODUCT_INFO *fru){

	PSU_DEBUG_PRINT(MSG_ALERT, "-----------------------  PRODUCT INFO  ----------------------");
	dump_fru_field("Manufacturer Name : ", 0, fru->manufacturer_name);
	dump_fru_field("Product Name : ", 0, fru->product_name);
	dump_fru_field("Model Number : ", 0, fru->model_number);
	dump_fru_field("VERSION : ", 0, fru->version);
	dump_fru_field("Serial Number : ", 0, fru->serial_number);
	dump_fru_field("asset_tag : ", 0, fru->asset_tag);
	dump_fru_field("FRU File ID : ", 0, fru->FRU_file_ID);

}

void FRUUtilityDialog::dump_MULTIRECORD(struct MULTIRECORD_INFO *fru){

	unsigned char *p, *n, *z;
	int i;

	/*
	 * Power Supply Information
	 */
	const char * POWER_SUPPLY_INFO[] = {
		"Overall capacity (watts)", /**< Overall capacity (watts) */ 
		"Peak VA", /**< Peak VA */
		"Inrush Current", /**< Inrush Current */
		"Inrush Interval", /**< Inrush Interval */
		"Low  End Input Voltage Range 1", /**< Low  End Input Voltage Range 1 */
		"High End Input Voltage Range 1", /**< High End Input Voltage Range 1 */
		"Low  End Input Voltage Range 2", /**< Low  End Input Voltage Range 2 */
		"High End Input Voltage Range 2", /**< High End Input Voltage Range 2 */
		"Low End Input Frequence Range", /**< Low End Input Frequence Range */
		"High End Input Frequence Range", /**< High End Input Frequence Range */
		"A/C Dropout Tolerance", /**< A/C Dropout Tolerance */
		"Binary Flags", /**<  */
		"Peak Wattage", /**< Peak Wattage */
		"Combined Wattage", /**< Combined Wattage */
		"Predictive fail tachometer lower threshold (RPS)", /**< Predictive fail tachometer lower threshold (RPS) */
	};

	// If Power Supply Information Exist
	if (fru->power_supply_info){

		PSU_DEBUG_PRINT(MSG_ALERT, "----------------------  MULTI AREA INFO ---------------------");

		z = (unsigned char*)x_calloc(1, 24);
		p = fru->power_supply_info;
		n = p + 5;

		if (memcmp(&n[0], z, 24)) {
			PSU_DEBUG_PRINT(MSG_ALERT, "Power Supply Infomation");
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[0], (n[0] | (n[1] << 8) & 0x0fff));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[1], (n[2] | (n[3] << 8)));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[2], (n[4]));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d(ms)", POWER_SUPPLY_INFO[3], (n[5]));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[4], (n[6] | (n[7] << 8)) * 10);
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[5], (n[8] | (n[9] << 8)) * 10);
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[6], (n[10] | (n[11] << 8)) * 10);
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[7], (n[12] | (n[13] << 8)) * 10);
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[8], (n[14]));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[9], (n[15]));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d(ms)", POWER_SUPPLY_INFO[10], (n[16]));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[11], (n[17]));
			PSU_DEBUG_PRINT(MSG_ALERT, "  %s:",        POWER_SUPPLY_INFO[12]);
			PSU_DEBUG_PRINT(MSG_ALERT, "    Hold up time in seconds: %d", ((n[18] | (n[19] << 8)) & 0xf000) >> 12);
			PSU_DEBUG_PRINT(MSG_ALERT, "    Peak capacity (watts): %d",   (n[18] | (n[19] << 8)) & 0x0fff);

			PSU_DEBUG_PRINT(MSG_ALERT, "  %s:",        POWER_SUPPLY_INFO[13]);
			PSU_DEBUG_PRINT(MSG_ALERT, "    Voltage 1: %d", ((n[20]) & 0xF0) >> 4);
			PSU_DEBUG_PRINT(MSG_ALERT, "    Voltage 2: %d", ((n[20]) & 0x0F));
			PSU_DEBUG_PRINT(MSG_ALERT, "    Total Combined Wattage: %d", (n[21] | (n[22] << 8)));


			PSU_DEBUG_PRINT(MSG_ALERT, "  %s: %d",     POWER_SUPPLY_INFO[14], (n[23]));
		}
		else{
			PSU_DEBUG_PRINT(MSG_ALERT, "  All Zeros");
		}

		free(z);
	}


	/*
	 * DC Load and DC Output Multi-record Definitions
	 * Table 8 from the VITA/ANSI 57.1 Spec
	 */
	const char * DC_Loads[] = {
		"P1 VADJ",			/* Load   :  0 */
		"P1 3P3V",			/* Load   :  1 */
		"P1 12P0V",			/* Load   :  2 */
		"P1 VIO_B_M2C",		/* Output :  3 */
		"P1 VREF_A_M2C",	/* Output :  4 */
		"P1 VREF_B_M2C",	/* Output :  5 */
		"P2 VADJ",			/* Load   :  6 */
		"P2 3P3V",			/* Load   :  7 */
		"P2 12P0V",			/* Load   :  8 */
		"P2 VIO_B_M2C",		/* Load   :  9 */
		"P2 VREF_A_M2C",	/* Load   : 10 */
		"P2 VREF_B_M2C",	/* Load   : 11 */
	};


	z = (unsigned char*)x_calloc(1, 12);

	for (i = 0; i <= NUM_SUPPLIES - 1; i++) {
		if (!fru->supplies[i])
			continue;
		p = fru->supplies[i];
		n = p + 5;
		switch (p[0]) {
		case 1:
			PSU_DEBUG_PRINT(MSG_ALERT, "DC Output");
			PSU_DEBUG_PRINT(MSG_ALERT, "  Output Number: %d (%s)", n[0] & 0xF, DC_Loads[n[0] & 0xF]);
			if (memcmp(&n[1], z, 11)) {
				PSU_DEBUG_PRINT(MSG_ALERT, "  Nominal volts:              %d (mV)", (n[1] | (n[2] << 8)) * 10);
				PSU_DEBUG_PRINT(MSG_ALERT, "  Maximum negative deviation: %d (mV)", (n[3] | (n[4] << 8)) * 10);
				PSU_DEBUG_PRINT(MSG_ALERT, "  Maximum positive deviation: %d (mV)", (n[5] | (n[6] << 8)) * 10);
				PSU_DEBUG_PRINT(MSG_ALERT, "  Ripple and Noise pk-pk:     %d (mV)", n[7] | (n[8] << 8));
				PSU_DEBUG_PRINT(MSG_ALERT, "  Minimum current draw:       %d (mA)", n[9] | (n[10] << 8));
				PSU_DEBUG_PRINT(MSG_ALERT, "  Maximum current draw:       %d (mA)", n[11] | (n[12] << 8));
			}
			else
				PSU_DEBUG_PRINT(MSG_ALERT, "  All Zeros");
			break;
		case 2:
			PSU_DEBUG_PRINT(MSG_ALERT, "DC Load");
			PSU_DEBUG_PRINT(MSG_ALERT, "  Output number: %d (%s)", n[0] & 0xF, DC_Loads[n[0] & 0xF]);
			PSU_DEBUG_PRINT(MSG_ALERT, "  Nominal Volts:         %04d (mV)", (n[1] | (n[2] << 8)) * 10);
			PSU_DEBUG_PRINT(MSG_ALERT, "  minimum voltage:       %04d (mV)", (n[3] | (n[4] << 8)) * 10);
			PSU_DEBUG_PRINT(MSG_ALERT, "  maximum voltage:       %04d (mV)", (n[5] | (n[6] << 8)) * 10);
			PSU_DEBUG_PRINT(MSG_ALERT, "  Ripple and Noise pk-pk %04d (mV)", n[7] | (n[8] << 8));
			PSU_DEBUG_PRINT(MSG_ALERT, "  Minimum current load   %04d (mA)", n[9] | (n[10] << 8));
			PSU_DEBUG_PRINT(MSG_ALERT, "  Maximum current load   %04d (mA)", n[11] | (n[12] << 8));
			break;
		}
	}
	free(z);

}

void FRUUtilityDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
{

	switch (level) {

	case wxLOG_FatalError:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
	case wxLOG_Error:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
		//case wxLOG_Warning:
		//break;
		//case wxLOG_Message:
		//break;
		//case wxLOG_Status:
		//break;
		//case wxLOG_Info:
		//break;
		//case wxLOG_Debug:
		//break;

	default:
		text->SetDefaultStyle(wxTextAttr(*wxBLUE, *wxWHITE));
		break;
	}

#ifdef _DEBUG

	//text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));
	text->AppendText(wxString::Format("%-8s   %s", threadstr, msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s %10s           %s", timestr, threadstr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#else
	//text->AppendText(wxString::Format("%9s           %s", timestr, msg));
	text->AppendText(wxString::Format("%-s", msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s           %s", timestr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#endif
}

void FRUUtilityDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
{
	// let the default GUI logger treat warnings and errors as they should be
	// more noticeable than just another line in the log window and also trace
	// messages as there may be too many of them
#if 0
	if (level <= wxLOG_Warning || level == wxLOG_Trace)
	{
		m_oldLogger->LogRecord(level, msg, info);
		return;
	}
#endif

	DoLogLine(
		level,
		this->m_logTC,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		: wxString::Format("%lx", info.threadId),
		msg + "\n"
		);

}

wxBEGIN_EVENT_TABLE(FRUUtilityDialog, wxDialog)
EVT_BUTTON(CID_BTN_LOAD, FRUUtilityDialog::OnBtnLOAD)
EVT_BUTTON(CID_BTN_WRITE, FRUUtilityDialog::OnBtnWRITE)
EVT_BUTTON(CID_BTN_READ, FRUUtilityDialog::OnBtnREAD)
EVT_BUTTON(CID_BTN_SAVE_AS_FILE, FRUUtilityDialog::OnBtnSaveAsFile)
EVT_THREAD(wxEVT_COMMAND_E2PROM_WRITE_END, FRUUtilityDialog::OnE2PRomWriteEnd)
EVT_THREAD(wxEVT_COMMAND_E2PROM_READ_END, FRUUtilityDialog::OnE2PRomReadEnd)
EVT_THREAD(wxEVT_COMMAND_E2PROM_WRITE_INTERRUPT, FRUUtilityDialog::OnE2PRomWriteInterrupt)
EVT_THREAD(wxEVT_COMMAND_E2PROM_READ_INTERRUPT, FRUUtilityDialog::OnE2PRomReadInterrupt)
EVT_CLOSE(FRUUtilityDialog::OnDialogClose)
wxEND_EVENT_TABLE()