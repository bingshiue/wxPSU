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

#define TOTALPHASE_I2C_SLAVEADDR_TRAN(SLAVE_ADDR) (SLAVE_ADDR >> 1)

#define BUFFER_SIZE  256

u16 num_write = 0;
u16 num_read = 0;

unsigned char i2cReadCMDBuffer[BUFFER_SIZE];
unsigned char i2cWriteCMDBuffer[BUFFER_SIZE];
unsigned char i2cBlockWRCMDBuffer[BUFFER_SIZE];

unsigned char TotalPhaseRecvBuffer[BUFFER_SIZE];

#define STR_MAX_LEN  255
wchar_t deviceName[STR_MAX_LEN] = L"TotalPhase";

int EnumerateAvailableTotalPhaseDevice(BOOL *array, unsigned int sizeofArray){

	// Find all the attached devices
	int count;
	count = aa_find_devices_ext(nelem, ports, nelem, unique_ids);
	int i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "%d device(s) found:", count);

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
		PSU_DEBUG_PRINT(MSG_DEBUG, "port=%-3d %s (%04d-%06d)",
			ports[i], status,
			unique_ids[i] / 1000000,
			unique_ids[i] % 1000000);

		port = ports[i];
	}

	return count;
}


int GetTotalPhaseDeviceStatus(void){
	if (handle <= 0){
		return IODEVICE_CLOSE;
	}
	else{
		return IODEVICE_OPEN;
	}
}


wchar_t* GetTotalPhaseOpenDeviceName(void){
	return deviceName;
}


int OpenTotalPhaseDevice(BOOL *array, unsigned int sizeofArray, PORT_SETTING_t* portSetting){

	int bitrate;

	// Open the device
	handle = aa_open(port);
	if (handle <= 0) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Unable to open Aardvark device on port %d", port);
		PSU_DEBUG_PRINT(MSG_ERROR, "Error code = %d", handle);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "Open Aardvark device on port %d Success", port);
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

	// Setup the bitrate
	bitrate = aa_i2c_bitrate(handle, PMBUSHelper::GetAppSettings()->m_totalPhase_I2C_Bitrate);
	PSU_DEBUG_PRINT(MSG_ALERT, "TOTAL PHASE Set Bitrate to %d kHz", bitrate);

	return EXIT_SUCCESS;
}


int TotalPhaseSendData(unsigned char* buff, unsigned int size){
	// 

	memset(i2cReadCMDBuffer, 0, BUFFER_SIZE);

	i2cReadCMDBuffer[0] = buff[0];// Write Bytes
	i2cReadCMDBuffer[1] = buff[1];// Read Bytes
	i2cReadCMDBuffer[2] = TOTALPHASE_I2C_SLAVEADDR_TRAN(buff[2]);// Slave Address
	i2cReadCMDBuffer[3] = buff[3];// CMD

	PSU_DEBUG_PRINT(MSG_DEBUG, "buff[0]=%02x", buff[0]);
	PSU_DEBUG_PRINT(MSG_DEBUG, "buff[1]=%02x", buff[1]);
	PSU_DEBUG_PRINT(MSG_DEBUG, "buff[2]=%02x", TOTALPHASE_I2C_SLAVEADDR_TRAN(buff[2]));
	PSU_DEBUG_PRINT(MSG_DEBUG, "buff[3]=%02x", buff[3]);
	PSU_DEBUG_PRINT(MSG_DEBUG, "buff[4]=%02x", buff[4]);
	PSU_DEBUG_PRINT(MSG_DEBUG, "buff[5]=%02x", buff[5]);

	PMBUSHelper::getTotalPhaseWriteReadLastError() = aa_i2c_write_read(
		handle,// handle
		TOTALPHASE_I2C_SLAVEADDR_TRAN(buff[2]),// slave address
		AA_I2C_NO_FLAGS,// flags
		buff[0],// out_num_bytes
		&buff[3],// out_data
		&num_write,//num_written
		buff[1],//in_num_bytes
		TotalPhaseRecvBuffer,//in_data
		&num_read //num_read
		);

	if (PMBUSHelper::getTotalPhaseWriteReadLastError() != 0){
		PSU_DEBUG_PRINT(MSG_ERROR, "%s : aa_i2c_write_read failed, Last Error = %d, Num_Write is %d, Num_Read is %d", __FUNCTIONW__, PMBUSHelper::getTotalPhaseWriteReadLastError(), num_write, num_read);
	}

#if 0
	ret = aa_i2c_write_ext(
		handle,
		i2cReadCMDBuffer[0],
		AA_I2C_NO_FLAGS,
		1,
		&buff[1],
		&num_write
		);

	PSU_DEBUG_PRINT(MSG_DEBUG, "ret = %d, Num_Write of aa_i2c_write_ext is %d", ret, num_write);
#endif

	return num_write;
}

int TotalPhaseReadData(unsigned char* buff, unsigned int sizeOfBuff){

	PSU_DEBUG_PRINT(MSG_DEBUG, "Num_Read of is %d:", num_read);
	for (int idx = 0; idx < num_read; idx++){
		PSU_DEBUG_PRINT(MSG_DEBUG, "TotalPhaseRecvBuffer[%d] = %02x", idx, TotalPhaseRecvBuffer[idx]);
		buff[idx] = TotalPhaseRecvBuffer[idx];
	}

#if 0
	u16 num_read;

	aa_i2c_read_ext(
		handle,
		i2cReadCMDBuffer[0],
		AA_I2C_NO_FLAGS,
		2,
		buff,
		&num_read
	);

	PSU_DEBUG_PRINT(MSG_DEBUG, "Num_Read of aa_i2c_read_ext is %d:", num_read);
	for (int idx = 0; idx < num_read; idx++){
		PSU_DEBUG_PRINT(MSG_DEBUG, "buff[%d] = %02x", idx, buff[idx]);
	}
#endif

	return num_read;
}

int CloseTotalPhaseDevice(void){

	int ret;

	// Close the device
	if (handle){
		ret = aa_close(handle);
		PSU_DEBUG_PRINT(MSG_DEBUG, "Ret of aa_close is %d", ret);
		handle = 0;
	}

	return EXIT_SUCCESS;
}