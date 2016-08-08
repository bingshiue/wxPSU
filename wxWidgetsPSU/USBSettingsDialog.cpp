/**
 * @file USBSettingsDialog.cpp
 */

#include "USBSettingsDialog.h"

USBSettingsDialog::USBSettingsDialog(wxWindow *parent, IOACCESS* ioaccess, AppSettings_t* appSettings, PMBUSStatusBar* pmbusStatusBar) : wxDialog(parent, wxID_ANY, wxString(wxT("USB Settings")), wxDefaultPosition) {

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(USB_16));

	this->SetIcon(icon);
	this->SetBackgroundColour(wxColour(255, 255, 255));

	m_parent = parent;
	m_ioaccess = ioaccess;
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

	m_i2cRs232Panel = new USBI2CRS232Panel(m_noteBook);// , wxID_ANY, wxDefaultPosition, wxSize(300, 300));
	m_spiCanPanel = new USBSPICANPanel(m_noteBook);
	m_gpioPanel = new USBGPIOPanel(m_noteBook);
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

void USBSettingsDialog::OnOKButton(wxCommandEvent& event){

	//this->CloseIODevice();
	//wxMilliSleep(200);
	//this->OpenIODevice();

	this->EndModal(0);
}

wxBEGIN_EVENT_TABLE(USBSettingsDialog, wxDialog)
EVT_BUTTON(CID_OK_BUTTOUN, USBSettingsDialog::OnOKButton)
wxEND_EVENT_TABLE()