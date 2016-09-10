/**
 * @file USBI2CRS232Panel.cpp
 */

#include "USBI2CRS232Panel.h"

USBI2CRS232Panel::USBI2CRS232Panel(wxWindow* parent, IOACCESS* ioaccess, unsigned int* currentUseIO) : wxPanel(parent){

	this->m_ioaccess = ioaccess;
	this->m_currentUseIO = currentUseIO;

	/* Initial Sizer */
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
    m_i2cportSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("I2C Port"));
	m_rs232portSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("RS232 Port"));
	m_fgSizer1 = new wxFlexGridSizer(3, 3, 5, 5);
	m_fgSizer2 = new wxFlexGridSizer(6, 2, 5, 5);

	// Setup Text Validator
	wxString DecimalCharIncludes = wxT("0123456789");
	m_decimalValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decimalValidator.SetCharIncludes(DecimalCharIncludes);

	/* Section 1 */
	// I2C Bit Rate Speed
	m_i2cBitRateST = new wxStaticText(m_i2cportSB->GetStaticBox(), wxID_ANY, wxT("Bit Rate Speed (KHz)"));
	m_i2cBitRateCB = new wxComboBox(m_i2cportSB->GetStaticBox(), wxID_ANY);

	i2cBitRateSpeedItemArray[0] = I2C_BIT_RATE_SPEED_ITEM_1;
	i2cBitRateSpeedItemArray[1] = I2C_BIT_RATE_SPEED_ITEM_2;
	i2cBitRateSpeedItemArray[2] = I2C_BIT_RATE_SPEED_ITEM_3;
	i2cBitRateSpeedItemArray[3] = I2C_BIT_RATE_SPEED_ITEM_4;
	i2cBitRateSpeedItemArray[4] = I2C_BIT_RATE_SPEED_ITEM_5;

	for (int idx=0; idx < I2C_BIT_RATE_SPEED_ITEM_SIZE; idx++){
		m_i2cBitRateCB->Append(wxString::Format("%d", i2cBitRateSpeedItemArray[idx]));
	}

	int select = 0;
	for (int idx = 0; idx < I2C_BIT_RATE_SPEED_ITEM_SIZE; idx++){
		if ((PMBUSHelper::GetAppSettings())->m_usbAdaptorI2CSetting.m_bitRateSpeed == i2cBitRateSpeedItemArray[idx]){
			select = idx;
			break;
		}
	}

	m_i2cBitRateCB->SetSelection(select);

	// I2C SMBUS
	m_smbusCheckBox = new wxCheckBox(m_i2cportSB->GetStaticBox(), CID_SMBUS_CHKBOX, wxT("SMBus"));

	m_smbusCheckBox->SetValue(((PMBUSHelper::GetAppSettings())->m_usbAdaptorI2CSetting.m_smBus) == Generic_Unchecked ? false : true);


	m_fgSizer1->Add(m_i2cBitRateST);
	m_fgSizer1->Add(m_i2cBitRateCB);
	m_fgSizer1->Add(m_smbusCheckBox);


	// I2C Comm & Bus TimeOut
	m_commBusTimeoutST = new wxStaticText(m_i2cportSB->GetStaticBox(), wxID_ANY, wxT("Comm/Bus Timeout (ms)"));
	
	m_commTC = new wxTextCtrl(m_i2cportSB->GetStaticBox(), wxID_ANY);
	m_commTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorI2CSetting.m_comm));
	m_commTC->SetValidator(m_decimalValidator);
	
	m_BusTimeoutTC = new wxTextCtrl(m_i2cportSB->GetStaticBox(), wxID_ANY);
	m_BusTimeoutTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorI2CSetting.m_busTimeout));
	m_BusTimeoutTC->SetValidator(m_decimalValidator);

	m_fgSizer1->Add(m_commBusTimeoutST);
	m_fgSizer1->Add(m_commTC);
	m_fgSizer1->Add(m_BusTimeoutTC);

	// I2C Receive Buffer Size
	m_i2cRecvBuffSizeST = new wxStaticText(m_i2cportSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	
	m_i2cRecvBuffSizeTC = new wxTextCtrl(m_i2cportSB->GetStaticBox(), wxID_ANY);
	m_i2cRecvBuffSizeTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorI2CSetting.m_receiveBufferSize));
	m_i2cRecvBuffSizeTC->SetValidator(m_decimalValidator);

	m_fgSizer1->Add(m_i2cRecvBuffSizeST);
	m_fgSizer1->Add(m_i2cRecvBuffSizeTC);
	

	m_i2cportSB->Add(m_fgSizer1, wxSizerFlags(1).Expand());

	/* Section 2 */
	m_rs232PortNumberST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Port Number"));
	m_rs232PortNumberCB = new wxComboBox(m_rs232portSB->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(110, -1));

	// USB UART Port Number
	for (int idx = 0; idx < USB_ADAPTOR_UART_SIZE; idx++){
		// Initialize Port Number & append it to Combo Box
		(PMBUSHelper::GetAppSettings())->m_usbAdaptorUARTSetting[idx].m_uartNumber = idx;
		m_rs232PortNumberCB->Append(wxString::Format("%d",idx));
	}

	m_rs232PortNumberCB->SetSelection(0);


	m_rs232BuadRateST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Buad Rate"));
	m_rs232BuadRateCB = new wxComboBox(m_rs232portSB->GetStaticBox(), CID_UART_BUADRATE_CHKBOX, wxEmptyString, wxDefaultPosition, wxSize(110, -1));

	// USB UART Buad Rate
	typedef struct {
		char *m_label;
		unsigned long  m_value;
	} BuadRateArray;

	BuadRateArray buadRatedArray[12] = {
		{ "600", 600 },
		{ "1200", 1200 },
		{ "2400", 2400 },
		{ "4800", 4800 },
		{ "9600", 9600 },
		{ "14400", 14400 },
		{ "19200", 19200 },
		{ "38400", 38400 },
		{ "56000", 56000 },
		{ "57600", 57600 },
		{ "115200", 115200 },
		{ "172800", 172800 }
	};

	for (unsigned int idx = 0; idx < sizeof(buadRatedArray) / sizeof(buadRatedArray[0]); idx++){
		m_rs232BuadRateCB->Append(buadRatedArray[idx].m_label);
	}

	// Note : Default get port 0's setting value as default value
	for (unsigned int idx = 0; idx < sizeof(buadRatedArray) / sizeof(buadRatedArray[0]); idx++){
		if ((PMBUSHelper::GetAppSettings())->m_usbAdaptorUARTSetting[0].m_buadRate == buadRatedArray[idx].m_value){
			select = idx;
			break;
		}
	}

	m_rs232BuadRateCB->SetSelection(select);

	m_rs232DataBitsST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Data Bits"));
	m_rs232DataBitsCB = new wxComboBox(m_rs232portSB->GetStaticBox(), CID_UART_DATABITS_CHKBOX, wxEmptyString, wxDefaultPosition, wxSize(110, -1));

	// USB UART Data Bits
	unsigned long dataBitsArray[2] = { 8, 9 };

	for (unsigned int idx = 0; idx < sizeof(dataBitsArray) / sizeof(dataBitsArray[0]); idx++){
		m_rs232DataBitsCB->Append(wxString::Format("%d", dataBitsArray[idx]));
	}

	for (unsigned int idx = 0; idx < sizeof(dataBitsArray) / sizeof(dataBitsArray[0]); idx++){
		if ((PMBUSHelper::GetAppSettings())->m_usbAdaptorUARTSetting[0].m_byteSize == dataBitsArray[idx]){
			select = idx;
			break;
		}
	}

	m_rs232DataBitsCB->SetSelection(select);

	m_rs232StopBitsST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Stop Bits"));
	m_rs232StopBitsCB = new wxComboBox(m_rs232portSB->GetStaticBox(), CID_UART_STOPBITS_CHKBOX, wxEmptyString, wxDefaultPosition, wxSize(110, -1));

	// USB UART Stop Bits
	typedef struct {
		char *m_label;
		unsigned long  m_value;
	} StopBitsArray;

	StopBitsArray stopBitsArray[2] = {
		{ "1", 0 },
		{ "2", 1 },
	};

	for (unsigned int idx = 0; idx < sizeof(stopBitsArray) / sizeof(stopBitsArray[0]); idx++){
		m_rs232StopBitsCB->Append(stopBitsArray[idx].m_label);
	}

	for (unsigned int idx = 0; idx < sizeof(stopBitsArray) / sizeof(stopBitsArray[0]); idx++){
		if ((PMBUSHelper::GetAppSettings())->m_usbAdaptorUARTSetting[0].m_stopBits == stopBitsArray[idx].m_value){
			select = idx;
			break;
		}
	}

	m_rs232StopBitsCB->SetSelection(select);

	m_rs232ParityCheckST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Parity Check"));
	m_rs232ParityCheckCB = new wxComboBox(m_rs232portSB->GetStaticBox(), CID_UART_PARITYCHK_CHKBOX, wxEmptyString, wxDefaultPosition, wxSize(110, -1));

	// USB UART Parity Check
	typedef struct {
		char *m_label;
		unsigned long  m_value;
	} ParityCheckArray;

	ParityCheckArray parityCheckArray[3] = {
		{ "N", 0 },
		{ "E", 1 },
		{ "O", 2 },
	};

	for (unsigned int idx = 0; idx < sizeof(parityCheckArray) / sizeof(parityCheckArray[0]); idx++){
		m_rs232ParityCheckCB->Append(parityCheckArray[idx].m_label);
	}

	for (unsigned int idx = 0; idx < sizeof(parityCheckArray) / sizeof(parityCheckArray[0]); idx++){
		if ((PMBUSHelper::GetAppSettings())->m_usbAdaptorUARTSetting[0].m_parityCheck == parityCheckArray[idx].m_value){
			select = idx;
			break;
		}
	}

	m_rs232ParityCheckCB->SetSelection(select);

	// If DataBits == 9, Diable Parity Check Combo Box
	if (m_rs232DataBitsCB->GetSelection() == 1){
		m_rs232ParityCheckCB->SetSelection(0);
		m_rs232ParityCheckCB->Enable(false);
	}

	m_rs232RecvBuffSizeST = new wxStaticText(m_rs232portSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	m_rs232RecvBuffSizeTC = new wxTextCtrl(m_rs232portSB->GetStaticBox(), wxID_ANY);

	// USB UART Received Buffer Size
	m_rs232RecvBuffSizeTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorUARTSetting[0].m_receiveBufferSize));
	m_rs232RecvBuffSizeTC->SetValidator(m_decimalValidator);

	m_fgSizer2->Add(m_rs232PortNumberST);
	m_fgSizer2->Add(m_rs232PortNumberCB);

	m_fgSizer2->Add(m_rs232BuadRateST);
	m_fgSizer2->Add(m_rs232BuadRateCB);

	m_fgSizer2->Add(m_rs232DataBitsST);
	m_fgSizer2->Add(m_rs232DataBitsCB);

	m_fgSizer2->Add(m_rs232StopBitsST);
	m_fgSizer2->Add(m_rs232StopBitsCB);

	m_fgSizer2->Add(m_rs232ParityCheckST);
	m_fgSizer2->Add(m_rs232ParityCheckCB);

	m_fgSizer2->Add(m_rs232RecvBuffSizeST);
	m_fgSizer2->Add(m_rs232RecvBuffSizeTC);

	m_rs232portSB->Add(m_fgSizer2, wxSizerFlags(1).Expand());

	/* Add element to topLevelSizer */
	m_topLevelSizer->Add(m_i2cportSB, wxSizerFlags(0).Expand());
	m_topLevelSizer->Add(m_rs232portSB, wxSizerFlags(1).Expand());

	this->SetSizerAndFit(m_topLevelSizer);
}

