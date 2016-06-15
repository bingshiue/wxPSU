/**
 * @file CalibrationDialog.cpp
 */

#include "CalibrationDialog.h"

//#if USE_MODAL_PRESENTATION

unsigned char CalibrationDialog::calibrationItemCommand[CALIBRATION_ITEM_SIZE] = {
	0x00,
	0x00,
	0x05,
	0x05,
	0x05,
	0x30,
	0x30,
	0x32,
	0x32,
	0x09
};

unsigned char CalibrationDialog::calibrationItemPointerMask[CALIBRATION_ITEM_SIZE] = {
	0x00,
	0x10,
	0x00,
	0x10,
	0x20,
	0x00,
	0x10,
	0x00,
	0x10,
	0x00
};

unsigned char CalibrationDialog::calibrationItemPointerValue[10] = {
	0x00,
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,
	0x07,
	0x08,
	0x09
};

double CalibrationDialog::defSelectablePointerCount[CALIBRATION_ITEM_SIZE] = {
	4,
	4,
	1,
	1,
	1,
	6,
	6,
	6,
	6,
	1
};

DATA_RESOLUTION_t CalibrationDialog::m_dataResolution[CALIBRATION_ITEM_SIZE] = {

	/* Data1  Resolution1  Data2  Resolution2 */
	{   0.0000, 0.12500000, 0.0000, 0.12500000 },
	{   0.0000, 0.00390625, 0.0000, 0.00390625 },
	{   0.0000, 0.10000000, 0.0000, 0.10000000 },
	{   0.0000, 0.10000000, 0.0000, 0.10000000 },
	{   0.0000, 0.10000000, 0.0000, 0.10000000 },
	{   0.0000, 0.01562500, 0.0000, 0.01562500 },
	{   0.0000, 0.01562500, 0.0000, 0.01562500 },
	{   0.0000, 0.25000000, 0.0000, 0.25000000 },
	{  64.0000, 0.25000000, 0.0000, 0.25000000 },
	{2250.0000, 1.00000000, 0.0000, 1.00000000 },

};

