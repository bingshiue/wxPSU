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

		PSU_DEBUG_PRINT(MSG_DETAIL, "Return of hid_set_nonblocking is %d", res);
#endif

	}

	return EXIT_SUCCESS;
}

int PickitSendData(unsigned char* buff, unsigned int size){

	int LengthToWrite = size;
	int bytes_write = 0;

	if (pickitHandle == NULL) { return 0; }
	if (LengthToWrite != 65) LengthToWrite = 65;

	bytes_write = hid_write(pickitHandle, buff, LengthToWrite);
	PSU_DEBUG_PRINT(MSG_DEBUG, "bytes_write of hid_write is %d", bytes_write);


	return bytes_write;
}

#define RETRY_TIMES  5
#define SECONDARY_RETRY_TIMES  50 /**< Secondary Retry Times */
#define HID_EXPECT_DATA_LENGTH  64/**< HID Expect Data Length */
int PickitReadData(unsigned char* buff, unsigned int bytesToRead){
	bool bDataReceived = false;
	int BytesToRead;
	unsigned char TmpBuffer[256] = { 0 };
	unsigned int retry = 0;
	unsigned int secRerty = 0; /**< Secondary Retry */
	int readSize = 0;
	int secReadSize = 0;
	// Retry Interval Time                     { 3, 20, 50, 100, 200 };
	unsigned int retryTimeArray[RETRY_TIMES] = { 3, 3, 5, 100, 1000 };
	//unsigned int secRetryTimeArray[SECONDARY_RETRY_TIMES] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	unsigned int readOffset = 0;

	// Detemine BytesToRead
	if (bytesToRead >= 6){
		BytesToRead = (((int)bytesToRead - 6) * 2) + 4;// Bytes To Read (bytesToRead = 0x1C, Total Length Should be 0x3C) 
	}
	else{
		BytesToRead = 4;
	}

	// Read Data
	while (retry < RETRY_TIMES && readSize <= 0){

		PSU_DEBUG_PRINT(MSG_DEBUG, "BytesToRead = %x, retry = %d", BytesToRead, retry);

		// Sleep
		wxMilliSleep(retryTimeArray[retry]);//3);

		// Read Data To TmpBuffer
		readSize = hid_read(pickitHandle, TmpBuffer, 64);//sizeOfBuff + 2);// Read To [0x0d] [0x0a]
		// Check Data Length of Receive Data
		if (readSize != HID_EXPECT_DATA_LENGTH){
			PSU_DEBUG_PRINT(MSG_DEBUG, "readSize = %d", readSize);
		}

		if (readSize > 0 ){

			PMBUSHelper::dumpReceiveBuffer(TmpBuffer, readSize);

			if (TmpBuffer[0] == 0x86){

				// Copy Previous Received Data To Target Buffer
				for (int idx = 0; idx < TmpBuffer[1] + 2; idx++){
					buff[idx] = TmpBuffer[idx];
					readOffset = idx;
				}
				readOffset++;
				PSU_DEBUG_PRINT(MSG_DETAIL, "BytesToRead (%x)- TmpBuffer[1] (%x)", BytesToRead, TmpBuffer[1]);
				BytesToRead -= TmpBuffer[1];

				PSU_DEBUG_PRINT(MSG_DEBUG, "readOffset = %d", readOffset);
				PMBUSHelper::dumpReceiveBuffer(buff, readOffset);

				// Read Util No Data Income
				while (BytesToRead > 0){//secRerty < SECONDARY_RETRY_TIMES){//secRerty < SECONDARY_RETRY_TIMES){// && secReadSize <= 0){
					// Sleep
					wxMilliSleep(1);

					PSU_DEBUG_PRINT(MSG_DEBUG, "Read Until No Data, Retry Times = %d", secRerty);

					// Read Data To TmpBuffer
					secReadSize = hid_read(pickitHandle, TmpBuffer, 64);

					// Check Data Length of Receive Data
					if (secReadSize != HID_EXPECT_DATA_LENGTH){
						PSU_DEBUG_PRINT(MSG_DEBUG, "secReadSize = %d", secReadSize);
					}

					if (secReadSize > 0){
						PMBUSHelper::dumpReceiveBuffer(TmpBuffer, secReadSize);

						PSU_DEBUG_PRINT(MSG_DEBUG, "TmpBuffer[1] = %d", TmpBuffer[1]);
						for (int idx = 0, off = readOffset; idx < TmpBuffer[1]; idx++){
							PSU_DEBUG_PRINT(MSG_DEBUG, "buff[%d] = %02x", (off + idx), TmpBuffer[2 + idx]);
							buff[off + idx] = TmpBuffer[2 + idx];
							readOffset = (off + idx);
						}

						readOffset++;
						PSU_DEBUG_PRINT(MSG_DEBUG, "BytesToRead (%x)- TmpBuffer[1] (%x)", BytesToRead, TmpBuffer[1]);
						BytesToRead -= TmpBuffer[1];
					}

					buff[1] = (readOffset - 2);
					PMBUSHelper::dumpReceiveBuffer(buff, readOffset);

					secRerty++;

					if (BytesToRead <= 0 || secRerty > SECONDARY_RETRY_TIMES){
						if (BytesToRead > 0){
							PSU_DEBUG_PRINT(MSG_ALERT, "BREAK : BytesToRead = %x, secRerty = %d", BytesToRead, secRerty);
						}
						break;
					}
				}

			}
			else{

				// Copy Received Data To Target Buffer
				for (int idx = 0; idx < TmpBuffer[1] + 2; idx++){
					buff[idx] = TmpBuffer[idx];
					readOffset = idx;
				}
				readOffset++;
				break;
				//readOffset = readSize;
			}
		}


		retry++;
	}

	if (retry >= RETRY_TIMES){
		PSU_DEBUG_PRINT(MSG_DEBUG, "Read Data Timeout Occurs, Retry = %d", retry);
		readSize = 0;
		return readSize;
	}

	return readOffset;//64;//sizeOfBuff + 2;//readSize;
}

int PickitSendDataExtra(unsigned char* buff, unsigned int size, void* ptr){

	return PickitSendData(buff, size);
}


int PickitReadDataExtra(unsigned char* buff, unsigned int sizeOfBuff, void* ptr){

	return PickitReadData(buff, sizeOfBuff);
}

int ClosePickitDevice(void){

	int ret = 0;

	/* Close handle */
	if (pickitHandle != NULL){
		hid_close(pickitHandle);

		pickitHandle = NULL;
	}


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