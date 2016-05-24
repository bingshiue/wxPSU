 /**
  * @file PMBUSHelper.h
  */
#ifndef _PMBUSHELPER_H_
#define _PMBUSHELPER_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "CommonDef.h"
#include "PMBUSStatus.h"

class PMBUSHelper {
public :

	enum {
		positive = 0,
		negative
	};

	static PMBUSSTATUS_t* GetPMBusStatus(void);

	static double ParseLinearDataFormat(unsigned char* buffer, unsigned int sizeOfBuffer);
	static int ProductLinearData(unsigned char *dest, double value, double scale);

protected :

private :

	static PMBUSSTATUS_t m_pmbusStatus;
};


#endif