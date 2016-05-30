/**
 * @file CalibrationDialog.cpp
 */

#include "CalibrationDialog.h"

//#if USE_MODAL_PRESENTATION

CalibrationDialog::CalibrationDialog(wxWindow *parent) : wxDialog(parent, wxID_ANY, wxString(wxT("Calibration dialog")))
{
	
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
	m_data1TC = new wxTextCtrl(m_settingControlSBS->GetStaticBox(), wxID_ANY);

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
wxEND_EVENT_TABLE()

//#endif // USE_MODAL_PRESENTATION

void CalibrationDialog::OnBtnApply(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void CalibrationDialog::OnBtnDone(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

void CalibrationDialog::OnBtnRead(wxCommandEvent& event){
	PSU_DEBUG_PRINT(MSG_ALERT, "Not Implement");
}

