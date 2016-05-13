 /**
  * @file STDPage.h
  */
#ifndef _STDPAGE_H_
#define _STDPAGE_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/statline.h>

enum {
	PAGE_SELECT_COMBO = 2001
};

class STDPage : public wxPanel {
public:
	/**
	 * @brief Constructor.
	 */
	STDPage(wxWindow* parent);
	/**
	 * @brief Deconstructor.
	 */
	~STDPage();

protected:

private:
	/**< Static Box */
	wxStaticBox *m_staticBox;
	
	/**< Box Sizer */
	wxStaticBoxSizer *m_staticBoxlSizer;

	wxGridSizer *m_gridSizer_1;
	wxGridSizer *m_gridSizer_2;

	wxBoxSizer *m_horizonSizer1;
	wxBoxSizer *m_horizonSizer2;
	wxBoxSizer *m_horizonSizer3;
	wxBoxSizer *m_horizonSizer4;

	/**< Parent */
	wxWindow *m_parent;

	/**< Combo Box */
	wxStaticText *m_stPage;
	wxComboBox *m_comboBox;

	/**< Static Line 1 */
	wxStaticLine *m_staticLine_1;

	/**< Static Line 2 */
	wxStaticLine *m_staticLine_2;

	/**< Static Line 3 */
	wxStaticLine *m_staticLine_3;

	/**< Padding Static Text */
	wxStaticText *m_stPadding_1;
	wxStaticText *m_stPadding_2;
	wxStaticText *m_stPadding_3;
	wxStaticText *m_stPadding_4;
	wxStaticText *m_stPadding_5;

	/**< PIN Static Text */
	wxStaticText *m_stPIN;

	/**< POUT Static Text */
	wxStaticText *m_stPOUT;

	/**< VIN Static Text */
	wxStaticText *m_stVIN;

	/**< IIN Static Text */
	wxStaticText *m_stIIN;

	/**< VOUT Static Text */
	wxStaticText *m_stVOUT;

	/**< IOUT Static Text */
	wxStaticText *m_stIOUT;

	/**< VoSBY Static Text */
	wxStaticText *m_stVoSBY;

	/**< IoSBY Static Text */
	wxStaticText *m_stIoSBY;


	/**< PIN TextCtrl  */
	wxTextCtrl *m_tcPIN;

	/**< POUT Static TextCtrl */
	wxTextCtrl *m_tcPOUT;

	/**< VIN Static TextCtrl */
	wxTextCtrl *m_tcVIN;

	/**< IIN Static TextCtrl */
	wxTextCtrl *m_tcIIN;

	/**< VOUT Static TextCtrl */
	wxTextCtrl *m_tcVOUT;

	/**< IOUT Static TextCtrl */
	wxTextCtrl *m_tcIOUT;

	/**< VoSBY Static TextCtrl */
	wxTextCtrl *m_tcVoSBY;

	/**< IoSBY Static TextCtrl */
	wxTextCtrl *m_tcIoSBY;


	/**< VCAP Static Text */
	wxStaticText *m_stVCAP;

	/**< AMD(8D) Static Text */
	wxStaticText *m_stAMD8D;

	/**< SEC(8E) Static Text */
	wxStaticText *m_stSEC8E;

	/**< PRI(8F) Static Text */
	wxStaticText *m_stPRI8F;

	/**< FAN1 Static Text */
	wxStaticText *m_stFAN1;

	/**< FAN2 Static Text */
	wxStaticText *m_stFAN2;

	/**< FAN3 Static Text */
	wxStaticText *m_stFAN3;

	/**< FAN4 Static Text */
	wxStaticText *m_stFAN4;


	/**< VCAP TextCtrl  */
	wxTextCtrl *m_tcVCAP;

	/**< AMD(8D) TextCtrl */
	wxTextCtrl *m_tcAMD8D;

	/**< SEC(8E) TextCtrl */
	wxTextCtrl *m_tcSEC8E;

	/**< PRI(8F) TextCtrl */
	wxTextCtrl *m_tcPRI8F;

	/**< FAN1 TextCtrl */
	wxTextCtrl *m_tcFAN1;

	/**< FAN2 TextCtrl */
	wxTextCtrl *m_tcFAN2;

	/**< FAN3 TextCtrl */
	wxTextCtrl *m_tcFAN3;

	/**< FAN4 TextCtrl */
	wxTextCtrl *m_tcFAN4;

};


#endif

