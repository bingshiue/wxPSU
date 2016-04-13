 /**
  * @file PMBusCMDGridTable.cpp
  */

#include "PMBusCMDGridTable.h"

wxString PMBusCMDGridTable::GetTypeName(int WXUNUSED(row), int col)
{
	switch (col)
	{
	case Col_Id:
	case Col_Priority:
		return wxGRID_VALUE_NUMBER;;

	case Col_Severity:
		// fall thorugh (TODO should be a list)

	case Col_Summary:
		return wxString::Format(wxT("%s:80"), wxGRID_VALUE_STRING);

	case Col_Platform:
		return wxString::Format(wxT("%s:all,MSW,GTK,other"), wxGRID_VALUE_CHOICE);

	case Col_Opened:
		return wxGRID_VALUE_BOOL;
	}

	wxFAIL_MSG(wxT("unknown column"));

	return wxEmptyString;
}

int PMBusCMDGridTable::GetNumberRows()
{
	return WXSIZEOF(gs_dataBugsGrid);
}

int PMBusCMDGridTable::GetNumberCols()
{
	return Col_Max;
}

bool PMBusCMDGridTable::IsEmptyCell(int WXUNUSED(row), int WXUNUSED(col))
{
	return false;
}

wxString PMBusCMDGridTable::GetValue(int row, int col)
{
	const BugsGridData& gd = gs_dataBugsGrid[row];

	switch (col)
	{
	case Col_Id:
		return wxString::Format(wxT("%d"), gd.id);

	case Col_Priority:
		return wxString::Format(wxT("%d"), gd.prio);

	case Col_Opened:
		return gd.opened ? wxT("1") : wxT("0");

	case Col_Severity:
		return severities[gd.severity];

	case Col_Summary:
		return gd.summary;

	case Col_Platform:
		return gd.platform;
	}

	return wxEmptyString;
}

void PMBusCMDGridTable::SetValue(int row, int col, const wxString& value)
{
	BugsGridData& gd = gs_dataBugsGrid[row];

	switch (col)
	{
	case Col_Id:
	case Col_Priority:
	case Col_Opened:
		wxFAIL_MSG(wxT("unexpected column"));
		break;

	case Col_Severity:
	{
		size_t n;
		for (n = 0; n < WXSIZEOF(severities); n++)
		{
			if (severities[n] == value)
			{
				gd.severity = (Severity)n;
				break;
			}
		}

		if (n == WXSIZEOF(severities))
		{
			wxLogWarning(wxT("Invalid severity value '%s'."),
				value.c_str());
			gd.severity = Sev_Normal;
		}
	}
	break;

	case Col_Summary:
		wxStrncpy(gd.summary, value, WXSIZEOF(gd.summary));
		break;

	case Col_Platform:
		wxStrncpy(gd.platform, value, WXSIZEOF(gd.platform));
		break;
	}
}

bool
PMBusCMDGridTable::CanGetValueAs(int WXUNUSED(row),
int col,
const wxString& typeName)
{
	if (typeName == wxGRID_VALUE_STRING)
	{
		return true;
	}
	else if (typeName == wxGRID_VALUE_BOOL)
	{
		return col == Col_Opened;
	}
	else if (typeName == wxGRID_VALUE_NUMBER)
	{
		return col == Col_Id || col == Col_Priority || col == Col_Severity;
	}
	else
	{
		return false;
	}
}

bool PMBusCMDGridTable::CanSetValueAs(int row, int col, const wxString& typeName)
{
	return CanGetValueAs(row, col, typeName);
}

long PMBusCMDGridTable::GetValueAsLong(int row, int col)
{
	const BugsGridData& gd = gs_dataBugsGrid[row];

	switch (col)
	{
	case Col_Id:
		return gd.id;

	case Col_Priority:
		return gd.prio;

	case Col_Severity:
		return gd.severity;

	default:
		wxFAIL_MSG(wxT("unexpected column"));
		return -1;
	}
}

bool PMBusCMDGridTable::GetValueAsBool(int row, int col)
{
	if (col == Col_Opened)
	{
		return gs_dataBugsGrid[row].opened;
	}
	else
	{
		wxFAIL_MSG(wxT("unexpected column"));

		return false;
	}
}

void PMBusCMDGridTable::SetValueAsLong(int row, int col, long value)
{
	BugsGridData& gd = gs_dataBugsGrid[row];

	switch (col)
	{
	case Col_Priority:
		gd.prio = value;
		break;

	default:
		wxFAIL_MSG(wxT("unexpected column"));
	}
}

void PMBusCMDGridTable::SetValueAsBool(int row, int col, bool value)
{
	if (col == Col_Opened)
	{
		gs_dataBugsGrid[row].opened = value;
	}
	else
	{
		wxFAIL_MSG(wxT("unexpected column"));
	}
}

wxString PMBusCMDGridTable::GetColLabelValue(int col)
{
	return headers[col];
}

MyGridCellAttrProvider::MyGridCellAttrProvider()
{
	m_attrForOddRows = new wxGridCellAttr;
	m_attrForOddRows->SetBackgroundColour(*wxLIGHT_GREY);
}

MyGridCellAttrProvider::~MyGridCellAttrProvider()
{
	m_attrForOddRows->DecRef();
}

wxGridCellAttr *MyGridCellAttrProvider::GetAttr(int row, int col,
	wxGridCellAttr::wxAttrKind  kind /* = wxGridCellAttr::Any */) const
{
	wxGridCellAttr *attr = wxGridCellAttrProvider::GetAttr(row, col, kind);

	if (row % 2)
	{
		if (!attr)
		{
			attr = m_attrForOddRows;
			attr->IncRef();
		}
		else
		{
			if (!attr->HasBackgroundColour())
			{
				wxGridCellAttr *attrNew = attr->Clone();
				attr->DecRef();
				attr = attrNew;
				attr->SetBackgroundColour(*wxLIGHT_GREY);
			}
		}
	}

	return attr;
}