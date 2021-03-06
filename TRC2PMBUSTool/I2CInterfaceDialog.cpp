/**
 * @file I2CIntefaceDialog.cpp
 */

#include "I2CInterfaceDialog.h"

I2CInterfaceDialog::I2CInterfaceDialog(wxWindow *parent, IOACCESS* ioaccess, unsigned int* currentUseIO, AppSettings_t* appSettings, PMBUSStatusBar* pmbusStatusBar, bool defaultAdaptor, int defaultAdaptorSelect) : wxDialog(parent, wxID_ANY, wxString(wxT("I2C Interface"))) {
	bool defAdaptor = defaultAdaptor;
	int defAdaptorSelect = defaultAdaptorSelect;

	wxIcon icon;
	icon.CopyFromBitmap(LOAD_PNG_RESOURCE(hwinfo_16));

	this->SetIcon(icon);
	this->SetBackgroundColour(wxColour(255, 255, 255));

	m_ioaccess = ioaccess;
	m_currentUseIO = currentUseIO;
	m_appSettings = appSettings;
	m_pmbusStatusBar = pmbusStatusBar;

	m_TopLevelSizer = new wxBoxSizer(wxHORIZONTAL);
	m_LeftSizer = new wxBoxSizer(wxVERTICAL);

	m_i2cIFModuleSBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT("I2C Interface Module"));

	m_generalFlexSizer = new wxFlexGridSizer(6,2,5,5);
	m_ButtonSizer = new wxBoxSizer(wxVERTICAL);

	// I2C Adaptor Module Board

	m_moduleNameST = new wxStaticText(m_i2cIFModuleSBS->GetStaticBox(), wxID_ANY, wxT("Module Name"));
	m_moduleNameCB = new wxComboBox(m_i2cIFModuleSBS->GetStaticBox(), CID_MODULE_BOARD_COMBO, wxT(""));
	m_moduleNameCB->Append("PICKIT Serial");
	m_moduleNameCB->Append("R90000-95611");
	m_moduleNameCB->Append("R90000-9271(USB)");
	m_moduleNameCB->Append("TOTAL PHASE");
	m_moduleNameCB->Append("TRC2 I2C Adapter");


	unsigned long adaptorArray[5] = {
		I2C_AdaptorModuleBoard_PICKIT_SERIAL,
		I2C_AdaptorModuleBoard_R90000_95611,
		I2C_AdaptorModuleBoard_R90000_9271_USB,
		I2C_AdaptorModuleBoard_TOTALPHASE,
		I2C_AdaptorModuleBoard_TRC2I2CAdapter
	};
	unsigned int module_select = 0;
	for (unsigned int idx = 0; idx < sizeof(adaptorArray) / sizeof(adaptorArray[0]); idx++){
		if (this->m_appSettings->m_I2CAdaptorModuleBoard == adaptorArray[idx]){
			module_select = idx;
			break;
		}
	}
	m_moduleNameCB->SetSelection(module_select);
	m_previousModuleBoardSelectIndex = module_select;

	if (defaultAdaptor == true){
		if (defaultAdaptorSelect != module_select){
			m_moduleNameCB->SetSelection(defaultAdaptorSelect);
		}
	}

	m_i2cIFModuleSBS->Add(m_moduleNameST, wxSizerFlags().Align(wxCENTER).Border());
	m_i2cIFModuleSBS->Add(m_moduleNameCB, wxSizerFlags().Align(wxCENTER).Border());

	m_generalNB = new wxNotebook(this, wxID_ANY);
	m_generalPanel = new wxPanel(m_generalNB, wxID_ANY);

	m_RegisterAddrLengthST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Register Addr Length"));
	m_MaxReadBytesST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Max Read Bytes"));
	m_MaxWriteBytesST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Max Write Bytes"));
	m_TrasmitTimeoutST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Transmit Timeout (ms)"));
	m_WriteCycleTimeST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Write Cycle Time (ms)"));
	m_PollingCycleTimeST = new wxStaticText(m_generalPanel, wxID_ANY, wxT("Polling Cycle Time (ms)"));

	m_RegisterAddrLengthCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_RegisterAddrLengthCB->Append("1");
	m_RegisterAddrLengthCB->Append("2");
	m_RegisterAddrLengthCB->Append("3");
	m_RegisterAddrLengthCB->Append("4");
	m_RegisterAddrLengthCB->SetSelection(0);

	m_MaxReadBytesCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_MaxReadBytesCB->Append("1");
	m_MaxReadBytesCB->Append("4");
	m_MaxReadBytesCB->Append("8");
	m_MaxReadBytesCB->Append("16");
	m_MaxReadBytesCB->Append("32");
	m_MaxReadBytesCB->Append("64");
	m_MaxReadBytesCB->SetSelection(4);

	m_MaxWriteBytesCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_MaxWriteBytesCB->Append("1");
	m_MaxWriteBytesCB->Append("4");
	m_MaxWriteBytesCB->Append("8");
	m_MaxWriteBytesCB->Append("16");
	m_MaxWriteBytesCB->Append("32");
	m_MaxWriteBytesCB->Append("64");
	m_MaxWriteBytesCB->SetSelection(4);

	m_TrasmitTimeoutCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_TrasmitTimeoutCB->Append("100");
	m_TrasmitTimeoutCB->Append("200");
	m_TrasmitTimeoutCB->Append("500");
	m_TrasmitTimeoutCB->Append("1000");
	m_TrasmitTimeoutCB->Append("1500");
	m_TrasmitTimeoutCB->Append("2000");
	m_TrasmitTimeoutCB->SetSelection(1);

	m_WriteCycleTimeCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_WriteCycleTimeCB->Append("0");
	m_WriteCycleTimeCB->Append("5");
	m_WriteCycleTimeCB->Append("10");
	m_WriteCycleTimeCB->Append("15");
	m_WriteCycleTimeCB->Append("20");
	m_WriteCycleTimeCB->Append("30");
	m_WriteCycleTimeCB->SetSelection(2);

	m_PollingCycleTimeCB = new wxComboBox(m_generalPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(100, -1));
	m_PollingCycleTimeCB->Append("0");
	m_PollingCycleTimeCB->Append("5");
	m_PollingCycleTimeCB->Append("10");
	m_PollingCycleTimeCB->Append("20");
	m_PollingCycleTimeCB->Append("50");
	m_PollingCycleTimeCB->Append("100");
	m_PollingCycleTimeCB->Append("200");
	m_PollingCycleTimeCB->Append("300");
	m_PollingCycleTimeCB->Append("500");
	m_PollingCycleTimeCB->Append("1000");
	m_PollingCycleTimeCB->Append("1500");
	m_PollingCycleTimeCB->Append("2000");
	m_PollingCycleTimeCB->SetSelection(3);

	m_generalFlexSizer->Add(m_RegisterAddrLengthST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_RegisterAddrLengthCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxReadBytesST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxReadBytesCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxWriteBytesST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_MaxWriteBytesCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_TrasmitTimeoutST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_TrasmitTimeoutCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_WriteCycleTimeST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_WriteCycleTimeCB, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_PollingCycleTimeST, wxSizerFlags().Align(wxCENTER).Border());
	m_generalFlexSizer->Add(m_PollingCycleTimeCB, wxSizerFlags().Align(wxCENTER).Border());
	
	m_generalPanel->SetSizer(m_generalFlexSizer);

	m_generalNB->AddPage(m_generalPanel, wxT("General"));

	m_OkButton = new wxButton(this, CID_OK_BUTTOUN, wxT("OK"), wxDefaultPosition, wxSize(80, -1));
	m_CancelButton = new wxButton(this, CID_CANCEL_BUTTON, wxT("Cancel"), wxDefaultPosition, wxSize(80, -1));
	m_ComportButton = new wxButton(this, CID_COMPORT_BUTTOUN, wxT("Comport"), wxDefaultPosition, wxSize(80, -1));
	m_ComportButton->SetBitmap(LOAD_PNG_RESOURCE(complug_16));

	m_USBSettingButton = new wxButton(this, CID_USB_SETTINGS_BUTTON, wxT("Setting"), wxDefaultPosition, wxSize(80, -1));
	m_USBSettingButton->SetBitmap(LOAD_PNG_RESOURCE(usb_16));

	if (module_select != I2C_AdaptorModuleBoard_R90000_9271_USB){
		m_USBSettingButton->Enable(false);
	}

	m_ButtonSizer->Add(m_OkButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_CancelButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_ComportButton, wxSizerFlags().Align(wxCENTER).Border());
	m_ButtonSizer->Add(m_USBSettingButton, wxSizerFlags().Align(wxCENTER).Border());

	/* ------------------------------------ */
	m_LeftSizer->Add(m_i2cIFModuleSBS, wxSizerFlags().Expand());
	m_LeftSizer->Add(m_generalNB, wxSizerFlags().Expand());

	m_TopLevelSizer->Add(m_LeftSizer);
	m_TopLevelSizer->Add(m_ButtonSizer);

	// Setup Sizer
	SetSizerAndFit(m_TopLevelSizer);

}