CalibrationDialog::CalibrationDialog(wxWindow *parent, IOACCESS* ioaccess, unsigned int* currentIO, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t>* sendCMDVector) : wxDialog(parent, wxID_ANY, wxString(wxT("Calibration dialog")))
{
	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(CALIBRATION_16));

	this->SetIcon(icon);
	
	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;
	this->m_monitor_running = monitor_running;
	this->m_sendCMDVector = sendCMDVector;

	m_bottonSizer = new wxBoxSizer(wxHORIZONTAL);
	m_calibrationItemSizer = new wxBoxSizer(wxHORIZONTAL);
	m_sizerTop = new wxBoxSizer(wxVERTICAL);

	m_btnApply = new wxButton(this, CID_BTN_APPLY, wxT("Apply"));
	m_btnDone = new wxButton(this, CID_BTN_DONE, wxT("Done"));
	m_btnRead = new wxButton(this, CID_BTN_READ, wxT("Read"));
	m_btnExit = new wxButton(this, wxID_CLOSE, wxT("&Exit"));

	m_settingControlSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Setting/Control"));

	m_calibrationItemST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT("Calibration Item"), wxDefaultPosition, wxDefaultSize);
	m_calibrationItemCB = new wxComboBox(m_settingControlSBS->GetStaticBox(), CID_CB_CALIBRATION_ITEM, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	m_calibrationItemCB->Append(wxT("Output Current Main"));
	m_calibrationItemCB->Append(wxT("Output Current SB"));
	m_calibrationItemCB->Append(wxT("Output Voltage Main(PWM)"));
	m_calibrationItemCB->Append(wxT("Output Voltage SB(PWM)"));
	m_calibrationItemCB->Append(wxT("Output Voltage LS(PWM)"));
	m_calibrationItemCB->Append(wxT("AC Vin Current 110V AC"));
	m_calibrationItemCB->Append(wxT("AC Vin Current 220V AC"));
	m_calibrationItemCB->Append(wxT("AC Vin Power 110V AC"));
	m_calibrationItemCB->Append(wxT("AC Vin Power 220V AC"));
	m_calibrationItemCB->Append(wxT("ACS SET Pointer"));
	m_calibrationItemCB->SetSelection(0);

	m_calibrationItemSizer->Add(m_calibrationItemST, wxSizerFlags().Border(wxALL, 5));
	m_calibrationItemSizer->Add(m_calibrationItemCB, wxSizerFlags().Border(wxALL, 5));

	m_bottonSizer->Add(m_btnApply, wxSizerFlags(1).Expand());
	m_bottonSizer->Add(m_btnDone, wxSizerFlags(1).Expand());
	m_bottonSizer->Add(m_btnRead, wxSizerFlags(1).Expand());
	m_bottonSizer->Add(m_btnExit, wxSizerFlags(1).Expand());

	m_settingControlSBS->Add(m_calibrationItemSizer, wxSizerFlags(0).Align(wxALIGN_CENTER));

	m_calibrationItemGridSizer = new wxGridSizer(3,4,10,10);

	m_pointerST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT("Pointer"), wxDefaultPosition, wxDefaultSize);
	m_pointerCB = new wxComboBox(m_settingControlSBS->GetStaticBox(), CID_CB_POINTER, wxEmptyString, wxDefaultPosition, wxDefaultSize);

	m_pointerCB->Append(wxT("0"));
	m_pointerCB->Append(wxT("1"));
	m_pointerCB->Append(wxT("2"));
	m_pointerCB->Append(wxT("3"));
	m_pointerCB->SetSelection(0);

	m_padding1ST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize);
	m_padding2ST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize);

	m_data1ST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT("Data1"), wxDefaultPosition, wxDefaultSize);
	m_data1TC = new wxTextCtrl(m_settingControlSBS->GetStaticBox(), CID_TC_DATA_1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	wxString data1DefaultText("0.0000");
	m_data1TC->SetValue(data1DefaultText);

	m_resolution1ST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT("Resolution 1"), wxDefaultPosition, wxDefaultSize);
	m_resolution1TC = new wxTextCtrl(m_settingControlSBS->GetStaticBox(), wxID_ANY);

	wxString resolution1DefaultText("0.12500000");
	m_resolution1TC->SetValue(resolution1DefaultText);

	m_data2ST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT("Data2"), wxDefaultPosition, wxDefaultSize);
	m_data2TC = new wxTextCtrl(m_settingControlSBS->GetStaticBox(), wxID_ANY);

	wxString data2DefaultText("0.0000");
	m_data2TC->SetValue(data2DefaultText);

	m_resolution2ST = new wxStaticText(m_settingControlSBS->GetStaticBox(), wxID_ANY, wxT("Resolution 2"), wxDefaultPosition, wxDefaultSize);
	m_resolution2TC = new wxTextCtrl(m_settingControlSBS->GetStaticBox(), wxID_ANY);

	wxString resolution2DefaultText("0.12500000");
	m_resolution2TC->SetValue(resolution2DefaultText);

	m_calibrationItemGridSizer->Add(m_pointerST);
	m_calibrationItemGridSizer->Add(m_pointerCB);

	m_calibrationItemGridSizer->Add(m_padding1ST);
	m_calibrationItemGridSizer->Add(m_padding2ST);

	m_calibrationItemGridSizer->Add(m_data1ST);
	m_calibrationItemGridSizer->Add(m_data1TC);

	m_calibrationItemGridSizer->Add(m_resolution1ST);
	m_calibrationItemGridSizer->Add(m_resolution1TC);

	m_calibrationItemGridSizer->Add(m_data2ST);
	m_calibrationItemGridSizer->Add(m_data2TC);

	m_calibrationItemGridSizer->Add(m_resolution2ST);
	m_calibrationItemGridSizer->Add(m_resolution2TC);

	m_settingControlSBS->Add(m_calibrationItemGridSizer, wxSizerFlags(0).Align(wxALIGN_CENTER));

	m_sizerTop->Add(m_bottonSizer, wxSizerFlags(0).Expand());
	m_sizerTop->Add(m_settingControlSBS, wxSizerFlags(0).Expand());

	SetSizerAndFit(m_sizerTop);

	SetEscapeId(wxID_CLOSE);

	m_btnApply->SetFocus();
	m_btnApply->SetDefault();
}

