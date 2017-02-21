/**
 * @file FRUWriterDialog.cpp
 */
#include "FRUWriterDialog.h"

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

FRUWriterDialog::FRUWriterDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO) : wxDialog(parent, wxID_ANY, wxString(wxT("FRU Writer Dialog")), wxDefaultPosition, wxSize(FRU_WRITER_DIALOG_WIDTH, FRU_WRITER_DIALOG_HEIGHT)){

	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

	// Setup Text Validator
	DecCharIncludes = wxT("0123456789");
	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);

	m_decValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decValidator.SetCharIncludes(DecCharIncludes);

	// Initialize Sizer 
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_e2pROMSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("EEPROM"));
	m_e2pROMLine1Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_e2pROMLine2Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_btnSizer = new wxBoxSizer(wxHORIZONTAL);

	// Initilaize Components
	m_fruFileST = new wxStaticText(m_e2pROMSBS->GetStaticBox(), wxID_ANY, wxT("FRU File"), wxDefaultPosition, wxSize(DEF_E2PROM_ST_WIDTH, -1));
	m_fruFileTC = new wxTextCtrl(m_e2pROMSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(DEF_E2PROM_TC_WIDTH,-1));
	m_fruFileTC->SetEditable(false);
	m_floppyLoadBB = new wxBitmapButton(m_e2pROMSBS->GetStaticBox(), CID_BTN_LOAD, wxBITMAP_PNG(FLOPPY_16));

	m_e2pROMSlaveAddrST = new wxStaticText(m_e2pROMSBS->GetStaticBox(), wxID_ANY, wxT("EEPROM Slave Address"), wxDefaultPosition, wxSize(DEF_E2PROM_ST_WIDTH, -1));
	m_e2pROMSlaveAddrTC = new wxTextCtrl(m_e2pROMSBS->GetStaticBox(), wxID_ANY, DEF_E2PROM_SLAVE_ADDR, wxDefaultPosition, wxSize(DEF_E2PROM_SLAVE_ADDR_WIDTH, -1));
	m_e2pROMSlaveAddrTC->SetValidator(m_hexValidator);
	m_e2pROMSlaveAddrTC->SetMaxLength(2);

	//m_stline1 = new wxStaticLine(this);
	//m_stline2 = new wxStaticLine(this);

	m_btnWRITE = new wxButton(this, CID_BTN_WRITE, wxT("WRITE"));
	m_btnWRITE->Enable(false);

	m_btnREAD = new wxButton(this, CID_BTN_READ, wxT("READ"));
	m_btnREAD->Enable(true);

	m_logTC = new PMBUSLogTextCtrl(this, wxID_ANY);

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
	m_e2pROMSBS->Add(m_e2pROMLine2Sizer);

	m_btnSizer->Add(m_btnREAD);
	m_btnSizer->Add(m_btnWRITE);

	m_topLevelSizer->Add(m_e2pROMSBS, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_btnSizer, wxSizerFlags().Expand().Border());
	m_topLevelSizer->Add(m_logTC, wxSizerFlags(1).Expand().Border());

	this->m_btnWRITE->Enable(true);

	memset(this->m_fruReadBuffer, 0, MAX_FRU_FILE_SIZE);
	memset(this->m_e2pRomContent, 0, MAX_FRU_FILE_SIZE);

	SetSizer(m_topLevelSizer);
}

FRUWriterDialog::~FRUWriterDialog(){

	wxLog::SetActiveTarget(m_oldLog);
}

