/**
 * @file PMBUSCMDWritePages.h
 */
#ifndef _PMBUSCMDWRITEPAGES_H_
#define _PMBUSCMDWRITEPAGES_H_

#include "CommonDef.h"
#include "BaseWritePage.h"

class WritePage00H : public BaseWritePage {
public :
	/**
	 * @brief Constructor.
	 */
	WritePage00H(wxWindow* parent, wxString& label);
	/**
	 * @brief Deconstructor.
	 */
	~WritePage00H();

protected :

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

private :

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);
	
	wxDECLARE_EVENT_TABLE();
};

#endif