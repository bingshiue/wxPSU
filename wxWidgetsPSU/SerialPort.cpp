/**
 * @file SerialPort.cpp
 */
#include <iostream>
using namespace std;
#include "SerialPort.h"

HANDLE hComm;/**< Handle for Serial Port */
wchar_t ComPortName[] = L"COM3"; // Name of the Serial port(May Change) to be opened,
DCB dcbSerialParams = { 0 };/**< Initializing DCB structure */
//OVERLAPPED g_ol;/**< Overlapped Sructure */

int OpenSerialPort(int PortNum)
{
	int ret = SUCCESS;
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
		PSU_DEBUG_PRINT("\n Error! - Port %s can't be opened", ComPortName);
	}
	else{
		PSU_DEBUG_PRINT("\n Port %s Opened\n ", ComPortName);
	}

	/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Status = GetCommState(hComm, &dcbSerialParams);     //retreives the current settings

	if (Status == FALSE)
		PSU_DEBUG_PRINT("\n   Error! in GetCommState()");

	dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity   = NOPARITY;      // Setting Parity = None 

	Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

	if (Status == FALSE)
	{
		PSU_DEBUG_PRINT("\n   Error! in Setting DCB Structure");
	}
	else
	{
		PSU_DEBUG_PRINT("\n   Setting DCB Structure Successfull\n");
		PSU_DEBUG_PRINT("\n   Baudrate = %d", dcbSerialParams.BaudRate);
		PSU_DEBUG_PRINT("\n   ByteSize = %d", dcbSerialParams.ByteSize);
		PSU_DEBUG_PRINT("\n   StopBits = %d", dcbSerialParams.StopBits);
		PSU_DEBUG_PRINT("\n   Parity   = %d", dcbSerialParams.Parity);
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
	}
	else{
		PSU_DEBUG_PRINT("Setting Serial Port Timeouts Successfull \n");
	}

	return ret;
}

int SerialSendData(char* buff, int size){

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
		PSU_DEBUG_PRINT("%s:IO_PENDING",__FUNCTION__);
		while (!GetOverlappedResult(hComm, &g_ol, &send_suu, FALSE));
		if (send_suu != send_suu2){
			PSU_DEBUG_PRINT("send_suu != send_suu2");
			return 2;
		}
		else{
			PSU_DEBUG_PRINT("send_suu = %d \n",send_suu);
			ResetEvent(g_ol.hEvent);
			CloseHandle(g_ol.hEvent);
		}
	}
	else
	{
		PSU_DEBUG_PRINT("ERROR in Send");
		ClearCommError(hComm, &lpErrorsCH1, &lpStatCH1);
		//ClearCommError(hCom1, &lpErrorsCH1, &lpStatCH1);
		//lpErrorsCH1_lach |= lpErrorsCH1;
		return 1;
	}

#if 0
	if (Status == TRUE){
		PSU_DEBUG_PRINT("%s : %d bytes Written \n",__FUNCTION__,dNoOfBytesWritten);
	}
	else{
		PSU_DEBUG_PRINT("Error %d in Writing to Serial Port", GetLastError());
    }
#endif

    return dNoOfBytesWritten;
}

int SerialReadData(char* buff){
	BOOL  Status;                          // Status of the various operations 
	DWORD dwEventMask;                     // Event mask to trigger
	unsigned char  TempChar[1024] = { 0 };                  // Temperory Character
	char  SerialBuffer[256];               // Buffer Containing Rxed Data
	DWORD endtime;                         // For Compute Timeout
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	int i = 0;
	OVERLAPPED g_ol;                       /**< Overlapped Sructure */

	memset(&g_ol, 0, sizeof(OVERLAPPED));
	g_ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	/*------------------------------------ Setting Receive Mask ----------------------------------------------*/

	Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

	if (Status == FALSE){
		PSU_DEBUG_PRINT("\n\n    Error! in Setting CommMask");
	}
	else{
		PSU_DEBUG_PRINT("\n\n    Setting CommMask successfull");
	}

	/*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

	PSU_DEBUG_PRINT("\n\n    Waiting for Data Reception");

	Status = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received

	/*-------------------------- Program will Wait here till a Character is received ------------------------*/

	if (Status == FALSE)
	{
		PSU_DEBUG_PRINT("\n Error! in Setting WaitCommEvent()");
	}
	else //If  WaitCommEvent()==True Read the RXed data using ReadFile();
	{
		PSU_DEBUG_PRINT("\n Characters Received");
		//do
		//{
			Status = ReadFile(hComm, &TempChar, 10, &NoBytesRead, &g_ol);
			if (GetLastError() == ERROR_IO_PENDING){
				//
				endtime = GetTickCount() + 10000;
				//
				while (GetOverlappedResult(hComm, &g_ol, &NoBytesRead, TRUE) == 0){
					if (GetTickCount() > endtime)
					{
						PSU_DEBUG_PRINT("Receive Data Timeout ]n");
						break;
					}
				}
			}
			else{
				PSU_DEBUG_PRINT("\n\n ReadFile Occurs Unkonwn Error");
			}

			if (NoBytesRead > 0){
				/*------------Printing the RXed Data to Console----------------------*/
				PSU_DEBUG_PRINT("Get %d Bytes From SerialPort \n", NoBytesRead);
				
				int j = 0;
				for (j = 0; j < NoBytesRead; j++)		// j < i-1 to remove the dupliated last character
					PSU_DEBUG_PRINT("%x", TempChar[j]);
			}

			//SerialBuffer[i] = TempChar;
			//i++;
		//} 
	    //while (NoBytesRead > 0);

		ResetEvent(g_ol.hEvent);
		CloseHandle(g_ol.hEvent);
	}

	return i;// Return how many bytes data readed
}


int CloseSerialPort(void){
	int ret = SUCCESS;

	PSU_DEBUG_PRINT("Close Serial Port %p \n",hComm);
	CloseHandle(hComm);//Closing the Serial Port

	return ret;
}