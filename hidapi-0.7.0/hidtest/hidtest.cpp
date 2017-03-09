/*******************************************************
Windows HID simplification

Alan Ott
Signal 11 Software

8/22/2009

Copyright 2009, All Rights Reserved.

This contents of this file may be used by anyone
for any reason without any conditions and may be
used as a starting point for your own applications
which use HIDAPI.
********************************************************/

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include "hidapi.h"

// Headers needed for sleeping.
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int sendData(hid_device *handle, unsigned char* buffer, unsigned int sizeOfBuffer){
	int res = 0;
	
	printf("================================================");
	printf("Data Send: ");
	// Print out the returned buffer.
	for (unsigned int i = 0; i < sizeOfBuffer; i++){
		if (i % 0x10 == 0) printf("\n");
		printf("%02hhx ", buffer[i]);
	}
	printf("\n");
	
	res = hid_write(handle, buffer, 65);
	printf("res=%d \n", res);
	if (res < 0){
		printf("Unable to write() (2)\n");
		wprintf(L"ERROR : %ls", hid_error(handle));
		printf("\n");
	}
	else{
		printf("write() (2) Success \n");
	}

	return res;
}

int readData(hid_device *handle, unsigned char* buffer){
	int readBytes = 0;
	int reTry = 0;

	readBytes = 0;
	while (readBytes == 0) {
		readBytes = hid_read(handle, buffer, 256);
		if (readBytes == 0){
			printf("waiting...\n");
			reTry++;

			if (reTry >= 3){
				printf("Retry = %d, Break \n", reTry);
				break;
			}

#ifdef WIN32
			Sleep(5);
#else
			usleep(500 * 1000);
#endif
		}
		if (readBytes < 0)
			printf("Unable to read()\n");
	}


	if (readBytes > 0){
		printf("Data Read: readBytes = %d\n", readBytes);
		// Print out the returned buffer.
		for (int i = 0; i < readBytes; i++){
			if (i % 0x10 == 0) printf("\n");
			printf("%02hhx ", buffer[i]);
		}
		printf("\n");
	}

	return readBytes;
}

int InitPicKit(hid_device *handle, unsigned char* sendBuffer, unsigned char* recvBuffer){
	unsigned int offset = 0;

	//# 1
#if 1   //76000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x76;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 2);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 2
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif


	//# 3
#if 1   //01000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 2);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 4
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 5
#if 1	//02 c0 00 00 0a ff 00 00 00 01 31 20 00 ff 3f 00 00 03 06 00 00 00 00 00 31 000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x02;
	sendBuffer[offset++] = 0xc0;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x0a;
	sendBuffer[offset++] = 0xff;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x31;
	sendBuffer[offset++] = 0x20;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0xff;
	sendBuffer[offset++] = 0x3f;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x03;
	sendBuffer[offset++] = 0x06;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x31;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 26);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 6 (Point For Pickit Can Write/Read Correctly)
#if 1   //01010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x01;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 7
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 8
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 9
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 10
#if 1   //01010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x00;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 11
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 12
#if 1	//02 e0 00 00 0a ff 00 00 00 01 31 20 00 ff 3f 00 00 03 06 00 00 00 00 00 31 00 00 02 000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x02;
	sendBuffer[offset++] = 0xe0;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x0a;
	sendBuffer[offset++] = 0xff;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x31;
	sendBuffer[offset++] = 0x20;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0xff;
	sendBuffer[offset++] = 0x3f;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x03;
	sendBuffer[offset++] = 0x06;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x31;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 29);

	// Receive Response
	readData(handle, recvBuffer);
#endif

	//# 13
#if 1   //01010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x01;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 14
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 15
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 16
#if 1	//030212c1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x03;
	sendBuffer[offset++] = 0x02;
	sendBuffer[offset++] = 0x12;
	sendBuffer[offset++] = 0xc1;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 5);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 17
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 18
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 19
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 20
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 21
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 22
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 23
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 24
#if 1   //01010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x00;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 25
#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 26
#if 1	//02 c0 00 00 0a ff 00 00 00 01 31 20 00 ff 3f 00 00 03 06 00 00 00 00 00 31 00 00 02 000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x02;
	sendBuffer[offset++] = 0xc0;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x0a;
	sendBuffer[offset++] = 0xff;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x31;
	sendBuffer[offset++] = 0x20;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0xff;
	sendBuffer[offset++] = 0x3f;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x03;
	sendBuffer[offset++] = 0x06;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x31;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x02;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 29);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	//# 27
#if 1   //01010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x01;
	sendBuffer[offset++] = 0x01;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	/*** Skip 23 Times 01 02 ***/

	//# 28
#if 1	//0bab0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	memset(sendBuffer, 0, 256);
	offset = 0;

	sendBuffer[offset++] = 0x00;
	sendBuffer[offset++] = 0x0b;
	sendBuffer[offset++] = 0xab;

	for (int idx = offset; idx<65; idx++){
		sendBuffer[idx] = 0;
	}

	// Send 
	sendData(handle, sendBuffer, 3);

	// Receive Response
	readData(handle, recvBuffer);

#endif

	return 0;
}

#define LOOP_TIIMES 1000
int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[256];
	unsigned char recvBuffer[256];
#define MAX_STR 255
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	int i;
	int times = 0;
	int sendTimes = 0;
	unsigned int offset = 0;

