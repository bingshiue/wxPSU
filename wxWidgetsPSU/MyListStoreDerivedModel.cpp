 /**
  * @file MyListStoreDerivedModel.cpp
  */

#include "MyListStoreDerivedModel.h"

bool MyListStoreDerivedModel::IsEnabledByRow(unsigned int row, unsigned int col) const
{
	// disabled the last two checkboxes
	return !(col == 0 && 8 <= row && row <= 9);
}