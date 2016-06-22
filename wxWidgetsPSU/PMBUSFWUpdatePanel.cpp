/**
 * @file PMBUSFWUpdatePanel.cpp
 */

#include "PMBUSFWUpdatePanel.h"

PMBUSFWUpdatePanel::PMBUSFWUpdatePanel(wxNotebook* parent, wxString hexFilePath, TIHexFileParser& tiHexFileStat) : wxPanel(parent) {

	this->m_parent = parent;

	this->m_hexFilePath = hexFilePath;
	
	this->m_tiHexFileStat = tiHexFileStat;

	tiHexFileStat.begin();
    this->m_startAddress = tiHexFileStat.currentAddress();

	tiHexFileStat.end();
	this->m_endAddress = tiHexFileStat.currentAddress();

	this->m_addressRange = (this->m_endAddress - this->m_startAddress) + 1UL;

	this->m_dataBytes = tiHexFileStat.size() * 2;

	PSU_DEBUG_PRINT(MSG_ALERT, "startAddress = 0x%08x", this->m_startAddress);
	PSU_DEBUG_PRINT(MSG_ALERT, "EndAddress   = 0x%08x", this->m_endAddress);
	PSU_DEBUG_PRINT(MSG_ALERT, "Address Range= %d", this->m_addressRange);
	PSU_DEBUG_PRINT(MSG_ALERT, "Data Bytes   = %d", this->m_dataBytes);

	this->m_topLevelSizer = new wxBoxSizer(wxVERTICAL);
	this->m_statisticSBS = new wxStaticBoxSizer(wxVERTICAL, this, wxT("MEMORY MAP"));
	this->m_buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	this->m_fileNameST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, this->m_hexFilePath);

	wxString StartAddress = wxString::Format("START Address : %d", this->m_startAddress);
	this->m_startAddressST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, StartAddress);

	wxString EndAddress   = wxString::Format("End Address   : %d", this->m_endAddress);
	this->m_endAddressST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, EndAddress);

	wxString AddressRange = wxString::Format("Address Range : %d", this->m_addressRange);
	this->m_addressRangeST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, AddressRange);

	wxString DataBytes    = wxString::Format("Data Bytes    : %d", this->m_dataBytes);
	this->m_dataBytesST = new wxStaticText(this->m_statisticSBS->GetStaticBox(), wxID_ANY, DataBytes);

	this->m_writeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_WRITE_BUTTON, wxT("WRITE"));
	this->m_writeButton->SetBitmap(wxBITMAP_PNG(MEMORY_32));

	this->m_closeButton = new wxButton(this->m_statisticSBS->GetStaticBox(), CID_CLOSE_BUTTON, wxT("CLOSE"));
	this->m_closeButton->SetBitmap(wxBITMAP_PNG(CLOSE_32));

	this->m_buttonSizer->Add(this->m_writeButton);
	this->m_buttonSizer->Add(this->m_closeButton);

	this->m_statisticSBS->Add(this->m_fileNameST, wxSizerFlags(0).Align(wxCENTER).Border());

	this->m_statisticSBS->Add(this->m_startAddressST, wxSizerFlags(0).Align(wxCENTER).Border());
	this->m_statisticSBS->Add(this->m_endAddressST, wxSizerFlags(0).Align(wxCENTER).Border());
	this->m_statisticSBS->Add(this->m_addressRangeST, wxSizerFlags(0).Align(wxCENTER).Border());
	this->m_statisticSBS->Add(this->m_dataBytesST, wxSizerFlags(0).Align(wxCENTER).Border());

	this->m_statisticSBS->Add(this->m_buttonSizer, wxSizerFlags(0).Align(wxCENTER));
	this->m_topLevelSizer->Add(this->m_statisticSBS, wxSizerFlags(0).Expand());

	this->SetupHexMMAPDVL();

	this->m_topLevelSizer->Add(this->m_tiHexMMAPDVC, wxSizerFlags(1).Expand());


	this->SetSizerAndFit(this->m_topLevelSizer);
}

PMBUSFWUpdatePanel::~PMBUSFWUpdatePanel(){

}

void PMBUSFWUpdatePanel::SetupHexMMAPDVL(void){

	this->m_tiHexMMAPDVC = new wxDataViewCtrl(this, ID_HEXMMAP_DVC, wxDefaultPosition, wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	this->m_tiHexMMAPDVC->SetFont(font);

	this->m_tiHexMMAPModel = new TIHexMMAPModel(1024, &this->m_tiHexFileStat);
	this->m_tiHexMMAPDVC->AssociateModel(this->m_tiHexMMAPModel.get());

	this->m_tiHexMMAPDVC->AppendTextColumn("ADDRESS", TIHexMMAPModel::Col_ADDRESS, wxDATAVIEW_CELL_ACTIVATABLE, 200, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("00H", TIHexMMAPModel::Col_00H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("01H", TIHexMMAPModel::Col_01H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("02H", TIHexMMAPModel::Col_02H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("03H", TIHexMMAPModel::Col_03H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("04H", TIHexMMAPModel::Col_04H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("05H", TIHexMMAPModel::Col_05H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("06H", TIHexMMAPModel::Col_06H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("07H", TIHexMMAPModel::Col_07H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("08H", TIHexMMAPModel::Col_08H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("09H", TIHexMMAPModel::Col_09H, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0AH", TIHexMMAPModel::Col_0AH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0BH", TIHexMMAPModel::Col_0BH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0CH", TIHexMMAPModel::Col_0CH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0DH", TIHexMMAPModel::Col_0DH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0EH", TIHexMMAPModel::Col_0EH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("0FH", TIHexMMAPModel::Col_0FH, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	this->m_tiHexMMAPDVC->AppendTextColumn("", TIHexMMAPModel::Col_ASCII, wxDATAVIEW_CELL_ACTIVATABLE, wxCOL_WIDTH_AUTOSIZE, wxALIGN_LEFT);
}

void PMBUSFWUpdatePanel::OnWriteButton(wxCommandEvent& event){

}

void PMBUSFWUpdatePanel::OnCloseButton(wxCommandEvent& event){

	unsigned int selected_index;

	selected_index = this->m_parent->GetSelection();

	this->m_parent->SetSelection(0);

	this->m_parent->RemovePage(selected_index);
}

wxBEGIN_EVENT_TABLE(PMBUSFWUpdatePanel, wxPanel)
EVT_BUTTON(CID_WRITE_BUTTON, PMBUSFWUpdatePanel::OnWriteButton)
EVT_BUTTON(CID_CLOSE_BUTTON, PMBUSFWUpdatePanel::OnCloseButton)
wxEND_EVENT_TABLE()