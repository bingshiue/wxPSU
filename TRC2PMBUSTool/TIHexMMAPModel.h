/**
 * @file TIHexMMAPModel.h
 */
#ifndef _TIHEXMMAPMODEL_H
#define _TIHEXMMAPMODEL_H

#include "CommonDef.h"
#include "main.h"
#include "TIHexFileParser.h"

class TIHexMMAPModel : public wxDataViewVirtualListModel
{
public:
	enum
	{
		Col_ADDRESS = 0,
		Col_00H,
		Col_01H,
		Col_02H,
		Col_03H,
		Col_04H,
		Col_05H,
		Col_06H,
		Col_07H,
		Col_08H,
		Col_09H,
		Col_0AH,
		Col_0BH,
		Col_0CH,
		Col_0DH,
		Col_0EH,
		Col_0FH,
		Col_ASCII,
		Col_Max
	};

	TIHexMMAPModel(unsigned int initSize, TIHexFileParser* tiHexFileStat, TIHexFileParser* compareTiHexFileStat);

	/* Implementation of base class virtuals methods to define model */
	/**
	 * @brief Get Column Conut.
	 */
	virtual unsigned int GetColumnCount() const wxOVERRIDE
	{
		return Col_Max;
	}

	/**
	 * @brief Get Column Type.
	 */
	 virtual wxString GetColumnType(unsigned int col) const wxOVERRIDE
	{
		return wxT("string");
	}

	/**
	 * @brief Get Value By Row.
	 */
	virtual void GetValueByRow(wxVariant &variant, unsigned int row, unsigned int col) const wxOVERRIDE;

	/**
	 * @brief Get Attr By Row.
	 */
	virtual bool GetAttrByRow(unsigned int row, unsigned int col, wxDataViewItemAttr &attr) const wxOVERRIDE;

	/**
	 * @brief Set Value By Row.
	 */
	virtual bool SetValueByRow(const wxVariant &variant, unsigned int row, unsigned int col) wxOVERRIDE;

protected:


private:
	
	TIHexFileParser *m_tiHexFileStat;/**<  TI Hex File Parser */

	TIHexFileParser *m_compareTiHexFileStat;/**< Compare TI Hex File Parser */

	unsigned long m_startAddress;

	unsigned long m_endAddress;

};


#endif



