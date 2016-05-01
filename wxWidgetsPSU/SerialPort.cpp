/**
 * @file SerialPort.cpp
 */
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include "SerialPort.h"


BOOL GetSerialPortName(wchar_t *buff, unsigned int sizeOfBuff, unsigned int num){
	BOOL ret = TRUE;

	if (sizeOfBuff < 16 || num < 0){
		PSU_DEBUG_PRINT("%s: Error Occurs, sizeOfBuff=%d, num=%d", __FUNCTIONW__, sizeOfBuff, num);
		ret = FALSE;
		return ret;
	}

	if (num <= 9){
		wsprintf(buff,L"Com%d",num+1);
	}
	else{
		wsprintf(buff,L"\\\\.\\COM%d", num + 1);// "\\.\COMx"
	}

	return ret;
}


int EnumerateAvailableSerialPort(BOOL *array, unsigned int sizeofArray){
    
	HANDLE enumHandle;
	wchar_t SerialPortName[64];
	unsigned int success = 0;


	for (unsigned int idx=0; idx < sizeofArray; idx++){

		GetSerialPortName(SerialPortName, sizeof(SerialPortName) / sizeof(wchar_t), idx);

		enumHandle =
			CreateFile(SerialPortName,        // Name of the Port to be Opened
			GENERIC_READ | GENERIC_WRITE,     // Read/Write Access
			0,                                // No Sharing, ports cant be shared
			NULL,                             // No Security
			OPEN_EXISTING,                    // Open existing port only
			FILE_FLAG_OVERLAPPED,             // (Non Overlapped I/O)
			NULL);

		if (enumHandle == INVALID_HANDLE_VALUE){
			PSU_DEBUG_PRINT("%s: Open %s Failed" , __FUNCTIONW__, SerialPortName);
		}
		else{
			PSU_DEBUG_PRINT("%s: Open %s Success", __FUNCTIONW__, SerialPortName);
			array[idx] = TRUE;
			success++;
			// Close Handle
			CloseHandle(enumHandle);
		}

	}

	return success;
}

unsigned int GetFirstAvailableSerialPortIndex(BOOL *array, unsigned int sizeofArray){

	unsigned int index = 0;

	for (unsigned int idx = 0; idx < sizeofArray; idx++){
		if (array[idx]==TRUE){
			return index;
		}
	}

	return index;

}


HANDLE hComm;/**< Handle for Serial Port */
wchar_t ComPortName[] = L"COM3"; // Name of the Serial port(May Change) to be opened,
DCB dcbSerialParams = { 0 };/**< Initializing DCB structure */
//OVERLAPPED g_ol;/**< Overlapped Sructure */

int OpenSerialPort(BOOL *array, unsigned int sizeofArray)//int PortNum)
{
	int ret = EXIT_SUCCESS;
	BOOL Status;
	wchar_t SerialPortName[64];

	unsigned int availableIndex = GetFirstAvailableSerialPortIndex(array, sizeofArray);
	GetSerialPortName(SerialPortName, sizeof(SerialPortName) / sizeof(wchar_t), availableIndex);


	hComm = 
		CreateFile(SerialPortName,//ComPortName,                // Name of the Port to be Opened
		GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
		0,                                 // No Sharing, ports cant be shared
		NULL,                              // No Security
		OPEN_EXISTING,                     // Open existing port only
		FILE_FLAG_OVERLAPPED,              // (Non Overlapped I/O)
		NULL);                             // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE){
		PSU_DEBUG_PRINT("Error! Port %s can't be opened", SerialPortName);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT("Port %s Opened", SerialPortName);
	}

	/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Status = GetCommState(hComm, &dcbSerialParams);     //retreives the current settings

	if (Status == FALSE){
		PSU_DEBUG_PRINT("Error! in GetCommState()");
		return EXIT_FAILURE;
	}

	dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity   = NOPARITY;      // Setting Parity = None 

	Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

	if (Status == FALSE)
	{
		PSU_DEBUG_PRINT("Error! in Setting DCB Structure");
		return EXIT_FAILURE;
	}
	else
	{
		PSU_DEBUG_PRINT("Setting DCB Structure Successfull");
		PSU_DEBUG_PRINT("Baudrate = %d", dcbSerialParams.BaudRate);
		PSU_DEBUG_PRINT("ByteSize = %d", dcbSerialParams.ByteSize);
		PSU_DEBUG_PRINT("StopBits = %d", dcbSerialParams.StopBits);
		PSU_DEBUG_PRINT("Parity   = %d", dcbSerialParams.Parity);
	}

	/*------------------------------------ Setting Timeouts --------------------------------------------------*/

	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
