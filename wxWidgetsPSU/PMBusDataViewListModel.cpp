 /**
  * @brief PMBusDataViewListModel.cpp
  */

#include "PMBusDataViewListModel.h"

#include "null.xpm"
#include "wx_small.xpm"
#include "green.xpm"
#include "red.xpm"

static int my_sort_reverse(int *v1, int *v2)
{
	return *v2 - *v1;
}

static int my_sort(int *v1, int *v2)
{
	return *v1 - *v2;
}

#define INITIAL_NUMBER_OF_ITEMS  2

PSUDataViewListModel::PSUDataViewListModel() :
wxDataViewVirtualListModel(INITIAL_NUMBER_OF_ITEMS)
{
	// Init m_available[]
	for (unsigned int idx = 0; idx < DATAVIEW_LIST_SIZE; idx++){
		m_available[idx] = true;
	}
	
	// the first 100 items are really stored in this model;
	// all the others are synthesized on request
	static const unsigned NUMBER_REAL_ITEMS = DATAVIEW_LIST_SIZE;

	m_textColValues.reserve(NUMBER_REAL_ITEMS);
	m_textColValues.push_back(wxT("PAGE"));
	for (unsigned int i = 1; i < NUMBER_REAL_ITEMS; i++)
	{
		m_textColValues.push_back(wxT("OPERATION"));//wxString::Format("real row %d", i));
	}

	m_accessColValues.assign(NUMBER_REAL_ITEMS, "R/W");

	m_iconColValues.assign(NUMBER_REAL_ITEMS, "00H");

	m_icon[0] = wxIcon(red_xpm);
	m_icon[1] = wxIcon(green_xpm);
}

void PSUDataViewListModel::Prepend(const wxString &text)
{
	m_textColValues.Insert(text, 0);
	RowPrepended();
}

void PSUDataViewListModel::DeleteItem(const wxDataViewItem &item)
{
	unsigned int row = GetRow(item);

	if (row >= m_textColValues.GetCount())
		return;

	m_textColValues.RemoveAt(row);
	RowDeleted(row);
}

void PSUDataViewListModel::DeleteItems(const wxDataViewItemArray &items)
{
	unsigned i;
	wxArrayInt rows;
	for (i = 0; i < items.GetCount(); i++)
	{
		unsigned int row = GetRow(items[i]);
		if (row < m_textColValues.GetCount())
			rows.Add(row);
	}

	if (rows.GetCount() == 0)
	{
		// none of the selected items were in the range of the items
		// which we store... for simplicity, don't allow removing them
		wxLogError("Cannot remove rows with an index greater than %u", unsigned(m_textColValues.GetCount()));
		return;
	}

	// Sort in descending order so that the last
	// row will be deleted first. Otherwise the
	// remaining indeces would all be wrong.
	rows.Sort(my_sort_reverse);
	for (i = 0; i < rows.GetCount(); i++)
		m_textColValues.RemoveAt(rows[i]);

	// This is just to test if wxDataViewCtrl can
	// cope with removing rows not sorted in
	// descending order
	rows.Sort(my_sort);
	RowsDeleted(rows);
}

void PSUDataViewListModel::AddMany()
{
	Reset(GetCount() + 1000);
}

 /**
  * @brief Get Value By Row.
  */
void PSUDataViewListModel::GetValueByRow(wxVariant &variant,
	unsigned int row, unsigned int col) const
{
	switch (col)
	{
	case Col_Toggle:
		if (this->m_available[row]==false){
			variant = false;
		}
		else{
			variant = true;
		}
		break;
	case Col_IconText:
	{
		wxString text;
		if (row >= m_iconColValues.GetCount())
			text = "virtual icon";
		else
			text = m_iconColValues[row];

		//variant << wxDataViewIconText(text, m_icon[row % 2]);
		if (this->m_available[row] == false){
			variant << wxDataViewIconText(text, m_icon[0]);
		}
		else{
			variant << wxDataViewIconText(text, m_icon[1]);
		}

	}
	break;
	case Col_NameText:
		if (row >= m_textColValues.GetCount())
			variant = wxString::Format("virtual row %d", row);
		else
			variant = m_textColValues[row];
		break;

	case Col_AccessText:
		if (row >= m_textColValues.GetCount())
			variant = wxString::Format("virtual access %d", row);
		else
			variant = m_accessColValues[row];
		break;

	case Col_QueryText:

		break;
	case Col_CookText:

		break;

	case Col_RawText:

		break;

	case Col_Date:
		variant = wxDateTime(1, wxDateTime::Jan, 2000).Add(wxTimeSpan(row));
		break;

	case Col_TextWithAttr:
	{
		static const char *labels[5] =
		{
			"blue", "green", "red", "bold cyan", "default",
		};

		variant = labels[row % 5];
	}
	break;

	case Col_Custom:
	{
		IntToStringMap::const_iterator it = m_customColValues.find(row);
		if (it != m_customColValues.end())
			variant = it->second;
		else
			variant = wxString::Format("%d", row % 100);
	}
	break;

	case Col_Max:
		wxFAIL_MSG("invalid column");
	}
}

bool PSUDataViewListModel::GetAttrByRow(unsigned int row, unsigned int col,
	wxDataViewItemAttr &attr) const
{
	switch (col)
	{
	case Col_Toggle:
		return false;
		break;
	case Col_IconText:
		if (!(row % 2))
			return false;
		attr.SetColour(*wxLIGHT_GREY);
		break;

	case Col_NameText:
	case Col_AccessText:
	case Col_QueryText:
	case Col_CookText:
	case Col_RawText: 
		return false;
		break;

	case Col_Date:
		return false;

	case Col_TextWithAttr:
	case Col_Custom:
		// do what the labels defined in GetValueByRow() hint at
		switch (row % 5)
		{
		case 0:
			attr.SetColour(*wxBLUE);
			break;

		case 1:
			attr.SetColour(*wxGREEN);
			break;

		case 2:
			attr.SetColour(*wxRED);
			break;

		case 3:
			attr.SetColour(*wxCYAN);
			attr.SetBold(true);
			break;

		case 4:
			return false;
		}
		break;

	case Col_Max:
		wxFAIL_MSG("invalid column");
	}

	return true;
}

bool PSUDataViewListModel::SetValueByRow(const wxVariant &variant,
	unsigned int row, unsigned int col)
{
	switch (col)
	{
	case Col_Toggle:
		PSU_DEBUG_PRINT("call %s : %d", __FUNCTIONW__, variant.GetBool());
		this->m_available[row] = variant.GetBool();
		return true;

	case Col_IconText:
	case Col_NameText:
		if (row >= m_textColValues.GetCount())
		{
			// the item is not in the range of the items
			// which we store... for simplicity, don't allow editing it
			wxLogError("Cannot edit rows with an index greater than %d",
				m_textColValues.GetCount());
			return false;
		}

		if (col == Col_NameText)
		{
			m_textColValues[row] = variant.GetString();
		}
		else // col == Col_IconText
		{
			wxDataViewIconText iconText;
			iconText << variant;
			m_iconColValues[row] = iconText.GetText();
		}
		return true;

		break;

	case Col_AccessText:

		break;
	case Col_QueryText:

		break;
	case Col_CookText:

		break;
	case Col_RawText:

		break;

	case Col_Date:
	case Col_TextWithAttr:
		wxLogError("Cannot edit the column %d", col);
		break;

	case Col_Custom:
		m_customColValues[row] = variant.GetString();
		break;

	case Col_Max:
		wxFAIL_MSG("invalid column");
	}

	return false;
}

bool* PSUDataViewListModel::getAvailable(void){
	return m_available;
}