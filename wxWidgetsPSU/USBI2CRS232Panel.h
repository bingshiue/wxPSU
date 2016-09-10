/**
 * @file USBI2CRS232Panel.h
 */
#ifndef _USBI2CRS232PANEL_H_
#define _USBI2CRS232PANEL_H_

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

#include "Task.h"
#include "PMBUSHelper.h"
#include "USBAdaptorSetting.h"

class USBI2CRS232Panel : public wxPanel {
public:

	enum {
		CID_SMBUS_CHKBOX = 5050,
	};

	enum {
		CID_UART_BUADRATE_CHKBOX = 5080,
		CID_UART_DATABITS_CHKBOX,
		CID_UART_STOPBITS_CHKBOX,
		CID_UART_PARITYCHK_CHKBOX
	};


	/**
	* @brief Constructor.
	*/
	USBI2CRS232Panel(wxWindow* parent, IOACCESS* ioaccess, unsigned int* currentUseIO);
	/**
	* @brief Deconstructor.
	*/
	~USBI2CRS232Panel();

	wxBoxSizer *m_topLevelSizer;
	wxFlexGridSizer* m_fgSizer1;
	wxFlexGridSizer* m_fgSizer2;
	wxStaticBoxSizer *m_i2cportSB;
	wxStaticBoxSizer *m_rs232portSB;

	wxTextValidator m_decimalValidator;

	/* I2C Port */
	wxStaticText *m_i2cBitRateST;
	wxComboBox *m_i2cBitRateCB;
	wxCheckBox *m_smbusCheckBox;

	wxStaticText *m_commBusTimeoutST;
	wxTextCtrl *m_commTC;
	wxTextCtrl *m_BusTimeoutTC;

	wxStaticText *m_i2cRecvBuffSizeST;
	wxTextCtrl *m_i2cRecvBuffSizeTC;

	/* RS232 Port */
	wxStaticText *m_rs232PortNumberST;
	wxComboBox *m_rs232PortNumberCB;

	wxStaticText *m_rs232BuadRateST;
	wxComboBox *m_rs232BuadRateCB;

	wxStaticText *m_rs232DataBitsST;
	wxComboBox *m_rs232DataBitsCB;

	wxStaticText *m_rs232StopBitsST;
	wxComboBox *m_rs232StopBitsCB;

	wxStaticText *m_rs232ParityCheckST;
	wxComboBox *m_rs232ParityCheckCB;

	wxStaticText *m_rs232RecvBuffSizeST;
	wxTextCtrl *m_rs232RecvBuffSizeTC;

	unsigned long i2cBitRateSpeedItemArray[I2C_BIT_RATE_SPEED_ITEM_SIZE];

private:

	IOACCESS *m_ioaccess;
	unsigned int *m_currentUseIO;

	void SendUARTSettingAgent(void);

	void OnSMBUSCheckBox(wxCommandEvent& event);

	void OnUARTBuadRateCheckBox(wxCommandEvent& event);
	void OnUARTDataBitsCheckBox(wxCommandEvent& event);
	void OnUARTStopBitsCheckBox(wxCommandEvent& event);
	void OnUARTParityCheckCheckBox(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

};


#endif