USBI2CRS232Panel::~USBI2CRS232Panel(){

}

void USBI2CRS232Panel::SendUARTSettingAgent(void){
	new(TP_SendUSBAdaptorUARTSettingTask)SendUSBAdaptorUARTSettingTask(
		this->m_ioaccess,
		this->m_currentUseIO,
		this->m_rs232PortNumberCB->GetSelection(), // UART Port
		this->m_rs232BuadRateCB->GetSelection(),   // Buad Rate
		this->m_rs232DataBitsCB->GetSelection(),   // Data Bits
		this->m_rs232StopBitsCB->GetSelection(),   // Stop Bits
		this->m_rs232ParityCheckCB->GetSelection()
		);
}

void USBI2CRS232Panel::OnSMBUSCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	PMBUSHelper::GetAppSettings()->m_usbAdaptorI2CSetting.m_smBus = this->m_smbusCheckBox->GetValue() == false ? 0 : 1;

	// Send USB Adaptor Config
	new(TP_SendUSBAdaptorConfigTask) SendUSBAdaptorConfigTask(
		this->m_ioaccess,
		this->m_currentUseIO,
		PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_autoReport,
		PMBUSHelper::GetAppSettings()->m_usbAdaptorI2CSetting.m_smBus,
		PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_enablePWM,
		PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_clockInDI6,
		PMBUSHelper::GetAppSettings()->m_usbAdaptorGPIOSetting.m_clockInDI7,
		wxAtoi(this->m_BusTimeoutTC->GetValue())
	);

}