#if 0
	if (SetCommTimeouts(hComm, &timeouts) == FALSE){
		PSU_DEBUG_PRINT("Error! in Setting Time Outs");
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT("Setting Serial Port Timeouts Successfull");
	}
#endif

	return ret;
}

int SerialSendData(unsigned char* buff, unsigned int size){

	wxString outputMsg("");
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
	g_ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);

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
		
			outputMsg += wxString::Format("%s:Send :", __FUNCTION__);
			for (unsigned int idx = 0; idx < size; idx++){
				outputMsg += wxString::Format(" %02x ", buff[idx]);
			}

			wxLogMessage("Serial Port Send Data Length (send_suu) = %d -> %s", send_suu, outputMsg.c_str());
			//PSU_DEBUG_PRINT(outputMsg.c_str());

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

    return dNoOfBytesWritten;
}

#define NUMBER_OF_BYTES_TO_READ    1   /**< Number of Bytes To Read */
#define STATUS_CHECK_TIMEOUT      50   // Milliseconds
int SerialReadData(unsigned char* buff){
	wxString outputMsg("");                // Output Messages
	BOOL  Status;                          // Status of the various operations
	int ReadFileStatus;                    //
	DWORD dwEventMask;                     // Event mask to trigger
	unsigned char TempChar;                // Temperory Character
	unsigned char RcvBuf[1024];            //
	//char  SerialBuffer[256];             // Buffer Containing Rxed Data
	DWORD endtime;                         // For Compute Timeout
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	OVERLAPPED g_ol;                       // Overlapped Sructure */
	OVERLAPPED g_ol2;                       // Overlapped Sructure */
	BOOL bWaitForSingle;                   //
	BOOL bWaitRxCharEvent;//
	DWORD lastError;                       // Last Error
	DWORD dwRes;
	unsigned int i = 0;


	dwEventMask = 0x00000000;

	bWaitForSingle = false;
	bWaitRxCharEvent = false;

	//
	memset(&g_ol, 0, sizeof(OVERLAPPED));
	g_ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//
	memset(&g_ol2, 0, sizeof(OVERLAPPED));
	g_ol2.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	/*------------------------------------ Setting Receive Mask ----------------------------------------------*/
#if 0
	Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

	if (Status == FALSE){
		wxLogMessage("Error! in Setting CommMask");
	}
	else{
		wxLogMessage("Setting CommMask successfull");
	}
#endif

	/*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

	wxLogMessage("Waiting for Data Reception");

	do {

	Sleep(25);

	Status = SetCommMask(hComm, EV_RXCHAR);

	if (Status == FALSE){
		PSU_DEBUG_PRINT("Error! in Setting CommMask");
	}
	else{
		PSU_DEBUG_PRINT("Setting CommMask successfull");
	}

	Status = WaitCommEvent(hComm, &dwEventMask, &g_ol); //Wait for the character to be received

	//wxLogMessage("Status = %d, dwEventMask = %lu", Status, dwEventMask);

	/*-------------------------- Program will Wait here till a Character is received ------------------------*/

	if (dwEventMask !=0 )
	{
		if ((dwEventMask & EV_RXCHAR) != EV_RXCHAR){
			wxLogMessage("dwEventMask != EV_RXCHAR");
			continue;
		}
		else{

			lastError = GetLastError();

			if (GetLastError() == ERROR_IO_PENDING){
				wxLogMessage("WaitCommEvent : %s", "ERROR_IO_PENDING");
				wxLogMessage("WaitForSingleObject");
				dwRes = WaitForSingleObject(g_ol.hEvent, 50);
			}
		}

		DWORD   dwErrors;
		COMSTAT ComStat;
		ClearCommError(hComm, &dwErrors, &ComStat);

		DWORD RcvLen = ComStat.cbInQue;

		wxLogMessage("RcvLen=%d Begin", RcvLen);

		if (RcvLen > 0){// Some Data in Queue
			
			//do { // Read Until No Data Can be Read

			do{
				// ReadFile return 0 if Operation failure
				ReadFileStatus = ReadFile(hComm, &TempChar, 1, &NoBytesRead, &g_ol2);
				if (ReadFileStatus == 0){

					lastError = GetLastError();

					if (lastError == ERROR_IO_PENDING){
						wxLogMessage("ReadFile IO PENDING Wait GetOverlappedResult");
						GetOverlappedResult(hComm, &g_ol2, &NoBytesRead, INFINITE);
					}
					else{
						wxLogMessage("lastError=%d", lastError);
						//break;
					}
				}
				else{
					wxLogMessage("Return of ReadFile = %d, NoBytesRead = %d", ReadFileStatus, NoBytesRead);
					if (NoBytesRead == 0){
						//break;
					}
				}

				//wxLogMessage("NoBytesRead = %d", NoBytesRead);
				if (NoBytesRead > 0) {
					buff[i] = TempChar;
					i++;
				}

			} while (NoBytesRead > 0);

				ResetEvent(g_ol.hEvent);
				ResetEvent(g_ol2.hEvent);

				bWaitRxCharEvent = true;

				ClearCommError(hComm, &dwErrors, &ComStat);
				RcvLen = ComStat.cbInQue;

				if (RcvLen == 0) {
					wxLogMessage("RcvLen=%d, End", RcvLen);
				}

				if (ComStat.fEof == TRUE){
					wxLogMessage("ComStat.fEof == TRUE");
				}

			//} while (i < 14);//NoBytesRead);//(RcvLen > 0);

#if 0
			// Handle Receive Data
			outputMsg += wxString::Format("Read %d Bytes Data From SerialPort :", i);

			for (unsigned int idx = 0; idx < i; idx++){
				outputMsg += wxString::Format(" %02x ", buff[idx]);
			}

			PSU_DEBUG_PRINT(outputMsg.c_str());
			wxLogMessage(outputMsg.c_str());

			ResetEvent(g_ol.hEvent);
			ResetEvent(g_ol2.hEvent);

			bWaitRxCharEvent = true;
#endif
		}// if (RcvLen > 0)
#if 0
			//bWaitingOnStatusHandle = TRUE;

			do { //while (bWaitForSingle==false);

				dwRes = WaitForSingleObject(g_ol.hEvent, STATUS_CHECK_TIMEOUT);

				switch (dwRes)
				{
					// Event occurred.
				case WAIT_OBJECT_0:
					wxLogMessage("WAIT_OBJECT_0");
					bWaitForSingle = true;

					if (dwEventMask != 1) break;

					bWaitRxCharEvent = true;

					PSU_DEBUG_PRINT("Characters Received");

					do {

						Status = ReadFile(hComm, &TempChar, NUMBER_OF_BYTES_TO_READ, &NoBytesRead, &g_ol);

						if (Status == true){
							wxLogMessage("Ret of ReadFile = %d, NoBytesRead = %d", Status, NoBytesRead);
						}
						else {

							lastError = GetLastError();
							if (lastError == ERROR_IO_PENDING){//|| lastError == ERROR_IO_INCOMPLETE){
								//
								endtime = GetTickCount() + 50000;
								//
								while (GetOverlappedResult(hComm, &g_ol, &NoBytesRead, TRUE) == 0){
									if (GetTickCount() > endtime)
									{
										PSU_DEBUG_PRINT("Receive Data Timeout");
										break;
									}
								}
							}
							else {
								//PSU_DEBUG_PRINT("ReadFile Occurs Unkonwn Error : %d", GetLastError());
								wxLogMessage("ReadFile Get Last Error : %d", lastError);
							}
						}

						wxLogMessage("NoBytesRead = %d", NoBytesRead);
						if (NoBytesRead > 0){
							buff[i] = TempChar;
							i++;
						}

					} while (NoBytesRead > 0);


					if (i == 0){
						wxLogMessage("i = %d", i);
					}

					if (i >= 0){//NoBytesRead > 0){
						/*------------Printing the RXed Data to Console----------------------*/
						outputMsg += wxString::Format("Read %d Bytes Data From SerialPort :", i);// NoBytesRead);

						for (unsigned int idx = 0; idx < i; idx++){
							outputMsg += wxString::Format(" %02x ", buff[idx]);
						}

						PSU_DEBUG_PRINT(outputMsg.c_str());
						wxLogMessage(outputMsg.c_str());
					}

					ResetEvent(g_ol.hEvent);
					CloseHandle(g_ol.hEvent);

					break;

				case WAIT_TIMEOUT:
					//wxLogMessage("WAIT_TIMEOUT");
					break;

				default:
					// Error in the WaitForSingleObject; abort
					// This indicates a problem with the OVERLAPPED structure's
					// event handle.
					CloseHandle(g_ol.hEvent);
					return 0;
				}

			} while (bWaitForSingle == false);

		}
		else {
			// error in WaitCommEvent; abort
			wxLogMessage("WaitCommEvent : %d", lastError);
		}
#endif 
	}// if dwEventMask !=0
	else //If dwEventMask !=0
	{
		//wxLogMessage("dwEventMask==0");
		//continue;
#if 0
		PSU_DEBUG_PRINT("Characters Received");
		i = 0;

		do {
			Status = ReadFile(hComm, &TempChar, NUMBER_OF_BYTES_TO_READ, &NoBytesRead, &g_ol);
			lastError = GetLastError();
			if (lastError == ERROR_IO_PENDING){
				//
				endtime = GetTickCount() + 50000;
				//
				while (GetOverlappedResult(hComm, &g_ol, &NoBytesRead, TRUE) == 0){
					if (GetTickCount() > endtime)
					{
						PSU_DEBUG_PRINT("Receive Data Timeout");
						break;
					}
				}
			}
			else if (lastError != 0){
				//PSU_DEBUG_PRINT("ReadFile Occurs Unkonwn Error : %d", GetLastError());
				wxLogMessage("ReadFile Get Last Error : %d", lastError);
			}

			wxLogMessage("NoBytesRead = %d", NoBytesRead);
			if (NoBytesRead > 0){
				buff[i] = TempChar;
				i++;
			}

		} while (NoBytesRead > 0);


		if (i==0){
			wxLogMessage("i = %d",i);
		}

		if (i >= 0){//NoBytesRead > 0){
			/*------------Printing the RXed Data to Console----------------------*/
			outputMsg += wxString::Format("Read %d Bytes Data From SerialPort :", i);// NoBytesRead);

			for (unsigned int idx = 0; idx < i; idx++){
				outputMsg += wxString::Format(" %02x ", buff[idx]);
			}

			PSU_DEBUG_PRINT(outputMsg.c_str());
			wxLogMessage(outputMsg.c_str());
		}

		ResetEvent(g_ol.hEvent);
		CloseHandle(g_ol.hEvent);
#endif
	}

	}while (bWaitRxCharEvent == false);//i < 14);

	// Handle Receive Data
	outputMsg += wxString::Format("Read %d Bytes Data From SerialPort :", i);

	for (unsigned int idx = 0; idx < i; idx++){
		outputMsg += wxString::Format(" %02x ", buff[idx]);
	}

	PSU_DEBUG_PRINT(outputMsg.c_str());
	wxLogMessage(outputMsg.c_str());

	CloseHandle(g_ol.hEvent);
	CloseHandle(g_ol2.hEvent);

	return i;// Return how many bytes data readed
}


int CloseSerialPort(void){
	int ret = SUCCESS;

	PSU_DEBUG_PRINT("Close Serial Port %p",hComm);
	CloseHandle(hComm);//Closing the Serial Port

	return ret;
}