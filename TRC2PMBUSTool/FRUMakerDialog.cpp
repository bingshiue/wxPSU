/**
 * @file FRUMakerDialog.cpp
 */
#include "FRUMakerDialog.h"

#define FRU_MAKER_DIALOG_WIDTH   (1024)
#define FRU_MAKER_DIALOG_HEIGHT  (720)

#define DEF_PRODUCTINFO_ST_WIDTH  (160)
#define DEF_PRODUCTINFO_TC_WIDTH  (200)

#define DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH  (180)
#define DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH  (80)

#define DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH  (180)
#define DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH  (80)

FRUMakerDialog::FRUMakerDialog(wxWindow *parent, IOACCESS *ioaccess, unsigned int *currentIO) : 
wxDialog(parent, wxID_ANY, wxString(wxT("FRU Maker")), wxDefaultPosition, wxSize(FRU_MAKER_DIALOG_WIDTH, FRU_MAKER_DIALOG_HEIGHT)){

	wxIcon icon;
	icon.CopyFromBitmap(wxBITMAP_PNG(MAKER_16));

	this->SetIcon(icon);

	m_oldLog = wxLog::GetActiveTarget();
	wxLog::SetActiveTarget(this);

	this->m_ioaccess = ioaccess;
	this->m_currentIO = currentIO;

	this->outputLog = false;

	// Setup Text Validator
	DecCharIncludes = wxT("0123456789");
	HexCharIncludes = wxT("0123456789abcdefABCDEF");
	m_hexValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_hexValidator.SetCharIncludes(HexCharIncludes);

	m_decValidator.SetStyle(wxFILTER_INCLUDE_CHAR_LIST);
	m_decValidator.SetCharIncludes(DecCharIncludes);

	// Initialize Sizer 
	m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	m_productInfoAreaSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("PRODUCT INFO AREA"));
	m_multiRecordAreaSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("MULTIRECORD AREA"));
	m_powerSupplyInformationSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Power Supply Information (Record Type 0x00)"));
	m_dcOutput1SBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("DC Output 1(Record Type 0x01)"));
	m_dcOutput2SBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("DC Output 2(Record Type 0x01)"));
	m_productInfoAreaFGS = new wxFlexGridSizer(4, 4, 3, 3);
	m_maPowerSupplyInformationFGS = new wxFlexGridSizer(6, 6, 0, 0);
	m_maDCOutput1FGS = new wxFlexGridSizer(6, 6, 0, 0);
	m_maDCOutput2FGS = new wxFlexGridSizer(6, 6, 0, 0);
	m_logSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("Operation Log"));

	m_piManufacturerNameBS = new wxBoxSizer(wxHORIZONTAL);
	m_piProductNameBS = new wxBoxSizer(wxHORIZONTAL);
	m_piProductModelNumberBS = new wxBoxSizer(wxHORIZONTAL);
	m_piProductVersionBS = new wxBoxSizer(wxHORIZONTAL);
	m_piProductSerialNumberBS = new wxBoxSizer(wxHORIZONTAL);
	m_piAssetTagBS = new wxBoxSizer(wxHORIZONTAL);
	m_piFRUFileIDBS = new wxBoxSizer(wxHORIZONTAL);


	// Initilaize Components
	m_makeBTN = new wxButton(this, CID_BTN_MAKE, wxT("Make"), wxDefaultPosition, wxDefaultSize);

	m_piManufacturerNameST = new wxStaticText(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("Manufacturer Name: "), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_ST_WIDTH, -1));
	m_piManufacturerNameTC = new wxTextCtrl(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("ACBEL"), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_TC_WIDTH, -1));

	m_piProductNameST = new wxStaticText(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("Product Name: "), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_ST_WIDTH, -1));
	m_piProductNameTC = new wxTextCtrl(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("R1CA2551B"), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_TC_WIDTH, -1));

	m_piProductModelNumberST = new wxStaticText(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("Product Model Number: "), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_ST_WIDTH, -1));
	m_piProductModelNumberTC = new wxTextCtrl(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("FSF059"), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_TC_WIDTH, -1));

	m_piProductVersionST = new wxStaticText(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("Product Version: "), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_ST_WIDTH, -1));
	m_piProductVersionTC = new wxTextCtrl(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("7LAG"), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_TC_WIDTH, -1));

	m_piProductSerialNumberST = new wxStaticText(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("Product Serial Number: "), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_ST_WIDTH, -1));
	m_piProductSerialNumberTC = new wxTextCtrl(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("FSF0590S37LAGT1549000001"), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_TC_WIDTH, -1));

	m_piAssetTagST = new wxStaticText(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("Asset Tag: "), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_ST_WIDTH, -1));
	m_piAssetTagTC = new wxTextCtrl(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("0S3"), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_TC_WIDTH, -1));

	m_piFRUFileIDST = new wxStaticText(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("FRU File ID: "), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_ST_WIDTH, -1));
	m_piFRUFileIDTC = new wxTextCtrl(m_productInfoAreaSBS->GetStaticBox(), wxID_ANY, wxT("APM13V0001"), wxDefaultPosition, wxSize(DEF_PRODUCTINFO_TC_WIDTH, -1));

	m_mapsiOverallcapacityST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Overall capacity (watts): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiOverallcapacityTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("550"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiPeakVAST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Peak VA: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiPeakVATC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("825"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiInrushCurrentST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Inrush current: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiInrushCurrentTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("40"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiInrushIntervalST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Inrush Interval(ms): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiInrushIntervalTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("10"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiLowEndInputVoltageRange1ST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Low end Input voltage range 1: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiLowEndInputVoltageRange1TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("90000"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiHighEndInputVoltageRange1ST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("High end Input voltage range 1: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiHighEndInputVoltageRange1TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("264000"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiLowEndInputVoltageRange2ST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Low end Input voltage range 2: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiLowEndInputVoltageRange2TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiHighEndInputVoltageRange2ST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("High end Input voltage range 2: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiHighEndInputVoltageRange2TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiLowEndInputFrequencyRangeST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Low End Input Frequency Range: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiLowEndInputFrequencyRangeTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("47"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiHighEndInputFrequencyRangeST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("High End Input Frequency Range: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiHighEndInputFrequencyRangeTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("63"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiACDropoutToleranceST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("A/C dropout tolerance: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiACDropoutToleranceTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("12"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiBinaryFlagsST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Binary Flags: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiBinaryFlagsTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("31"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiPeakWattageHoldUpTimeST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Peak Wattage Hold Up Time: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiPeakWattageHoldUpTimeTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("15"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiPeakWattagePeakCapacityST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Peak Wattage Peak Capacity: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiPeakWattagePeakCapacityTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("825"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiCombinedWattageVoltage1ST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Combined Wattage Voltage 1: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiCombinedWattageVoltage1TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiCombinedWattageVoltage2ST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Combined Wattage Voltage 2: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiCombinedWattageVoltage2TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiTotalCombinedWattageST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("Total Combined Wattage: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiTotalCombinedWattageTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiRPSST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("RPS: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiRPSTC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("15"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_maDCOutput1OutputNumberST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Output Number: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1OutputNumberTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1NominalVoltageST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Nominal voltage (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1NominalVoltageTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("12000"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MaximumNegativeVoltageDeviationST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Maximum negative voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MaximumNegativeVoltageDeviationTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("11640"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MaximumPositiveVoltageDeviationST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Maximum positive voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MaximumPositiveVoltageDeviationTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("12360"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1RippleAndNoiseST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Ripple and Noise pk-pk 10Hz to 30 MHz (mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1RippleAndNoiseTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("120"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MinimumCurrentDrawST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Minimum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MinimumCurrentDrawTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MaximumCurrentDrawST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Maximum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MaximumCurrentDrawTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("45833"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2OutputNumberST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Output Number: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2OutputNumberTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2NominalVoltageST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Nominal voltage (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2NominalVoltageTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("12000"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MaximumNegativeVoltageDeviationST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Maximum negative voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MaximumNegativeVoltageDeviationTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("11640"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MaximumPositiveVoltageDeviationST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Maximum positive voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MaximumPositiveVoltageDeviationTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("12360"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2RippleAndNoiseST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Ripple and Noise pk-pk 10Hz to 30 MHz (mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2RippleAndNoiseTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("120"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MinimumCurrentDrawST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Minimum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MinimumCurrentDrawTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MaximumCurrentDrawST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Maximum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MaximumCurrentDrawTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("45833"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	// Log TextCtrl
	m_logTC = new PMBUSLogTextCtrl(m_logSBS->GetStaticBox(), wxID_ANY);

	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	this->m_logTC->SetFont(font);

	// Add Components To Sizer
	// --- Product Info Area ---
	/* Product Info Area : Manufacturer Name */
	m_productInfoAreaFGS->Add(m_piManufacturerNameST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_productInfoAreaFGS->Add(m_piManufacturerNameTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	
	//m_productInfoAreaSBS->Add(m_piManufacturerNameBS);
	/* */

	/* Product Info Area : Product Name */
	m_productInfoAreaFGS->Add(m_piProductNameST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductNameTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductNameBS);
	/* */

	/* Product Info Area : Product Model Number */
	m_productInfoAreaFGS->Add(m_piProductModelNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductModelNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductModelNumberBS);
	/* */

	/* Product Info Area : Product Version */
	m_productInfoAreaFGS->Add(m_piProductVersionST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductVersionTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductVersionBS);
	/* */

	/* Product Info Area : Product Seria lNumber */
	m_productInfoAreaFGS->Add(m_piProductSerialNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductSerialNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductSerialNumberBS);
	/* */

	/* Product Info Area : Asset Tag */
	m_productInfoAreaFGS->Add(m_piAssetTagST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_productInfoAreaFGS->Add(m_piAssetTagTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piAssetTagBS);
	/* */

	/* Product Info Area : FRU File ID */
	m_productInfoAreaFGS->Add(m_piFRUFileIDST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_productInfoAreaFGS->Add(m_piFRUFileIDTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_productInfoAreaSBS->Add(m_productInfoAreaFGS);
	/* */

	// --- MultiRecord Area ---
	m_maPowerSupplyInformationFGS->Add(m_mapsiOverallcapacityST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiOverallcapacityTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakVAST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakVATC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushCurrentST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushCurrentTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushIntervalST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushIntervalTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange1ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange1TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange1ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange1TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange2ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange2TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange2ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange2TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputFrequencyRangeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputFrequencyRangeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputFrequencyRangeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputFrequencyRangeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiACDropoutToleranceST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiACDropoutToleranceTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiBinaryFlagsST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiBinaryFlagsTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattageHoldUpTimeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattageHoldUpTimeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattagePeakCapacityST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattagePeakCapacityTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage1ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage1TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage2ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage2TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiTotalCombinedWattageST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiTotalCombinedWattageTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiRPSST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiRPSTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_powerSupplyInformationSBS->Add(m_maPowerSupplyInformationFGS);

	m_multiRecordAreaSBS->Add(m_powerSupplyInformationSBS, wxSizerFlags(0).Expand().Border(wxDirection::wxALL, 5));
	
	m_maDCOutput1FGS->Add(m_maDCOutput1OutputNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1OutputNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1NominalVoltageST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1NominalVoltageTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumNegativeVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumNegativeVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumPositiveVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumPositiveVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1RippleAndNoiseST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1RippleAndNoiseTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MinimumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MinimumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	
	m_dcOutput1SBS->Add(m_maDCOutput1FGS);

	m_multiRecordAreaSBS->Add(m_dcOutput1SBS, wxSizerFlags(0).Expand().Border(wxDirection::wxALL, 5));

	m_maDCOutput2FGS->Add(m_maDCOutput2OutputNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2OutputNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2NominalVoltageST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2NominalVoltageTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumNegativeVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumNegativeVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumPositiveVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumPositiveVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2RippleAndNoiseST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2RippleAndNoiseTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MinimumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MinimumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxDirection::wxALL, 0));


	m_dcOutput2SBS->Add(m_maDCOutput2FGS);

	m_multiRecordAreaSBS->Add(m_dcOutput2SBS, wxSizerFlags(0).Expand().Border(wxDirection::wxALL, 5));


	m_logSBS->Add(m_logTC, wxSizerFlags(1).Expand().Border(wxDirection::wxALL, 5));
	
	m_topLevelSizer->Add(m_productInfoAreaSBS, wxSizerFlags(0).Expand().Border(wxDirection::wxALL, 5));
	m_topLevelSizer->Add(m_multiRecordAreaSBS, wxSizerFlags(0).Expand().Border(wxDirection::wxALL, 5));
	m_topLevelSizer->Add(m_makeBTN, wxSizerFlags(0).Expand());
	m_topLevelSizer->Add(m_logSBS, wxSizerFlags(1).Expand().Border(wxDirection::wxALL, 5));

	SetSizer(m_topLevelSizer);

}

FRUMakerDialog::~FRUMakerDialog(){

	wxLog::SetActiveTarget(m_oldLog);

}

void FRUMakerDialog::OnBtnMAKE(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT(MSG_DEBUG, "OnBtnMAKE");
}

void FRUMakerDialog::OnDialogClose(wxCloseEvent& event){

	PSU_DEBUG_PRINT(MSG_DEBUG, "OnDialogClose");

	this->EndModal(wxID_CANCEL);

}

void FRUMakerDialog::DoLogLine(wxLogLevel level, wxTextCtrl *text, const wxString& timestr, const wxString& threadstr, const wxString& msg)
{

	switch (level) {

	case wxLOG_FatalError:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
	case wxLOG_Error:
		text->SetDefaultStyle(wxTextAttr(*wxRED, *wxWHITE));
		break;
		//case wxLOG_Warning:
		//break;
		//case wxLOG_Message:
		//break;
		//case wxLOG_Status:
		//break;
		//case wxLOG_Info:
		//break;
		//case wxLOG_Debug:
		//break;

	default:
		text->SetDefaultStyle(wxTextAttr(*wxBLUE, *wxWHITE));
		break;
	}

#ifdef _DEBUG

	//text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));
	text->AppendText(wxString::Format("%-8s   %s", threadstr, msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s %10s           %s", timestr, threadstr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#else
	//text->AppendText(wxString::Format("%9s           %s", timestr, msg));
	text->AppendText(wxString::Format("%-s", msg));

#if 0
	// If enable output log to file
	if (this->m_appSettings.m_logToFile == Generic_Enable){
		if (this->m_logFileTextOutputStream){
			*this->m_logFileTextOutputStream << wxString::Format("%9s           %s", timestr, msg);// << endl;
			(*this->m_logFileTextOutputStream).Flush();
		}
	}
#endif

#endif
}

void FRUMakerDialog::DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info)
{
	// let the default GUI logger treat warnings and errors as they should be
	// more noticeable than just another line in the log window and also trace
	// messages as there may be too many of them
#if 0
	if (level <= wxLOG_Warning || level == wxLOG_Trace)
	{
		m_oldLogger->LogRecord(level, msg, info);
		return;
	}
#endif

	DoLogLine(
		level,
		this->m_logTC,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		: wxString::Format("%lx", info.threadId),
		msg + "\n"
		);

}

wxBEGIN_EVENT_TABLE(FRUMakerDialog, wxDialog)
EVT_BUTTON(CID_BTN_MAKE, FRUMakerDialog::OnBtnMAKE)
EVT_CLOSE(FRUMakerDialog::OnDialogClose)
wxEND_EVENT_TABLE()