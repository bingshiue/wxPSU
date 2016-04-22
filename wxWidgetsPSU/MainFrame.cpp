/**
 * @file MainFrame.cpp
 */

#include "MainFrame.h"
#include "CommonDef.h"
#include "SerialPortReadThread.h"
#include "SerialPort.h"
#include "MyListStoreDerivedModel.h"
#include "PMBUSCommand.h"
#include "PMBusCMDGridTable.h"
#include "sample.xpm"

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{	
	// Initializa Semaphore
	this->m_rxTxSemaphore = new wxSemaphore(0,0);
	
	//this->m_parent = new wxPanel(this, wxID_ANY);
	this->m_topVeriticalSizer = new wxBoxSizer(wxVERTICAL);
	this->m_hbox = new wxBoxSizer(wxHORIZONTAL);

	// Setup Icon
	SetIcon(sample_xpm);

	// Get old logger
	m_oldLogger = wxLog::GetActiveTarget();
	
	// Setup Menu
	SetupMenuBar();

	// Setup ToolBar
	SetupToolBar();

	// Setup StatusBar
	SetupStatusBar();

	//CreateStatusBar();
	//SetStatusText("PSU Tool");

	// create the logging text control and a header showing the meaning of the
	// different columns
	wxTextCtrl *header = new wxTextCtrl(this, wxID_ANY, "",
		wxDefaultPosition, wxDefaultSize,
		wxTE_READONLY);
	DoLogLine(header, "  Time", " Thread", "          Message");
	m_txtctrl = new wxTextCtrl(this, wxID_ANY, "",
		wxDefaultPosition, wxDefaultSize,
		wxTE_MULTILINE | wxTE_READONLY);
	wxLog::SetActiveTarget(this);

	// use fixed width font to align output in nice columns
	wxFont font(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_TELETYPE,
		wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	header->SetFont(font);
	m_txtctrl->SetFont(font);
	m_txtctrl->SetFocus();

	//
#if 0 /**< Grid */
	m_grid = new wxGrid(this, wxID_ANY);
	m_table = new PMBusCMDGridTable();
	m_table->SetAttrProvider(new MyGridCellAttrProvider);
	m_grid->SetTable(m_table, true);

	wxGridCellAttr *attrRO = new wxGridCellAttr,
		*attrRangeEditor = new wxGridCellAttr,
		*attrCombo = new wxGridCellAttr;

	attrRO->SetReadOnly();
	attrRangeEditor->SetEditor(new wxGridCellNumberEditor(1, 5));
	attrCombo->SetEditor(new wxGridCellChoiceEditor(WXSIZEOF(severities),
		severities));

	m_grid->SetColAttr(Col_Id, attrRO);
	m_grid->SetColAttr(Col_Priority, attrRangeEditor);
	m_grid->SetColAttr(Col_Severity, attrCombo);

	m_grid->Fit();
	//SetClientSize(m_grid->GetSize());
#endif

	this->m_notebook = new wxNotebook(this, wxID_ANY);

	this->GeneralPanel = new wxPanel(m_notebook, wxID_ANY);
	
	SetupPSUDataView(GeneralPanel);

	this->PMBusStatusPanel = new wxPanel(m_notebook, wxID_ANY);

	this->PMBusMFR = new wxPanel(m_notebook, wxID_ANY);

	this->VerificationPanel = new wxPanel(m_notebook, wxID_ANY);

	this->STATUSPanel = new wxPanel(m_notebook, wxID_ANY);

	// Add each panl into notebook component
	m_notebook->AddPage(this->GeneralPanel, "General");
	m_notebook->AddPage(this->PMBusStatusPanel, "PM Bus Status");
	m_notebook->AddPage(this->PMBusMFR, "PMBus MFR");
	m_notebook->AddPage(this->VerificationPanel, "Verification");
	m_notebook->AddPage(this->STATUSPanel, "STATUS(DCH)");

	//Connect(ID_Hello, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnHello));
	//Connect(ID_Monitor, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnMonitor));
	//Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnAbout));
	//Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::OnExit));

	//this->m_topVeriticalSizer->Add(this->m_toolbar);
	//this->m_topVeriticalSizer->Add(this->m_hbox, wxSizerFlags(1).Expand());//1, wxEXPAND | (wxALL & ~wxLEFT), 1);
	//this->m_topVeriticalSizer->Add(this->m_dataViewCtrl, wxSizerFlags(1).Expand());
	this->m_topVeriticalSizer->Add(this->m_notebook, wxSizerFlags(1).Expand());
	this->m_topVeriticalSizer->Add(header, wxSizerFlags(0).Expand());
	this->m_topVeriticalSizer->Add(this->m_txtctrl, wxSizerFlags(1).Expand());
	//this->m_parent->SetSizer(this->m_topVeriticalSizer, true);

	SetSizer(this->m_topVeriticalSizer);
	//SetSizerAndFit(this->m_topVeriticalSizer);

	// Put Window in Center
	Centre();

	this->m_polling_time = wxAtoi(m_polling_time_combobox->GetValue());

#if 0
	// Log : Set Active Target 
	/wxLog::SetActiveTarget(new wxLogStderr());
#endif
}

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_MENU(ID_Hello, MainFrame::OnHello)
EVT_MENU(ID_Monitor, MainFrame::OnMonitor)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_DATAVIEW_ITEM_VALUE_CHANGED(ID_ATTR_CTRL, MainFrame::OnValueChanged)
wxEND_EVENT_TABLE()

MainFrame::~MainFrame()
{
	wxLog::SetActiveTarget(m_oldLogger);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	// Close Serial Port
	CloseSerialPort();

	Close(true);
}
void MainFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
}
void MainFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

