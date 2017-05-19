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
	icon.CopyFromBitmap(LOAD_PNG_RESOURCE(maker_16));

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
	m_mapsiLowEndInputVoltageRange1TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("9000"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

	m_mapsiHighEndInputVoltageRange1ST = new wxStaticText(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("High end Input voltage range 1: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_ST_WIDTH, -1));
	m_mapsiHighEndInputVoltageRange1TC = new wxTextCtrl(m_powerSupplyInformationSBS->GetStaticBox(), wxID_ANY, wxT("26400"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_POWER_SUPPLY_INFOMATION_TC_WIDTH, -1));

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
	m_maDCOutput1NominalVoltageTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("1200"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MaximumNegativeVoltageDeviationST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Maximum negative voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MaximumNegativeVoltageDeviationTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("1164"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MaximumPositiveVoltageDeviationST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Maximum positive voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MaximumPositiveVoltageDeviationTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("1236"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1RippleAndNoiseST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Ripple and Noise pk-pk 10Hz to 30 MHz (mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1RippleAndNoiseTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("120"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MinimumCurrentDrawST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Minimum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MinimumCurrentDrawTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput1MaximumCurrentDrawST = new wxStaticText(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("Maximum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput1MaximumCurrentDrawTC = new wxTextCtrl(m_dcOutput1SBS->GetStaticBox(), wxID_ANY, wxT("45833"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2OutputNumberST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Output Number: "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2OutputNumberTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("130"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2NominalVoltageST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Nominal voltage (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2NominalVoltageTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("1200"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MaximumNegativeVoltageDeviationST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Maximum negative voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MaximumNegativeVoltageDeviationTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("1164"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MaximumPositiveVoltageDeviationST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Maximum positive voltage deviation (10 mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MaximumPositiveVoltageDeviationTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("1236"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2RippleAndNoiseST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Ripple and Noise pk-pk 10Hz to 30 MHz (mV): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2RippleAndNoiseTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("120"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MinimumCurrentDrawST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Minimum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MinimumCurrentDrawTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("0"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	m_maDCOutput2MaximumCurrentDrawST = new wxStaticText(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("Maximum current draw (mA): "), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_ST_WIDTH, -1));
	m_maDCOutput2MaximumCurrentDrawTC = new wxTextCtrl(m_dcOutput2SBS->GetStaticBox(), wxID_ANY, wxT("3000"), wxDefaultPosition, wxSize(DEF_MULTIRECORD_DC_OUTPUT_TC_WIDTH, -1));

	// Log TextCtrl
	m_logTC = new PMBUSLogTextCtrl(m_logSBS->GetStaticBox(), wxID_ANY);

	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

	this->m_logTC->SetFont(font);

	// Add Components To Sizer
	// --- Product Info Area ---
	/* Product Info Area : Manufacturer Name */
	m_productInfoAreaFGS->Add(m_piManufacturerNameST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_productInfoAreaFGS->Add(m_piManufacturerNameTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	
	//m_productInfoAreaSBS->Add(m_piManufacturerNameBS);
	/* */

	/* Product Info Area : Product Name */
	m_productInfoAreaFGS->Add(m_piProductNameST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductNameTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductNameBS);
	/* */

	/* Product Info Area : Product Model Number */
	m_productInfoAreaFGS->Add(m_piProductModelNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductModelNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductModelNumberBS);
	/* */

	/* Product Info Area : Product Version */
	m_productInfoAreaFGS->Add(m_piProductVersionST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductVersionTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductVersionBS);
	/* */

	/* Product Info Area : Product Seria lNumber */
	m_productInfoAreaFGS->Add(m_piProductSerialNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_productInfoAreaFGS->Add(m_piProductSerialNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piProductSerialNumberBS);
	/* */

	/* Product Info Area : Asset Tag */
	m_productInfoAreaFGS->Add(m_piAssetTagST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_productInfoAreaFGS->Add(m_piAssetTagTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	//m_productInfoAreaSBS->Add(m_piAssetTagBS);
	/* */

	/* Product Info Area : FRU File ID */
	m_productInfoAreaFGS->Add(m_piFRUFileIDST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_productInfoAreaFGS->Add(m_piFRUFileIDTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_productInfoAreaSBS->Add(m_productInfoAreaFGS);
	/* */

	// --- MultiRecord Area ---
	m_maPowerSupplyInformationFGS->Add(m_mapsiOverallcapacityST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiOverallcapacityTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakVAST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakVATC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushCurrentST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushCurrentTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushIntervalST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiInrushIntervalTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange1ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange1TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange1ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange1TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange2ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputVoltageRange2TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange2ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputVoltageRange2TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputFrequencyRangeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiLowEndInputFrequencyRangeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputFrequencyRangeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiHighEndInputFrequencyRangeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiACDropoutToleranceST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiACDropoutToleranceTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiBinaryFlagsST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiBinaryFlagsTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattageHoldUpTimeST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattageHoldUpTimeTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattagePeakCapacityST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiPeakWattagePeakCapacityTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage1ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage1TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage2ST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiCombinedWattageVoltage2TC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiTotalCombinedWattageST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiTotalCombinedWattageTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maPowerSupplyInformationFGS->Add(m_mapsiRPSST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maPowerSupplyInformationFGS->Add(m_mapsiRPSTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_powerSupplyInformationSBS->Add(m_maPowerSupplyInformationFGS);

	m_multiRecordAreaSBS->Add(m_powerSupplyInformationSBS, wxSizerFlags(0).Expand().Border(wxALL, 5));
	
	m_maDCOutput1FGS->Add(m_maDCOutput1OutputNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1OutputNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1NominalVoltageST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1NominalVoltageTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumNegativeVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumNegativeVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumPositiveVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumPositiveVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1RippleAndNoiseST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1RippleAndNoiseTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MinimumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MinimumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput1FGS->Add(m_maDCOutput1MaximumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	
	m_dcOutput1SBS->Add(m_maDCOutput1FGS);

	m_multiRecordAreaSBS->Add(m_dcOutput1SBS, wxSizerFlags(0).Expand().Border(wxALL, 5));

	m_maDCOutput2FGS->Add(m_maDCOutput2OutputNumberST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2OutputNumberTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2NominalVoltageST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2NominalVoltageTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumNegativeVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumNegativeVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumPositiveVoltageDeviationST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumPositiveVoltageDeviationTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2RippleAndNoiseST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2RippleAndNoiseTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MinimumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MinimumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));

	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumCurrentDrawST, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));
	m_maDCOutput2FGS->Add(m_maDCOutput2MaximumCurrentDrawTC, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxALL, 0));


	m_dcOutput2SBS->Add(m_maDCOutput2FGS);

	m_multiRecordAreaSBS->Add(m_dcOutput2SBS, wxSizerFlags(0).Expand().Border(wxALL, 5));


	m_logSBS->Add(m_logTC, wxSizerFlags(1).Expand().Border(wxALL, 5));
	
	m_topLevelSizer->Add(m_productInfoAreaSBS, wxSizerFlags(0).Expand().Border(wxALL, 5));
	m_topLevelSizer->Add(m_multiRecordAreaSBS, wxSizerFlags(0).Expand().Border(wxALL, 5));
	m_topLevelSizer->Add(m_makeBTN, wxSizerFlags(0).Expand());
	m_topLevelSizer->Add(m_logSBS, wxSizerFlags(1).Expand().Border(wxALL, 5));

	SetSizer(m_topLevelSizer);

}

FRUMakerDialog::~FRUMakerDialog(){

	wxLog::SetActiveTarget(m_oldLog);

}

void FRUMakerDialog::OnBtnMAKE(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT(MSG_ALERT, "OnBtnMAKE");

	size_t len;



	// Start Build FRU
	struct FRU_DATA *fru = NULL;

	fru = (FRU_DATA *)x_calloc(1, sizeof(struct FRU_DATA));

	if (fru == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Allocate Space For FRU Build");
		return;
	}

	fru->Product_Area = (PRODUCT_INFO*)x_calloc(1, sizeof(struct PRODUCT_INFO));

	if (fru->Product_Area == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Allocate Space For FRU PRODUCT INFO Build");
		return;
	}

	// === Start of Product Info Area ===
	PSU_DEBUG_PRINT(MSG_ALERT, "=== Start of Product Info Area ===");
	// Manufacturer Name
	wxString pi_manufacturer_name = this->m_piManufacturerNameTC->GetValue();
	fru->Product_Area->manufacturer_name = (unsigned char*)x_calloc(1, strlen(pi_manufacturer_name.c_str()) + 3);
	
	fru->Product_Area->manufacturer_name[0] = strlen(pi_manufacturer_name.c_str()) | (FRU_STRING_ASCII << 6);
	memcpy(&fru->Product_Area->manufacturer_name[1], pi_manufacturer_name.c_str(), strlen(pi_manufacturer_name.c_str()));
	PSU_DEBUG_PRINT(MSG_ALERT, "changing Product Info Area manufacturer name to %s", pi_manufacturer_name.c_str());

	// Product Name
	wxString pi_product_name = this->m_piProductNameTC->GetValue();
	fru->Product_Area->product_name = (unsigned char*)x_calloc(1, strlen(pi_product_name.c_str()) + 3);

	fru->Product_Area->product_name[0] = strlen(pi_product_name.c_str()) | (FRU_STRING_ASCII << 6);
	memcpy(&fru->Product_Area->product_name[1], pi_product_name.c_str(), strlen(pi_product_name.c_str()));
	PSU_DEBUG_PRINT(MSG_ALERT, "changing Product Info Area product name to %s", pi_product_name.c_str());

	// Model Number
	wxString pi_model_number = this->m_piProductModelNumberTC->GetValue();
	fru->Product_Area->model_number = (unsigned char*)x_calloc(1, strlen(pi_model_number.c_str()) + 3);

	fru->Product_Area->model_number[0] = strlen(pi_model_number.c_str()) | (FRU_STRING_ASCII << 6);
	memcpy(&fru->Product_Area->model_number[1], pi_model_number.c_str(), strlen(pi_model_number.c_str()));
	PSU_DEBUG_PRINT(MSG_ALERT, "changing Product Info Area model number to %s", pi_model_number.c_str());

	// Version
	wxString pi_version = this->m_piProductVersionTC->GetValue();
	fru->Product_Area->version = (unsigned char*)x_calloc(1, strlen(pi_version.c_str()) + 3);

	fru->Product_Area->version[0] = strlen(pi_version.c_str()) | (FRU_STRING_ASCII << 6);
	memcpy(&fru->Product_Area->version[1], pi_version.c_str(), strlen(pi_version.c_str()));
	PSU_DEBUG_PRINT(MSG_ALERT, "changing Product Info Area version to %s", pi_version.c_str());

	// Serial Number
	wxString pi_serial_number = this->m_piProductSerialNumberTC->GetValue();
	fru->Product_Area->serial_number = (unsigned char*)x_calloc(1, strlen(pi_serial_number.c_str()) + 3);

	fru->Product_Area->serial_number[0] = strlen(pi_serial_number.c_str()) | (FRU_STRING_ASCII << 6);
	memcpy(&fru->Product_Area->serial_number[1], pi_serial_number.c_str(), strlen(pi_serial_number.c_str()));
	PSU_DEBUG_PRINT(MSG_ALERT, "changing Product Info Area serial number to %s", pi_serial_number.c_str());

	// Asset Tag
	wxString pi_asset_tag = this->m_piAssetTagTC->GetValue();
	fru->Product_Area->asset_tag = (unsigned char*)x_calloc(1, strlen(pi_asset_tag.c_str()) + 3);

	fru->Product_Area->asset_tag[0] = strlen(pi_asset_tag.c_str()) | (FRU_STRING_ASCII << 6);
	memcpy(&fru->Product_Area->asset_tag[1], pi_asset_tag.c_str(), strlen(pi_asset_tag.c_str()));
	PSU_DEBUG_PRINT(MSG_ALERT, "changing Product Info Area asset tag to %s", pi_asset_tag.c_str());

	// FRU File ID
	wxString pi_fru_file_id = this->m_piFRUFileIDTC->GetValue();
	fru->Product_Area->FRU_file_ID = (unsigned char*)x_calloc(1, strlen(pi_fru_file_id.c_str()) + 3);

	fru->Product_Area->FRU_file_ID[0] = strlen(pi_fru_file_id.c_str()) | (FRU_STRING_ASCII << 6);
	memcpy(&fru->Product_Area->FRU_file_ID[1], pi_fru_file_id.c_str(), strlen(pi_fru_file_id.c_str()));
	PSU_DEBUG_PRINT(MSG_ALERT, "changing Product Info Area fru file id to %s", pi_fru_file_id.c_str());

	PSU_DEBUG_PRINT(MSG_ALERT, "=== End of Product Info Area ===");

	// === Start of MultiRecord Area ===
	PSU_DEBUG_PRINT(MSG_ALERT, "=== Start of MultiRecord Area Area ===");

	fru->MultiRecord_Area = (MULTIRECORD_INFO*)x_calloc(1, sizeof(struct MULTIRECORD_INFO));

	if (fru->MultiRecord_Area == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can't Allocate Space For FRU MultiRecord Build");
		return;
	}

	// === Start of Power Supply Information ===
	fru->MultiRecord_Area->power_supply_info = (unsigned char*)x_calloc(1, 5 + 24);// Header + Record Size
	fru->MultiRecord_Area->power_supply_info[0] = 0x00;// Power Supply Information (Record Type 0x00)
	fru->MultiRecord_Area->power_supply_info[1] = 0x02;// 7:7 \A1V End of list 6:4 \A1V Reserved, write as 000b 3:0 \A1V Record Format version(= 2h unless otherwise specified)
	fru->MultiRecord_Area->power_supply_info[2] = 0x18;// Record Length (Bytes)
	//fru->MultiRecord_Area->power_supply_info[3] = 0x00;// Record Checksum Determine Later
	//fru->MultiRecord_Area->power_supply_info[4] = 0x00;// Header Checksum Determine Later

	/*
	Offset 0, Length 2, Overall capacity (watts) (LSB First)
	15:12 \A1V Reserved, write as 0000b
	11:0 - Overall capacity (watts) (LSB First)
	*/
	unsigned short OverallCapacity = (unsigned short)wxAtoi(this->m_mapsiOverallcapacityTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 5, &OverallCapacity, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[5]=%02x, [6]=%02x", fru->MultiRecord_Area->power_supply_info[5], fru->MultiRecord_Area->power_supply_info[6]);

	/*
	Offset 2, Length 2, Peak VA (LSB First)
	*/
	unsigned short PeakVA = (unsigned short)wxAtoi(this->m_mapsiPeakVATC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 7, &PeakVA, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[7]=%02x, [8]=%02x", fru->MultiRecord_Area->power_supply_info[7], fru->MultiRecord_Area->power_supply_info[8]);

	/*
	Offset 4, Length 1, Inrush Current
	*/
	unsigned char InrushCurrent = (unsigned short)wxAtoi(this->m_mapsiInrushCurrentTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 9, &InrushCurrent, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[9]=%02x", fru->MultiRecord_Area->power_supply_info[9]);

	/*
	Offset 5, Length 1, Inrush Interval in ms
	*/
	unsigned char InrushInterval = (unsigned short)wxAtoi(this->m_mapsiInrushIntervalTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 10, &InrushInterval, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[10]=%02x", fru->MultiRecord_Area->power_supply_info[10]);

	/*
	Offset 6, Length 2, Low end Input voltage range 1 (10mV, LSB First)
	*/
	unsigned short LowEndInputVoltageRange1 = (unsigned short)wxAtoi(this->m_mapsiLowEndInputVoltageRange1TC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 11, &LowEndInputVoltageRange1, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[11]=%02x, [12]=%02x", fru->MultiRecord_Area->power_supply_info[11], fru->MultiRecord_Area->power_supply_info[12]);

	/*
	Offset 8, Length 2, High end Input voltage range 1 (10mV, LSB First)
	*/
	unsigned short HighEndInputVoltageRange1 = (unsigned short)wxAtoi(this->m_mapsiHighEndInputVoltageRange1TC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 13, &HighEndInputVoltageRange1, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[13]=%02x, [14]=%02x", fru->MultiRecord_Area->power_supply_info[13], fru->MultiRecord_Area->power_supply_info[14]);

	/*
	Offset 10, Length 2, Low end Input voltage range 2 (10mV, LSB First)
	*/
	unsigned short LowEndInputVoltageRange2 = (unsigned short)wxAtoi(this->m_mapsiLowEndInputVoltageRange2TC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 15, &LowEndInputVoltageRange2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[15]=%02x, [16]=%02x", fru->MultiRecord_Area->power_supply_info[15], fru->MultiRecord_Area->power_supply_info[16]);

	/*
	Offset 12, Length 2, High end Input voltage range 2 (10mV, LSB First)
	*/
	unsigned short HighEndInputVoltageRange2 = (unsigned short)wxAtoi(this->m_mapsiHighEndInputVoltageRange2TC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 17, &HighEndInputVoltageRange2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[17]=%02x, [18]=%02x", fru->MultiRecord_Area->power_supply_info[17], fru->MultiRecord_Area->power_supply_info[18]);

	/*
	Offset 14, Length 1, Low end Input frequency range
	*/
	unsigned char LowEndInputFrequencyRange = (unsigned short)wxAtoi(this->m_mapsiLowEndInputFrequencyRangeTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 19, &LowEndInputFrequencyRange, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[19]=%02x", fru->MultiRecord_Area->power_supply_info[19]);

	/*
	Offset 15, Length 1, High end Input frequency range
	*/
	unsigned char HighEndInputFrequencyRange = (unsigned short)wxAtoi(this->m_mapsiHighEndInputFrequencyRangeTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 20, &HighEndInputFrequencyRange, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[20]=%02x", fru->MultiRecord_Area->power_supply_info[20]);

	/*
	Offset 16, Length 1, A/C dropout tolerance in ms
	*/
	unsigned char ACDropOutTolerance = (unsigned short)wxAtoi(this->m_mapsiACDropoutToleranceTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 21, &ACDropOutTolerance, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[21]=%02x", fru->MultiRecord_Area->power_supply_info[21]);

	/*
	Offset 17, Length 1, Binary flags
	7:5 \A1V Reserved, write as 0000b
	4:4 \A1V Tachometer pulses per rotation/Predictive fail polarity
	3:3 \A1V Hot Swap Support
	2:2 \A1V Autoswitch
	1:1 - Power factor correction
	*/
	unsigned char BinaryFlags = (unsigned short)wxAtoi(this->m_mapsiBinaryFlagsTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 22, &BinaryFlags, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[22]=%02x", fru->MultiRecord_Area->power_supply_info[22]);

	/*
	Offset 18, Length 2, Peak Wattage.
	15:12 \A1V Hold up time in seconds
	11:0  \A1V Peak capacity (watts) (LSB First)
	*/
	unsigned char HoldUpTimeInTimes = (unsigned char)wxAtoi(this->m_mapsiPeakWattageHoldUpTimeTC->GetValue());
	unsigned short PeakCapacity = (unsigned short)wxAtoi(this->m_mapsiPeakWattagePeakCapacityTC->GetValue());

	unsigned short PeakWattage_Combine = (unsigned short)((HoldUpTimeInTimes & 0x0f) << 12) | 0xf000;

	PeakWattage_Combine |= (PeakCapacity & 0x0fff);

	memcpy(fru->MultiRecord_Area->power_supply_info + 23, &PeakWattage_Combine, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[23]=%02x, [24]=%02x", fru->MultiRecord_Area->power_supply_info[23], fru->MultiRecord_Area->power_supply_info[24]);

	/*
	Offset 20, Length 3, Combined Wattage
	Byte 1:
	7:4 \A1V Voltage 1
	3:0 \A1V Voltage 2
	Byte 2:3
	Total Combined Wattage (LSB First)
	*/
	unsigned char voltage1 = (unsigned char)wxAtoi(this->m_mapsiCombinedWattageVoltage1TC->GetValue());
	unsigned char voltage2 = (unsigned char)wxAtoi(this->m_mapsiCombinedWattageVoltage2TC->GetValue());

	voltage1 |= (voltage1 & 0xf0) << 4;
	voltage2 |= (voltage2 & 0x0f);

	unsigned byte1 = voltage1 | voltage2;

	memcpy(fru->MultiRecord_Area->power_supply_info + 25, &byte1, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[25]=%02x", fru->MultiRecord_Area->power_supply_info[25]);

	unsigned short CombinedWattage = (unsigned short)wxAtoi(this->m_mapsiTotalCombinedWattageTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 26, &CombinedWattage, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[26]=%02x, [27]=%02x", fru->MultiRecord_Area->power_supply_info[26], fru->MultiRecord_Area->power_supply_info[27]);

	/*
	Offset 20, Length 1, Predictive fail tachometer lower threshold (RPS)
	*/
	unsigned char RPS= (unsigned short)wxAtoi(this->m_mapsiRPSTC->GetValue());

	memcpy(fru->MultiRecord_Area->power_supply_info + 28, &RPS, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[28]=%02x", fru->MultiRecord_Area->power_supply_info[28]);


	// === Start of DC Output 1 ===
	fru->MultiRecord_Area->supplies[0] = (unsigned char*)x_calloc(1, 5 + 13);// Header + Record Size
	fru->MultiRecord_Area->supplies[0][0] = 0x01;// DC Output (Record Type 0x01)
	fru->MultiRecord_Area->supplies[0][1] = 0x02;// 7:7 \A1V End of list 6:4 \A1V Reserved, write as 000b 3:0 \A1V Record Format version(= 2h unless otherwise specified)
	fru->MultiRecord_Area->supplies[0][2] = 0x0D;// Record Length (Bytes)
	fru->MultiRecord_Area->supplies[0][3] = 0x00;// Record Checksum Determine Later
	fru->MultiRecord_Area->supplies[0][4] = 0x00;// Header Checksum Determine Later

	/*
	Offset 0, Length 1, Output information
	7:7 \A1V Standby
	6:4 \A1V Reserved, write as 000b
	3:0 \A1V Output number
	*/
	unsigned char OutputInformation = (unsigned char)wxAtoi(this->m_maDCOutput1OutputNumberTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[0] + 5, &OutputInformation, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[5]=%02x", fru->MultiRecord_Area->supplies[0][5]);

	/*
	Offset 1, Length 2, Nominal voltage (10 mV)
	*/
	unsigned short NominalVoltage = (unsigned short)wxAtoi(this->m_maDCOutput1NominalVoltageTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[0] + 6, &NominalVoltage, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[6]=%02x, [7]=%02x", fru->MultiRecord_Area->supplies[0][6], fru->MultiRecord_Area->supplies[0][7]);

	/*
	Offset 3, Length 2, Maximum negative voltage deviation (10 mV)
	*/
	unsigned short MaxNegativeVoltageDeviation = (unsigned short)wxAtoi(this->m_maDCOutput1MaximumNegativeVoltageDeviationTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[0] + 8, &MaxNegativeVoltageDeviation, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[8]=%02x, [9]=%02x", fru->MultiRecord_Area->supplies[0][8], fru->MultiRecord_Area->supplies[0][9]);

	/*
	Offset 5, Length 2, Maximum positive voltage deviation (10 mV)
	*/
	unsigned short MaxPositiveVoltageDeviation = (unsigned short)wxAtoi(this->m_maDCOutput1MaximumPositiveVoltageDeviationTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[0] + 10, &MaxPositiveVoltageDeviation, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[10]=%02x, [11]=%02x", fru->MultiRecord_Area->supplies[0][10], fru->MultiRecord_Area->supplies[0][11]);

	/*
	Offset 7, Length 2, Ripple and Noise pk-pk 10Hz to 30 MHz (mV)
	*/
	unsigned short RippleAndNoise = (unsigned short)wxAtoi(this->m_maDCOutput1RippleAndNoiseTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[0] + 12, &RippleAndNoise, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[12]=%02x, [13]=%02x", fru->MultiRecord_Area->supplies[0][12], fru->MultiRecord_Area->supplies[0][13]);

	/*
	Offset 9, Length 2, Minimum current draw (mA)
	*/
	unsigned short MinimumCurrentDraw = (unsigned short)wxAtoi(this->m_maDCOutput1MinimumCurrentDrawTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[0] + 14, &MinimumCurrentDraw, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[14]=%02x, [15]=%02x", fru->MultiRecord_Area->supplies[0][14], fru->MultiRecord_Area->supplies[0][15]);

	/*
	Offset 11, Length 2, Maximum current draw (mA)
	*/
	unsigned short MaximumCurrentDraw = (unsigned short)wxAtoi(this->m_maDCOutput1MaximumCurrentDrawTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[0] + 16, &MaximumCurrentDraw, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[16]=%02x, [17]=%02x", fru->MultiRecord_Area->supplies[0][16], fru->MultiRecord_Area->supplies[0][17]);

	// === End of Start of DC Output 1 ===

	// === Start of DC Output 2 ===

	fru->MultiRecord_Area->supplies[1] = (unsigned char*)x_calloc(1, 5 + 13);// Header + Record Size
	fru->MultiRecord_Area->supplies[1][0] = 0x01;// DC Output (Record Type 0x01)
	fru->MultiRecord_Area->supplies[1][1] = 0x02;// 7:7 \A1V End of list 6:4 \A1V Reserved, write as 000b 3:0 \A1V Record Format version(= 2h unless otherwise specified)
	fru->MultiRecord_Area->supplies[1][2] = 0x0D;// Record Length (Bytes)
	fru->MultiRecord_Area->supplies[1][3] = 0x00;// Record Checksum Determine Later
	fru->MultiRecord_Area->supplies[1][4] = 0x00;// Header Checksum Determine Later

	/*
	Offset 0, Length 1, Output information
	7:7 \A1V Standby
	6:4 \A1V Reserved, write as 000b
	3:0 \A1V Output number
	*/
	unsigned char OutputInformation2 = (unsigned char)wxAtoi(this->m_maDCOutput2OutputNumberTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[1] + 5, &OutputInformation2, 1);
	PSU_DEBUG_PRINT(MSG_ALERT, "[5]=%02x", fru->MultiRecord_Area->supplies[1][5]);

	/*
	Offset 1, Length 2, Nominal voltage (10 mV)
	*/
	unsigned short NominalVoltage2 = (unsigned short)wxAtoi(this->m_maDCOutput2NominalVoltageTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[1] + 6, &NominalVoltage2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[6]=%02x, [7]=%02x", fru->MultiRecord_Area->supplies[1][6], fru->MultiRecord_Area->supplies[1][7]);

	/*
	Offset 3, Length 2, Maximum negative voltage deviation (10 mV)
	*/
	unsigned short MaxNegativeVoltageDeviation2 = (unsigned short)wxAtoi(this->m_maDCOutput2MaximumNegativeVoltageDeviationTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[1] + 8, &MaxNegativeVoltageDeviation2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[8]=%02x, [9]=%02x", fru->MultiRecord_Area->supplies[1][8], fru->MultiRecord_Area->supplies[1][9]);

	/*
	Offset 5, Length 2, Maximum positive voltage deviation (10 mV)
	*/
	unsigned short MaxPositiveVoltageDeviation2 = (unsigned short)wxAtoi(this->m_maDCOutput2MaximumPositiveVoltageDeviationTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[1] + 10, &MaxPositiveVoltageDeviation2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[10]=%02x, [11]=%02x", fru->MultiRecord_Area->supplies[1][10], fru->MultiRecord_Area->supplies[1][11]);

	/*
	Offset 7, Length 2, Ripple and Noise pk-pk 10Hz to 30 MHz (mV)
	*/
	unsigned short RippleAndNoise2 = (unsigned short)wxAtoi(this->m_maDCOutput2RippleAndNoiseTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[1] + 12, &RippleAndNoise2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[12]=%02x, [13]=%02x", fru->MultiRecord_Area->supplies[1][12], fru->MultiRecord_Area->supplies[1][13]);

	/*
	Offset 9, Length 2, Minimum current draw (mA)
	*/
	unsigned short MinimumCurrentDraw2 = (unsigned short)wxAtoi(this->m_maDCOutput2MinimumCurrentDrawTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[1] + 14, &MinimumCurrentDraw2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[14]=%02x, [15]=%02x", fru->MultiRecord_Area->supplies[1][14], fru->MultiRecord_Area->supplies[1][15]);

	/*
	Offset 11, Length 2, Maximum current draw (mA)
	*/
	unsigned short MaximumCurrentDraw2 = (unsigned short)wxAtoi(this->m_maDCOutput2MaximumCurrentDrawTC->GetValue());

	memcpy(fru->MultiRecord_Area->supplies[1] + 16, &MaximumCurrentDraw2, 2);
	PSU_DEBUG_PRINT(MSG_ALERT, "[16]=%02x, [17]=%02x", fru->MultiRecord_Area->supplies[1][16], fru->MultiRecord_Area->supplies[1][17]);

	// === End of Start of DC Output 2 ===

	// === End of MultiRecord Area ===
	PSU_DEBUG_PRINT(MSG_ALERT, "=== End of MultiRecord Area Area ===");

	m_pFRUBinaryContent = build_FRU_blob(fru, &len, false);

	PSU_DEBUG_PRINT(MSG_ALERT, "Length of FRU Binary is %d", len);
	PSU_DEBUG_PRINT(MSG_ALERT, "E2PROM CONTENT :");
	PMBUSHelper::PrintFRUContent(this->m_pFRUBinaryContent, 256);

	/* Save Built FRU To File */

	// Save FRU Binary File
	wxString FileName = wxT("FRU-");
	wxString DateString("");

	PMBUSHelper::GetNowDateTimeString(DateString);
	FileName += DateString;
	FileName += wxT(".bin");

	wxFileDialog SaveFRUBinaryFileDialog(this, L"Save FRU Binary File", "", FileName, "BIN Files (*.bin)|*.bin", wxFD_SAVE);

	SaveFRUBinaryFileDialog.Centre();

	// If the user changed idea...
	if (SaveFRUBinaryFileDialog.ShowModal() == wxID_CANCEL){
		return;
	}

	// Get Save Path
	wxString path = SaveFRUBinaryFileDialog.GetPath();
	PSU_DEBUG_PRINT(MSG_ALERT, "Save FRU Binary File To %s", path.c_str());

	// Start Save Binary File
	wxString SavePath = path;

	wxFFileOutputStream fileOutStream(SavePath);

	if (!fileOutStream.IsOk()){
		PSU_DEBUG_PRINT(MSG_ERROR, "Can not Save Binary To %s", SavePath);
		return;
	}

	wxDataOutputStream dataOutputStream(fileOutStream);

	for (unsigned int idx = 0; idx < MAX_FRU_FILE_SIZE; idx++){

		wxUint8 u8(m_pFRUBinaryContent[idx]);
		dataOutputStream.Write8(u8);

	}

	fileOutStream.Sync();


	/*                        */

	// Free FRU
	if (fru) free(fru);

	// Free 
	if (m_pFRUBinaryContent) free(m_pFRUBinaryContent);

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