I2CInterfaceDialog::~I2CInterfaceDialog(){

}

void I2CInterfaceDialog::OnModuleBoardCombo(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_ALERT, "OnModuleBoardCombo");

	if (this->m_moduleNameCB->GetSelection() == I2C_AdaptorModuleBoard_R90000_9271_USB){
		this->m_USBSettingButton->Enable(true);
	}
	else{
		this->m_USBSettingButton->Enable(false);
	}
}

void I2CInterfaceDialog::OnOKButton(wxCommandEvent& event){
	int select = 0;

	// Save Settings
	// I2C Adaptor Module Board
	select = this->m_moduleNameCB->GetSelection();

	// If Module Board Changed
	if (m_previousModuleBoardSelectIndex == select){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Module Board Don't Changed");
		this->EndModal(0);
		return;
	}

	switch (select){

	case I2C_AdaptorModuleBoard_PICKIT_SERIAL:
		this->m_appSettings->m_I2CAdaptorModuleBoard = I2C_AdaptorModuleBoard_PICKIT_SERIAL;
		break;
	
	case I2C_AdaptorModuleBoard_R90000_95611:
		this->m_appSettings->m_I2CAdaptorModuleBoard = I2C_AdaptorModuleBoard_R90000_95611;
		break;

	case I2C_AdaptorModuleBoard_R90000_9271_USB:
		this->m_appSettings->m_I2CAdaptorModuleBoard = I2C_AdaptorModuleBoard_R90000_9271_USB;
		break;

	case I2C_AdaptorModuleBoard_TOTALPHASE:
		this->m_appSettings->m_I2CAdaptorModuleBoard = I2C_AdaptorModuleBoard_TOTALPHASE;
		break;

	case I2C_AdaptorModuleBoard_TRC2I2CAdapter:
		this->m_appSettings->m_I2CAdaptorModuleBoard = I2C_AdaptorModuleBoard_TRC2I2CAdapter;
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Save I2C Adaptor Module Board Error");
		break;
	}

	// Current Use IO
	switch (this->m_appSettings->m_I2CAdaptorModuleBoard){

	case I2C_AdaptorModuleBoard_PICKIT_SERIAL:

		*this->m_currentUseIO = IOACCESS_PICKIT;

		break;

	case I2C_AdaptorModuleBoard_R90000_95611:

		*this->m_currentUseIO = IOACCESS_SERIALPORT;

		break;

	case I2C_AdaptorModuleBoard_R90000_9271_USB:

		*this->m_currentUseIO = IOACCESS_HID;

		break;

	case I2C_AdaptorModuleBoard_TOTALPHASE:

		*this->m_currentUseIO = IOACCESS_TOTALPHASE;

		break;

	case I2C_AdaptorModuleBoard_TRC2I2CAdapter:

		*this->m_currentUseIO = IOACCESS_TRC2_I2C_ADAPTER;

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "I2C Adaptor Module Board Setting Error");
		break;
	}

	this->CloseIODevice();
	wxMilliSleep(200);
	this->OpenIODevice();

	this->EndModal(0);
}

