/**
 * @file ModelSelectDialog.cpp
 */

#include "ModelSelectDialog.h"
#include "acbel_large.xpm"


ModelSelectDialog::ModelSelectDialog(wxWindow *parent, MODEL_TYPE_t* modelList, unsigned int modelListSize) : wxDialog(parent, wxID_ANY, wxString(wxT("Model Selection")), wxDefaultPosition, wxSize(375, 140)){

	m_modelList = modelList;
	m_modelListSize = modelListSize;
	
	LoadConfig();

	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_line1Sizer = new wxBoxSizer(wxHORIZONTAL);
	m_line2Sizer = new wxBoxSizer(wxHORIZONTAL);

	m_buttonSizer = new wxBoxSizer(wxVERTICAL);

	m_customerSizer = new wxBoxSizer(wxVERTICAL);
	m_modelNameSizer = new wxBoxSizer(wxVERTICAL);

	m_acbelLogoSB = new wxStaticBitmap(this, wxID_ANY, wxBitmap(Acbel_large_xpm));

	m_byCustomerPNCheckBox = new wxCheckBox(this, CID_CHKBOX_BYCUSTOMERPN, wxT("Buy Customer P/N"));

	m_btnOK = new wxButton(this, CID_BTN_OK, wxT("OK"));

	m_paddingST = new wxStaticText(this, wxID_ANY, wxT(" "));

	m_btnCancel = new wxButton(this, CID_BTN_CANCEL, wxT("Cancel"));

	m_customerST = new wxStaticText(this, wxID_ANY, wxT("Customer"));
	m_customerComboBox = new wxComboBox(this, CID_CBBOX_CUSTOMER, wxEmptyString, wxDefaultPosition, wxSize(110, -1), wxArrayString(), wxCB_READONLY);

	m_modelNameST = new wxStaticText(this, wxID_ANY, wxT("Model Name :"));
	m_modelNameComboBox = new wxComboBox(this, CID_CBBOX_MODELNAME, wxEmptyString, wxDefaultPosition, wxSize(155, -1), wxArrayString(), wxCB_READONLY);

	SetupComboBox();

	this->m_buttonSizer->Add(m_btnOK, wxSizerFlags().Expand().Border(wxALL, 2));
	this->m_buttonSizer->Add(m_btnCancel, wxSizerFlags().Expand().Border(wxALL, 2));

	this->m_line1Sizer->Add(m_acbelLogoSB, wxSizerFlags().Border(wxALL,17).Align(wxALIGN_CENTER_VERTICAL));
	this->m_line1Sizer->Add(m_byCustomerPNCheckBox, wxSizerFlags().Border().Align(wxALIGN_CENTER_VERTICAL));
	this->m_line1Sizer->Add(m_paddingST, wxSizerFlags(1).Expand().Border(wxRIGHT, 50));
	this->m_line1Sizer->Add(m_buttonSizer, wxSizerFlags().Border().Align(wxALIGN_CENTER_VERTICAL));

	this->m_customerSizer->Add(m_customerST);
	this->m_customerSizer->Add(m_customerComboBox);

	this->m_modelNameSizer->Add(m_modelNameST);
	this->m_modelNameSizer->Add(m_modelNameComboBox);

	this->m_line2Sizer->Add(m_customerSizer, wxSizerFlags().Border().Align(wxALIGN_CENTER_VERTICAL));
	this->m_line2Sizer->Add(m_modelNameSizer, wxSizerFlags().Border().Align(wxALIGN_CENTER_VERTICAL));

	this->m_topLevelSizer->Add(this->m_line1Sizer);
	this->m_topLevelSizer->Add(this->m_line2Sizer);
	this->SetSizerAndFit(m_topLevelSizer);

}

ModelSelectDialog::~ModelSelectDialog(){

}

void ModelSelectDialog::SetupComboBox(void){
	// Customer ComboBox
	m_customerComboBox->Append(wxT("NEC"));
	m_customerComboBox->Select(0);
	m_customerComboBox->Enable(false);

	// Model Name ComBox
	for (unsigned int idx = 0; idx < m_modelListSize; idx++){
		m_modelNameComboBox->Append(m_modelList[idx].m_modelName);
	}
	m_modelNameComboBox->Select(this->m_currentUseModel);

}

void ModelSelectDialog::OnOKButton(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_DEBUG, "");

	this->EndModal(wxID_OK);
}

void ModelSelectDialog::OnCancelButton(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_DEBUG, "");
	
	this->EndModal(wxID_CANCEL);
}

void ModelSelectDialog::OnCustomerComboBox(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void ModelSelectDialog::OnModelNameComboBox(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_DEBUG, "");
	this->m_currentUseModel = this->m_modelNameComboBox->GetSelection();

	this->SaveConfig();

}

void ModelSelectDialog::OnByCustomerPNCheckBox(wxCommandEvent& event){
	//PSU_DEBUG_PRINT(MSG_DEBUG, "");
}

void ModelSelectDialog::OnDialogClose(wxCloseEvent& event){


	this->EndModal(wxID_CANCEL);
}

void ModelSelectDialog::LoadConfig(void){
	wxConfigBase::Set(new wxFileConfig(wxT(""), wxT(""), wxT("psu.ini"), wxT(""), wxCONFIG_USE_RELATIVE_PATH));

	wxConfigBase *pConfig = wxConfigBase::Get();

	pConfig->SetPath(wxT("/APP"));
	
	// Model
	long model;
	if (pConfig->Read(wxT("Model"), &model) == false){
		pConfig->Write(wxT("Model"), DEFAULT_MODEL);
		this->m_currentUseModel = DEFAULT_MODEL;
	}
	else{
		this->m_currentUseModel = model;
	}
}

void ModelSelectDialog::SaveConfig(void){
	wxConfigBase::Set(new wxFileConfig(wxT(""), wxT(""), wxT("psu.ini"), wxT(""), wxCONFIG_USE_RELATIVE_PATH));

	wxConfigBase *pConfig = wxConfigBase::Get();

	if (pConfig == NULL) return;

	pConfig->SetPath(wxT("/APP"));

	// Model
	pConfig->Write(wxT("Model"), this->m_currentUseModel);

	pConfig->Flush();

}

wxBEGIN_EVENT_TABLE(ModelSelectDialog, wxDialog)
EVT_BUTTON(CID_BTN_OK, ModelSelectDialog::OnOKButton)
EVT_BUTTON(CID_BTN_CANCEL, ModelSelectDialog::OnCancelButton)
EVT_CHECKBOX(CID_CHKBOX_BYCUSTOMERPN, ModelSelectDialog::OnByCustomerPNCheckBox)
EVT_COMBOBOX(CID_CBBOX_CUSTOMER, ModelSelectDialog::OnCustomerComboBox)
EVT_COMBOBOX(CID_CBBOX_MODELNAME, ModelSelectDialog::OnModelNameComboBox)
EVT_CLOSE(ModelSelectDialog::OnDialogClose)
wxEND_EVENT_TABLE()