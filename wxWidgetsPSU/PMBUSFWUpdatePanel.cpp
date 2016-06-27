/**
 * @file PMBUSFWUpdatePanel.cpp
 */

#include "PMBUSFWUpdatePanel.h"

PMBUSFWUpdatePanel::PMBUSFWUpdatePanel(wxNotebook* parent, wxString hexFilePath, TIHexFileParser tiHexFileStat, IOACCESS* ioaccess, unsigned int* currentIO, bool* isMonitorRunning) : wxPanel(parent) {

	this->m_parent = parent;

	this->m_hexFilePath = hexFilePath;
	
	this->m_tiHexFileStat = tiHexFileStat;

	this->m_ioaccess = ioaccess;

	this->m_currentIO = currentIO;

	this->m_isMonitorRunning = isMonitorRunning;

	tiHexFileStat.begin();
    this->m_startAddress = tiHexFileStat.currentAddress();

	tiHexFileStat.end();
	this->m_endAddress = tiHexFileStat.currentAddress();

	this->m_addressRange = (this->m_endAddress - this->m_startAddress) + 1UL;

	this->m_dataBytes = tiHexFileStat.size() * 2;

	this->m_dvlRowCount = (this->m_addressRange % 16 == 0) ? this->m_addressRange / 16 : (this->m_addressRange / 16) + 1;

	PSU_DEBUG_PRINT(MSG_ALERT, "startAddress = 0x%08x", this->m_startAddress);
	PSU_DEBUG_PRINT(MSG_ALERT, "EndAddress   = 0x%08x", this->m_endAddress);
	PSU_DEBUG_PRINT(MSG_ALERT, "Address Range= %d", this->m_addressRange);
	PSU_DEBUG_PRINT(MSG_ALERT, "Data Bytes   = %d", this->m_dataBytes);

	this->m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	this->m_statisticSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("MEMORY MAP"));
	this->m_buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	this->m_fileStatFGS = new wxFlexGridSizer(2, 8, 5, 5);

	// File Name
	wxString fileName = wxT("File : ");
	fileName += this->m_hexFilePath;
	this->m_fileNameST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, fileName);
	wxFont font = this->m_fileNameST->GetFont();
	font.SetPointSize(10);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	this->m_fileNameST->SetFont(font);


	// Start Address
	this->m_startAddressST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("START Address : "));
	this->m_startAddressST->SetFont(font);
	wxString StartAddress = wxString::Format("0x%08x", this->m_startAddress);
	this->m_startAddressTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, StartAddress);

	this->m_startAddressTC->SetEditable(false);

	this->m_endAddressST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("End Address : "));
	this->m_endAddressST->SetFont(font);
	wxString EndAddress = wxString::Format("0x%08x", this->m_endAddress);
	this->m_endAddressTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, EndAddress);

	this->m_endAddressTC->SetEditable(false);

	this->m_addressRangeST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("Address Range : "));
	this->m_addressRangeST->SetFont(font);
	wxString AddressRange = wxString::Format("%d", this->m_addressRange);
	this->m_addressRangeTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, AddressRange);

	this->m_addressRangeTC->SetEditable(false);

	this->m_dataBytesST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, wxT("Data Bytes : "));
	this->m_dataBytesST->SetFont(font);
	wxString DataBytes = wxString::Format("%d", this->m_dataBytes);
	this->m_dataBytesTC = new wxTextCtrl(this->m_statisticSBS->GetStaticBox(), wxID_ANY, DataBytes);

	this->m_dataBytesTC->SetEditable(false);

	this->m_writeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_WRITE_BUTTON, wxT("WRITE"));
	this->m_writeButton->SetBitmap(wxBITMAP_PNG(MEMORY_32));

	this->m_closeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_CLOSE_BUTTON, wxT("CLOSE"));
	this->m_closeButton->SetBitmap(wxBITMAP_PNG(CLOSE_32));

	this->m_buttonSizer->Add(this->m_writeButton);
	this->m_buttonSizer->Add(this->m_closeButton);

	this->m_statisticSBS->Add(this->m_fileNameST, wxSizerFlags(0).Align(wxALIGN_CENTER).Border());

	this->m_fileStatFGS->Add(this->m_startAddressST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_startAddressTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_endAddressST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_endAddressTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_addressRangeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_addressRangeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_dataBytesST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));
	this->m_fileStatFGS->Add(this->m_dataBytesTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL));

	this->m_statisticSBS->Add(this->m_fileStatFGS, wxSizerFlags(0).Align(wxALIGN_CENTER).Border());
	
	this->m_statisticSBS->Add(this->m_buttonSizer, wxSizerFlags(0).Align(wxALIGN_CENTER).Border());
	this->m_topLevelSizer->Add(this->m_statisticSBS, wxSizerFlags(0).Expand());

	this->SetupHexMMAPDVL();

	this->m_topLevelSizer->Add(this->m_tiHexMMAPDVC, wxSizerFlags(1).Expand());


	this->SetSizerAndFit(this->m_topLevelSizer);
}

