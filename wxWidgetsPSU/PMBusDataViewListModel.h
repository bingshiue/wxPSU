 /**
  * @file PMBusDataViewListModel.h
  */
#ifndef _PMBUSDATAVIEWLISTMODEL_H_
#define _PMBUSDATAVIEWLISTMODEL_H_

#include "main.h"
#include "CommonDef.h"
#include "PMBusCommandType.h"
#include "wx/hashmap.h"

class MyCustomRenderer : public wxDataViewCustomRenderer
{
public:
	// This renderer can be either activatable or editable, for demonstration
	// purposes. In real programs, you should select whether the user should be
	// able to activate or edit the cell and it doesn't make sense to switch
	// between the two -- but this is just an example, so it doesn't stop us.
	explicit MyCustomRenderer(wxDataViewCellMode mode)
		: wxDataViewCustomRenderer("string", mode, wxALIGN_CENTER)
	{ }

	virtual bool Render(wxRect rect, wxDC *dc, int state) wxOVERRIDE
	{
		dc->SetBrush(*wxLIGHT_GREY_BRUSH);
		dc->SetPen(*wxTRANSPARENT_PEN);

		rect.Deflate(2);
		dc->DrawRoundedRectangle(rect, 5);

		RenderText(m_value,
			0, // no offset
			wxRect(dc->GetTextExtent(m_value)).CentreIn(rect),
			dc,
			state);

		return true;
	}

	virtual bool ActivateCell(const wxRect& WXUNUSED(cell),
		wxDataViewModel *WXUNUSED(model),
		const wxDataViewItem &WXUNUSED(item),
		unsigned int WXUNUSED(col),
		const wxMouseEvent *mouseEvent) wxOVERRIDE
	{
		wxString position;
		if (mouseEvent)
			position = wxString::Format("via mouse at %d, %d", mouseEvent->m_x, mouseEvent->m_y);
		else
			position = "from keyboard";
		wxLogMessage("MyCustomRenderer ActivateCell() %s", position);
		return false;
	}

	virtual wxSize GetSize() const wxOVERRIDE
	{
		return wxSize(60, 20);
	}

	virtual bool SetValue(const wxVariant &value) wxOVERRIDE
	{
		m_value = value.GetString();
		return true;
	}

	virtual bool GetValue(wxVariant &WXUNUSED(value)) const wxOVERRIDE{ return true; }

	virtual bool HasEditorCtrl() const wxOVERRIDE{ return true; }

	virtual wxWindow* CreateEditorCtrl(wxWindow* parent,wxRect labelRect,const wxVariant& value) wxOVERRIDE
	{
		//wxTextCtrl* text = new wxTextCtrl(parent, wxID_ANY, value,
		wxCheckBox* checkbox = new wxCheckBox(parent, wxID_ANY, value,
		labelRect.GetPosition(),
		labelRect.GetSize(),
		wxTE_PROCESS_ENTER);
		
		//text->SetInsertionPointEnd();

		//return text;

		return checkbox;
	}

	virtual bool GetValueFromEditorCtrl(wxWindow* ctrl, wxVariant& value) wxOVERRIDE
	{
		wxTextCtrl* text = wxDynamicCast(ctrl, wxTextCtrl);
		if (!text)
			return false;

		value = text->GetValue();

		return true;
	}

private:
	wxString m_value;
};

WX_DECLARE_HASH_MAP(unsigned, wxString, wxIntegerHash, wxIntegerEqual,
	IntToStringMap);

#define DATAVIEW_LIST_SIZE (PMBUSCOMMAND_SIZE)/**< Size of DataView List */
#define XPM_SIZE  4/**< Size of XPM Array */

class PSUDataViewListModel : public wxDataViewVirtualListModel
{
public:
	enum
	{
		Col_Toggle,
		Col_RegisterIconText,
		Col_NameText,
		Col_AccessText,
		Col_QueryText,
		Col_CookText,
		Col_RawText,
		Col_Date,
		Col_TextWithAttr,
		Col_Custom,
		Col_Max
	};

	enum
	{
		XPM_red = 0,
		XPM_green,
		XPM_yellow,
		XPM_grey
	};

	PSUDataViewListModel(PMBUSCOMMAND_t *pmBusCommand);

	// helper methods to change the model

	void Prepend(const wxString &text);
	void DeleteItem(const wxDataViewItem &item);
	void DeleteItems(const wxDataViewItemArray &items);
	void AddMany();


	// implementation of base class virtuals to define model

	virtual unsigned int GetColumnCount() const wxOVERRIDE
	{
		return Col_Max;
	}

	virtual wxString GetColumnType(unsigned int col) const wxOVERRIDE
	{
		if (col == Col_Toggle) 
		return wxT("bool");
		
		if (col == Col_RegisterIconText)
		return wxT("wxDataViewIconText");

		return wxT("string");
	}

	virtual void GetValueByRow(wxVariant &variant,unsigned int row, unsigned int col) const wxOVERRIDE;
	
	virtual bool GetAttrByRow(unsigned int row, unsigned int col,wxDataViewItemAttr &attr) const wxOVERRIDE;
	
	virtual bool SetValueByRow(const wxVariant &variant,unsigned int row, unsigned int col) wxOVERRIDE;

	bool* getAvailable(void);

private:
	bool             m_available[DATAVIEW_LIST_SIZE];
	wxArrayString    m_registerColValues;
	wxArrayString    m_nameColValues;
	wxArrayString    m_accessColValues;
	wxArrayString    m_queryColValues;
	wxArrayString    m_cookColValues;
	wxArrayString    m_rawColValues;
	IntToStringMap   m_customColValues;
	wxIcon           m_icon[XPM_SIZE];
	PMBUSCOMMAND_t  *m_pmBusCommand;
};

#endif
