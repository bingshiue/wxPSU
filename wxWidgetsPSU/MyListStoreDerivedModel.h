 /**
  * @file MyListStoreDerivedModel.h
  */
#ifndef _MYLISTSTOREDERIVEDMODEL_H_
#define _MYLISTSTOREDERIVEDMODEL_H_

#include "main.h"

class MyListStoreDerivedModel : public wxDataViewListStore
{
public:
	virtual bool IsEnabledByRow(unsigned int row, unsigned int col) const wxOVERRIDE;
};

#endif