PMBUSFWUpdatePanel::~PMBUSFWUpdatePanel(){

}

void PMBUSFWUpdatePanel::SetupHexMMAPDVL(void){

	this->m_tiHexMMAPDVC = new wxDataViewCtrl(this, ID_HEXMMAP_DVC, wxDefaultPosition, wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	this->m_tiHexMMAPDVC->SetFont(font);

	this->m_tiHexMMAPModel = new TIHexMMAPModel(this->m_dvlRowCount, &this->m_tiHexFileStat);
	this->m_tiHexMMAPDVC->AssociateModel(this->m_tiHexMMAPModel.get());

	this->m_tiHexMMAPDVC->AppendTextColumn("ADDRESS", TIHexMMAPModel::Col_ADDRESS, wxDATAVIEW_CELL_ACTIVATABLE, 200, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("00H", TIHexMMAPModel::Col_00H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("01H", TIHexMMAPModel::Col_01H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("02H", TIHexMMAPModel::Col_02H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("03H", TIHexMMAPModel::Col_03H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("04H", TIHexMMAPModel::Col_04H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("05H", TIHexMMAPModel::Col_05H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("06H", TIHexMMAPModel::Col_06H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("07H", TIHexMMAPModel::Col_07H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("08H", TIHexMMAPModel::Col_08H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("09H", TIHexMMAPModel::Col_09H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0AH", TIHexMMAPModel::Col_0AH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0BH", TIHexMMAPModel::Col_0BH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0CH", TIHexMMAPModel::Col_0CH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0DH", TIHexMMAPModel::Col_0DH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0EH", TIHexMMAPModel::Col_0EH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0FH", TIHexMMAPModel::Col_0FH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("", TIHexMMAPModel::Col_ASCII, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
}

#define CMD_F0H_BYTES_TO_READ  6/**< Bytes To Read */
void PMBUSFWUpdatePanel::OnWriteButton(wxCommandEvent& event){
	
	// Check if Monitor is Running
	if (*this->m_isMonitorRunning == true){
		wxMessageBox(wxT("Monitor is running, Please stop monitor then try again !"),
			wxT("Monitor is running !"),  // caption
			wxOK | wxICON_INFORMATION);

		return;
	}

	// Create Progress Dialog
	wxProgressDialog dialog(wxT("ISP is in Progress"),
		// "Reserve" enough space for the multiline
		// messages below, we'll change it anyhow
		// immediately in the loop below
		wxString(' ', 100) + "\n\n\n\n",
		100,    // range
		this,   // parent
		wxPD_CAN_ABORT |
		//wxPD_CAN_SKIP |
		wxPD_APP_MODAL |
		//wxPD_AUTO_HIDE | // -- try this as well
		wxPD_ELAPSED_TIME |
		//wxPD_ESTIMATED_TIME |
		//wxPD_REMAINING_TIME |
		wxPD_SMOOTH // - makes indeterminate mode bar on WinXP very small
		);

	// Prepare Send Buffer
	unsigned char SendBuffer[8] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xF0, 0x60, 0x00, 0x0D, 0x0A
	};

	unsigned char pec = 0;
	pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 3);

	SendBuffer[5] = pec;

	PMBUSSendCOMMAND_t CMDF0H;

	CMDF0H.m_sendDataLength = sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	CMDF0H.m_bytesToRead = CMD_F0H_BYTES_TO_READ;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		CMDF0H.m_sendData[idx] = SendBuffer[idx];
	}

	unsigned char ispStatus = ISP_Status_InProgress;
	double percentage = 0;
	wxString information("");

	new(TP_SendISPStartCMDTask) SendISPStartCMDTask(m_ioaccess, m_currentIO, CMDF0H, &this->m_tiHexFileStat, &ispStatus);


	int not_cancel;
	bool inProcess = true;
	unsigned char header_index = 0;

	// Wait for ISP Sequence End
	while (inProcess){//Task::GetCount() > 0){

		if (ispStatus == ISP_Status_InProgress){

			// Header
			switch (header_index){

			case 0:
				information = wxString::Format("PC > - - - - - - - DSP");
				break;

			case 1:
				information = wxString::Format("PC - > - - - - - - DSP");
				break;

			case 2:
				information = wxString::Format("PC - - > - - - - - DSP");
				break;

			case 3:
				information = wxString::Format("PC - - - > - - - - DSP");
				break;

			case 4:
				information = wxString::Format("PC - - - - > - - - DSP");
				break;

			case 5:
				information = wxString::Format("PC - - - - - > - - DSP");
				break;

			case 6:
				information = wxString::Format("PC - - - - - - > - DSP");
				break;

			case 7:
				information = wxString::Format("PC - - - - - - - > DSP");
				break;

			default:
				PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs !")
					break;
			}
			header_index++;
			header_index %= 8;

			information += wxT("\n");

		}
		else if (ispStatus == ISP_Status_ALLDone){

			information = wxT("ISP Progress Complete");

			information += wxT("\n");
		}

		// Show Current Address
		unsigned long currentAddress = this->m_tiHexFileStat.currentAddress();
		information += wxString::Format("Current Process Address : %08x", currentAddress);
		information += wxT("\n");

		// Show Processed Bytes
		unsigned long processed_bytes = ((currentAddress - this->m_startAddress) + 1UL) * 2;
		information += wxString::Format("Current Processed Bytes : (%d/%d)", processed_bytes, this->m_dataBytes);

		// Compute Percentage (Percentage = processed bytes / total bytes)
		percentage = ((double)processed_bytes / this->m_dataBytes);
		percentage *= 100;
		if (percentage > 100) percentage = 100;
		PSU_DEBUG_PRINT(MSG_DETAIL, "Percentage = %f, Processed bytes = %d, data bytes = %d, Current Address = %08x", percentage, processed_bytes, this->m_dataBytes, currentAddress);


		// Update Dialogs
		not_cancel = dialog.Update((int)percentage, information);

		if (not_cancel == false){
			ispStatus = ISP_Status_UserRequestCancel;
		}


		// If Error Occurs
		if (ispStatus == ISP_Status_ErrorOccurs){
			wxMessageBox(wxT("Error occurs in ISP progress !"),
			             wxT("Error !"),  // caption
						 wxOK | wxICON_ERROR);

			break;
		}

		// Check Still have Task
		if (Task::GetCount()== 0){
			inProcess = false;
		}

		wxMilliSleep(200);
	}

}

void PMBUSFWUpdatePanel::OnCloseButton(wxCommandEvent& event){

	unsigned int selected_index;

	selected_index = this->m_parent->GetSelection();

	this->m_parent->SetSelection(0);

	this->m_parent->RemovePage(selected_index);
}

wxBEGIN_EVENT_TABLE(PMBUSFWUpdatePanel, wxPanel)
EVT_BUTTON(CID_WRITE_BUTTON, PMBUSFWUpdatePanel::OnWriteButton)
EVT_BUTTON(CID_CLOSE_BUTTON, PMBUSFWUpdatePanel::OnCloseButton)
wxEND_EVENT_TABLE()