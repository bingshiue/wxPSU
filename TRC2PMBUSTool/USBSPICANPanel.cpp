/**
 * @file USBSPICANPanel.cpp
 */

#include "USBSPICANPanel.h"

USBSPICANPanel::USBSPICANPanel(wxWindow* parent) : wxPanel(parent){

	/* Initial Sizer */
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_fgSizer1 = new wxFlexGridSizer(3, 2, 5, 5);
	m_fgSizer2 = new wxFlexGridSizer(4, 2, 5, 5);
	m_spiPortSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("SPI Port"));
	m_canPortSB = new wxStaticBoxSizer(wxVERTICAL, this, wxT("CAN Port"));

	// Setup Text Validator
	wxString DecimalCharIncludes = wxT("0123456789");
	m_decimalValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decimalValidator.SetCharIncludes(DecimalCharIncludes);

	/* Section 1 */
	m_spiRecvBuffSizeST = new wxStaticText(m_spiPortSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	m_spiRecvBuffSizeTC = new wxTextCtrl(m_spiPortSB->GetStaticBox(), wxID_ANY);
	m_spiRecvBuffSizeTC->SetValidator(m_decimalValidator);
	m_spiRecvBuffSizeTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorSPISetting.m_receiveBufferSize));

	m_spiRecvTimeoutST = new wxStaticText(m_spiPortSB->GetStaticBox(), wxID_ANY, wxT("Received Timeout (ms)"));
	m_spiRecvTimeoutTC = new wxTextCtrl(m_spiPortSB->GetStaticBox(), wxID_ANY);
	m_spiRecvTimeoutTC->SetValidator(m_decimalValidator);
	m_spiRecvTimeoutTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorSPISetting.m_receivedTimeout));

	m_spiBitRateSpeedST = new wxStaticText(m_spiPortSB->GetStaticBox(), wxID_ANY, wxT("Bit Rate Speed (KHz)"));
	m_spiBitRateSpeedCB = new wxComboBox(m_spiPortSB->GetStaticBox(), wxID_ANY);

	spiBitRateSpeedItemArray[0] = SPI_BIT_RATE_SPEED_ITEM_1;
	spiBitRateSpeedItemArray[1] = SPI_BIT_RATE_SPEED_ITEM_2;
	spiBitRateSpeedItemArray[2] = SPI_BIT_RATE_SPEED_ITEM_3;
	spiBitRateSpeedItemArray[3] = SPI_BIT_RATE_SPEED_ITEM_4;
	spiBitRateSpeedItemArray[4] = SPI_BIT_RATE_SPEED_ITEM_5;
	spiBitRateSpeedItemArray[5] = SPI_BIT_RATE_SPEED_ITEM_6;

	for (int idx = 0; idx < SPI_BIT_RATE_SPEED_ITEM_SIZE; idx++){
		m_spiBitRateSpeedCB->Append(wxString::Format("%d", spiBitRateSpeedItemArray[idx]));
	}

	int select = 0;
	for (int idx = 0; idx < SPI_BIT_RATE_SPEED_ITEM_SIZE; idx++){
		if ((PMBUSHelper::GetAppSettings())->m_usbAdaptorSPISetting.m_bitRateSpeed == spiBitRateSpeedItemArray[idx]){
			select = idx;
			break;
		}
	}

	m_spiBitRateSpeedCB->SetSelection(select);

	m_fgSizer1->Add(m_spiRecvBuffSizeST);
	m_fgSizer1->Add(m_spiRecvBuffSizeTC);

	m_fgSizer1->Add(m_spiRecvTimeoutST);
	m_fgSizer1->Add(m_spiRecvTimeoutTC);

	m_fgSizer1->Add(m_spiBitRateSpeedST);
	m_fgSizer1->Add(m_spiBitRateSpeedCB);

	m_spiPortSB->Add(m_fgSizer1, wxSizerFlags(1).Expand());

	/* Section 2 */
	m_canRecvBuffSizeST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Received Buffer Size (bytes)"));
	m_canRecvBuffSizeTC = new wxTextCtrl(m_canPortSB->GetStaticBox(), wxID_ANY);
	m_canRecvBuffSizeTC->SetValidator(m_decimalValidator);
	m_canRecvBuffSizeTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorCANSetting.m_receiveBufferSize));

	m_canRecvMSGSizeST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Received Message Size"));
	m_canRecvMSGSizeTC = new wxTextCtrl(m_canPortSB->GetStaticBox(), wxID_ANY);
	m_canRecvMSGSizeTC->SetValidator(m_decimalValidator);
	m_canRecvMSGSizeTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorCANSetting.m_receivedMSGSize));

	m_canRecvTimeoutST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Received Timeout (ms)"));
	m_canRecvTimeoutTC = new wxTextCtrl(m_canPortSB->GetStaticBox(), wxID_ANY);
	m_canRecvTimeoutTC->SetValidator(m_decimalValidator);
	m_canRecvTimeoutTC->SetValue(wxString::Format("%d", (PMBUSHelper::GetAppSettings())->m_usbAdaptorCANSetting.m_receivedTimeout));

	m_canBitRateSpeedST = new wxStaticText(m_canPortSB->GetStaticBox(), wxID_ANY, wxT("Bit Rate Speed (KHz)"));
	m_canBitRateSpeedCB = new wxComboBox(m_canPortSB->GetStaticBox(), wxID_ANY);

	canBitRateSpeedItemArray[0] = CAN_BIT_RATE_SPEED_ITEM_1;
	canBitRateSpeedItemArray[1] = CAN_BIT_RATE_SPEED_ITEM_2;

	for (int idx = 0; idx < CAN_BIT_RATE_SPEED_ITEM_SIZE; idx++){
		m_canBitRateSpeedCB->Append(wxString::Format("%d", canBitRateSpeedItemArray[idx]));
	}

	select = 0;
	for (int idx = 0; idx < SPI_BIT_RATE_SPEED_ITEM_SIZE; idx++){
		if ((PMBUSHelper::GetAppSettings())->m_usbAdaptorCANSetting.m_bitRateSpeed == canBitRateSpeedItemArray[idx]){
			select = idx;
			break;
		}
	}

	m_canBitRateSpeedCB->SetSelection(select);

	m_fgSizer2->Add(m_canRecvBuffSizeST);
	m_fgSizer2->Add(m_canRecvBuffSizeTC);

	m_fgSizer2->Add(m_canRecvMSGSizeST);
	m_fgSizer2->Add(m_canRecvMSGSizeTC);

	m_fgSizer2->Add(m_canRecvTimeoutST);
	m_fgSizer2->Add(m_canRecvTimeoutTC);

	m_fgSizer2->Add(m_canBitRateSpeedST);
	m_fgSizer2->Add(m_canBitRateSpeedCB);

	m_canPortSB->Add(m_fgSizer2, wxSizerFlags(1).Expand());

	/* Add elements to topLevelSizer */
	m_topLevelSizer->Add(m_spiPortSB, wxSizerFlags(0).Expand());
	m_topLevelSizer->Add(m_canPortSB, wxSizerFlags(1).Expand());

	this->SetSizerAndFit(m_topLevelSizer);
}

USBSPICANPanel::~USBSPICANPanel(){

}


wxBEGIN_EVENT_TABLE(USBSPICANPanel, wxPanel)

wxEND_EVENT_TABLE()