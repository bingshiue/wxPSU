/**
 * @file TotalPhase.cpp
 */

#include "TotalPhase.h"

// Global Parameters
Aardvark handle;
u16 ports[16];
int port;
u32 unique_ids[16];
int nelem = 16;


int EnumerateAvailableTotalPhaseDevice(BOOL *array, unsigned int sizeofArray){

	// Find all the attached devices
	int count = aa_find_devices_ext(nelem, ports, nelem, unique_ids);
	int i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d device(s) found:\n", count);

	// Print the information on each device
	if (count > nelem)  count = nelem;
	for (i = 0; i < count; ++i) {
		// Determine if the device is in-use
		const char *status = "(avail) ";
		if (ports[i] & AA_PORT_NOT_FREE) {
			ports[i] &= ~AA_PORT_NOT_FREE;
			status = "(in-use)";
		}

		// Display device port number, in-use status, and serial number
		PSU_DEBUG_PRINT(MSG_DEBUG, "port=%-3d %s (%04d-%06d)\n",
			ports[i], status,
			unique_ids[i] / 1000000,
			unique_ids[i] % 1000000);

		port = ports[i];
	}

	return 0;
}


int GetTotalPhaseDeviceStatus(void){

	return 0;
}


wchar_t* GetTotalPhaseOpenDeviceName(void){
	wchar_t* ret = NULL;

	return ret;
}


int OpenTotalPhaseDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting){

	// Open the device
	handle = aa_open(port);
	if (handle <= 0) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Unable to open Aardvark device on port %d\n", port);
		PSU_DEBUG_PRINT(MSG_ERROR, "Error code = %d\n", handle);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "Open Aardvark device on port %d Success\n", port);
	}

	// Ensure that the I2C subsystem is enabled
	aa_configure(handle, AA_CONFIG_SPI_I2C);

	// Enable the I2C bus pullup resistors (2.2k resistors).
	// This command is only effective on v2.0 hardware or greater.
	// The pullup resistors on the v1.02 hardware are enabled by default.
	aa_i2c_pullup(handle, AA_I2C_PULLUP_BOTH);

	// Enable the Aardvark adapter's power pins.
	// This command is only effective on v2.0 hardware or greater.
	// The power pins on the v1.02 hardware are not enabled by default.
	aa_target_power(handle, AA_TARGET_POWER_BOTH);

	return EXIT_SUCCESS;
}


int TotalPhaseSendData(unsigned char* buff, unsigned int size){

	return 0;
}

int TotalPhaseReadData(unsigned char* buff, unsigned int sizeOfBuff){

	return 0;
}

int CloseTotalPhaseDevice(void){

	// Close the device
	aa_close(handle);

	return EXIT_SUCCESS;
}