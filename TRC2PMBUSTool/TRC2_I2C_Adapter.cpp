/**
 * @file TRC2_I2C_Adapter.cpp
 */
#include <iostream>
using namespace std;

#include "CommonDef.h"
#include "PMBUSHelper.h"
#include "TRC2_I2C_Adapter.h"

#define DEFAULT_TRC2_I2C_ADAPTER_VID 0x1234/**< Default TRC2 I2C Adapter VID */
#define DEFAULT_TRC2_I2C_ADAPTER_PID 0x0006/**< Default TRC2 I2C Adapter PID */
#define MAX_STR 255

static hid_device *handle;/**< HID Device Handle */

wchar_t trc2_i2c_adapter_wstr[MAX_STR];
wchar_t trc2_i2c_adapter_productString[MAX_STR] = L"TRC2 I2C Adapter";

int EnumerateAvailableTRC2I2CAdapterDevice(BOOL *array, unsigned int sizeofArray){

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
	devs = hid_enumerate(DEFAULT_TRC2_I2C_ADAPTER_VID, DEFAULT_TRC2_I2C_ADAPTER_PID);
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

int GetTRC2I2CAdapterDeviceStatus(void){
	if (handle <= 0){
		return IODEVICE_CLOSE;
	}
	else{
		return IODEVICE_OPEN;
	}
}

wchar_t* GetTRC2I2CAdapterOpenDeviceName(void){
	return trc2_i2c_adapter_productString;
}

int OpenTRC2I2CAdapterDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting){

#ifdef WIN32
	UNREFERENCED_PARAMETER(array);
	UNREFERENCED_PARAMETER(sizeofArray);
#endif

	int res;

	handle = NULL;

	handle = hid_open(DEFAULT_TRC2_I2C_ADAPTER_VID, DEFAULT_TRC2_I2C_ADAPTER_PID, NULL);

	if (handle == NULL){
		PSU_DEBUG_PRINT(MSG_ERROR, "HID device can't be opened");
		PSU_DEBUG_PRINT(MSG_DEBUG, "handle=%p", handle);
		return EXIT_FAILURE;
	}
	else{
		// Read the Manufacturer String
		trc2_i2c_adapter_wstr[0] = 0x0000;
		res = hid_get_manufacturer_string(handle, trc2_i2c_adapter_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read manufacturer string");
		//PSU_DEBUG_PRINT(MSG_ALERT, "Manufacturer String: %ls", wstr);
		PSU_DEBUG_PRINT(MSG_ALERT, "HID Device Manufacturer : %ls", trc2_i2c_adapter_wstr);

		COPY_WIDE_CHARACTERS(PMBUSHelper::GetUSBInfo()->m_vendor_name, trc2_i2c_adapter_wstr, 255);

		// Read the Product String
		trc2_i2c_adapter_wstr[0] = 0x0000;
		res = hid_get_product_string(handle, trc2_i2c_adapter_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read product string");
		//PSU_DEBUG_PRINT(MSG_ALERT, "Product String: %ls", wstr);
		PSU_DEBUG_PRINT(MSG_ALERT, "HID Device Product Name : %ls", trc2_i2c_adapter_wstr);

		COPY_WIDE_CHARACTERS(PMBUSHelper::GetUSBInfo()->m_product_name, trc2_i2c_adapter_wstr, 255);

		// Read the Serial Number String
		trc2_i2c_adapter_wstr[0] = 0x0000;
		res = hid_get_serial_number_string(handle, trc2_i2c_adapter_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read serial number string");
		//PSU_DEBUG_PRINT(MSG_ALERT, "Serial Number String: (%d) %ls", wstr[0], wstr);
		PSU_DEBUG_PRINT(MSG_ALERT, "HID Device Serial Number : (%d) %ls", trc2_i2c_adapter_wstr[0], trc2_i2c_adapter_wstr);

		// Read Indexed String 1
		trc2_i2c_adapter_wstr[0] = 0x0000;
		res = hid_get_indexed_string(handle, 1, trc2_i2c_adapter_wstr, MAX_STR);
		if (res < 0)
			PSU_DEBUG_PRINT(MSG_ALERT, "Unable to read indexed string 1");
		PSU_DEBUG_PRINT(MSG_DEBUG, "HID Device Indexed String 1: %ls", trc2_i2c_adapter_wstr);

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

int TRC2I2CAdapterSendData(unsigned char* buff, unsigned int size){

	int bytes_write = 0;

	if (handle == NULL) { return 0; }

	bytes_write = hid_write(handle, buff, size+1);// Write 65 Bytes

	return bytes_write;
}

int TRC2I2CAdapterSendDataExtra(unsigned char* buff, unsigned int size, void* ptr){
	return TRC2I2CAdapterSendData(buff,size);
}

#define RETRY_TIMES  5
#define HID_EXPECT_DATA_LENGTH  64/**< HID Expect Data Length */
int TRC2I2CAdapterReadData(unsigned char* buff, unsigned int sizeOfBuff){
	unsigned int retry = 0;
	unsigned int readSize = 0;
	//                                         { 3, 20, 50, 100, 200 };
	unsigned int retryTimeArray[RETRY_TIMES] = { 1, 3, 5, 10, 100 };

	if(sizeOfBuff >=6){
		sizeOfBuff -= 6;
	}else{
		PSU_DEBUG_PRINT(MSG_ALERT, "sizeOfBuff < 6", sizeOfBuff);
	}


	while (retry < RETRY_TIMES && readSize <= 0){

		wxMilliSleep(retryTimeArray[retry]);//3);

		readSize = hid_read(handle, buff, 64);// Fix Read 64 Bytes
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

	return sizeOfBuff;//readSize;
}

int TRC2I2CAdapterReadDataExtra(unsigned char* buff, unsigned int sizeOfBuff, void* ptr){
	return TRC2I2CAdapterReadData(buff, sizeOfBuff);
}

int CloseTRC2I2CAdapterDevice(void){

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






