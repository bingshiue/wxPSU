/**
 * @file ComportDialog.cpp
 */

#include "ComportDialog.h"

ComportDialog::ComportDialog(wxWindow *parent, IOACCESS* ioaccess, AppSettings_t* appSettings, PMBUSStatusBar* pmbusStatusBar) : wxDialog(parent, wxID_ANY, wxString(wxT("Com Port"))) {

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(COMPLUG_16));

	this->SetIcon(icon);
	this->SetBackgroundColour(wxColour(255, 255, 255));

	m_parent = parent;
	m_ioaccess = ioaccess;
	m_appSettings = appSettings;
	m_pmbusStatusBar = pmbusStatusBar;

	m_TopLevelSizer = new wxBoxSizer(wxHORIZONTAL);

	m_SettingSBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT(""));
	m_SettingFGS = new wxFlexGridSizer(5,2,5,5);

	m_RightVerticalSizer = new wxBoxSizer(wxVERTICAL);
	m_ButtonSizer = new wxBoxSizer(wxVERTICAL);
	m_CheckBoxSizer = new wxBoxSizer(wxVERTICAL);

	m_ComportNumberST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Comport Number"));
	m_BuadRateST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Buad Rate"));
	m_ParityCheckST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Parity Check"));
	m_DataBitsST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Data Bits"));
	m_StopBitsST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Stop Bits"));

	// 
	this->CloseIODevice();
	wxMilliSleep(200);

	// Comport Number
	m_ComportNumberCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100,-1));

	int comport_cnt = m_ioaccess->m_EnumerateAvailableDevice(this->enumArray, sizeof(this->enumArray) / sizeof(this->enumArray[0]));
	PSU_DEBUG_PRINT(MSG_DEBUG, "comport_cnt=%d", comport_cnt);

	if (comport_cnt == 0){
		wxMessageBox(wxT("Can not find any Comport Interface !"),
			wxT("Error !"),  // caption
			wxOK | wxICON_ERROR);

		// Can't find any comport interface, use default setting
		unsigned long comportNumberArray_fixed[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
		for (unsigned int idx = 0; idx < sizeof(comportNumberArray_fixed) / sizeof(comportNumberArray_fixed[0]); idx++){
			m_ComportNumberCB->Append(wxString::Format("%d", comportNumberArray_fixed[idx]));
		}

		unsigned int select_fixed = 0;
		for (unsigned int idx = 0; idx < sizeof(comportNumberArray_fixed) / sizeof(comportNumberArray_fixed[0]); idx++){
			if (this->m_appSettings->m_comportSetting.m_comportNumber == comportNumberArray_fixed[idx]){
				select_fixed = idx;
				break;
			}
		}

		m_ComportNumberCB->SetSelection(select_fixed);
	}
	else{
		unsigned long* comportNumberArray = new unsigned long[comport_cnt];

		// Get Comport Number
		for (unsigned int idx = 0, cnt_idx =0; idx < sizeof(this->enumArray) / sizeof(this->enumArray[0]); idx++){
			if (this->enumArray[idx] == TRUE){
				comportNumberArray[cnt_idx++] = (idx + 1);
			}
		}

		// Append Comport Number to Combo Box
		for (unsigned int idx = 0; idx < comport_cnt; idx++){
			m_ComportNumberCB->Append(wxString::Format("%d", comportNumberArray[idx]));
		}

		// Default Select Index
		unsigned int select_dynamic = 0;
		for (unsigned int idx = 0; idx < comport_cnt; idx++){
			if (this->m_appSettings->m_comportSetting.m_comportNumber == comportNumberArray[idx]){
				select_dynamic = idx;
				break;
			}
		}

		m_ComportNumberCB->SetSelection(select_dynamic);
		//

		delete[] comportNumberArray;
	}



	unsigned int select;

	// Buad Rate
	m_BuadRateCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));

	typedef struct {
		         char *m_label;
		unsigned long  m_value;
	} BuadRateArray;

	BuadRateArray buadRatedArray[13] = {
		{ "110" ,   110    },
		{ "300",    300    },
		{ "600",    600    },
		{ "1200",   1200   },
		{ "2400",   2400   },
		{ "4800",   4800   },
		{ "9600",   9600   },
		{ "11400",  11400  },
		{ "19200",  19200  },
		{ "38400",  38400  },
		{ "56000",  56000  },
		{ "57600",  57600  },
		{ "115200", 115200 }
	};

	for (unsigned int idx = 0; idx < sizeof(buadRatedArray) / sizeof(buadRatedArray[0]); idx++){
		m_BuadRateCB->Append(buadRatedArray[idx].m_label);
	}

	for (unsigned int idx = 0; idx < sizeof(buadRatedArray) / sizeof(buadRatedArray[0]); idx++){
		if (this->m_appSettings->m_comportSetting.m_buadRate == buadRatedArray[idx].m_value){
			select = idx;
			break;
		}
	}

	m_BuadRateCB->SetSelection(select);

	// Parity Check
	m_ParityCheckCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));

	typedef struct {
		         char *m_label;
		unsigned long  m_value;
	} ParityCheckArray;

	ParityCheckArray parityCheckArray[5] = {
		{ "N", 0 },
		{ "O", 1 },
		{ "E", 2 },
		{ "M", 3 },
		{ "S", 4 }
	};

	for (unsigned int idx = 0; idx < sizeof(parityCheckArray) / sizeof(parityCheckArray[0]); idx++){
		m_ParityCheckCB->Append(parityCheckArray[idx].m_label);
	}

	for (unsigned int idx = 0; idx < sizeof(parityCheckArray) / sizeof(parityCheckArray[0]); idx++){
		if (this->m_appSettings->m_comportSetting.m_parityCheck == parityCheckArray[idx].m_value){
			select = idx;
			break;
		}
	}

	m_ParityCheckCB->SetSelection(select);

	// Data Bits
	m_DataBitsCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));

	unsigned long dataBitsArray[4] = { 5, 6, 7, 8 };

	for (unsigned int idx = 0; idx < sizeof(dataBitsArray) / sizeof(dataBitsArray[0]); idx++){
		m_DataBitsCB->Append(wxString::Format("%d", dataBitsArray[idx]));
	}

	for (unsigned int idx = 0; idx < sizeof(dataBitsArray) / sizeof(dataBitsArray[0]); idx++){
		if (this->m_appSettings->m_comportSetting.m_byteSize == dataBitsArray[idx]){
			select = idx;
			break;
		}
	}

	m_DataBitsCB->SetSelection(select);

	// Stop Bits 
	m_StopBitsCB = new wxComboBox(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));

	typedef struct {
		         char *m_label;
		unsigned long  m_value;
	} StopBitsArray;

	StopBitsArray stopBitsArray[3] = {
		{ "1",   0 },
		{ "1.5", 1 },
		{ "2",   2 },
	};

	for (unsigned int idx = 0; idx < sizeof(stopBitsArray) / sizeof(stopBitsArray[0]); idx++){
		m_StopBitsCB->Append(stopBitsArray[idx].m_label);
	}

	for (unsigned int idx = 0; idx < sizeof(stopBitsArray) / sizeof(stopBitsArray[0]); idx++){
		if (this->m_appSettings->m_comportSetting.m_stopBits== stopBitsArray[idx].m_value){
			select = idx;
			break;
		}
	}

	m_StopBitsCB->SetSelection(select);

	m_SettingFGS->Add(m_ComportNumberST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_ComportNumberCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_BuadRateST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_BuadRateCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_ParityCheckST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_ParityCheckCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_DataBitsST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_DataBitsCB, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_StopBitsST, wxSizerFlags().Align(wxCENTER).Border());
	m_SettingFGS->Add(m_StopBitsCB, wxSizerFlags().Align(wxCENTER).Border());

	m_SettingSBS->Add(m_SettingFGS);

	m_OKButton = new wxButton(this, CID_OK_BUTTOUN, wxT("OK"));
	m_CancelButton = new wxButton(this, wxID_CLOSE, wxT("Cancel"));

	m_ButtonSizer->Add(m_OKButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_CancelButton, wxSizerFlags().Align(wxCENTER).Border());

	m_paddiingST = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, 50));
	m_TurnOnRTS = new wxCheckBox(this, wxID_ANY, wxT("Turn On RTS"));
	m_TurnOnDTR = new wxCheckBox(this, wxID_ANY, wxT("Turn On DTR"));

	
	m_CheckBoxSizer->Add(m_paddiingST, wxSizerFlags().Border().Align(wxUP));
	m_CheckBoxSizer->Add(m_TurnOnRTS, wxSizerFlags().Border().Align(wxDOWN));
	m_CheckBoxSizer->Add(m_TurnOnDTR, wxSizerFlags().Border().Align(wxDOWN));

	m_RightVerticalSizer->Add(m_ButtonSizer, wxSizerFlags().Align(wxCENTER).Border());
	m_RightVerticalSizer->Add(m_CheckBoxSizer, wxSizerFlags().Align(wxDOWN).Border());

	m_TopLevelSizer->Add(m_SettingSBS, wxSizerFlags().Align(wxCENTER).Expand());
	m_TopLevelSizer->Add(m_RightVerticalSizer, wxSizerFlags(0).Align(wxCENTER).Expand());

	// Setup Sizer
	SetSizerAndFit(m_TopLevelSizer);

	// Setup Escapse ID
	SetEscapeId(wxID_CLOSE);
}