void I2CInterfaceDialog::OnCancelButton(wxCommandEvent& event){
	this->EndModal(0);
}

void I2CInterfaceDialog::OnComportButton(wxCommandEvent& event){
	ComportDialog* comportDialog = new ComportDialog(this, this->m_ioaccess, this->m_appSettings, this->m_pmbusStatusBar);
	comportDialog->Centre();
	comportDialog->ShowModal();

	delete comportDialog;
}

void I2CInterfaceDialog::OnUSBSettingsButton(wxCommandEvent& event){
	USBSettingsDialog* usbSettingsDialog = new USBSettingsDialog(this, this->m_ioaccess, this->m_currentUseIO, this->m_appSettings, this->m_pmbusStatusBar);
	usbSettingsDialog->Centre();
	usbSettingsDialog->ShowModal();

	delete usbSettingsDialog;
}

void I2CInterfaceDialog::UpdateStatusBarIOSettingFiled(wxString io_string){
	this->m_pmbusStatusBar->SetStatusText(io_string, PMBUSStatusBar::Field_IO_Setting);
}

void I2CInterfaceDialog::UpdateStatusBarIOSettingFiled(unsigned long i2cBitRateSpeed){
	wxString i2cBitRateString = wxString::Format("%ld", i2cBitRateSpeed);
	i2cBitRateString += wxT("kHz");
	
	this->m_pmbusStatusBar->SetStatusText(i2cBitRateString, PMBUSStatusBar::Field_I2C_Clock);
}

