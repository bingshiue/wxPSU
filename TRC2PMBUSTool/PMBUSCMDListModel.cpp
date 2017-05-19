 /**
  * @file PMBUSCMDListModel.cpp
  */

#include "PMBUSCMDListModel.h"

#include "null.xpm"
#include "wx_small.xpm"
#include "green.xpm"
#include "red.xpm"
#include "yellow.xpm"
#include "gray.xpm"

static int my_sort_reverse(int *v1, int *v2)
{
	return *v2 - *v1;
}

static int my_sort(int *v1, int *v2)
{
	return *v1 - *v2;
}

#define USE_PNG
//#define INITIAL_NUMBER_OF_ITEMS  (PMBUSCOMMAND_SIZE)

PMBUSCMDListModel::PMBUSCMDListModel(PMBUSCOMMAND_t *pmBusCommand, unsigned int NumberOfItems) : wxDataViewVirtualListModel(NumberOfItems)
{
	
	m_numberOfItems = NumberOfItems;
	
	// the first "DATAVIEW_LIST_SIZE" items are really stored in this model;
	// all the others are synthesized on request
	//static const unsigned NUMBER_REAL_ITEMS = DATAVIEW_LIST_SIZE;
	
	// Init m_available[] for toggle switch
	m_available = new bool[NumberOfItems];

	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		m_available[idx] = pmBusCommand[idx].m_toggle;
	}

	// Setup Register
	m_registerColValues.reserve(m_numberOfItems);
	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		wxString tmpStr = wxString::Format(wxT("%s"), pmBusCommand[idx].m_label);
		//tmpStr.UpperCase();
		//tmpStr += wxT("h");
		m_registerColValues.push_back(tmpStr);
	}
	
	// Setup Name
	m_nameColValues.reserve(m_numberOfItems);
	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		wxString tmpStr = wxString::Format(wxT("%s"), pmBusCommand[idx].m_name);
		m_nameColValues.push_back(tmpStr);
	}

	// Setup Access
	m_accessColValues.reserve(m_numberOfItems);
	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		if (pmBusCommand[idx].m_access == cmd_access_readwrite){
			m_accessColValues.push_back(wxT("R/W"));
		}
		else if (pmBusCommand[idx].m_access == cmd_access_brbw){
			m_accessColValues.push_back(wxT("BR/BW"));
		}
		else if (pmBusCommand[idx].m_access == cmd_access_read){
			m_accessColValues.push_back(wxT("R"));
		}
		else if (pmBusCommand[idx].m_access == cmd_access_br){
			m_accessColValues.push_back(wxT("BR"));
		}
		else if (pmBusCommand[idx].m_access == cmd_access_write){
			m_accessColValues.push_back(wxT("W"));
		}
		else if (pmBusCommand[idx].m_access == cmd_access_bw){
			m_accessColValues.push_back(wxT("BW"));
		}
		else if (pmBusCommand[idx].m_access == cmd_access_bwr_read){
			m_accessColValues.push_back(wxT("BWP/BRP"));
		}
		else if (pmBusCommand[idx].m_access == cmd_access_bwr_readwrite){
			m_accessColValues.push_back(wxT("BWP/BRP W"));
		}
	}

	// Setup Query
	m_queryColValues.reserve(m_numberOfItems);
	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		m_queryColValues.push_back(wxT(""));
	}

	// Setup Coefficients
	m_coefficientsColValues.reserve(m_numberOfItems);
	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		m_coefficientsColValues.push_back(wxT(""));
	}

	// Setup Cook
	m_cookColValues.reserve(m_numberOfItems);
	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		m_cookColValues.push_back(wxT(""));
	}


	// Setup Raw
	m_rawColValues.reserve(m_numberOfItems);
	for (unsigned int idx = 0; idx < m_numberOfItems; idx++){
		m_rawColValues.push_back(wxT(""));
	}

#ifdef USE_PNG
	// Setup Icon
	m_icon[XPM_red].CopyFromBitmap(LOAD_PNG_RESOURCE(status_red));    //= wxIcon(red_xpm);

	m_icon[XPM_green].CopyFromBitmap(LOAD_PNG_RESOURCE(status_green));  //= wxIcon(green_xpm);

	m_icon[XPM_yellow].CopyFromBitmap(LOAD_PNG_RESOURCE(status_yellow)); //= wxIcon(yellow_xpm);

	m_icon[XPM_grey].CopyFromBitmap(LOAD_PNG_RESOURCE(status_grey)); //= wxIcon(gray_xpm);

