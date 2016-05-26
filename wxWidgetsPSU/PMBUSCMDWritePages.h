/**
 * @file PMBUSCMDWritePages.h
 */
#ifndef _PMBUSCMDWRITEPAGES_H_
#define _PMBUSCMDWRITEPAGES_H_

#include "CommonDef.h"
#include "PMBUSHelper.h"
#include "BaseWritePage.h"

/* 00H PAGE */
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

/* 01H OPERATION */
class WritePage01H : public BaseWritePage {
public:
    /**
	 * @brief Constructor.
	 */
	WritePage01H(wxWindow* parent, wxString& label);
	/**
	 * @brief Deconstructor.
	 */
	~WritePage01H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage02H(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage02H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage03H(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage03H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

/* 1BH SMBALERT_MASK */
class WritePage1BH : public BaseWritePage {
public:
	/**
	* @brief Constructor.
	*/
	WritePage1BH(wxWindow* parent, wxString& label);
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
	WritePage3AH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage3AH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage3BH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage3BH();

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

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
	WritePage51H(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage51H();

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

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
	WritePage5DH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage5DH();

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

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
	WritePage6AH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage6AH();

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

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
	WritePage6BH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage6BH();

protected:

	wxStaticText *m_hintName;

	wxStaticText *m_scale;

	wxTextCtrl *m_inputValue;
	wxTextCtrl *m_scaleValue;

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
	WritePage99H(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage99H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage9AH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9AH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage9BH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9BH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage9CH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9CH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage9DH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9DH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePage9EH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePage9EH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePageD0H(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePageD0H();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePageDCH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePageDCH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePageDDH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePageDDH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

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
	WritePageFAH(wxWindow* parent, wxString& label);
	/**
	* @brief Deconstructor.
	*/
	~WritePageFAH();

protected:

	wxStaticText *m_hintName;
	wxTextCtrl *m_inputValue;

private:

	void OnRadioButtonCook(wxCommandEvent& event);

	void OnRadioButtonRaw(wxCommandEvent& event);

	void OnButtonWrite(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

#endif