int I2CInterfaceDialog::SetIODeviceOption(void){
	this->m_portSetting.m_comportNumber = this->m_appSettings->m_comportSetting.m_comportNumber;
	this->m_portSetting.m_buadRate = this->m_appSettings->m_comportSetting.m_buadRate;
	this->m_portSetting.m_byteSize = this->m_appSettings->m_comportSetting.m_byteSize;
	this->m_portSetting.m_parityCheck = this->m_appSettings->m_comportSetting.m_parityCheck;
	this->m_portSetting.m_stopBits = this->m_appSettings->m_comportSetting.m_stopBits;

	return EXIT_SUCCESS;
}

int I2CInterfaceDialog::OpenIODevice(void){

	int ret = EXIT_FAILURE;

	// Open Device

	if (this->m_ioaccess[*this->m_currentUseIO].m_GetDeviceStatus() == IODEVICE_CLOSE) {
		this->m_ioaccess[*this->m_currentUseIO].m_EnumerateAvailableDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT);

		this->SetIODeviceOption();
		ret = this->m_ioaccess[*this->m_currentUseIO].m_OpenDevice(this->m_enumIOPort, IO_PORT_MAX_COUNT, &this->m_portSetting);

		if (ret != EXIT_SUCCESS){
			PSU_DEBUG_PRINT(MSG_DEBUG, "Open IO Device Failed !");
		}
		else{
			//this->m_ioDeviceOpen = true;

			if (*this->m_currentUseIO == IOACCESS_SERIALPORT) {

				// Append Comport Number
				wxString openDeviceName(this->m_ioaccess[*this->m_currentUseIO].m_GetOpenDeviceName());
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
			else if (*this->m_currentUseIO == IOACCESS_HID){

				wxString usbDeviceName(wxT("R90000-9271(USB)"));

				this->UpdateStatusBarIOSettingFiled(usbDeviceName);

				new (TP_SendUSBAdaptorBitRateTask) SendUSBAdaptorBitRateTask(
					this->m_ioaccess,
					this->m_currentUseIO,
					this->m_appSettings->m_usbAdaptorI2CSetting.m_bitRateSpeed,
					this->m_appSettings->m_usbAdaptorSPISetting.m_bitRateSpeed,
					this->m_appSettings->m_usbAdaptorCANSetting.m_bitRateSpeed,
					this->m_appSettings->m_usbAdaptorI2CSetting.m_busTimeout
					);

				//
				while (TaskEx::GetCount(task_ID_SendUSBAdaptorBitRateTask) != 0){

					wxMilliSleep(200);
				}

				// Update I2C Clock Speed Field
				this->UpdateStatusBarIOSettingFiled(this->m_appSettings->m_usbAdaptorI2CSetting.m_bitRateSpeed);

			}
			else if (*this->m_currentUseIO == IOACCESS_TOTALPHASE){

				wxString totalPhaseDeviceName(wxT("TOTAL PHASE"));

				this->UpdateStatusBarIOSettingFiled(totalPhaseDeviceName);

				// Update I2C Clock Speed Field
				this->UpdateStatusBarIOSettingFiled(this->m_appSettings->m_totalPhase_I2C_Bitrate);

			}				
			else if (*this->m_currentUseIO == IOACCESS_PICKIT){

				wxString pickitSerialDeviceName(wxT("PICKIT Serial"));

				this->UpdateStatusBarIOSettingFiled(pickitSerialDeviceName);

				// Update I2C Clock Speed Field
				this->UpdateStatusBarIOSettingFiled(100);

			}else if(*this->m_currentUseIO == IOACCESS_TRC2_I2C_ADAPTER){

				wxString trc2I2CAdapterDeviceName(wxT("TRC2 I2C Adapter"));

				this->UpdateStatusBarIOSettingFiled(trc2I2CAdapterDeviceName);

				// Create TRC2AdapterGetFWVersion Task
				new(TP_TRC2AdapterGetFWVersionTask) TRC2AdapterGetFWVersionTask(this->m_ioaccess, this->m_currentUseIO, this->m_eventHandler);

				// Update I2C Clock Speed Field
				this->UpdateStatusBarIOSettingFiled(PMBUSHelper::GetAppSettings()->m_trc2Adapter_I2C_Bitrate);

			}

#if 0 // Don't Work Due To Main Frame Instance Not be Created 
			/*** Send Query Start Event To Handler Function ***/
			wxThreadEvent *threadQueryStart_evt;

			threadQueryStart_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_QUERY_SEQUENCE_START);
			threadQueryStart_evt->SetString(wxT("Query All Commands"));
			wxQueueEvent(this->GetEventHandler(), threadQueryStart_evt);
#endif

		}
	}
	//}

	return ret;

}

