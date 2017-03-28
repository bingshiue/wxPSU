/**
 * @file FRUMakerDialog.h
 */
#ifndef _FRU_MAKER_DIALOG_H_
#define _FRU_MAKER_DIALOG_H_

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

#include "CommonDef.h"
#include "FRU.h"
#include "IOACCESS.h"
#include "PMBUSHelper.h"
#include "PMBUSLogTextCtrl.h"
#include "Task.h"
#include "version.h"

#define MAX_FRU_FILE_SIZE  256 // Max FRU File Size

class FRUMakerDialog : public wxDialog, private wxLog
{
public:
	FRUMakerDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO);

	~FRUMakerDialog();

	enum {
		CID_BTN_MAKE, /**< Make Button */
	};

protected:

	virtual void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) wxOVERRIDE;


private:

	IOACCESS *m_ioaccess;
	unsigned int *m_currentIO;

	bool m_outputLog;

	wxLog* m_oldLog;

	bool outputLog;

	unsigned char m_fruBinaryContent[MAX_FRU_FILE_SIZE];/**< Buffer for Save FRU Binary File Content */

	// Sizer
	wxBoxSizer *m_topLevelSizer;
	wxStaticBoxSizer *m_productInfoAreaSBS;
	wxStaticBoxSizer *m_multiRecordAreaSBS;
	wxStaticBoxSizer *m_powerSupplyInformationSBS;
	wxStaticBoxSizer *m_dcOutput1SBS;
	wxStaticBoxSizer *m_dcOutput2SBS;

	wxStaticBoxSizer *m_logSBS;

	wxBoxSizer *m_piManufacturerNameBS;
	wxBoxSizer *m_piProductNameBS;
	wxBoxSizer *m_piProductModelNumberBS;
	wxBoxSizer *m_piProductVersionBS;
	wxBoxSizer *m_piProductSerialNumberBS;
	wxBoxSizer *m_piAssetTagBS;
	wxBoxSizer *m_piFRUFileIDBS;

	wxFlexGridSizer *m_productInfoAreaFGS;
	wxFlexGridSizer *m_maPowerSupplyInformationFGS;
	wxFlexGridSizer *m_maDCOutput1FGS;
	wxFlexGridSizer *m_maDCOutput2FGS;

	// Components
	wxButton *m_makeBTN;

	wxStaticText *m_piManufacturerNameST;
	wxTextCtrl *m_piManufacturerNameTC;

	wxStaticText *m_piProductNameST;
	wxTextCtrl *m_piProductNameTC;

	wxStaticText *m_piProductModelNumberST;
	wxTextCtrl *m_piProductModelNumberTC;

	wxStaticText *m_piProductVersionST;
	wxTextCtrl *m_piProductVersionTC;

	wxStaticText *m_piProductSerialNumberST;
	wxTextCtrl *m_piProductSerialNumberTC;

	wxStaticText *m_piAssetTagST;
	wxTextCtrl *m_piAssetTagTC;

	wxStaticText *m_piFRUFileIDST;
	wxTextCtrl *m_piFRUFileIDTC;

	wxStaticText *m_mapsiOverallcapacityST;
	wxTextCtrl *m_mapsiOverallcapacityTC;

	wxStaticText *m_mapsiPeakVAST;
	wxTextCtrl *m_mapsiPeakVATC;

	wxStaticText *m_mapsiInrushCurrentST;
	wxTextCtrl *m_mapsiInrushCurrentTC;

	wxStaticText *m_mapsiInrushIntervalST;
	wxTextCtrl *m_mapsiInrushIntervalTC;

	wxStaticText *m_mapsiLowEndInputVoltageRange1ST;
	wxTextCtrl *m_mapsiLowEndInputVoltageRange1TC;

	wxStaticText *m_mapsiHighEndInputVoltageRange1ST;
	wxTextCtrl *m_mapsiHighEndInputVoltageRange1TC;

	wxStaticText *m_mapsiLowEndInputVoltageRange2ST;
	wxTextCtrl *m_mapsiLowEndInputVoltageRange2TC;

	wxStaticText *m_mapsiHighEndInputVoltageRange2ST;
	wxTextCtrl *m_mapsiHighEndInputVoltageRange2TC;

	wxStaticText *m_mapsiLowEndInputFrequencyRangeST;
	wxTextCtrl *m_mapsiLowEndInputFrequencyRangeTC;

	wxStaticText *m_mapsiHighEndInputFrequencyRangeST;
	wxTextCtrl *m_mapsiHighEndInputFrequencyRangeTC;

	wxStaticText *m_mapsiACDropoutToleranceST;
	wxTextCtrl *m_mapsiACDropoutToleranceTC;

	wxStaticText *m_mapsiBinaryFlagsST;
	wxTextCtrl *m_mapsiBinaryFlagsTC;

	wxStaticText *m_mapsiPeakWattageHoldUpTimeST;
	wxTextCtrl *m_mapsiPeakWattageHoldUpTimeTC;

	wxStaticText *m_mapsiPeakWattagePeakCapacityST;
	wxTextCtrl *m_mapsiPeakWattagePeakCapacityTC;

	wxStaticText *m_mapsiCombinedWattageVoltage1ST;
	wxTextCtrl *m_mapsiCombinedWattageVoltage1TC;

	wxStaticText *m_mapsiCombinedWattageVoltage2ST;
	wxTextCtrl *m_mapsiCombinedWattageVoltage2TC;

	wxStaticText *m_mapsiTotalCombinedWattageST;
	wxTextCtrl *m_mapsiTotalCombinedWattageTC;

	wxStaticText *m_mapsiRPSST;
	wxTextCtrl *m_mapsiRPSTC;

	wxStaticText *m_maDCOutput1OutputNumberST;
	wxTextCtrl *m_maDCOutput1OutputNumberTC;

	wxStaticText *m_maDCOutput1NominalVoltageST;
	wxTextCtrl *m_maDCOutput1NominalVoltageTC;

	wxStaticText *m_maDCOutput1MaximumNegativeVoltageDeviationST;
	wxTextCtrl *m_maDCOutput1MaximumNegativeVoltageDeviationTC;

	wxStaticText *m_maDCOutput1MaximumPositiveVoltageDeviationST;
	wxTextCtrl *m_maDCOutput1MaximumPositiveVoltageDeviationTC;

	wxStaticText *m_maDCOutput1RippleAndNoiseST;
	wxTextCtrl *m_maDCOutput1RippleAndNoiseTC;

	wxStaticText *m_maDCOutput1MinimumCurrentDrawST;
	wxTextCtrl *m_maDCOutput1MinimumCurrentDrawTC;

	wxStaticText *m_maDCOutput1MaximumCurrentDrawST;
	wxTextCtrl *m_maDCOutput1MaximumCurrentDrawTC;

	wxStaticText *m_maDCOutput2OutputNumberST;
	wxTextCtrl *m_maDCOutput2OutputNumberTC;

	wxStaticText *m_maDCOutput2NominalVoltageST;
	wxTextCtrl *m_maDCOutput2NominalVoltageTC;

	wxStaticText *m_maDCOutput2MaximumNegativeVoltageDeviationST;
	wxTextCtrl *m_maDCOutput2MaximumNegativeVoltageDeviationTC;

	wxStaticText *m_maDCOutput2MaximumPositiveVoltageDeviationST;
	wxTextCtrl *m_maDCOutput2MaximumPositiveVoltageDeviationTC;

	wxStaticText *m_maDCOutput2RippleAndNoiseST;
	wxTextCtrl *m_maDCOutput2RippleAndNoiseTC;

	wxStaticText *m_maDCOutput2MinimumCurrentDrawST;
	wxTextCtrl *m_maDCOutput2MinimumCurrentDrawTC;

	wxStaticText *m_maDCOutput2MaximumCurrentDrawST;
	wxTextCtrl *m_maDCOutput2MaximumCurrentDrawTC;

	PMBUSLogTextCtrl *m_logTC;

	// TextValidator
	wxString DecCharIncludes;
	wxString HexCharIncludes;
	wxTextValidator m_hexValidator;
	wxTextValidator m_decValidator;

	void DoLogLine(
		wxLogLevel level,
		wxTextCtrl *text,
		const wxString& timestr,
		const wxString& threadstr,
		const wxString& msg);

	void OnBtnMAKE(wxCommandEvent& event);
	void OnDialogClose(wxCloseEvent& event);

	wxDECLARE_EVENT_TABLE();
};


#endif