/**
 * @file PMBUSCMDWritePages.h
 */
#ifndef _PMBUSCMDWRITEPAGES_H_
#define _PMBUSCMDWRITEPAGES_H_

#include <vector>
#include "CommonDef.h"
#include "PMBUSCommandType.h"
#include "PMBUSHelper.h"
#include "BaseWritePage.h"

#include "Task.h"

/* 00H PAGE */
class WritePage00H : public BaseWritePage {
public :
	/**
	 * @brief Constructor.
	 */
	WritePage00H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	 * @brief Deconstructor.
	 */
	~WritePage00H();

protected :

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private :

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);
	
	wxDECLARE_EVENT_TABLE();
};

/* 01H OPERATION */
class WritePage01H : public BaseWritePage {
public:
    /**
	 * @brief Constructor.
	 */
	WritePage01H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	 * @brief Deconstructor.
	 */
	~WritePage01H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 02H ON_OFF_CONFIG */
class WritePage02H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage02H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage02H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 03H CLEAR_FAULTS */
class WritePage03H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage03H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage03H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 05H PAGE PLUS WRITE */
class WritePage05H : public BaseWritePage {
public:
	
	enum {
		CID_PAGE_COMBOBOX = 7901,
		CID_DATA_COUNT_COMBOBOX,
	};
	
	/**
	 * @brief Constructor.
	 */
	WritePage05H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	 * @brief Deconstructor.
	 */
	~WritePage05H();

protected:
	wxGridSizer *m_fieldGridSizer;

	wxBoxSizer* m_pageSizer;
	wxBoxSizer* m_cmdSizer;
	wxBoxSizer* m_dataCountSZ;

	wxStaticText *m_pageST;
	wxStaticText *m_pagePaddingST;
	wxComboBox   *m_pageCB;
	//wxTextCtrl *m_pageTC;

	wxStaticText *m_cmdST;
	wxTextCtrl *m_cmdTC;

	wxStaticText *m_dataCountST;
	wxStaticText *m_dataCountPaddingST;
	wxComboBox* m_dataCountCB;

	wxStaticText *m_data1;
	wxTextCtrl *m_data1InputValue;

	wxStaticText *m_data2;
	wxTextCtrl *m_data2InputValue;

	wxStaticText *m_padding;
	wxStaticText *m_padding2;
	wxStaticText *m_padding3;
	wxStaticText *m_padding4;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	void OnPageComboBox(wxCommandEvent& event);

	void OnDataCountComboBox(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 1BH SMBALERT_MASK */
class WritePage1BH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage1BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage1BH();

protected:

	wxStaticText *m_code;
	wxTextCtrl *m_codeInputValue;

	wxStaticText *m_mask;
	wxTextCtrl *m_maskInputValue;

	wxStaticText *m_padding;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 31H POUT_MAX */
class WritePage31H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage31H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage31H();

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 3AH FAN_CONFIG_1_2 */
class WritePage3AH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage3AH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage3AH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 3BH FAN_COMMAND_1 */
class WritePage3BH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage3BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage3BH();

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 46H IOUT_OC_FAULT_LIMIT */
class WritePage46H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage46H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage46H();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

protected:

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 4AH IOUT_OC_WARN_LIMIT */
class WritePage4AH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage4AH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage4AH();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 51H OT_WARN_LIMIT */
class WritePage51H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage51H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage51H();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 5DH IIC_OC_WARN_LIMIT */
class WritePage5DH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage5DH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage5DH();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 6AH POUT_OP_WARN_LIMIT */
class WritePage6AH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage6AH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage6AH();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 6BH PIN_OP_WARN_LIMIT */
class WritePage6BH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage6BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage6BH();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 99H MFR_ID */
class WritePage99H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage99H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage99H();

protected:

	wxTextValidator m_textValidator;

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	wxStaticText *m_hintMaxLengthST;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 9AH MFR_MODEL */
class WritePage9AH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage9AH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9AH();

protected:

	wxTextValidator m_textValidator;

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	wxStaticText *m_hintMaxLengthST;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 9BH MFR_REVISION */
class WritePage9BH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage9BH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9BH();

protected:

	wxTextValidator m_textValidator;

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	wxStaticText *m_hintMaxLengthST;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 9CH MFR_LOCATION */
class WritePage9CH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage9CH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9CH();

protected:

	wxTextValidator m_textValidator;

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	wxStaticText *m_hintMaxLengthST;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 9DH MFR_DATE */
class WritePage9DH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage9DH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9DH();

protected:

	wxTextValidator m_textValidator;

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	wxStaticText *m_hintMaxLengthST;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 9EH MFR_SERIAL */
class WritePage9EH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage9EH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9EH();

protected:

	wxTextValidator m_textValidator;

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	wxStaticText *m_hintMaxLengthST;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* C0H MFR_MAX_TEMP_1 */
class WritePageC0H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageC0H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageC0H();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* C1H MFR_MAX_TEMP_2 */
class WritePageC1H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageC1H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageC1H();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* C2H MFR_MAX_TEMP_3 */
class WritePageC2H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageC2H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageC2H();

	virtual void changeLayOutByDataFormat(unsigned int dataFormat, PMBUSCOMMAND_t *pmbuscmd);

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* D0H MFR_SERIAL */
class WritePageD0H : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageD0H(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageD0H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* DCH Read_BoxSTATUS */
class WritePageDCH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageDCH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageDCH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* DDH Black_BOX_Index */
class WritePageDDH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageDDH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageDDH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* ECH Set Point (For RFWE_24_28_1200W_SCP Model) */
class WritePageECH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageECH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageECH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	wxCheckBox *m_confirmCB;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* FAH Firmware_Update_Command */
class WritePageFAH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePageFAH(wxWindow* parent, wxString& label, bool* monitor_running, std::vector<PMBUSSendCOMMAND_t> *sendCMDVector, IOACCESS* ioaccess, unsigned int* currentIO);
	/**
	* @brief Deconstructor.
	*/
	~WritePageFAH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

	bool *m_monitor_running;
	std::vector<PMBUSSendCOMMAND_t> *m_sendCMDVector;

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif