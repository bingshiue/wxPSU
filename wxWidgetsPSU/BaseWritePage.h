/**
 * @file BaseWritePage.h
 */
#ifndef _BASEWRITEPAGE_H_
#define _BASEWRITEPAGE_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/statline.h>

class BaseWritePage : public wxPanel {
public:
	/**
	 * @brief Constructor.
	 */
	BaseWritePage(wxWindow* parent, wxString& label);
	/**
	 * @brief Deconstructor.
	 */
	~BaseWritePage();

protected:
	enum {
		PADDING_DEFAULT_HEIGHT = 10,
		PADDING_DEFAULT_WIDTH = 50
	};

	enum {
		CID_RADIO_BOX_COOK = 8001,
		CID_RADIO_BOX_RAW
	};

	enum {
		CID_BUTTON_WRITE = 9001,
	};

	wxString HexCharIncludes;

	wxString DecimalCharIncludes;

	void BaseLayOut(void);

	void SetupValidator(void);

	/**<  Label */
	wxString m_Label;

	/**< Static Box */
	wxStaticBox *m_staticBox;

	/**< Box Sizer */
	wxStaticBoxSizer *m_staticBoxlSizer;

	wxFlexGridSizer *m_flexGridSizer;

	wxGridSizer *m_gridSizer_1;
	wxGridSizer *m_gridSizer_2;

	wxBoxSizer *m_horizonSizer1;
	wxBoxSizer *m_horizonSizer2;
	wxBoxSizer *m_horizonSizer3;
	wxBoxSizer *m_horizonSizer4;

	/**< Parent */
	wxWindow *m_parent;

	/**< Radio Button */
	wxRadioButton* m_cookRadioButton;
	wxRadioButton* m_rawRadioButton;

	/**< Button */
	wxButton* m_writeButton;

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

	/**< wxValidator */
	wxTextValidator m_numberValidator;
	wxTextValidator m_hexValidator;

private:

};

#endif