/**
 * @file PMBUSCMDReadPages.h
 */
#ifndef _PMBUSCMDREADPAGES_H_
#define _PMBUSCMDREADPAGES_H_

#include <vector>
#include "CommonDef.h"
#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "BaseReadPage.h"

#include "Task.h"

/* 06H PAGE_PLUS_WRITE */
class ReadPage06H : public BaseReadPage {
public:

	enum {
		CID_BLOCK_SIZE_COMBOBOX = 6701,
	};

	/**
	 * @brief Constructor.
	 */
	ReadPage06H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	 * @brief Deconstructor.
	 */
	~ReadPage06H();

protected:

	wxBoxSizer   *m_blockSizeSizer;
	wxBoxSizer   *m_data1Sizer;

	wxStaticText *m_blockSizeST;
	wxStaticText *m_blockSizePaddingST;
	wxComboBox   *m_blockSizeCB;

	wxStaticText *m_page;
	wxTextCtrl *m_pageInputValue;

	wxStaticText *m_cmd;
	wxTextCtrl *m_cmdInputValue;

	wxStaticText *m_data1ST;
	wxTextCtrl *m_data1InputValue;

	wxStaticText *m_padding;
	wxStaticText *m_padding2;
	wxStaticText *m_padding3;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnBlockSizeCB(wxCommandEvent& event);

	void OnButtonSet(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 1AH QUERY */
class ReadPage1AH : public BaseReadPage {
public:
	/**
	* @brief Constructor.
	*/
	ReadPage1AH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~ReadPage1AH();

protected:

	wxStaticText *m_cmd;
	wxTextCtrl *m_cmdInputValue;

	wxStaticText *m_padding;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonSet(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 1BH SMBALERT_MASK */
class ReadPage1BH : public BaseReadPage {
public:
	/**
	* @brief Constructor.
	*/
	ReadPage1BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~ReadPage1BH();

protected:

	wxStaticText *m_cmd;
	wxTextCtrl *m_cmdInputValue;

	wxStaticText *m_padding;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonSet(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 30H COEFFICIENTS */
class ReadPage30H : public BaseReadPage {
public:
	/**
	* @brief Constructor.
	*/
	ReadPage30H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~ReadPage30H();

protected:

	wxStaticText *m_cmd;
	wxTextCtrl *m_cmdInputValue;

	wxStaticText *m_rw;
	wxTextCtrl *m_rwInputValue;

	wxStaticText *m_padding;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonSet(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};


#endif