void CalibrationDialog::OnButton(wxCommandEvent& event)
{
#if 0
	if (event.GetEventObject() == m_btnDelete)
	{
		wxDELETE(m_btnModal);
		m_btnDelete->Disable();
	}
	else if (event.GetEventObject() == m_btnModal)
	{
#if wxUSE_TEXTDLG
		wxGetTextFromUser(wxT("Dummy prompt"),
			wxT("Modal dialog called from dialog"),
			wxEmptyString, this);
#else
		wxMessageBox(wxT("Modal dialog called from dialog"));
#endif // wxUSE_TEXTDLG
	}
	else if (event.GetEventObject() == m_btnModeless)
	{
		//(new MyModelessDialog(this))->Show();
	}
	else
	{
		event.Skip();
	}
#endif
}

wxBEGIN_EVENT_TABLE(CalibrationDialog, wxDialog)
	EVT_BUTTON(CID_BTN_APPLY, CalibrationDialog::OnBtnApply)
	EVT_BUTTON(CID_BTN_DONE, CalibrationDialog::OnBtnDone)
	EVT_BUTTON(CID_BTN_READ, CalibrationDialog::OnBtnRead)
	EVT_COMBOBOX(CID_CB_CALIBRATION_ITEM, CalibrationDialog::OnCBCalibrationItem)
	EVT_COMBOBOX(CID_CB_POINTER, CalibrationDialog::OnCBPointer)
	//EVT_TEXT_ENTER(CID_TC_DATA_1, CalibrationDialog::OnTCData1)
wxEND_EVENT_TABLE()

//#endif // USE_MODAL_PRESENTATION

#define INDEX_CALIBRATION_ITEM   4
#define INDEX_POINTER            5
#define INDEX_DATA_1_START       6
#define INDEX_DATA_2_START       8
#define INDEX_PEC               10 


//#define USE_LINEAR_DATA_FORMAT
#define CALIBRATION_ITEM_BYTES_TO_READ  6
void CalibrationDialog::OnBtnApply(wxCommandEvent& event){
	// Send Buffer
	unsigned char SendBuffer[13] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x0A
	};

	// Get Calibration Item Command
	SendBuffer[INDEX_CALIBRATION_ITEM] = calibrationItemCommand[this->m_calibrationItemCB->GetSelection()];

	// Get Pointer
	SendBuffer[INDEX_POINTER] = calibrationItemPointerMask[this->m_calibrationItemCB->GetSelection()] | calibrationItemPointerValue[this->m_pointerCB->GetSelection()];

	// Data 1
	double value1 = 0;
	this->m_data1TC->GetValue().ToDouble(&value1);

	double resolution1 = 0;
	this->m_resolution1TC->GetValue().ToDouble(&resolution1);

#ifdef USE_LINEAR_DATA_FORMAT
	PMBUSHelper::ProductLinearData(SendBuffer + INDEX_DATA_1_START, value1, resolution1);
#else
	PMBUSHelper::ProductFakeLinearData(SendBuffer + INDEX_DATA_1_START, value1, resolution1);
#endif

	// Data 2
	double value2 = 0;
	this->m_data2TC->GetValue().ToDouble(&value2);

	double resolution2 = 0;
	this->m_resolution2TC->GetValue().ToDouble(&resolution2);

