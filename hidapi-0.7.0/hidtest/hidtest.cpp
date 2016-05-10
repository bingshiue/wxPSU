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


void productSendBuffer(unsigned char* buffer, unsigned int lengthOfBuffer, unsigned int command, unsigned int responseLength);

int main(int argc, char* argv[])
{
	int res;
	unsigned char buf[64];
#define MAX_STR 255
	wchar_t wstr[MAX_STR];
	hid_device *handle;
	int i;
	int times = 0;

#ifdef WIN32
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#endif

	struct hid_device_info *devs, *cur_dev;

#if 1
	devs = hid_enumerate(0x0, 0x0);
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
	////handle = hid_open(0x4d8, 0x3f, L"12345");
	handle = hid_open(0x4d8, 0x3f, NULL);
	if (!handle) {
		printf("unable to open device\n");
		return 1;
	}

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

	// Set the hid_read() function to be non-blocking.
	hid_set_nonblocking(handle, 1);

	// Try to read from the device. There shoud be no
	// data here, but execution should not block.
	res = hid_read(handle, buf, 17);

	// Send a Feature Report to the device
	buf[0] = 0x2;
	buf[1] = 0xa0;
	buf[2] = 0x0a;
	buf[3] = 0x00;
	buf[4] = 0x00;
	res = hid_send_feature_report(handle, buf, 17);
	if (res < 0) {
		printf("Unable to send a feature report.\n");
	}

	memset(buf, 0, sizeof(buf));

	// Read a Feature Report from the device
	buf[0] = 0x2;
	res = hid_get_feature_report(handle, buf, sizeof(buf));
	if (res < 0) {
		printf("Unable to get a feature report.\n");
		printf("%ls", hid_error(handle));
	}
	else {
		// Print out the returned buffer.
		printf("Feature Report\n   ");
		for (i = 0; i < res; i++)
			printf("%02hhx ", buf[i]);
		printf("\n");
	}

	do {
		// Issue Command
		//productSendBuffer(buf, sizeof(buf), 0xdb, 0x05);// dynamic change value
		productSendBuffer(buf, sizeof(buf), 0x00, 0x02);


		// Read Data form HID Device
		res = 0;
		res = hid_write(handle, buf, 64);
		printf("res=%d \n", res);
		if (res < 0){
			printf("Unable to write() (2)\n");
		}

		// Read requested state. hid_read() has been set to be
		// non-blocking by the call to hid_set_nonblocking() above.
		// This loop demonstrates the non-blocking nature of hid_read().
		res = 0;
		while (res == 0) {
			res = hid_read(handle, buf, sizeof(buf));
			if (res == 0)
				printf("waiting...\n");
			if (res < 0)
				printf("Unable to read()\n");
#ifdef WIN32
			Sleep(20);
#else
			usleep(500 * 1000);
#endif
		}

		printf("Data read: Res = %d\n", res);
		// Print out the returned buffer.
		for (i = 0; i < res; i++){
			if (i % 0x10 == 0) printf("\n");
			printf("%02hhx ", buf[i]);
		}
		printf("\n");

		times++;

	} while (times < 5);

	/* Close handle */
	hid_close(handle);

	/* Free static HIDAPI objects. */
	hid_exit();

#ifdef WIN32
	system("pause");
#endif

	return 0;
}

void productSendBuffer(unsigned char* buffer, unsigned int lengthOfBuffer, unsigned int command, unsigned int responseLength){
	memset(buffer, 0x00, lengthOfBuffer);
	buffer[0] = 0x05;           // Report ID is 0x05
	buffer[1] = 0x0a;
	buffer[2] = 0x41;
	buffer[3] = 0x44;
	buffer[4] = 0xb6;
	buffer[5] = command;        // Command is 0x3a
	buffer[6] = 0x0d;
	buffer[7] = 0x0a;
	buffer[8] = 0xb7;
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
	buffer[30] = 0xb7;
	buffer[31] = responseLength; // Response Data Length

	buffer[32] = 0x00;
	buffer[33] = 0x01; //
	buffer[34] = 0xb7; //
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

#if 0
	memset(buf, 0x00, sizeof(buf));
	buf[0] = 0x05; // ID is 0x05
	buf[1] = 0x0a;
	buf[2] = 0x41;
	buf[3] = 0x44;
	buf[4] = 0xb6;
	buf[5] = 0x3a; // Command is 0x3a
	buf[6] = 0x0d;
	buf[7] = 0x0a;
	buf[8] = 0xb7;
	buf[9] = 0x02; // Response Data Length
	buf[10] = 0x0d;
	buf[11] = 0x0a;
	buf[12] = 0x01;
	buf[13] = 0x00;
	buf[14] = 0x00;
	buf[15] = 0x00;

	buf[16] = 0x00;
	buf[17] = 0x00;
	buf[18] = 0x00;
	buf[19] = 0x00;
	buf[20] = 0x00;
	buf[21] = 0x00;
	buf[22] = 0x00;
	buf[23] = 0x00;
	buf[24] = 0x00;
	buf[25] = 0x01;
	buf[26] = 0x02;//
	buf[27] = 0x00;
	buf[28] = 0x00;
	buf[29] = 0x02;
	buf[30] = 0xb7;
	buf[31] = 0x02;

	buf[32] = 0x00;
	buf[33] = 0x01;//
	buf[34] = 0xb7;//
	buf[35] = 0x00;
	buf[36] = 0x00;
	buf[37] = 0x00;
	buf[38] = 0x00;
	buf[39] = 0x00;
	buf[40] = 0x00;
	buf[41] = 0x00;
	buf[42] = 0x00;
	buf[43] = 0x00;
	buf[44] = 0x00;
	buf[45] = 0x00;
	buf[46] = 0x00;
	buf[47] = 0x00;

	buf[48] = 0x00;
	buf[49] = 0x00;
	buf[50] = 0x00;
	buf[51] = 0x00;
	buf[52] = 0x00;
	buf[53] = 0x00;
	buf[54] = 0x00;
	buf[55] = 0x00;
	buf[56] = 0x00;
	buf[57] = 0x00;
	buf[58] = 0x00;
	buf[59] = 0x00;
	buf[60] = 0x00;
	buf[61] = 0x00;
	buf[62] = 0x00;
	buf[63] = 0x00;
#endif
}