void MainFrame::OnMonitor(wxCommandEvent& event){
	
	PSU_DEBUG_PRINT("On Monitor : Polling Time = %d", this->m_polling_time);

	int loop = 0;
	int ret;

	//PSU_DEBUG_PRINT("Available = %d", this->m_list_model.get()->getAvailable()[0]);

	while (loop < 2) {
		Sleep(this->m_polling_time - SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);// Sleep
		wxLogMessage("loop=%d", loop);
		// Send 2 Commands in turn For Loop Test
		switch (loop % 2){
		case 0:
 			SerialSendData(pmbusCommand[0].mData, CMD_DATA_SIZE);
			break;

		case 1:
			SerialSendData(pmbusCommand[1].mData, CMD_DATA_SIZE);
			break;

		};

		loop++;
		// Semaphore Wait for Read Thread Complete.
		PSU_DEBUG_PRINT("Semaphore WaitTimeout : %d", m_rxTxSemaphore->IsOk());
		ret = m_rxTxSemaphore->WaitTimeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);
		if (ret != wxSEMA_NO_ERROR){
			PSU_DEBUG_PRINT("%s: Semaphore wait timout occurs : error = %d", __FUNCTIONW__,ret);
		}
	};

	// Work Around for txtctrl can't be focus
	this->m_txtctrl->SetFocus();

}

void MainFrame::DoLogLine(wxTextCtrl *text,
const wxString& timestr,
const wxString& threadstr,
const wxString& msg)
{
	text->AppendText(wxString::Format("%9s %10s           %s", timestr, threadstr, msg));
}

void
MainFrame::DoLogRecord(wxLogLevel level,
const wxString& msg,
const wxLogRecordInfo& info)
{
	// let the default GUI logger treat warnings and errors as they should be
	// more noticeable than just another line in the log window and also trace
	// messages as there may be too many of them
	if (level <= wxLOG_Warning || level == wxLOG_Trace)
	{
		m_oldLogger->LogRecord(level, msg, info);
		return;
	}

	DoLogLine
		(
		m_txtctrl,
		wxDateTime(info.timestamp).FormatISOTime(),
		info.threadId == wxThread::GetMainId()
		? wxString("main")
		: wxString::Format("%lx", info.threadId),
		msg + "\n"
		);
}

