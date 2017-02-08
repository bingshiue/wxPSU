/**
 * @file Pickit.cpp
 */

#include <iostream>
using namespace std;

#include "CommonDef.h"
#include "PMBUSHelper.h"
#include "Pickit.h"

#define MAX_STR 255

hid_device *pickitHandle;/**< Pickit Device Handle */

wchar_t pickit_wstr[MAX_STR];
wchar_t pickit_productString[MAX_STR] = L"USB";

static unsigned char InitArray[64];

int EnumerateAvailablePickitDevice(BOOL *array, unsigned int sizeofArray){

#ifdef WIN32
	UNREFERENCED_PARAMETER(array);
	UNREFERENCED_PARAMETER(sizeofArray);
#endif

	int devicesFound = 0;

	struct hid_device_info *devs, *cur_dev;
	devs = hid_enumerate(0x0, 0x0);
	cur_dev = devs;
	while (cur_dev) {
		PSU_DEBUG_PRINT(MSG_DEBUG, "Device Found ->");
		PSU_DEBUG_PRINT(MSG_DEBUG, "Type: %04hx %04hx", cur_dev->vendor_id, cur_dev->product_id);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Path: %s", cur_dev->path);
		//PSU_DEBUG_PRINT(MSG_DEBUG, "serial_number: %ls", cur_dev->serial_number);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Manufacturer: %ls", cur_dev->manufacturer_string);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Product:      %ls", cur_dev->product_string);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Release:      %hx", cur_dev->release_number);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Interface:    %d", cur_dev->interface_number);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Usage Page:   0x%02x", cur_dev->usage_page);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Usage:        0x%02x", cur_dev->usage);
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	/* Enumerate VID : PICKIT_SERIAL_USB_VID, PID : PICKIT_SERIAL_USB_PID */
	devs = hid_enumerate(PICKIT_SERIAL_USB_VID, PICKIT_SERIAL_USB_PID);
	cur_dev = devs;
	while (cur_dev) {
		++devicesFound;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Device Found ->");
		PSU_DEBUG_PRINT(MSG_DEBUG, "Type: %04hx %04hx", cur_dev->vendor_id, cur_dev->product_id);

		PMBUSHelper::GetUSBInfo()->m_vid = cur_dev->vendor_id;
		PMBUSHelper::GetUSBInfo()->m_pid = cur_dev->product_id;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Path: %s", cur_dev->path);
		//PSU_DEBUG_PRINT(MSG_DEBUG, "serial_number: %ls", cur_dev->serial_number);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Manufacturer: %ls", cur_dev->manufacturer_string);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Product:      %ls", cur_dev->product_string);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Release:      %hx", cur_dev->release_number);

		PMBUSHelper::GetUSBInfo()->m_release = cur_dev->release_number;

		PSU_DEBUG_PRINT(MSG_DEBUG, "Interface:    %d", cur_dev->interface_number);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Usage Page:   0x%02x", cur_dev->usage_page);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Usage:        0x%02x", cur_dev->usage);
		
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	//PSU_DEBUG_PRINT(MSG_DEBUG, "devicesFound : %d", devicesFound);

	return devicesFound;//EXIT_SUCCESS;
}

int GetPickitDeviceStatus(void){
	if (pickitHandle <= 0){
		return IODEVICE_CLOSE;
	}
	else{
		return IODEVICE_OPEN;
	}
}

wchar_t* GetPickitOpenDeviceName(void){
	return pickit_productString;
}

int OpenPickitDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting){

#ifdef WIN32
	UNREFERENCED_PARAMETER(array);
	UNREFERENCED_PARAMETER(sizeofArray);
#endif

	int res;

	pickitHandle = NULL;

	pickitHandle = hid_open(PICKIT_SERIAL_USB_VID, PICKIT_SERIAL_USB_PID, NULL);

	PSU_DEBUG_PRINT(MSG_DEBUG, "pickitHandle = %p", pickitHandle);

	if (pickitHandle == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "HID device can't be opend");
		PSU_DEBUG_PRINT(MSG_DEBUG, "pickitHandle=%p", pickitHandle);
		return EXIT_FAILURE;
	}
	else{

#if 1
		// Read the Manufacturer String
		pickit_wstr[0] = 0x0000;
		res = hid_get_manufacturer_string(pickitHandle, pickit_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read manufacturer string");
		//PSU_DEBUG_PRINT(MSG_ALERT, "Manufacturer String: %ls", wstr);
		PSU_DEBUG_PRINT(MSG_ALERT, "HID Device Manufacturer : %ls", pickit_wstr);

		lstrcpynW(PMBUSHelper::GetUSBInfo()->m_vendor_name, pickit_wstr, 255);

		// Read the Product String
		pickit_wstr[0] = 0x0000;
		res = hid_get_product_string(pickitHandle, pickit_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read product string");
		//PSU_DEBUG_PRINT(MSG_ALERT, "Product String: %ls", wstr);
		PSU_DEBUG_PRINT(MSG_ALERT, "HID Device Product Name : %ls", pickit_wstr);

		lstrcpynW(PMBUSHelper::GetUSBInfo()->m_product_name, pickit_wstr, 255);

		// Read the Serial Number String
		pickit_wstr[0] = 0x0000;
		res = hid_get_serial_number_string(pickitHandle, pickit_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read serial number string");
		//PSU_DEBUG_PRINT(MSG_ALERT, "Serial Number String: (%d) %ls", wstr[0], wstr);
		PSU_DEBUG_PRINT(MSG_ALERT, "HID Device Serial Number : (%d) %ls", pickit_wstr[0], pickit_wstr);

		// Read Indexed String 1
		pickit_wstr[0] = 0x0000;
		res = hid_get_indexed_string(pickitHandle, 1, pickit_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read indexed string 1");
		PSU_DEBUG_PRINT(MSG_DEBUG, "HID Device Indexed String 1: %ls", pickit_wstr);

#ifdef READ_OPERATION_BLOCKING
		// Set the hid_read() function to be blocking.
		hid_set_nonblocking(pickitHandle, 0);
#else
		// Set the hid_read() function to be non-blocking.
		res = hid_set_nonblocking(pickitHandle, 1);

		PSU_DEBUG_PRINT(MSG_DEBUG, "Ret of hid_set_nonblocking is %d", res);
#endif

#endif
		//for (unsigned id = 1; id < 2; id++){
			
		    
			// Test Write
			InitArray[0] = 0x01;//0x02;
			InitArray[1] = 0x02;//0x02;
			
			/*
		    InitArray[0] = 0x02;
			InitArray[1] = 0xc0;
			InitArray[2] = 0x00;
			InitArray[3] = 0x00;
			InitArray[4] = 0x0a;
			InitArray[5] = 0xff;
			InitArray[6] = 0x00;
			InitArray[7] = 0x00;
			InitArray[8] = 0x00;
			InitArray[9] = 0x01;
			InitArray[10] = 0x31;
			InitArray[11] = 0x20;
			InitArray[12] = 0x00;
			InitArray[13] = 0x00;
			InitArray[14] = 0x00;
			InitArray[15] = 0x00;
			InitArray[16] = 0x00;
			InitArray[17] = 0x03;
			InitArray[18] = 0x06;
			InitArray[19] = 0x00;
			InitArray[20] = 0x00;
			InitArray[21] = 0x00;
			InitArray[22] = 0x00;
			InitArray[23] = 0x00;
			InitArray[24] = 0x31;

			*/

			for (unsigned int idx = 2; idx < 64; idx++){
				InitArray[idx] = 0;
			}


			for (unsigned int len = 0; len < 256; len++){

				res = PickitSendData(InitArray, len);
				PSU_DEBUG_PRINT(MSG_DEBUG, "res of Pickit Test Write is %d, len = %d", res, len);

				if (res < 0){
					PSU_DEBUG_PRINT(MSG_DEBUG, "Pickit Write Error String : %s", hid_error(pickitHandle));
					wxMilliSleep(10);
				}
				else{
					PSU_DEBUG_PRINT(MSG_DEBUG, "Pickit Write Successfully");
				}
			}
		//}

	}

	return EXIT_SUCCESS;
}

int PickitSendData(unsigned char* buff, unsigned int size){

	int bytes_write = 0;

	if (pickitHandle == NULL) { return 0; }

	bytes_write = hid_write(pickitHandle, buff, size);
	PSU_DEBUG_PRINT(MSG_DEBUG, "bytes_write of hid_write is %d", bytes_write);


	return bytes_write;
}

#define RETRY_TIMES  5
#define HID_EXPECT_DATA_LENGTH  64/**< HID Expect Data Length */
int PickitReadData(unsigned char* buff, unsigned int sizeOfBuff){
	unsigned int retry = 0;
	unsigned int readSize = 0;
	//                                         { 3, 20, 50, 100, 200 };
	unsigned int retryTimeArray[RETRY_TIMES] = { 1, 3, 5, 10, 100 };

	while (retry < RETRY_TIMES && readSize <= 0){

		wxMilliSleep(retryTimeArray[retry]);//3);

		readSize = hid_read(pickitHandle, buff, sizeOfBuff + 2);// Read To [0x0d] [0x0a]
		if (readSize != HID_EXPECT_DATA_LENGTH){
			PSU_DEBUG_PRINT(MSG_DEBUG, "readSize = %d", readSize);
		}

		retry++;
	}

	if (retry >= RETRY_TIMES){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Read Data Timeout Occurs, Retry = %d", retry);
		readSize = 0;
		return readSize;
	}

	return sizeOfBuff + 2;//readSize;
}

int ClosePickitDevice(void){

	int ret = 0;

	/* Close handle */
	hid_close(pickitHandle);

	pickitHandle = NULL;

	/* Free static HIDAPI objects. */
	ret = hid_exit();

	if (ret < 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "Close Pickit Device Handle Failed");
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Close Pickit Device Handle Success");
	}

	return EXIT_SUCCESS;
}