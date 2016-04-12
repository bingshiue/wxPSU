/**
 * @file SerialPort.cpp
 */
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include "SerialPort.h"

HANDLE hComm;/**< Handle for Serial Port */
wchar_t ComPortName[] = L"COM3"; // Name of the Serial port(May Change) to be opened,
DCB dcbSerialParams = { 0 };/**< Initializing DCB structure */
//OVERLAPPED g_ol;/**< Overlapped Sructure */

int OpenSerialPort(int PortNum)
{
	int ret = EXIT_SUCCESS;
	BOOL Status;
	hComm = 
	CreateFile(ComPortName,                // Name of the Port to be Opened
		GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
		0,                                 // No Sharing, ports cant be shared
		NULL,                              // No Security
		OPEN_EXISTING,                     // Open existing port only
		FILE_FLAG_OVERLAPPED,              // (Non Overlapped I/O)
		NULL);                             // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE){
		PSU_DEBUG_PRINT("Error! Port %s can't be opened \n", ComPortName);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT("Port %s Opened \n", ComPortName);
	}

	/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Status = GetCommState(hComm, &dcbSerialParams);     //retreives the current settings

	if (Status == FALSE){
		PSU_DEBUG_PRINT("Error! in GetCommState() \n");
		return EXIT_FAILURE;
	}

	dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity   = NOPARITY;      // Setting Parity = None 

	Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

	if (Status == FALSE)
	{
		PSU_DEBUG_PRINT("Error! in Setting DCB Structure \n");
		return EXIT_FAILURE;
	}
	else
	{
		PSU_DEBUG_PRINT("Setting DCB Structure Successfull \n");
		PSU_DEBUG_PRINT("Baudrate = %d \n", dcbSerialParams.BaudRate);
		PSU_DEBUG_PRINT("ByteSize = %d \n", dcbSerialParams.ByteSize);
		PSU_DEBUG_PRINT("StopBits = %d \n", dcbSerialParams.StopBits);
		PSU_DEBUG_PRINT("Parity   = %d \n", dcbSerialParams.Parity);
	}

	/*------------------------------------ Setting Timeouts --------------------------------------------------*/

	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (SetCommTimeouts(hComm, &timeouts) == FALSE){
		PSU_DEBUG_PRINT("Error! in Setting Time Outs \n");
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT("Setting Serial Port Timeouts Successfull \n");
	}

	return ret;
}

int SerialSendData(unsigned char* buff, unsigned int size){

	BOOL Status;
	DWORD  dNoOfBytesWritten = 0;
	OVERLAPPED g_ol;/**< Overlapped Sructure */
	int send_err;
	DWORD send_suu;
	DWORD send_suu2;
	DWORD lpErrorsCH1; /* Error Information */
	COMSTAT lpStatCH1; /* Port Status */

	send_suu  = size;
	send_suu2 = send_suu;

	ZeroMemory(&g_ol, sizeof(g_ol));
	g_ol.Offset = 0;
	g_ol.OffsetHigh = 0;
	g_ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);;

	Status =
		WriteFile(hComm,     // Handle to the Serialport
		buff,                // Data to be written to the port 
		size,                // No of bytes to write into the port
		&dNoOfBytesWritten,  // No of bytes written to the port
		&g_ol);

	send_err = GetLastError();
	if (send_err == ERROR_IO_PENDING)
	{
		PSU_DEBUG_PRINT("%s:IO_PENDING \n",__FUNCTION__);
		while (!GetOverlappedResult(hComm, &g_ol, &send_suu, FALSE));
		if (send_suu != send_suu2){
			PSU_DEBUG_PRINT("send_suu != send_suu2 \n");
			return 2;
		}
		else{
			PSU_DEBUG_PRINT("send_suu = %d \n",send_suu);
			PSU_DEBUG_PRINT("%s:Send :",__FUNCTION__);
			for (unsigned int idx = 0; idx < size; idx++){
				PSU_DEBUG_PRINT(" %2x ",buff[idx]);
			}
			PSU_DEBUG_PRINT("\n")
			ResetEvent(g_ol.hEvent);
			CloseHandle(g_ol.hEvent);
		}
	}
	else
	{
		PSU_DEBUG_PRINT("ERROR in Send \n");
		ClearCommError(hComm, &lpErrorsCH1, &lpStatCH1);
		//ClearCommError(hCom1, &lpErrorsCH1, &lpStatCH1);
		//lpErrorsCH1_lach |= lpErrorsCH1;
		return 1;
	}

    return dNoOfBytesWritten;
}

int SerialReadData(unsigned char* buff){
	BOOL  Status;                          // Status of the various operations 
	DWORD dwEventMask;                     // Event mask to trigger
	unsigned char  TempChar[1024] = { 0 }; // Temperory Character
	//char  SerialBuffer[256];             // Buffer Containing Rxed Data
	DWORD endtime;                         // For Compute Timeout
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	int i = 0;
	OVERLAPPED g_ol;                       /**< Overlapped Sructure */

	memset(&g_ol, 0, sizeof(OVERLAPPED));
	g_ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	/*------------------------------------ Setting Receive Mask ----------------------------------------------*/

	Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

	if (Status == FALSE){
		PSU_DEBUG_PRINT("Error! in Setting CommMask \n");
	}
	else{
		PSU_DEBUG_PRINT("Setting CommMask successfull \n");
	}

	/*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

	PSU_DEBUG_PRINT("Waiting for Data Reception \n");

	Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received

	/*-------------------------- Program will Wait here till a Character is received ------------------------*/

	if (Status == FALSE)
	{
		PSU_DEBUG_PRINT("Error! in Setting WaitCommEvent() \n");
	}
	else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
	{
		PSU_DEBUG_PRINT("Characters Received \n");

		Status = ReadFile(hComm, &TempChar, 10, &NoBytesRead, &g_ol);
		if (GetLastError() == ERROR_IO_PENDING){
			//
			endtime = GetTickCount() + 50000;
			//
			while (GetOverlappedResult(hComm, &g_ol, &NoBytesRead, FALSE) == 0){
				if (GetTickCount() > endtime)
				{
					PSU_DEBUG_PRINT("Receive Data Timeout \n");
					break;
				}
			}
		}
		else{
			PSU_DEBUG_PRINT("ReadFile Occurs Unkonwn Error : %d \n", GetLastError());
		}

		if (NoBytesRead > 0){
			/*------------Printing the RXed Data to Console----------------------*/
			PSU_DEBUG_PRINT("Get %d Bytes From SerialPort :", NoBytesRead);
				
			for (unsigned int idx = 0; idx < NoBytesRead; idx++){
				PSU_DEBUG_PRINT(" %2x ", TempChar[idx]);
			}
			PSU_DEBUG_PRINT("\n");
		}

		ResetEvent(g_ol.hEvent);
		CloseHandle(g_ol.hEvent);
	}

	return NoBytesRead;// Return how many bytes data readed
}


int CloseSerialPort(void){
	int ret = SUCCESS;

	PSU_DEBUG_PRINT("Close Serial Port %p \n",hComm);
	CloseHandle(hComm);//Closing the Serial Port

	return ret;
}