int FRUWriterDialog::ProductE2PRomWriteBuffer(unsigned int idx, unsigned char* sendBuffer, unsigned int* currentIO){

	unsigned int current_index = 0;

	if (sendBuffer == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "Send Buffer = NULL");
		return 0;
	}

	switch (*currentIO){

	case IOACCESS_SERIALPORT:
		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		sendBuffer[0] = 0x41;
		sendBuffer[1] = 0x54;
		sendBuffer[2] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str());// E2PROM Slave Address
		sendBuffer[3] = 0x00; // Indicates Start Write Offset
		// Data start from index 4
		current_index = 4;
		sendBuffer[current_index++] = this->m_fruReadBuffer[idx];

		break;

	case IOACCESS_HID:

		// 0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0x00, cmdPageValue, 0x00, 0x0D, 0x0A
		sendBuffer[0] = 0x05;

		sendBuffer[2] = 0x41;
		sendBuffer[3] = 0x54;
		sendBuffer[4] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str());// E2PROM Slave Address
		sendBuffer[5] = idx; // Indicates Start Write Offset
		// Data start from index 6
		current_index = 6;
		sendBuffer[current_index++] = this->m_fruReadBuffer[idx];

		// Fill Last 2

		if (sendBuffer[current_index - 1] == 0x0d){
			sendBuffer[current_index++] = 0x0d;
		}
		sendBuffer[current_index++] = 0x0D;
		sendBuffer[current_index++] = 0x0A;

		sendBuffer[1] = current_index - 2;

		break;

	case IOACCESS_TOTALPHASE:

		sendBuffer[0] = 0; // Write Bytes(Updated later)
		sendBuffer[1] = 0; // Read Bytes
		sendBuffer[2] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str());// E2PROM Slave Address
		sendBuffer[3] = 0x00; // Indicates Start Write Offset

		// Data start from index 4
		current_index = 4;
		sendBuffer[current_index++] = this->m_fruReadBuffer[idx];

		// Update Write Bytes For Write CMD
		sendBuffer[0] = current_index - 3;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error");
		break;
	}

	return current_index;


}

int FRUWriterDialog::ProductE2PRomReadBuffer(unsigned int idx, unsigned char* sendBuffer, unsigned int* currentIO){
	unsigned int baseIndex = 0;
	int buffer_len = 0;

	switch (*currentIO){

	case IOACCESS_SERIALPORT:

		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str());// E2PROM Slave Address
		sendBuffer[baseIndex++] = idx;

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()) | 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		buffer_len = baseIndex;


		break;

	case IOACCESS_HID:

		sendBuffer[baseIndex++] = 0x05;           // Report ID is 0x05
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = 0x41;
		sendBuffer[baseIndex++] = 0x44;
		sendBuffer[baseIndex++] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str());// E2PROM Slave Address
		sendBuffer[baseIndex++] = idx;

		// May Have 0x0d Command
		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;
		sendBuffer[baseIndex++] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()) | 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data

		if (sendBuffer[baseIndex - 1] == 0x0d){
			sendBuffer[baseIndex++] = 0x0d;
		}

		sendBuffer[baseIndex++] = 0x0d;
		sendBuffer[baseIndex++] = 0x0a;

		sendBuffer[1] = (baseIndex - 2);
		buffer_len = baseIndex;

		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x02;
		sendBuffer[baseIndex++] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()) | 0x01;
		sendBuffer[baseIndex++] = 1;// Read 1 Byte Data

		sendBuffer[baseIndex++] = 0x00;
		sendBuffer[baseIndex++] = 0x01; //
		sendBuffer[baseIndex++] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str()) | 0x01;

		for (int local = baseIndex; local<64; local++){
			sendBuffer[local] = 0;
		}

		break;

	case IOACCESS_TOTALPHASE:

		sendBuffer[baseIndex++] = 0;// write bytes
		sendBuffer[baseIndex++] = 1;// read bytes
		sendBuffer[baseIndex++] = (unsigned char)PMBUSHelper::HexToDecimal(this->m_e2pROMSlaveAddrTC->GetValue().c_str());// E2PROM Slave Address
		sendBuffer[baseIndex++] = idx;

		buffer_len = baseIndex;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	return buffer_len;
}

