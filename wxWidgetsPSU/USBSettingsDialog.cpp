/**
 * @file USBSettingsDialog.cpp
 */

#include "USBSettingsDialog.h"

USBSettingsDialog::USBSettingsDialog(wxWindow *parent, IOACCESS* ioaccess, unsigned int* currentUseIO, AppSettings_t* appSettings, PMBUSStatusBar* pmbusStatusBar) : wxDialog(parent, wxID_ANY, wxString(wxT("USB Settings")), wxDefaultPosition) {

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(USB_16));

	this->SetIcon(icon);
	this->SetBackgroundColour(wxColour(255, 255, 255));

	m_parent = parent;
	m_ioaccess = ioaccess;
	m_currentUseIO = currentUseIO;
	m_appSettings = appSettings;
	m_pmbusStatusBar = pmbusStatusBar;

	m_TopLevelSizer = new wxBoxSizer(wxVERTICAL);

	//m_SettingSBS = new wxStaticBoxSizer(wxHORIZONTAL, this, wxT(""));
	//m_SettingFGS = new wxFlexGridSizer(5, 2, 5, 5);

	//m_RightVerticalSizer = new wxBoxSizer(wxVERTICAL);
	m_ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
	//m_CheckBoxSizer = new wxBoxSizer(wxVERTICAL);

	//m_ComportNumberST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Comport Number"));
	//m_BuadRateST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Buad Rate"));
	//m_ParityCheckST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Parity Check"));
	//m_DataBitsST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Data Bits"));
	//m_StopBitsST = new wxStaticText(m_SettingSBS->GetStaticBox(), wxID_ANY, wxT("Stop Bits"));

	//this->CloseIODevice();
	//wxMilliSleep(200);

	m_noteBook = new wxNotebook(this, wxID_ANY);

	m_i2cRs232Panel = new USBI2CRS232Panel(m_noteBook,this->m_ioaccess, this->m_currentUseIO);
	m_spiCanPanel = new USBSPICANPanel(m_noteBook);
	m_gpioPanel = new USBGPIOPanel(m_noteBook, this->m_ioaccess, this->m_currentUseIO, m_i2cRs232Panel);
	m_infoPanel = new USBInfoPanel(m_noteBook);

	m_noteBook->AddPage(m_i2cRs232Panel, wxT("I2C/RS232"));
	m_noteBook->AddPage(m_spiCanPanel, wxT("SPI/CAN"));
	m_noteBook->AddPage(m_gpioPanel, wxT("GPIO"));
	m_noteBook->AddPage(m_infoPanel, wxT("Info"));

	//m_paddingST = new wxStaticText(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(150,-1));
	m_OKButton = new wxButton(this, CID_OK_BUTTOUN, wxT("OK"), wxDefaultPosition, wxSize(150, -1));
	m_CancelButton = new wxButton(this, wxID_CLOSE, wxT("Cancel"), wxDefaultPosition, wxSize(150, -1));

	//m_ButtonSizer->Add(m_paddingST, wxSizerFlags(1).Expand());
	m_ButtonSizer->Add(m_OKButton);
	m_ButtonSizer->Add(m_CancelButton);

	m_TopLevelSizer->Add(m_noteBook, wxSizerFlags().Expand());
	m_TopLevelSizer->Add(m_ButtonSizer, wxSizerFlags(0).Align(wxCENTER).Border());

	// Setup Sizer
	SetSizerAndFit(m_TopLevelSizer);

	// Setup Escapse ID
	SetEscapeId(wxID_CLOSE);
}

USBSettingsDialog::~USBSettingsDialog(){

}

void USBSettingsDialog::UpdateStatusBarIOSettingFiled(wxString io_string){
	//this->m_pmbusStatusBar->SetStatusText(io_string, PMBUSStatusBar::Field_IO_Setting);
}

int USBSettingsDialog::SetIODeviceOption(void){
	this->m_portSetting.m_comportNumber = this->m_appSettings->m_comportSetting.m_comportNumber;
	this->m_portSetting.m_buadRate = this->m_appSettings->m_comportSetting.m_buadRate;
	this->m_portSetting.m_byteSize = this->m_appSettings->m_comportSetting.m_byteSize;
	this->m_portSetting.m_parityCheck = this->m_appSettings->m_comportSetting.m_parityCheck;
	this->m_portSetting.m_stopBits = this->m_appSettings->m_comportSetting.m_stopBits;

	return EXIT_SUCCESS;
}