#ifdef WIN32
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#endif

	struct hid_device_info *devs, *cur_dev;

	memset(recvBuffer, 0, 256);

#if 1
	devs = hid_enumerate(0x4d8, 0x036);
	cur_dev = devs;
	while (cur_dev) {
		printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
		printf("\n");
		printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
		printf("  Product:      %ls\n", cur_dev->product_string);
		printf("  Release:      %hx\n", cur_dev->release_number);
		printf("  Interface:    %d\n", cur_dev->interface_number);
		printf("  Usage Page:   0x%02x\n", cur_dev->usage_page);
		printf("  Usage:        0x%02x\n", cur_dev->usage);
		printf("\n");
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);
#endif

	// Set up the command buffer.
	memset(buf, 0x00, sizeof(buf));
	buf[0] = 0x01;
	buf[1] = 0x81;


	// Open the device using the VID, PID,
	// and optionally the Serial number.
	//handle = hid_open(0x4d8, 0x3f, L"12345");
	handle = hid_open(0x4d8, 0x36, NULL);
	if (!handle) {
		printf("unable to open device\n");
		return 1;
	}

#if 1
	// Read the Manufacturer String
	wstr[0] = 0x0000;
	res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read manufacturer string\n");
	printf("Manufacturer String: %ls\n", wstr);

	// Read the Product String
	wstr[0] = 0x0000;
	res = hid_get_product_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read product string\n");
	printf("Product String: %ls\n", wstr);

	// Read the Serial Number String
	wstr[0] = 0x0000;
	res = hid_get_serial_number_string(handle, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read serial number string\n");
	printf("Serial Number String: (%d) %ls", wstr[0], wstr);
	printf("\n");

	// Read Indexed String 1
	wstr[0] = 0x0000;
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	if (res < 0)
		printf("Unable to read indexed string 1\n");
	printf("Indexed String 1: %ls\n", wstr);
#endif

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);

	// Try to read from the device. There shoud be no
	// data here, but execution should not block.
	res = hid_read(handle, buf, 17);

	// Send a Feature Report to the device

#if 1
	res = hid_send_feature_report(handle, buf, 17);
	if (res < 0) {
		printf("Unable to send a feature report.\n");
	}
	else{
		printf("Send a feature report OK.\n");
	}

	memset(buf, 0, sizeof(buf));

	// Read a Feature Report from the device
	buf[0] = 0x2;
	res = hid_get_feature_report(handle, buf, sizeof(buf));
	if (res < 0) {
		printf("Unable to get a feature report.\n");
		printf("%ls \n", hid_error(handle));
	}
	else {
		// Print out the returned buffer.
		printf("Feature Report\n   ");
		for (i = 0; i < res; i++)
			printf("%02hhx ", buf[i]);
		printf("\n");
	}
#endif

	// Initialize Pickit
	InitPicKit(handle, buf, recvBuffer);

	// Infinite Loop
	for (;;){

		printf("SendTimes =%d \n", sendTimes);
		sendTimes++;

		if (sendTimes % 2 == 0){

#if 1   //01020000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
			offset = 0;

			buf[offset++] = 0x00;
			buf[offset++] = 0x01;
			buf[offset++] = 0x02;

			for (int idx = offset; idx < 65; idx++){
				buf[idx] = 0;
			}

			// Send 
			sendData(handle, buf, 3);

#endif
		}
		else
		{
#if 1	//03 0e 81 84 02 b6 ec 83 84 01 b7 89 03 82 1f 77 000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
		//Response As Below
		//86 0a 80 10 00 10 08 10 c2 81 1c 77 80 00 01 31 20 00 ff 3f 00 00 03 06 00 00 00 00 
		//00 31 83 00 02 00 00 00 00 01 f6 00 00 00 00 00 00 00 00 00 c2 c2 31 84 00 ff 00 ff 
		//00 ff 80 b6 56 2c 9e 55
			offset = 0;

			buf[offset++] = 0x00;
			buf[offset++] = 0x03;
			buf[offset++] = 0x0e;
			buf[offset++] = 0x81;
			buf[offset++] = 0x84;
			buf[offset++] = 0x02;
			buf[offset++] = 0xb6;
			buf[offset++] = 0xec;
			buf[offset++] = 0x83;
			buf[offset++] = 0x84;
			buf[offset++] = 0x01;
			buf[offset++] = 0xb7;
			buf[offset++] = 0x89;
			buf[offset++] = 0x03;
			buf[offset++] = 0x82;
			buf[offset++] = 0x1f;
			buf[offset++] = 0x77;

			for (int idx = offset; idx < 65; idx++){
				buf[idx] = 0;
			}

			// Send 
			sendData(handle, buf, 17);
		}

#endif
		Sleep(1);

		// Read requested state. hid_read() has been set to be
		// non-blocking by the call to hid_set_nonblocking() above.
		// This loop demonstrates the non-blocking nature of hid_read().
		readData(handle, recvBuffer);

		Sleep(1);

		if (sendTimes >= LOOP_TIIMES){
			printf("SendTimes = %d, Break Loop  \n", sendTimes);
			break;
		}

	}

	/* Close handle */
	hid_close(handle);

	/* Free static HIDAPI objects. */
	hid_exit();

#ifdef WIN32
	system("pause");
#endif

	return 0;
}