#else
	// Setup Icon
	m_icon[XPM_red] = wxIcon(red_xpm);

	m_icon[XPM_green] = wxIcon(green_xpm);

	m_icon[XPM_yellow] = wxIcon(yellow_xpm);

	m_icon[XPM_grey] = wxIcon(gray_xpm);

#endif

	// Save PMBus Command Handle
	m_pmBusCommand = pmBusCommand;
}

PMBUSCMDListModel::~PMBUSCMDListModel(){
	delete[] m_available;
}

void PMBUSCMDListModel::Prepend(const wxString &text)
{
	m_nameColValues.Insert(text, 0);
	RowPrepended();
}

void PMBUSCMDListModel::DeleteItem(const wxDataViewItem &item)
{
	unsigned int row = GetRow(item);

	if (row >= m_nameColValues.GetCount())
		return;

	m_nameColValues.RemoveAt(row);
	RowDeleted(row);
}

void PMBUSCMDListModel::DeleteItems(const wxDataViewItemArray &items)
{
	unsigned i;
	wxArrayInt rows;
	for (i = 0; i < items.GetCount(); i++)
	{
		unsigned int row = GetRow(items[i]);
		if (row < m_nameColValues.GetCount())
			rows.Add(row);
	}

	if (rows.GetCount() == 0)
	{
		// none of the selected items were in the range of the items
		// which we store... for simplicity, don't allow removing them
		wxLogError("Cannot remove rows with an index greater than %u", (unsigned)(m_nameColValues.GetCount()));
		return;
	}

	// Sort in descending order so that the last
	// row will be deleted first. Otherwise the
	// remaining indeces would all be wrong.
	rows.Sort(my_sort_reverse);
	for (i = 0; i < rows.GetCount(); i++)
		m_nameColValues.RemoveAt(rows[i]);

	// This is just to test if wxDataViewCtrl can
	// cope with removing rows not sorted in
	// descending order
	rows.Sort(my_sort);
	RowsDeleted(rows);
}

void PMBUSCMDListModel::AddMany()
{
	Reset(GetCount() + 1000);
}

 /**
  * @brief Get Value By Row.
  */