#if 0
int USBSettingsDialog::OpenIODevice(void){
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

int USBSettingsDialog::CloseIODevice(void){
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
#endif

void USBSettingsDialog::SaveConfig(void){

	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	// Save Config
	wxConfigBase *pConfig = wxConfigBase::Get();

	if (pConfig == NULL) return;

	pConfig->SetPath(wxT("/USBAdaptor"));

	// I2C Bit Rate Speed
	if (this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_bitRateSpeed != this->m_i2cRs232Panel->i2cBitRateSpeedItemArray[this->m_i2cRs232Panel->m_i2cBitRateCB->GetSelection()]){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save I2C Bit Rate Speed");
		this->m_appSettings->m_usbAdaptorI2CSetting.m_bitRateSpeed = this->m_i2cRs232Panel->i2cBitRateSpeedItemArray[this->m_i2cRs232Panel->m_i2cBitRateCB->GetSelection()];
		pConfig->Write(wxT("I2CBitRateSpeed"), this->m_appSettings->m_usbAdaptorI2CSetting.m_bitRateSpeed);
		this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_bitRateSpeed = this->m_appSettings->m_usbAdaptorI2CSetting.m_bitRateSpeed;
	}

	// I2C SMBUS
	if (this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_smBus != ((this->m_i2cRs232Panel->m_smbusCheckBox->GetValue() == false) ? 0 : 1)){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save I2C SMBUS");
		this->m_appSettings->m_usbAdaptorI2CSetting.m_smBus = (this->m_i2cRs232Panel->m_smbusCheckBox->GetValue() == false) ? 0 : 1;
		pConfig->Write(wxT("I2CSMBUS"), this->m_appSettings->m_usbAdaptorI2CSetting.m_smBus);
		this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_smBus = this->m_appSettings->m_usbAdaptorI2CSetting.m_smBus;
	}

	// I2C COMM
	if (this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_comm != wxAtoi(this->m_i2cRs232Panel->m_commTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save I2C COMM");
		this->m_appSettings->m_usbAdaptorI2CSetting.m_comm = wxAtoi(this->m_i2cRs232Panel->m_commTC->GetValue());
		pConfig->Write(wxT("I2CCOMM"), this->m_appSettings->m_usbAdaptorI2CSetting.m_comm);
		this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_comm = this->m_appSettings->m_usbAdaptorI2CSetting.m_comm;
	}

	// I2C BUS TIME OUT
	if (this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_busTimeout != wxAtoi(this->m_i2cRs232Panel->m_BusTimeoutTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save I2C BUS TIME OUT");
		this->m_appSettings->m_usbAdaptorI2CSetting.m_busTimeout = wxAtoi(this->m_i2cRs232Panel->m_BusTimeoutTC->GetValue());
		pConfig->Write(wxT("I2CBusTimeOut"), this->m_appSettings->m_usbAdaptorI2CSetting.m_busTimeout);
		this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_busTimeout = this->m_appSettings->m_usbAdaptorI2CSetting.m_busTimeout;
	}

	// I2C Receive Buffer Size
	if (this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_receiveBufferSize != wxAtoi(this->m_i2cRs232Panel->m_i2cRecvBuffSizeTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save I2C Receive Buffer Size");
		this->m_appSettings->m_usbAdaptorI2CSetting.m_receiveBufferSize = wxAtoi(this->m_i2cRs232Panel->m_i2cRecvBuffSizeTC->GetValue());
		pConfig->Write(wxT("I2CReceiveBufferSize"), this->m_appSettings->m_usbAdaptorI2CSetting.m_receiveBufferSize);
		this->m_appSettings->m_usbAdaptorI2CSetting.m_previous_receiveBufferSize = this->m_appSettings->m_usbAdaptorI2CSetting.m_receiveBufferSize;
	}

	// SPI Bit Rate Speed
	if (this->m_appSettings->m_usbAdaptorSPISetting.m_previous_bitRateSpeed != this->m_spiCanPanel->spiBitRateSpeedItemArray[this->m_spiCanPanel->m_spiBitRateSpeedCB->GetSelection()]){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save SPI Bit Rate Speed");
		this->m_appSettings->m_usbAdaptorSPISetting.m_bitRateSpeed = this->m_spiCanPanel->spiBitRateSpeedItemArray[this->m_spiCanPanel->m_spiBitRateSpeedCB->GetSelection()];
		pConfig->Write(wxT("SPIBitRateSpeed"), this->m_appSettings->m_usbAdaptorSPISetting.m_bitRateSpeed);
		this->m_appSettings->m_usbAdaptorSPISetting.m_previous_bitRateSpeed = this->m_appSettings->m_usbAdaptorSPISetting.m_bitRateSpeed;
	}

	// SPI Received Buffer Size
	if (this->m_appSettings->m_usbAdaptorSPISetting.m_previous_receiveBufferSize != wxAtoi(this->m_spiCanPanel->m_spiRecvBuffSizeTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save SPI Received Buffer Size");
		this->m_appSettings->m_usbAdaptorSPISetting.m_receiveBufferSize = wxAtoi(this->m_spiCanPanel->m_spiRecvBuffSizeTC->GetValue());
		pConfig->Write(wxT("SPIReceiveBufferSize"), this->m_appSettings->m_usbAdaptorSPISetting.m_receiveBufferSize);
		this->m_appSettings->m_usbAdaptorSPISetting.m_previous_receiveBufferSize = this->m_appSettings->m_usbAdaptorSPISetting.m_receiveBufferSize;
	}

	// SPI Received Time Out
	if (this->m_appSettings->m_usbAdaptorSPISetting.m_previous_receivedTimeout != wxAtoi(this->m_spiCanPanel->m_spiRecvTimeoutTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save SPI Received Time Out");
		this->m_appSettings->m_usbAdaptorSPISetting.m_receivedTimeout = wxAtoi(this->m_spiCanPanel->m_spiRecvTimeoutTC->GetValue());
		pConfig->Write(wxT("SPIReceivedTimeOut"), this->m_appSettings->m_usbAdaptorSPISetting.m_receivedTimeout);
		this->m_appSettings->m_usbAdaptorSPISetting.m_previous_receivedTimeout = this->m_appSettings->m_usbAdaptorSPISetting.m_receivedTimeout;
	}

	// CAN Bit Rate Speed
	if (this->m_appSettings->m_usbAdaptorCANSetting.m_previous_bitRateSpeed != this->m_spiCanPanel->canBitRateSpeedItemArray[this->m_spiCanPanel->m_canBitRateSpeedCB->GetSelection()]){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save CAN Bit Rate Speed");
		this->m_appSettings->m_usbAdaptorCANSetting.m_bitRateSpeed = this->m_spiCanPanel->canBitRateSpeedItemArray[this->m_spiCanPanel->m_canBitRateSpeedCB->GetSelection()];
		pConfig->Write(wxT("CANBitRateSpeed"), this->m_appSettings->m_usbAdaptorCANSetting.m_bitRateSpeed);
		this->m_appSettings->m_usbAdaptorCANSetting.m_previous_bitRateSpeed = this->m_appSettings->m_usbAdaptorCANSetting.m_bitRateSpeed;
	}

	// CAN Received MSG Size
	if (this->m_appSettings->m_usbAdaptorCANSetting.m_previous_receivedMSGSize != wxAtoi(this->m_spiCanPanel->m_canRecvMSGSizeTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save CAN Received MSG Size");
		this->m_appSettings->m_usbAdaptorCANSetting.m_receivedMSGSize = wxAtoi(this->m_spiCanPanel->m_canRecvMSGSizeTC->GetValue());
		pConfig->Write(wxT("CANReceivedMSGSize"), this->m_appSettings->m_usbAdaptorCANSetting.m_receivedMSGSize);
		this->m_appSettings->m_usbAdaptorCANSetting.m_previous_receivedMSGSize = this->m_appSettings->m_usbAdaptorCANSetting.m_receivedMSGSize;
	}

	// CAN Received Buffer Size
	if (this->m_appSettings->m_usbAdaptorCANSetting.m_previous_receiveBufferSize != wxAtoi(this->m_spiCanPanel->m_canRecvBuffSizeTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save CAN Received Buffer Size");
		this->m_appSettings->m_usbAdaptorCANSetting.m_receiveBufferSize = wxAtoi(this->m_spiCanPanel->m_canRecvBuffSizeTC->GetValue());
		pConfig->Write(wxT("CANReceiveBufferSize"), this->m_appSettings->m_usbAdaptorCANSetting.m_receiveBufferSize);
		this->m_appSettings->m_usbAdaptorCANSetting.m_previous_receiveBufferSize = this->m_appSettings->m_usbAdaptorCANSetting.m_receiveBufferSize;
	}

	// CAN Received Time Out
	if (this->m_appSettings->m_usbAdaptorCANSetting.m_previous_receivedTimeout != wxAtoi(this->m_spiCanPanel->m_canRecvTimeoutTC->GetValue())){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Save CAN Received Time Out");
		this->m_appSettings->m_usbAdaptorCANSetting.m_receivedTimeout = wxAtoi(this->m_spiCanPanel->m_canRecvTimeoutTC->GetValue());
		pConfig->Write(wxT("CANReceivedTimeOut"), this->m_appSettings->m_usbAdaptorCANSetting.m_receivedTimeout);
		this->m_appSettings->m_usbAdaptorCANSetting.m_previous_receivedTimeout = this->m_appSettings->m_usbAdaptorCANSetting.m_receivedTimeout;
	}


	// GPIO Auto Report
	if (this->m_appSettings->m_usbAdaptorGPIOSetting.m_autoReport != ((this->m_gpioPanel->m_autoReportCheckBox->GetValue() == false) ? 0 : 1)){
		PSU_DEBUG_PRINT(MSG_DEBUG, "GPIO Auto Report");
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_autoReport = (this->m_gpioPanel->m_autoReportCheckBox->GetValue() == false) ? 0 : 1;
		//pConfig->Write(wxT("I2CSMBUS"), this->m_appSettings->m_usbAdaptorGPIOSetting.m_autoReport);
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_previous_autoReport = this->m_appSettings->m_usbAdaptorGPIOSetting.m_autoReport;
	}

	// GPIO Enable PWM
	if (this->m_appSettings->m_usbAdaptorGPIOSetting.m_enablePWM != ((this->m_gpioPanel->m_enablePWMCheckBox->GetValue() == false) ? 0 : 1)){
		PSU_DEBUG_PRINT(MSG_DEBUG, "GPIO Auto Report");
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_enablePWM = (this->m_gpioPanel->m_enablePWMCheckBox->GetValue() == false) ? 0 : 1;
		//pConfig->Write(wxT("I2CSMBUS"), this->m_appSettings->m_usbAdaptorGPIOSetting.m_enablePWM);
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_previous_enablePWM = this->m_appSettings->m_usbAdaptorGPIOSetting.m_enablePWM;
	}

	// GPIO Clock In DI 6
	if (this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI6 != ((this->m_gpioPanel->m_clockInDI6CheckBox->GetValue() == false) ? 0 : 1)){
		PSU_DEBUG_PRINT(MSG_DEBUG, "GPIO Auto Report");
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI6 = (this->m_gpioPanel->m_clockInDI6CheckBox->GetValue() == false) ? 0 : 1;
		//pConfig->Write(wxT("I2CSMBUS"), this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI6);
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_previous_clockInDI6= this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI6;
	}

	// GPIO Clock In DI 7
	if (this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI7 != ((this->m_gpioPanel->m_clockInDI7CheckBox->GetValue() == false) ? 0 : 1)){
		PSU_DEBUG_PRINT(MSG_DEBUG, "GPIO Auto Report");
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI7 = (this->m_gpioPanel->m_clockInDI7CheckBox->GetValue() == false) ? 0 : 1;
		//pConfig->Write(wxT("I2CSMBUS"), this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI7);
		this->m_appSettings->m_usbAdaptorGPIOSetting.m_previous_clockInDI7 = this->m_appSettings->m_usbAdaptorGPIOSetting.m_clockInDI7;
	}


	// 
	if (this->m_ioaccess[*this->m_currentUseIO].m_GetDeviceStatus() == IODEVICE_OPEN){
		new (TP_SendUSBAdaptorBitRateTask) SendUSBAdaptorBitRateTask(
			this->m_ioaccess,
			this->m_currentUseIO,
			this->m_appSettings->m_usbAdaptorI2CSetting.m_bitRateSpeed,
			this->m_appSettings->m_usbAdaptorSPISetting.m_bitRateSpeed,
			this->m_appSettings->m_usbAdaptorCANSetting.m_bitRateSpeed,
			this->m_appSettings->m_usbAdaptorI2CSetting.m_busTimeout
			);
	}
}

void USBSettingsDialog::OnOKButton(wxCommandEvent& event){

	this->SaveConfig();

	this->EndModal(0);
}

wxBEGIN_EVENT_TABLE(USBSettingsDialog, wxDialog)
EVT_BUTTON(CID_OK_BUTTOUN, USBSettingsDialog::OnOKButton)
wxEND_EVENT_TABLE()