void MainFrame::OnValueChanged(wxDataViewEvent &event)
{
	/*wxString title*/ unsigned int row = m_list_model->GetRow(event.GetItem());//GetTitle(event.GetItem());
	wxLogMessage("wxEVT_DATAVIEW_ITEM_VALUE_CHANGED");// , Item Id : %s;  Column: %d",
		//title, event.GetColumn());
}

void MainFrame::SetupMenuBar(void){
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
		"Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuRun = new wxMenu;
	menuRun->Append(ID_Monitor, "&Monitor...\tCtrl-M",
		"Start Monitor");

	wxMenu *menuPSU = new wxMenu;

	wxMenu *menuOption = new wxMenu;

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile,   "&File");
	menuBar->Append(menuRun,    "&Run");
	menuBar->Append(menuPSU,    wxT("PSU"));
	menuBar->Append(menuOption, wxT("Option"));
	menuBar->Append(menuHelp,   "&Help");
	SetMenuBar(menuBar);
}

void MainFrame::SetupToolBar(void){
	// Setup Tool Bar
	long style = TOOLBAR_STYLE;
	style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT);

	// Create Tool Bar Instance
	m_toolbar = CreateToolBar(style, ID_TOOLBAR);

	// Append Exit Button
	m_toolbar->AddTool(wxID_EXIT, wxEmptyString, wxBITMAP(EXIT), wxT("Exit Program"), wxITEM_NORMAL);

	// Append Separator
	m_toolbar->AddSeparator();

	// Append Interation
	m_iteration_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Iteration"));
	m_toolbar->AddControl(m_iteration_text, wxEmptyString);

	m_iteration_input = new wxTextCtrl(m_toolbar, wxID_ANY);
	m_iteration_input->SetLabel(wxT("100"));
	m_toolbar->AddControl(m_iteration_input, wxEmptyString);

	// Append Polling Time
	m_polling_time_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Polling Time(ms)"));
	m_toolbar->AddControl(m_polling_time_text, wxEmptyString);

	m_polling_time_combobox = new wxComboBox(m_toolbar, ID_COMBO, wxEmptyString, wxDefaultPosition, wxSize(100, -1));
	m_polling_time_combobox->Append(wxT("  20"));
	m_polling_time_combobox->Append(wxT("  50"));
	m_polling_time_combobox->Append(wxT(" 100"));
	m_polling_time_combobox->Append(wxT(" 200"));
	m_polling_time_combobox->Append(wxT(" 300"));
	m_polling_time_combobox->Append(wxT(" 500"));
	m_polling_time_combobox->Append(wxT("1000"));
	m_polling_time_combobox->Append(wxT("1500"));

	m_polling_time_combobox->SetSelection(0);
	m_toolbar->AddControl(m_polling_time_combobox, wxEmptyString);

	// Append Address 
	m_address_text = new wxStaticText(m_toolbar, wxID_ANY, wxT("Address"));
	m_toolbar->AddControl(m_address_text, wxEmptyString);

	m_address_input = new wxTextCtrl(m_toolbar, wxID_ANY);
	m_address_input->SetLabel(wxT("B0"));
	m_toolbar->AddControl(m_address_input, wxEmptyString);

	// Append A2 A1 A0 Check Box
	m_a2_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A2, wxT("A2"), wxDefaultPosition, wxDefaultSize);
	m_toolbar->AddControl(m_a2_chkbox, wxEmptyString);

	m_a1_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A1, wxT("A1"), wxDefaultPosition, wxDefaultSize);
	m_toolbar->AddControl(m_a1_chkbox, wxEmptyString);

	m_a0_chkbox = new wxCheckBox(m_toolbar, CID_CHECKBOX_A0, wxT("A0"), wxDefaultPosition, wxDefaultSize);
	m_toolbar->AddControl(m_a0_chkbox, wxEmptyString);

	m_toolbar->Realize();
}