void FRUWriterDialog::OnBtnLOAD(wxCommandEvent& event){
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
	PSU_DEBUG_PRINT(MSG_ALERT, "BIN File Path : %s", path.c_str());

	// Update FRU File Path Static Text
	m_fruFileTC->SetValue(path);

	// Open Binary File
	wxFile *fruFile = new wxFile(path, wxFile::read);

	if (fruFile->IsOpened() != true){
		PSU_DEBUG_PRINT(MSG_ERROR, "Open BINARY File Failed");
		return;
	}

	// Load Conten Of FRU Buiary File
	PSU_DEBUG_PRINT(MSG_ALERT, "BINARY File Size is %d Bytes", fruFile->Length());

	// If File Size Large Than 256, Should be a error
	if (fruFile->Length() > MAX_FRU_FILE_LOAD_LENGTH){
		PSU_DEBUG_PRINT(MSG_ERROR, "BINARY FILE Size Large Than %d", MAX_FRU_FILE_LOAD_LENGTH);
		wxDELETE(fruFile);
		return;
	}

	readBytes = fruFile->Read((void*)this->m_fruReadBuffer, MAX_FRU_FILE_LOAD_LENGTH);
	this->m_fruFileLength = readBytes;
	PSU_DEBUG_PRINT(MSG_DEBUG, "Bytes Loaeded : %d", readBytes);

#ifdef DUMP_BINARY_CONTENT
	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------- BINARY FILE CONTENT -------------------");
	PrintFRUContent(this->m_fruReadBuffer, readBytes);
#endif

	// Seems like No Error On FRU Binary File Content
	m_btnWRITE->Enable(true);
	wxDELETE(fruFile);
}

#define WRITE_CMD_BYTES_TO_READ  6
void FRUWriterDialog::OnBtnWRITE(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	unsigned char sendBuffer[MAX_FRU_FILE_WRITE_LENGTH];
	unsigned char recvBuffer[MAX_RECV_BUFFER_LENGTH];
	int sendResult;
	int retry;
	bool sendRetryStillFailed = false;
	bool validateFailed = false;
	int recvLength = 0;
	int bytesToRead;

	memset(sendBuffer, 0, sizeof(sendBuffer) / sizeof(sendBuffer[0]));

	// Disable Read/Write Button
	this->m_btnREAD->Enable(false);
	this->m_btnWRITE->Enable(false);

	for (int offset = 0; offset <MAX_FRU_FILE_WRITE_LENGTH; offset++){
		// Prepare Send Buffer
		int sendDataLength = 0;
		sendDataLength = this->ProductE2PRomWriteBuffer(offset, sendBuffer, this->m_currentIO);

		// 
		wxString sendData("Send Data : ");
		//if (*this->m_outputLog == true){
			for (int idx = 0; idx < sendDataLength; idx++){
				sendData += wxString::Format(" %02x ", sendBuffer[idx]);
			}
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", sendData.c_str());
		//}

		// Decide Send Data Length
		switch (*this->m_currentIO){

		case IOACCESS_HID:
			sendDataLength = HID_SEND_DATA_SIZE;
			break;

		default:

			break;
		}

		retry = 0;

		// Send Read CMD
		do{
			sendResult = this->m_ioaccess[*this->m_currentIO].m_DeviceSendData(sendBuffer, sendDataLength);
			if (sendResult <= 0){
				PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Failed, sendResult=%d", sendResult);
				// Retry 
				retry++;
				if (retry >= MAX_E2PROM_WRITE_RETRY_TIMES){
					PSU_DEBUG_PRINT(MSG_ERROR, "Still Send Failed, Retry Times = %d", retry);
					sendRetryStillFailed = true;
					break;
				}
				else{
					PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
				}

			}
			else{
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			}

		} while (sendResult <= 0);

		if (sendRetryStillFailed == true){
			PSU_DEBUG_PRINT(MSG_ERROR, "Retry Send Still Failed, Exit Task");
			return;
		}

		wxMilliSleep(WRITE_CMD_INTERVAL_TIME);

		// Receive Response
		bytesToRead = (*this->m_currentIO == IOACCESS_SERIALPORT) ? WRITE_CMD_BYTES_TO_READ : WRITE_CMD_BYTES_TO_READ + 1;
		recvLength = this->m_ioaccess[*this->m_currentIO].m_DeviceReadData(recvBuffer, bytesToRead);

		//if (*this->m_outputLog == true){
			PSU_DEBUG_PRINT(MSG_ALERT, "RecvLength = %d", recvLength);
		//}

		wxString RecvData("Recv Data : ");
		//if (*this->m_outputLog == true){
			for (int idx = 0; idx < recvLength; idx++){
				RecvData += wxString::Format(" %02x ", recvBuffer[idx]);
			}
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", RecvData.c_str());
			PSU_DEBUG_PRINT(MSG_ALERT, "------------------------------------------------------------");
		//}

	}

	// Read Data From E2PRom For Validate 
	DumpE2PROM(recvBuffer, this->m_currentIO);

	// Print Content of E2PROM 
	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------- E2PROM CONTENT -------------------");
	PrintFRUContent(this->m_e2pRomContent, 256);

    // Compare Content of E2PROM with Original FRU Binary Data
	for (unsigned int idx = 0; idx < this->m_fruFileLength; idx++){
		if (this->m_fruReadBuffer[idx] != this->m_e2pRomContent[idx]){
			PSU_DEBUG_PRINT(MSG_ERROR, "Offset %d Data Not The Same As Original FRU BINARY FILE !", idx);
			PSU_DEBUG_PRINT(MSG_ERROR, "Original Data is %02x, Data On E2ROM is %02x", this->m_fruReadBuffer[idx], this->m_e2pRomContent[idx]);
			validateFailed = true;
		}
	}

	if (validateFailed == false){
		PSU_DEBUG_PRINT(MSG_ALERT, "Write And Validate E2PRom Success !");
	}

	// Enable Read/Write Button
	this->m_btnREAD->Enable(true);
	this->m_btnWRITE->Enable(true);
}

