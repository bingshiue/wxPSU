/**
 * @file USBInfoType.h
 */
#ifndef _USBINFOTYPE_H_
#define _USBINFOTYPE_H_

typedef struct USBInfo_tag {

	unsigned short m_vid; /**< VID */
	unsigned short m_pid; /**< PID */

	wchar_t m_vendor_name[256]; /**< Vendor Name */
	wchar_t m_product_name[256]; /**< Product Name */
	unsigned short m_release; /**< Release */

	USBInfo_tag(){

	}

}USBINFO;

#endif