void MainFrame::SetupStatusBar(void){
	this->m_status_bar = new PSUStatusBar(this);

	SetStatusBar(this->m_status_bar);

	PositionStatusBar();

}

void MainFrame::SetupPSUDataView(wxPanel* parent){
	
	wxASSERT(!this->m_dataViewCtrl && !m_list_model);
	this->m_dataViewCtrl = new wxDataViewCtrl(parent, ID_ATTR_CTRL, wxDefaultPosition,
		wxDefaultSize, wxDV_VERT_RULES | wxDV_ROW_LINES);

	m_list_model = new PSUDataViewListModel();
	this->m_dataViewCtrl->AssociateModel(m_list_model.get());

	// the various columns
	this->m_dataViewCtrl->AppendToggleColumn("",
		PSUDataViewListModel::Col_Toggle,
		wxDATAVIEW_CELL_ACTIVATABLE,
		wxDVC_TOGGLE_DEFAULT_WIDTH,
		wxALIGN_NOT,
		wxDATAVIEW_COL_RESIZABLE
		);

	this->m_dataViewCtrl->AppendIconTextColumn("Register",
		PSUDataViewListModel::Col_IconText,
		wxDATAVIEW_CELL_EDITABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_REORDERABLE | wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Name",
		PSUDataViewListModel::Col_NameText,
		wxDATAVIEW_CELL_EDITABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Access",
		PSUDataViewListModel::Col_AccessText,
		wxDATAVIEW_CELL_EDITABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Query",
		PSUDataViewListModel::Col_QueryText,
		wxDATAVIEW_CELL_EDITABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Cook",
		PSUDataViewListModel::Col_CookText,
		wxDATAVIEW_CELL_EDITABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_SORTABLE);

	this->m_dataViewCtrl->AppendTextColumn("Raw",
		PSUDataViewListModel::Col_RawText,
		wxDATAVIEW_CELL_EDITABLE,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_NOT,
		wxDATAVIEW_COL_SORTABLE);

#if 0
	this->m_dataViewCtrl->AppendDateColumn("date",
		PSUDataViewListModel::Col_Date);

	m_attributes =
		new wxDataViewColumn("attributes",
		new wxDataViewTextRenderer,
		PSUDataViewListModel::Col_TextWithAttr,
		wxCOL_WIDTH_AUTOSIZE,
		wxALIGN_RIGHT,
		wxDATAVIEW_COL_REORDERABLE | wxDATAVIEW_COL_RESIZABLE | wxDATAVIEW_COL_SORTABLE);
	this->m_dataViewCtrl->AppendColumn(m_attributes);

	this->m_dataViewCtrl->AppendColumn(
		new wxDataViewColumn("custom renderer",
		new MyCustomRenderer(wxDATAVIEW_CELL_EDITABLE),
		PSUDataViewListModel::Col_Custom)
		);
#endif

	// Setup Sub Notebook
	this->m_subNotebook = new wxNotebook(parent, wxID_ANY);

	this->STDPanel   = new wxPanel(this->m_subNotebook, wxID_ANY);
	this->ReadPanel  = new wxPanel(this->m_subNotebook, wxID_ANY);
	this->WritePanel = new wxPanel(this->m_subNotebook, wxID_ANY);

	this->m_subNotebook->AddPage(this->STDPanel,  "STD");
	this->m_subNotebook->AddPage(this->ReadPanel, "Read");
	this->m_subNotebook->AddPage(this->WritePanel,"Write");

	// Setup Sizer
	wxSizer *GeneralPanelSz = new wxBoxSizer(wxHORIZONTAL);
	this->m_subNotebook->SetMinSize(wxSize(-1, 200));
	this->m_dataViewCtrl->SetMinSize(wxSize(-1, 200));
	GeneralPanelSz->Add(m_subNotebook,3);
	GeneralPanelSz->Add(this->m_dataViewCtrl, 7, wxGROW | wxALL, 5);

	parent->SetSizerAndFit(GeneralPanelSz);

}