void PMBUSCMDListModel::GetValueByRow(wxVariant &variant, unsigned int row, unsigned int col) const
{
	wxString rawStr("");
	
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
	case Col_RegisterIconText:
	{
		//PSU_DEBUG_PRINT("Count of m_registerColValues = %d", m_registerColValues.GetCount());
		wxString text;
		if (row >= m_registerColValues.GetCount()){
			text = "virtual icon";
		}
		else{
			text = m_registerColValues[row];
		}

		//variant << wxDataViewIconText(text, m_icon[row % 2]);
		if(this->m_available[row] == true){

			switch (this->m_pmBusCommand[row].m_cmdStatus.m_status){

			case cmd_status_not_run:
				if (PMBUSHelper::isOwnReadAccess(this->m_pmBusCommand[row].m_access) == true){//this->m_pmBusCommand[row].m_access != cmd_access_write){
					variant << wxDataViewIconText(text, m_icon[XPM_red]);
				}
				else{
					variant << wxDataViewIconText(text, m_icon[XPM_grey]);
				}
				break;

			case cmd_status_running:
				variant << wxDataViewIconText(text, m_icon[XPM_yellow]);
				break;

			case cmd_status_success:
				variant << wxDataViewIconText(text, m_icon[XPM_green]);
				break;

			case cmd_status_failure:
			case cmd_status_checksum_error:
			case cmd_status_i2c_bus_not_acknowledge:
				variant << wxDataViewIconText(text, m_icon[XPM_red]);
				break;


			default:
				PSU_DEBUG_PRINT(MSG_ERROR, "CMD Status Abnormal, Status=%d", this->m_pmBusCommand[row].m_cmdStatus.m_status);
				break;
			}
		}
		else{
			variant << wxDataViewIconText(text, m_icon[XPM_grey]);
		}

	}
	break;
	case Col_NameText:
		if (row >= m_nameColValues.GetCount())
			variant = wxString::Format("virtual row %d", row);
		else
			variant = m_nameColValues[row];
		break;

	case Col_AccessText:
		if (row >= m_nameColValues.GetCount())
			variant = wxString::Format("virtual access %d", row);
		else
			variant = m_accessColValues[row];
		break;

	case Col_QueryText:
		variant = m_queryColValues[row];

		break;

	case Col_CoefficientsText:
		variant = m_coefficientsColValues[row];

		break;

	case Col_CookText:

		variant = m_cookColValues[row];

		break;

	case Col_RawText:

		variant = m_rawColValues[row];

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

bool PMBUSCMDListModel::GetAttrByRow(unsigned int row, unsigned int col,
	wxDataViewItemAttr &attr) const
{
	switch (col)
	{
	case Col_Toggle:
		return false;
		break;
	case Col_RegisterIconText:
		//if (!(row % 2))
			//return false;
		attr.SetColour(*wxBLUE);

		break;

	case Col_QueryText:
		if (this->m_pmBusCommand[row].m_cmdStatus.m_support == cmd_unsupport){
			attr.SetColour(*wxRED);
		}
		else{
			
			switch (this->m_pmBusCommand[row].m_dataFormat.m_formatType){

			case cmd_data_format_LinearData_Format:

				attr.SetColour(wxColour( 0, 0, 255));

				break;

			case cmd_data_format_DirectData_Format:

				attr.SetColour(wxColour(255, 0, 255));

				break;

			case cmd_data_format_16bit_Signed_Number:
			case cmd_data_format_8bit_Unsigned_Number:
			case cmd_data_format_VID_Mode:
			case cmd_data_format_Manufacturer_Specific:
			case cmd_data_format_Reserved:
			case cmd_data_format_Don_t_Return_Numeric_Data:

				attr.SetColour(wxColour(68, 160, 119));

				break;

			default:
				PSU_DEBUG_PRINT(MSG_ERROR, "Something Error Occurs");
				break;
			}
			
		}

		break;

	case Col_NameText:
	case Col_AccessText:
	case Col_CoefficientsText:
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

//#define PRINT_RAW_IN_FEILD
bool PMBUSCMDListModel::SetValueByRow(const wxVariant &variant, unsigned int row, unsigned int col)
{

	wxDataViewIconText iconText;

	switch (col)
	{
	case Col_Toggle:
		PSU_DEBUG_PRINT(MSG_DETAIL, "%d", variant.GetBool());
		this->m_available[row] = variant.GetBool();
		this->m_pmBusCommand[row].m_toggle = this->m_available[row];
		return true;

	case Col_RegisterIconText:
		if (row >= m_registerColValues.GetCount())
		{
			// the item is not in the range of the items
			// which we store... for simplicity, don't allow editing it
			wxLogError("Cannot edit rows with an index greater than %d",
				m_registerColValues.GetCount());
			return false;
		}

		iconText << variant;
		m_registerColValues[row] = iconText.GetText();

		return true;

		break;

	case Col_NameText:
		if (row >= m_nameColValues.GetCount())
		{
			// the item is not in the range of the items
			// which we store... for simplicity, don't allow editing it
			wxLogError("Cannot edit rows with an index greater than %d",
				m_nameColValues.GetCount());
			return false;
		}

		m_nameColValues[row] = variant.GetString();
		
		return true;

		break;

	case Col_AccessText:

		break;

	case Col_QueryText:

		m_queryColValues[row] = variant.GetString();

		break;

	case Col_CoefficientsText:

		m_coefficientsColValues[row] = variant.GetString();

		break;

	case Col_CookText:

		m_cookColValues[row] = variant.GetString();

		break;

	case Col_RawText:
#ifdef PRINT_RAW_IN_FEILD
		PSU_DEBUG_PRINT(MSG_DETAIL, "");
		PSU_DEBUG_PRINT(MSG_DETAIL, "row = %d, length = %d ", row, this->m_pmBusCommand[row].m_recvBuff.m_length);
		m_rawColValues[row].clear();
		for (unsigned int idx = 0; idx < this->m_pmBusCommand[row].m_recvBuff.m_length; idx++){
			m_rawColValues[row] += wxString::Format(" %02x ", this->m_pmBusCommand[row].m_recvBuff.m_recvBuff[idx]);
		}
		PSU_DEBUG_PRINT(MSG_DETAIL, "call %s , %s", m_rawColValues[row].c_str());
#else
		m_rawColValues[row] = variant.GetString();
#endif

		return true;

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

bool* PMBUSCMDListModel::getAvailable(void){
	return m_available;
}