void FRUWriterDialog::OnBtnREAD(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	bool preWriteBTNEnable = this->m_btnWRITE->IsEnabled();

	unsigned char recvBuffer[MAX_RECV_BUFFER_LENGTH];

	this->m_btnREAD->Enable(false);
	this->m_btnWRITE->Enable(false);
	this->UpdateWindowUI();

	// Read Data From E2PRom For Validate 
	DumpE2PROM(recvBuffer, this->m_currentIO);

	// Print Content of E2PROM 
	PSU_DEBUG_PRINT(MSG_ALERT, "-------------------- E2PROM CONTENT -------------------");
	PrintFRUContent(this->m_e2pRomContent, 256);

	this->m_btnREAD->Enable(true);
	if (preWriteBTNEnable == true){
		this->m_btnWRITE->Enable(true);
	}
}

int FRUWriterDialog::DumpE2PROM(unsigned char* RecvBuffer, unsigned int* currentIO){

	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", __FUNCTIONW__);

	int sendResult;
	int retry;
	int readRetry = 0;
	bool sendRetryStillFailed = false;
	int recvLength = 0;
	int bytesToRead;
	unsigned offset = 0;

	unsigned char sendBuffer[MAX_FRU_FILE_WRITE_LENGTH];
	unsigned char recvBuffer[MAX_RECV_BUFFER_LENGTH];


	// Read Data From E2PRom
	while (offset <MAX_FRU_FILE_READ_LENGTH){//for (unsigned int offset = 0; offset < MAX_FRU_FILE_READ_LENGTH; offset++){

		// Prepare Read Operation Send Data Buffer
		int sendDataLength = 0;
		sendDataLength = ProductE2PRomReadBuffer(offset, sendBuffer, this->m_currentIO);
		//if (*this->m_outputLog == true){
			PSU_DEBUG_PRINT(MSG_ALERT, "SendBufferLen = %d", sendDataLength);
		//}


		wxString sendData("Send Data : ");
		//if (*this->m_outputLog == true){
			for (int idx = 0; idx < sendDataLength; idx++){
				sendData += wxString::Format(" %02x ", sendBuffer[idx]);
			}
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", sendData.c_str());
		//}

		// Decide Send Data Length
		switch (*this->m_currentIO){

		case IOACCESS_HID:
			sendDataLength = HID_SEND_DATA_SIZE;
			break;

		default:

			break;
		}

		retry = 0;

		// Send Read CMD
		do{
			sendResult = this->m_ioaccess[*this->m_currentIO].m_DeviceSendData(sendBuffer, sendDataLength);
			if (sendResult <= 0){
				PSU_DEBUG_PRINT(MSG_ALERT, "IO Send Failed, sendResult=%d", sendResult);
				// Retry 
				retry++;
				if (retry >= 3){
					PSU_DEBUG_PRINT(MSG_ERROR, "Still Send Failed, Retry Times = %d", retry);
					sendRetryStillFailed = true;
					break;
				}
				else{
					PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
				}

			}
			else{
				PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
			}

		} while (sendResult <= 0);

		if (sendRetryStillFailed == true){
			PSU_DEBUG_PRINT(MSG_ERROR, "Retry Send Still Failed, Exit Task");
			return -1;
		}

		wxMilliSleep(READ_CMD_INTERVAL_TIME);

		// Receive Response
		bytesToRead = 1 + BASE_RESPONSE_DATA_LENGTH;
		recvLength = this->m_ioaccess[*this->m_currentIO].m_DeviceReadData(recvBuffer, bytesToRead);

		//if (*this->m_outputLog == true){
			PSU_DEBUG_PRINT(MSG_ALERT, "RecvLength = %d", recvLength);
		//}

		wxString RecvData("Recv Data : ");
		//if (*this->m_outputLog == true){
			for (int idx = 0; idx < recvLength; idx++){
				RecvData += wxString::Format(" %02x ", recvBuffer[idx]);
			}
			PSU_DEBUG_PRINT(MSG_ALERT, "%s", RecvData.c_str());
		//}

		//if (m_intervalTime > 0){
			//wxMilliSleep(m_intervalTime);
		//}

		// Copy Data To E2PROM Content Buffer
		switch (*this->m_currentIO){

		case IOACCESS_SERIALPORT:

			break;

		case IOACCESS_HID: // Offset Of Content Data is 6
			if (recvBuffer[5] == 0x4e && recvBuffer[6]==0x47){
				readRetry++;
				PSU_DEBUG_PRINT(MSG_ALERT, "Receive Data From E2PRom NG, Retry %d !", readRetry);
				if (readRetry < MAX_E2PROM_READ_RETRY_TIMES){
					continue;
				}
				else{
					PSU_DEBUG_PRINT(MSG_ERROR, "Receive Data From E2PRom Retry Still Failed !");
					offset++;
					readRetry = 0;
					continue;
				}
			}

			this->m_e2pRomContent[offset] = recvBuffer[6];
			offset++;
			readRetry = 0;
			break;

		case IOACCESS_TOTALPHASE:

			break;
		
		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs !");
			break;

		}

	}

	return 0;
}

