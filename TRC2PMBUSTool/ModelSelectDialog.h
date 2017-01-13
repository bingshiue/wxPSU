/**
 * @file ModelSelectDialog.h
 */
#ifndef _MODELSELECTDIALOG_H_
#define _MODELSELECTDIALOG_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/aboutdlg.h>
#include <wx/artprov.h>
#include <wx/colordlg.h>
#include <wx/wfstream.h>
#include <wx/animate.h>
#include <wx/statline.h>
#include "wx/config.h"
#include "wx/fileconf.h"

#include "CommonDef.h"
#include "PMBUSHelper.h"
#include "Customers.h"
#include "Models.h"
#include "Customers.h"
#include "CustomerType.h"
#include "ModelType.h"

class ModelSelectDialog : public wxDialog
{
public:
	ModelSelectDialog(wxWindow *parent, CUSTOMER_TYPE_t* customerList, unsigned int customerListSize);

	~ModelSelectDialog();

	enum {
		CID_BTN_OK = 5601,
		CID_BTN_CANCEL,

		CID_CHKBOX_BYCUSTOMERPN,

		CID_CBBOX_CUSTOMER,
		CID_CBBOX_MODELNAME,
	};

private:

	unsigned long m_currentUseCustomer;
	unsigned long m_currentUseModel;

	CUSTOMER_TYPE_t* m_customerList;
	unsigned int m_customerListSize;

	MODEL_TYPE_t *m_modelList;
	unsigned int  m_modelListSize;

	// Sizer
	wxBoxSizer *m_topLevelSizer;
	wxBoxSizer *m_line1Sizer;
	wxBoxSizer *m_line2Sizer;
	wxBoxSizer *m_buttonSizer;
	wxBoxSizer *m_customerSizer;
	wxBoxSizer *m_modelNameSizer;


	// Static BMP
	wxStaticBitmap *m_acbelLogoSB;

	// By Customer P/N
	wxCheckBox *m_byCustomerPNCheckBox;

	// OK & Cancel Button
	wxButton *m_btnOK;
	wxButton *m_btnCancel;
	wxStaticText *m_paddingST;

	// Customer & Model Name Combo Box
	wxStaticText *m_customerST;
	wxStaticText *m_modelNameST;

	wxComboBox *m_customerComboBox;
	wxComboBox *m_modelNameComboBox;

	// CallBack Function 
	void OnOKButton(wxCommandEvent& event);
	void OnCancelButton(wxCommandEvent& event);

	void OnByCustomerPNCheckBox(wxCommandEvent& event);

	void OnCustomerComboBox(wxCommandEvent& event);
	void OnModelNameComboBox(wxCommandEvent& event);

	void OnDialogClose(wxCloseEvent& event);

	// Setup Function
	void SetupModelListAndSize(void);

	void SetupCustomerComboBox(void);
	void SetupModelNameComboBox(void);

	// Save & Load 
	void LoadConfig(void);
	void SaveConfig(void);

	wxDECLARE_EVENT_TABLE();
};

#endif