void USBI2CRS232Panel::OnUARTBuadRateCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
	this->SendUARTSettingAgent();
}

void USBI2CRS232Panel::OnUARTDataBitsCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	// If DataBits == 9, Diable Parity Check Combo Box
	if (m_rs232DataBitsCB->GetSelection() == 1){
		m_rs232ParityCheckCB->SetSelection(0);
		m_rs232ParityCheckCB->Enable(false);
	} else{
		m_rs232ParityCheckCB->SetSelection(0);
		m_rs232ParityCheckCB->Enable(true);
	}

	this->SendUARTSettingAgent();
}

void USBI2CRS232Panel::OnUARTStopBitsCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
	this->SendUARTSettingAgent();
}

void USBI2CRS232Panel::OnUARTParityCheckCheckBox(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_DEBUG, "");
	this->SendUARTSettingAgent();
}

wxBEGIN_EVENT_TABLE(USBI2CRS232Panel, wxPanel)
EVT_CHECKBOX(CID_SMBUS_CHKBOX, USBI2CRS232Panel::OnSMBUSCheckBox)

EVT_COMBOBOX(CID_UART_BUADRATE_CHKBOX, USBI2CRS232Panel::OnUARTBuadRateCheckBox)
EVT_COMBOBOX(CID_UART_DATABITS_CHKBOX, USBI2CRS232Panel::OnUARTDataBitsCheckBox)
EVT_COMBOBOX(CID_UART_STOPBITS_CHKBOX, USBI2CRS232Panel::OnUARTStopBitsCheckBox)
EVT_COMBOBOX(CID_UART_PARITYCHK_CHKBOX, USBI2CRS232Panel::OnUARTParityCheckCheckBox)

wxEND_EVENT_TABLE()