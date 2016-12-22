/**
 * @file TIHexMMAPModel.cpp
 */

#include "TIHexMMAPModel.h"

TIHexMMAPModel::TIHexMMAPModel(unsigned int initSize, TIHexFileParser* tiHexFileStat, TIHexFileParser* compareTiHexFileStat) : wxDataViewVirtualListModel(initSize)
{
	this->m_tiHexFileStat = tiHexFileStat;

	this->m_compareTiHexFileStat = compareTiHexFileStat;

	tiHexFileStat->begin();
	m_startAddress = tiHexFileStat->currentAddress();

	tiHexFileStat->end();
	m_endAddress = tiHexFileStat->currentAddress();

}

void TIHexMMAPModel::GetValueByRow(wxVariant &variant, unsigned int row, unsigned int col) const {

	wxString value("");
	wxString ascii_debug("");
	unsigned short data;
	unsigned long address;
	unsigned char ascii[32] = { 0 };
	unsigned int ascii_index = 0;
	unsigned int bytes_cnt = 0;

	switch (col){

	case Col_ADDRESS:
		value = wxString::Format("%08x", this->m_startAddress + (row*0x10));

		value.UpperCase();

		variant = value;

		break;

	case Col_00H:
	case Col_01H:
	case Col_02H:
	case Col_03H:
	case Col_04H:
	case Col_05H:
	case Col_06H:
	case Col_07H:
	case Col_08H:
	case Col_09H:
	case Col_0AH:
	case Col_0BH:
	case Col_0CH:
	case Col_0DH:
	case Col_0EH:
	case Col_0FH:

		address = this->m_startAddress + ((row * 0x10) + (col - 1));

		if (address <= this->m_endAddress){

			this->m_tiHexFileStat->getData(&data, this->m_startAddress + (row * 0x10) + (col - 1));

			value = wxString::Format("%04x", data);

			value.UpperCase();

			variant = value;

		}

		break;

	case Col_ASCII:

		ascii_index = 0;

		for (unsigned int idx = 1; idx < 17; idx++){

			address = this->m_startAddress + ((row * 0x10) + (idx - 1));

			if (address <= this->m_endAddress){

				this->m_tiHexFileStat->getData(&data, this->m_startAddress + ((row * 0x10) + (idx - 1)));

				for (int k = 1; k >=0; k--){

					PSU_DEBUG_PRINT(MSG_DETAIL, "ascii_index=%d", ascii_index);
					PSU_DEBUG_PRINT(MSG_DETAIL, "*(data+k)  =%d", *(((char*)&data + k)));

					ascii[ascii_index++] = *((unsigned char*)&data + k);
					bytes_cnt++;
				}
			}
			else{
				break;
			}
		}


		for (unsigned int idx = 0; idx < bytes_cnt; idx++){
			ascii_debug += wxString::Format(" %02x ", ascii[idx]);
		}
		
		PSU_DEBUG_PRINT(MSG_DETAIL, "%s", ascii_debug.c_str());

		for (unsigned int idx = 0; idx < bytes_cnt; idx++){
			if (ascii[idx] >= 0x2e && ascii[idx] <= 0x7e){
				value += wxString::Format("%c", (signed)ascii[idx]);
			}
			else{
				value += wxT(".");
			}
		}

		PSU_DEBUG_PRINT(MSG_DETAIL, "%s", value.c_str());

		variant = value;

		break;

	case Col_Max:
		PSU_DEBUG_PRINT(MSG_ERROR, "invalid column");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "invalid column");
		break;
	}

}

bool TIHexMMAPModel::GetAttrByRow(unsigned int row, unsigned int col, wxDataViewItemAttr &attr) const {

	unsigned short data;
	unsigned short data_compare;
	unsigned long address;
	bool diff = false;

	switch (col){

	case Col_ADDRESS:

		break;

	case Col_00H:
	case Col_01H:
	case Col_02H:
	case Col_03H:
	case Col_04H:
	case Col_05H:
	case Col_06H:
	case Col_07H:
	case Col_08H:
	case Col_09H:
	case Col_0AH:
	case Col_0BH:
	case Col_0CH:
	case Col_0DH:
	case Col_0EH:
	case Col_0FH:

		address = this->m_startAddress + ((row * 0x10) + (col - 1));

		if (address <= this->m_endAddress){

			this->m_tiHexFileStat->getData(&data, this->m_startAddress + (row * 0x10) + (col - 1));

			this->m_compareTiHexFileStat->getData(&data_compare, this->m_startAddress + (row * 0x10) + (col - 1));

			if (data != data_compare){
				attr.SetBackgroundColour(wxColour(255,183,76));
			}
		}

		attr.SetBold(true);
		break;

	case Col_ASCII:

		for (unsigned int idx = 1; idx < 17; idx++){

			address = this->m_startAddress + ((row * 0x10) + (idx - 1));

			if (address <= this->m_endAddress && diff == false){

				this->m_tiHexFileStat->getData(&data, this->m_startAddress + ((row * 0x10) + (idx - 1)));

				this->m_compareTiHexFileStat->getData(&data_compare, this->m_startAddress + ((row * 0x10) + (idx - 1)));

				if (data != data_compare){
					attr.SetBackgroundColour(wxColour(255, 183, 76));
					diff = true;
				}

			}
			else{
				break;
			}
		}

		break;

	case Col_Max:
		PSU_DEBUG_PRINT(MSG_ERROR, "invalid column");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "invalid column");
		break;
	}

	return true;
}

bool TIHexMMAPModel::SetValueByRow(const wxVariant &variant, unsigned int row, unsigned int col) {

	switch (col){

	case Col_ADDRESS:

		break;

	case Col_00H:

		break;

	case Col_01H:

		break;

	case Col_02H:

		break;

	case Col_03H:

		break;

	case Col_04H:

		break;

	case Col_05H:

		break;

	case Col_06H:

		break;

	case Col_07H:

		break;

	case Col_08H:

		break;

	case Col_09H:

		break;

	case Col_0AH:

		break;

	case Col_0BH:

		break;

	case Col_0CH:

		break;

	case Col_0DH:

		break;

	case Col_0EH:

		break;

	case Col_0FH:

		break;

	case Col_ASCII:

		break;

	case Col_Max:
		PSU_DEBUG_PRINT(MSG_ERROR, "invalid column");
		break;

	default:
		PSU_DEBUG_PRINT(MSG_ERROR, "invalid column");
		break;
	}

	return false;
}