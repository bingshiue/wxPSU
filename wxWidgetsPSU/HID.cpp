/**
 * @file HID.cpp
 */

#include <iostream>
using namespace std;

#include "CommonDef.h"
#include "PMBUSHelper.h"
#include "HID.h"

//#define READ_OPERATION_BLOCKING

#define DEFAULT_VID 0x4d8/**< Default VID */
#define DEFAULT_PID 0x3f/**< Default PID */
#define MAX_STR 255

hid_device *handle;/**< HID Device Handle */

wchar_t wstr[MAX_STR];
wchar_t productString[MAX_STR] = L"USB";

int EnumerateAvailableHIDDevice(BOOL *array, unsigned int sizeofArray){

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

	/* Enumerate VID : 0x4d8 PID : 0x3f */
	devs = hid_enumerate(DEFAULT_VID, DEFAULT_PID);
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

	return devicesFound;//EXIT_SUCCESS;
}

int GetHIDDeviceStatus(void){
	if (handle <= 0){
		return IODEVICE_CLOSE;
	}
	else{
		return IODEVICE_OPEN;
	}
}

wchar_t* GetHIDOpenDeviceName(void){
	return productString;
}

int OpenHIDDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting){

#ifdef WIN32
	UNREFERENCED_PARAMETER(array);
	UNREFERENCED_PARAMETER(sizeofArray);
#endif

	int res;

	handle = NULL;

	handle = hid_open(DEFAULT_VID, DEFAULT_PID, NULL);

	if (handle == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "HID device can't be opend");
		PSU_DEBUG_PRINT(MSG_DEBUG, "handle=%p", handle);
		return EXIT_FAILURE;
	}
	else{
		// Read the Manufacturer String
		wstr[0] = 0x0000;
		res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read manufacturer string");
		PSU_DEBUG_PRINT(MSG_ALERT, "Manufacturer String: %ls", wstr);

		lstrcpynW(PMBUSHelper::GetUSBInfo()->m_vendor_name, wstr, 255);

		// Read the Product String
		wstr[0] = 0x0000;
		res = hid_get_product_string(handle, wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read product string");
		PSU_DEBUG_PRINT(MSG_ALERT, "Product String: %ls", wstr);

		lstrcpynW(PMBUSHelper::GetUSBInfo()->m_product_name, wstr, 255);

		// Read the Serial Number String
		wstr[0] = 0x0000;
		res = hid_get_serial_number_string(handle, wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read serial number string");
		PSU_DEBUG_PRINT(MSG_ALERT, "Serial Number String: (%d) %ls", wstr[0], wstr);

		// Read Indexed String 1
		wstr[0] = 0x0000;
		res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read indexed string 1");
		PSU_DEBUG_PRINT(MSG_ALERT, "Indexed String 1: %ls", wstr);

#ifdef READ_OPERATION_BLOCKING
		// Set the hid_read() function to be blocking.
		hid_set_nonblocking(handle, 0);
#else
		// Set the hid_read() function to be non-blocking.
		hid_set_nonblocking(handle, 1);
#endif
	}

	return EXIT_SUCCESS;
}

int HIDSendData(unsigned char* buff, unsigned int size){

	int bytes_write = 0;

	if (handle == NULL) { return 0; }

	bytes_write = hid_write(handle, buff, size);

	return bytes_write;
}

#define RETRY_TIMES  5
#define HID_EXPECT_DATA_LENGTH  64/**< HID Expect Data Length */
int HIDReadData(unsigned char* buff, unsigned int sizeOfBuff){
	unsigned int retry = 0;
	unsigned int readSize = 0;
	unsigned int retryTimeArray[RETRY_TIMES] = { 3, 20, 50, 100, 200 };

	while (retry < RETRY_TIMES && readSize <= 0){

		wxMilliSleep(retryTimeArray[retry]);//3);

		readSize = hid_read(handle, buff, sizeOfBuff+2);// Read To [0x0d] [0x0a]
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

int CloseHIDDevice(void){

	int ret = 0;

	/* Close handle */
	hid_close(handle);

	handle = NULL;

	/* Free static HIDAPI objects. */
	ret = hid_exit();

	if (ret < 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "Close HID Device Handle Failed");
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Close HID Device Handle Success");
	}

	return EXIT_SUCCESS;
}

void productSendBuffer(unsigned char* buffer, unsigned int lengthOfBuffer, unsigned int command, unsigned int responseLength){
	memset(buffer, 0x00, lengthOfBuffer);
	buffer[0] = 0x05;           // Report ID is 0x05
	buffer[1] = 0x0a;
	buffer[2] = 0x41;
	buffer[3] = 0x44;
	buffer[4] = PMBUSHelper::GetSlaveAddress();
	buffer[5] = command;        // Command is 0x3a
	buffer[6] = 0x0d;
	buffer[7] = 0x0a;
	buffer[8] = PMBUSHelper::GetSlaveAddress() | 0x01;
	buffer[9] = responseLength; // Response Data Length
	buffer[10] = 0x0d;
	buffer[11] = 0x0a;
	buffer[12] = 0x01;
	buffer[13] = 0x00;
	buffer[14] = 0x00;
	buffer[15] = 0x00;

	buffer[16] = 0x00;
	buffer[17] = 0x00;
	buffer[18] = 0x00;
	buffer[19] = 0x00;
	buffer[20] = 0x00;
	buffer[21] = 0x00;
	buffer[22] = 0x00;
	buffer[23] = 0x00;
	buffer[24] = 0x00;
	buffer[25] = 0x01;
	buffer[26] = responseLength; // Response Data Length
	buffer[27] = 0x00;
	buffer[28] = 0x00;
	buffer[29] = 0x02;
	buffer[30] = PMBUSHelper::GetSlaveAddress() | 0x01;
	buffer[31] = responseLength; // Response Data Length

	buffer[32] = 0x00;
	buffer[33] = 0x01; //
	buffer[34] = PMBUSHelper::GetSlaveAddress() | 0x01;
	buffer[35] = 0x00;
	buffer[36] = 0x00;
	buffer[37] = 0x00;
	buffer[38] = 0x00;
	buffer[39] = 0x00;
	buffer[40] = 0x00;
	buffer[41] = 0x00;
	buffer[42] = 0x00;
	buffer[43] = 0x00;
	buffer[44] = 0x00;
	buffer[45] = 0x00;
	buffer[46] = 0x00;
	buffer[47] = 0x00;

	buffer[48] = 0x00;
	buffer[49] = 0x00;
	buffer[50] = 0x00;
	buffer[51] = 0x00;
	buffer[52] = 0x00;
	buffer[53] = 0x00;
	buffer[54] = 0x00;
	buffer[55] = 0x00;
	buffer[56] = 0x00;
	buffer[57] = 0x00;
	buffer[58] = 0x00;
	buffer[59] = 0x00;
	buffer[60] = 0x00;
	buffer[61] = 0x00;
	buffer[62] = 0x00;
	buffer[63] = 0x00;
}