#ifdef USE_LINEAR_DATA_FORMAT
	PMBUSHelper::ProductLinearData(SendBuffer + INDEX_DATA_2_START, value2, resolution2);
#else
	PMBUSHelper::ProductFakeLinearData(SendBuffer + INDEX_DATA_2_START, value2, resolution2);
#endif

	unsigned char separate_pec = 0;;

	separate_pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 8);
	PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", separate_pec);

	SendBuffer[INDEX_PEC] = separate_pec;

	//PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
	wxString debugStr("Send Buffer :");
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		debugStr += wxString::Format(" %02x ", SendBuffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", debugStr.c_str());

	PMBUSSendCOMMAND_t calibrationItem;

	calibrationItem.m_sendDataLength = sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	calibrationItem.m_bytesToRead = CALIBRATION_ITEM_BYTES_TO_READ;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		calibrationItem.m_sendData[idx] = SendBuffer[idx];
	}

	// Send Data
	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(calibrationItem);
			PSU_DEBUG_PRINT(MSG_ALERT, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask) SendWriteCMDTask(m_ioaccess, m_currentIO, calibrationItem);
	}

}

void CalibrationDialog::OnBtnDone(wxCommandEvent& event){
	// Send Buffer
	unsigned char SendBuffer[13] = {
		0x41, 0x54, PMBUSHelper::GetSlaveAddress(), 0xCB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x0A
	};

	// Get Calibration Item Command
	SendBuffer[INDEX_CALIBRATION_ITEM] = calibrationItemCommand[this->m_calibrationItemCB->GetSelection()];

	// Get Pointer
	SendBuffer[INDEX_POINTER] = 0x1f;//calibrationItemPointerMask[this->m_calibrationItemCB->GetSelection()] | calibrationItemPointerValue[this->m_pointerCB->GetSelection()];

	// Data 1
	double value1 = 0;
	this->m_data1TC->GetValue().ToDouble(&value1);

	double resolution1 = 0;
	this->m_resolution1TC->GetValue().ToDouble(&resolution1);

#ifdef USE_LINEAR_DATA_FORMAT
	PMBUSHelper::ProductLinearData(SendBuffer + INDEX_DATA_1_START, value1, resolution1);
#else
	PMBUSHelper::ProductFakeLinearData(SendBuffer + INDEX_DATA_1_START, value1, resolution1);
#endif

	// Data 2
	double value2 = 0;
	this->m_data2TC->GetValue().ToDouble(&value2);

	double resolution2 = 0;
	this->m_resolution2TC->GetValue().ToDouble(&resolution2);

#ifdef USE_LINEAR_DATA_FORMAT
	PMBUSHelper::ProductLinearData(SendBuffer + INDEX_DATA_2_START, value2, resolution2);
#else
	PMBUSHelper::ProductFakeLinearData(SendBuffer + INDEX_DATA_2_START, value2, resolution2);
#endif

	unsigned char separate_pec = 0;;

	separate_pec = PMBusSlave_Crc8MakeBitwise(0, 7, SendBuffer + 2, 8);
	PSU_DEBUG_PRINT(MSG_DEBUG, "separate_pec = %02xh", separate_pec);

	SendBuffer[INDEX_PEC] = separate_pec;

	//PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
	wxString debugStr("Send Buffer :");
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		debugStr += wxString::Format(" %02x ", SendBuffer[idx]);
	}

	PSU_DEBUG_PRINT(MSG_ALERT, "%s", debugStr.c_str());

	PMBUSSendCOMMAND_t calibrationItem;

	calibrationItem.m_sendDataLength = sizeof(SendBuffer) / sizeof(SendBuffer[0]);
	calibrationItem.m_bytesToRead = CALIBRATION_ITEM_BYTES_TO_READ;
	for (unsigned idx = 0; idx < sizeof(SendBuffer) / sizeof(SendBuffer[0]); idx++){
		calibrationItem.m_sendData[idx] = SendBuffer[idx];
	}

	// Send Data
	if (*this->m_monitor_running == true){
		if (this->m_sendCMDVector->size() == 0){
			this->m_sendCMDVector->push_back(calibrationItem);
			PSU_DEBUG_PRINT(MSG_ALERT, "Size of m_sendCMDVector is %d", this->m_sendCMDVector->size());
		}
	}
	else{
		// If monitor is not running
		int cnt = Task::GetCount();
		if (cnt != 0) return;

		new(TP_SendWriteCMDTask)SendWriteCMDTask(m_ioaccess, m_currentIO, calibrationItem);
	}

}