ComportDialog::~ComportDialog(){

}

void ComportDialog::UpdateStatusBarIOSettingFiled(wxString io_string){
	this->m_pmbusStatusBar->SetStatusText(io_string, PMBUSStatusBar::Field_IO_Setting);
}

int ComportDialog::SetIODeviceOption(void){
	this->m_portSetting.m_comportNumber = this->m_appSettings->m_comportSetting.m_comportNumber;
	this->m_portSetting.m_buadRate = this->m_appSettings->m_comportSetting.m_buadRate;
	this->m_portSetting.m_byteSize = this->m_appSettings->m_comportSetting.m_byteSize;
	this->m_portSetting.m_parityCheck = this->m_appSettings->m_comportSetting.m_parityCheck;
	this->m_portSetting.m_stopBits = this->m_appSettings->m_comportSetting.m_stopBits;

	return EXIT_SUCCESS;
}

int ComportDialog::OpenIODevice(void){
	int ret = EXIT_FAILURE;

	// Open Device
	PSU_DEBUG_PRINT(MSG_DEBUG, "this->m_CurrentUseIOInterface].m_GetDeviceStatus() = %d", this->m_ioaccess[0].m_GetDeviceStatus());

	if (this->m_ioaccess[0].m_GetDeviceStatus() == IODEVICE_CLOSE) {

		this->SetIODeviceOption();
		ret = this->m_ioaccess[0].m_OpenDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT, &this->m_portSetting);

		if (ret != EXIT_SUCCESS){
			PSU_DEBUG_PRINT(MSG_ERROR, "Open IO Device Failed !");
		}
		else{
			//this->m_ioDeviceOpen = true;
			wxString openDeviceName(this->m_ioaccess[0].m_GetOpenDeviceName());
			//openDeviceName += wxT("-9600-N81");

			// Append BuadRate
			switch (this->m_appSettings->m_comportSetting.m_buadRate){

			case CBR_110:
				openDeviceName += wxString::Format("-%d-", 110);
				break;

			case CBR_300:
				openDeviceName += wxString::Format("-%d-", 300);
				break;

			case CBR_600:
				openDeviceName += wxString::Format("-%d-", 600);
				break;

			case CBR_1200:
				openDeviceName += wxString::Format("-%d-", 1200);
				break;

			case CBR_2400:
				openDeviceName += wxString::Format("-%d-", 2400);
				break;

			case CBR_4800:
				openDeviceName += wxString::Format("-%d-", 4800);
				break;

			case CBR_9600:
				openDeviceName += wxString::Format("-%d-", 9600);
				break;

			case CBR_14400:
				openDeviceName += wxString::Format("-%d-", 14400);
				break;

			case CBR_19200:
				openDeviceName += wxString::Format("-%d-", 19200);
				break;

			case CBR_38400:
				openDeviceName += wxString::Format("-%d-", 38400);
				break;

			case CBR_56000:
				openDeviceName += wxString::Format("-%d-", 56000);
				break;

			case CBR_57600:
				openDeviceName += wxString::Format("-%d-", 57600);
				break;

			case CBR_115200:
				openDeviceName += wxString::Format("-%d-", 115200);
				break;

			default:
				PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
				break;
			}

			// Append Parity Check
			switch (this->m_appSettings->m_comportSetting.m_parityCheck){

			case NOPARITY:
				openDeviceName += wxString::Format("%s", "N");
				break;

			case ODDPARITY:
				openDeviceName += wxString::Format("%s", "O");
				break;

			case EVENPARITY:
				openDeviceName += wxString::Format("%s", "E");
				break;

			case MARKPARITY:
				openDeviceName += wxString::Format("%s", "M");
				break;
			case SPACEPARITY:
				openDeviceName += wxString::Format("%s", "S");
				break;

			default:
				PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
				break;
			}

			// Append Byte Bits
			openDeviceName += wxString::Format("%d", this->m_appSettings->m_comportSetting.m_byteSize);

			// Append Stop Bits
			switch (this->m_appSettings->m_comportSetting.m_stopBits){

			case ONESTOPBIT:
				openDeviceName += wxString::Format("%d", 1);
				break;

			case ONE5STOPBITS:
				openDeviceName += wxString::Format("%f", 1.5);
				break;

			case TWOSTOPBITS:
				openDeviceName += wxString::Format("%d", 2);
				break;

			default:
				PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
				break;
			}

			this->UpdateStatusBarIOSettingFiled(openDeviceName);
		}
	}

	return ret;
}