int I2CInterfaceDialog::CloseIODevice(void){
	int ret = EXIT_FAILURE;

	//if (this->m_ioDeviceOpen == true){
	// Close IO Device
	if (this->m_ioaccess[*this->m_currentUseIO].m_GetDeviceStatus() == IODEVICE_OPEN){
		ret = this->m_ioaccess[*this->m_currentUseIO].m_CloseDevice();

		if (ret != EXIT_SUCCESS){
			PSU_DEBUG_PRINT(MSG_ERROR, "Close IO Device Failed !");
		}
		else{
			//this->m_ioDeviceOpen = false;
			this->UpdateStatusBarIOSettingFiled(wxString("Disconnect"));
		}
	}

	//}

	return ret;
}

wxBEGIN_EVENT_TABLE(I2CInterfaceDialog, wxDialog)
EVT_COMBOBOX(CID_MODULE_BOARD_COMBO, I2CInterfaceDialog::OnModuleBoardCombo)
EVT_BUTTON(CID_OK_BUTTOUN, I2CInterfaceDialog::OnOKButton)
EVT_BUTTON(CID_CANCEL_BUTTON, I2CInterfaceDialog::OnCancelButton)
EVT_BUTTON(CID_COMPORT_BUTTOUN, I2CInterfaceDialog::OnComportButton)
EVT_BUTTON(CID_USB_SETTINGS_BUTTON, I2CInterfaceDialog::OnUSBSettingsButton)
wxEND_EVENT_TABLE()
