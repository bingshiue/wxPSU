 /**
  * @file PMBysCMDGridTable.h 
  */
#ifndef _PMBUSCMDGRIDTABLE_H_
#define _PMBUSCMDGRIDTABLE_H_

#include "main.h"

enum Columns
{
	Col_Id,
	Col_Summary,
	Col_Severity,
	Col_Priority,
	Col_Platform,
	Col_Opened,
	Col_Max
};

enum Severity
{
	Sev_Wish,
	Sev_Minor,
	Sev_Normal,
	Sev_Major,
	Sev_Critical,
	Sev_Max
};

static const wxString severities[] =
{
	wxT("wishlist"),
	wxT("minor"),
	wxT("normal"),
	wxT("major"),
	wxT("critical"),
};

static struct BugsGridData
{
	int id;
	wxChar summary[80];
	Severity severity;
	int prio;
	wxChar platform[12];
	bool opened;
} gs_dataBugsGrid[] =
{
	{ 18, wxT("foo doesn't work"), Sev_Major, 1, wxT("wxMSW"), true },
	{ 27, wxT("bar crashes"), Sev_Critical, 1, wxT("all"), false },
	{ 45, wxT("printing is slow"), Sev_Minor, 3, wxT("wxMSW"), true },
	{ 68, wxT("Rectangle() fails"), Sev_Normal, 1, wxT("wxMSW"), false },
};

static const wxChar *headers[Col_Max] =
{
	wxT("Id"),
	wxT("Summary"),
	wxT("Severity"),
	wxT("Priority"),
	wxT("Platform"),
	wxT("Opened?"),
};

 /**
  * @brief PM Bus Command Grid Table.
  */
class PMBusCMDGridTable : public wxGridTableBase
{
public:
	PMBusCMDGridTable() { }

	virtual int GetNumberRows() wxOVERRIDE;
	virtual int GetNumberCols() wxOVERRIDE;
	virtual bool IsEmptyCell(int row, int col) wxOVERRIDE;
	virtual wxString GetValue(int row, int col) wxOVERRIDE;
	virtual void SetValue(int row, int col, const wxString& value) wxOVERRIDE;

	virtual wxString GetColLabelValue(int col) wxOVERRIDE;

	virtual wxString GetTypeName(int row, int col) wxOVERRIDE;
	virtual bool CanGetValueAs(int row, int col, const wxString& typeName) wxOVERRIDE;
	virtual bool CanSetValueAs(int row, int col, const wxString& typeName) wxOVERRIDE;

	virtual long GetValueAsLong(int row, int col) wxOVERRIDE;
	virtual bool GetValueAsBool(int row, int col) wxOVERRIDE;

	virtual void SetValueAsLong(int row, int col, long value) wxOVERRIDE;
	virtual void SetValueAsBool(int row, int col, bool value) wxOVERRIDE;
};

/**
 * @brief an example of custom attr provider: this one makes all odd rows appear grey.
 */
class MyGridCellAttrProvider : public wxGridCellAttrProvider
{
public:
	MyGridCellAttrProvider();
	virtual ~MyGridCellAttrProvider();

	virtual wxGridCellAttr *GetAttr(int row, int col,
		wxGridCellAttr::wxAttrKind  kind) const wxOVERRIDE;

private:
	wxGridCellAttr *m_attrForOddRows;
};

#endif