int ComportDialog::CloseIODevice(void){
	int ret = EXIT_SUCCESS;

	if (this->m_ioaccess[0].m_GetDeviceStatus() == IODEVICE_OPEN){
		ret = this->m_ioaccess[0].m_CloseDevice();
	
		if (ret != EXIT_SUCCESS){
			PSU_DEBUG_PRINT(MSG_ERROR, "Close IO Device Failed !");
		}
		else{
			this->UpdateStatusBarIOSettingFiled(wxString("Disconnect"));
		}
	}

	return ret;
}

void ComportDialog::OnOKButton(wxCommandEvent& event){
	int select = 0;
	
	// Comport Number
	this->m_appSettings->m_comportSetting.m_comportNumber = wxAtoi(m_ComportNumberCB->GetValue());

	// BuadRate
	select = m_BuadRateCB->GetSelection();

	switch (select){

	case 0:// "110"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_110;
		break;
	case 1:// "300"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_300;
		break;
	case 2:// "600"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_600;
		break;
	case 3:// "1200"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_1200;
		break;
	case 4:// "2400"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_2400;
		break;
	case 5:// "4800"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_4800;
		break;
	case 6:// "9600"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_9600;
		break;
	case 7:// "11400"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_14400;
		break;
	case 8:// "19200"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_19200;
		break;
	case 9:// "38400"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_38400;
		break;
	case 10://"56000"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_56000;
		break;
	case 11://"57600"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_57600;
		break;
	case 12://"115200"
		this->m_appSettings->m_comportSetting.m_buadRate = CBR_115200;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	// Byte Size
	this->m_appSettings->m_comportSetting.m_byteSize = wxAtoi(m_DataBitsCB->GetValue());

	// Stop Bits
	select = m_StopBitsCB->GetSelection();

	switch (select){
	case 0 :// "1"
		this->m_appSettings->m_comportSetting.m_stopBits = ONESTOPBIT;
		break;

	case 1: // "1.5"
		this->m_appSettings->m_comportSetting.m_stopBits = ONE5STOPBITS;

		break;

	case 2: // "2"
		this->m_appSettings->m_comportSetting.m_stopBits = TWOSTOPBITS;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}

	// Parity Size
	select = m_ParityCheckCB->GetSelection();

	switch (select){

	case 0: // "N"
		this->m_appSettings->m_comportSetting.m_parityCheck = NOPARITY;
		break;

	case 1: // "O"
		this->m_appSettings->m_comportSetting.m_parityCheck = ODDPARITY;
		break;

	case 2: // "E"
		this->m_appSettings->m_comportSetting.m_parityCheck = EVENPARITY;
		break;

	case 3: // "M"
		this->m_appSettings->m_comportSetting.m_parityCheck = MARKPARITY;
		break;

	case 4: //"S"
		this->m_appSettings->m_comportSetting.m_parityCheck = SPACEPARITY;
		break;

	default :
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error !");
		break;
	}


	this->CloseIODevice();
	wxMilliSleep(200);
	this->OpenIODevice();

	this->EndModal(0);
}

wxBEGIN_EVENT_TABLE(ComportDialog, wxDialog)
EVT_BUTTON(CID_OK_BUTTOUN, ComportDialog::OnOKButton)
wxEND_EVENT_TABLE()