void CalibrationDialog::OnBtnRead(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void CalibrationDialog::OnCBCalibrationItem(wxCommandEvent& event){
	
	wxString pointer_label("");
	wxString tmp("");

	switch (this->m_calibrationItemCB->GetSelection()){

	case Output_Current_Main :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[Output_Current_Main]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Current_Main].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Current_Main].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Current_Main].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Current_Main].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case Output_Current_SB :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[Output_Current_SB]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Current_SB].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Current_SB].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Current_SB].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Current_SB].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case Output_Voltage_Main_PWM :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[Output_Voltage_Main_PWM]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Voltage_Main_PWM].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Voltage_Main_PWM].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Voltage_Main_PWM].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Voltage_Main_PWM].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case Output_Voltage_SB_PWM :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[Output_Voltage_SB_PWM]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Voltage_SB_PWM].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Voltage_SB_PWM].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Voltage_SB_PWM].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Voltage_SB_PWM].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case Output_Voltage_LS_PWM :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[Output_Voltage_LS_PWM]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Voltage_LS_PWM].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Voltage_LS_PWM].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[Output_Voltage_LS_PWM].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[Output_Voltage_LS_PWM].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case AC_Vin_Current_110V_AC :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[AC_Vin_Current_110V_AC]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Current_110V_AC].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Current_110V_AC].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Current_110V_AC].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Current_110V_AC].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case AC_Vin_Current_220V_AC :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[AC_Vin_Current_220V_AC]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Current_220V_AC].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Current_220V_AC].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Current_220V_AC].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Current_220V_AC].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case AC_Vin_Power_110V_AC :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[AC_Vin_Power_110V_AC]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Power_110V_AC].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Power_110V_AC].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Power_110V_AC].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Power_110V_AC].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case AC_Vin_Power_220V_AC :
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[AC_Vin_Power_220V_AC]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Power_220V_AC].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Power_220V_AC].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[AC_Vin_Power_220V_AC].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[AC_Vin_Power_220V_AC].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	case ACS_SETPOINT:
		// Set Pinter CB Field
		this->m_pointerCB->Clear();

		for (unsigned int idx = 0; idx < defSelectablePointerCount[ACS_SETPOINT]; idx++){
			pointer_label = wxString::Format("%d", idx);
			this->m_pointerCB->Append(pointer_label);
		}

		this->m_pointerCB->SetSelection(0);

		// Set Data & Resolution
		tmp = wxString::Format("%5.4f", m_dataResolution[ACS_SETPOINT].m_data1);
		this->m_data1TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[ACS_SETPOINT].m_Resolution1);
		this->m_resolution1TC->SetValue(tmp);

		tmp = wxString::Format("%5.4f", m_dataResolution[ACS_SETPOINT].m_data2);
		this->m_data2TC->SetValue(tmp);

		tmp = wxString::Format("%5.8f", m_dataResolution[ACS_SETPOINT].m_Resolution2);
		this->m_resolution2TC->SetValue(tmp);

		break;

	default:
		PSU_DEBUG_PRINT(MSG_ALERT, "Something Error Occurs");
		break;
	}

}

void CalibrationDialog::OnCBPointer(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void CalibrationDialog::OnTCData1(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}