void FRUWriterDialog::PrintFRUContent(unsigned char* contentBuffer, unsigned int dumpSize){
	PSU_DEBUG_PRINT(MSG_ALERT, "------------------------------------------------------------");
	wxString data("");
	unsigned int addr = 0x00;

	for (unsigned int idx = 0; idx < dumpSize; idx++){

		if (idx != 0 && idx % 0x10 == 0){
			addr = (idx - 0x10);
			PSU_DEBUG_PRINT(MSG_ALERT, "[%08x]%s", addr, data.c_str());
			data.Clear();
		}

		data += wxString::Format("%02x", contentBuffer[idx]);
		data += wxString::Format(" ");

		// Last
		if (idx == (dumpSize - 1)){
			PSU_DEBUG_PRINT(MSG_ALERT, "[%08x]%s", addr + 0x10, data.c_str());
			data.Clear();
			break;
		}
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "------------------------------------------------------------");
}

void FRUWriterDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	this->EndModal(wxID_CANCEL);

}

void FRUWriterDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
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

void FRUWriterDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
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

wxBEGIN_EVENT_TABLE(FRUWriterDialog, wxDialog)
EVT_BUTTON(CID_BTN_LOAD, FRUWriterDialog::OnBtnLOAD)
EVT_BUTTON(CID_BTN_READ, FRUWriterDialog::OnBtnREAD)
EVT_BUTTON(CID_BTN_WRITE, FRUWriterDialog::OnBtnWRITE)
EVT_CLOSE(FRUWriterDialog::OnDialogClose)
wxEND_EVENT_TABLE()