/**
 * @file SerialPort.cpp
 */
#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include "CommonDef.h"
#include "SerialPort.h"

BOOL GetSerialPortName(wchar_t *buff, unsigned int sizeOfBuff, unsigned int num){
	BOOL ret = TRUE;

	if (sizeOfBuff < 16 || num < 0){
		PSU_DEBUG_PRINT(MSG_FATAL, "%s: Error Occurs, sizeOfBuff=%d, num=%d", __FUNCTIONW__, sizeOfBuff, num);
		ret = FALSE;
		return ret;
	}

	if (num <= 9){
		wsprintf(buff, L"Com%d", num + 1);
	}
	else{
		wsprintf(buff, L"\\\\.\\COM%d", num + 1);// "\\.\COMx"
	}

	return ret;
}

int EnumerateAvailableSerialPort(BOOL *array, unsigned int sizeofArray){

	HANDLE enumHandle;
	wchar_t SerialPortName[64];
	unsigned int success = 0;

	for (unsigned int idx = 0; idx < sizeofArray; idx++){

		GetSerialPortName(SerialPortName, sizeof(SerialPortName) / sizeof(wchar_t), idx);

		enumHandle = CreateFile(
			SerialPortName,                   // Name of the Port to be Opened
			GENERIC_READ | GENERIC_WRITE,     // Read/Write Access
			0,                                // No Sharing, ports cant be shared
			NULL,                             // No Security
			OPEN_EXISTING,                    // Open existing port only
			FILE_FLAG_OVERLAPPED,             // (Non Overlapped I/O)
			NULL);

		if (enumHandle == INVALID_HANDLE_VALUE){
			//PSU_DEBUG_PRINT("%s: Open %s Failed \n", __FUNCTIONW__, SerialPortName);
		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "Find Serial Port : %s", SerialPortName);
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
		if (array[idx] == TRUE){
			index = idx;
			return index;
		}
	}

	return index;

}




HANDLE hComm = INVALID_HANDLE_VALUE;/**< Handle for Serial Port */
wchar_t ComPortName[64] = L""; // Name of the Serial port to be opened,
DCB dcbSerialParams = { 0 };/**< Initializing DCB structure */
OVERLAPPED ol_write;/**< Overlapped Write */
OVERLAPPED ol_read;/**< Overlapped Read */
OVERLAPPED ol_wait;/**< Overlapped Wait */


int SetSerialPortTimeouts(void){

	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = MAXWORD;//50;
	timeouts.ReadTotalTimeoutConstant = 0;//50;
	timeouts.ReadTotalTimeoutMultiplier = 0;// 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;


	if (SetCommTimeouts(hComm, &timeouts) == FALSE){
		PSU_DEBUG_PRINT(MSG_FATAL, "Error! in Setting Time Outs");
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Setting Serial Port Timeouts Successfull");
	}

	return EXIT_SUCCESS;
}

int GetSerialPortStatus(void){
	PSU_DEBUG_PRINT(MSG_DEBUG, "hComm = %d", hComm);
	if (hComm == INVALID_HANDLE_VALUE){
		return IODEVICE_CLOSE;
	}
	else{
		return IODEVICE_OPEN;
	}
}

wchar_t* GetSerialPortOpenDeviceName(){
	return ComPortName;
}

int OpenSerialPort(BOOL *array, unsigned int sizeofArray)//int PortNum)
{
	int ret = EXIT_SUCCESS;
	BOOL Status;

	unsigned int availableIndex = GetFirstAvailableSerialPortIndex(array, sizeofArray);
	GetSerialPortName(ComPortName, sizeof(ComPortName) / sizeof(wchar_t), availableIndex);


	hComm = CreateFile(
		ComPortName,                    // Name of the Port to be Opened
		GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
		0,                                 // No Sharing, ports cant be shared
		NULL,                              // No Security
		OPEN_EXISTING,                     // Open existing port only
		FILE_FLAG_OVERLAPPED,              // (Non Overlapped I/O)
		NULL);                             // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE){
		PSU_DEBUG_PRINT(MSG_FATAL, "Error! Port %s can't be opened", ComPortName);
		return EXIT_FAILURE;
	}
	else{
		PSU_DEBUG_PRINT(MSG_ALERT, "Port %s Opened", ComPortName);
	}

	/*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	Status = GetCommState(hComm, &dcbSerialParams);     //retreives the current settings

	if (Status == FALSE){
		PSU_DEBUG_PRINT(MSG_FATAL, "Error! in GetCommState()");
		return EXIT_FAILURE;
	}

	dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity   = NOPARITY;      // Setting Parity   = None

	//dcbSerialParams.EofChar = '\n';

	Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

	if (Status == FALSE)
	{
		PSU_DEBUG_PRINT(MSG_FATAL, "Error! in Setting DCB Structure");
		return EXIT_FAILURE;
	}
	else
	{
		PSU_DEBUG_PRINT(MSG_ALERT, "Setting DCB Structure Successfull");
		PSU_DEBUG_PRINT(MSG_ALERT, "Baudrate = %d", dcbSerialParams.BaudRate);
		PSU_DEBUG_PRINT(MSG_ALERT, "ByteSize = %d", dcbSerialParams.ByteSize);
		PSU_DEBUG_PRINT(MSG_ALERT, "StopBits = %d", dcbSerialParams.StopBits);
		PSU_DEBUG_PRINT(MSG_ALERT, "Parity   = %d", dcbSerialParams.Parity);
	}

	/*------------------------------------ Setting Timeouts --------------------------------------------------*/

#if 1
	SetSerialPortTimeouts();
#endif

	return ret;
}

int DumpComStat(void){
	DWORD dwErrors;
	COMSTAT ComStat;

	PSU_DEBUG_PRINT(MSG_FATAL, "DumpComStat");

	ClearCommError(hComm, &dwErrors, &ComStat);

	PSU_DEBUG_PRINT(MSG_FATAL, "dwErrors=%ld", dwErrors);
	PSU_DEBUG_PRINT(MSG_FATAL, "ComStat.cbOutQue=%ld", ComStat.cbOutQue);
	PSU_DEBUG_PRINT(MSG_FATAL, "ComStat.cbInQue=%ld", ComStat.cbInQue);

	return ComStat.cbInQue;// Return how many data bytes in In-Queue
}

//#define WRITE_WAIT_INFINITE // Wait Infinite for Write Overlapped Operation

int SerialSendData(unsigned char* buff, unsigned int size){

	BOOL Status;
	DWORD  dNoOfBytesWritten = 0;
	DWORD endtime; // For Compute Timeout
	//OVERLAPPED g_ol;/**< Overlapped Sructure */
	int send_err;
	DWORD send_size;

	send_size = size;

	ZeroMemory(&ol_write, sizeof(ol_write));
	ol_write.Offset = 0;
	ol_write.OffsetHigh = 0;
	ol_write.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// Purge CommPort
	PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);

	Status =
		WriteFile(hComm,     // Handle to the Serialport
		buff,                // Data to be written to the port 
		size,                // No of bytes to write into the port
		&dNoOfBytesWritten,  // No of bytes written to the port
		&ol_write);

	if (Status == 0){

		send_err = GetLastError();
		if (send_err == ERROR_IO_PENDING)
		{
			PSU_DEBUG_PRINT(MSG_DEBUG, "IO_PENDING");

#ifdef WRITE_WAIT_INFINITE
			//while (!GetOverlappedResult(hComm, &g_ol, &dNoOfBytesWritten, FALSE));
			GetOverlappedResult(hComm, &g_ol, &dNoOfBytesWritten, TRUE);

#else
			endtime = GetTickCount() + 500;
			while (!GetOverlappedResult(hComm, &ol_write, &dNoOfBytesWritten, FALSE)){
				if (GetTickCount() > endtime)
				{
					PSU_DEBUG_PRINT(MSG_ALERT, "GetOverlappedResult Timeout");
					PSU_DEBUG_PRINT(MSG_ALERT, "dNoOfBytesWritten=%d", dNoOfBytesWritten);
					DumpComStat();

					ResetEvent(ol_write.hEvent);
					CloseHandle(ol_write.hEvent);
					return -3;

					break;
				}
			};

#endif

			if (dNoOfBytesWritten != send_size){
				PSU_DEBUG_PRINT(MSG_FATAL, "Send Size Unexpected ! dNoOfBytesWritten=%d", dNoOfBytesWritten);
				DumpComStat();

				ResetEvent(ol_write.hEvent);
				CloseHandle(ol_write.hEvent);
				return -2;
			}
			else{
				PSU_DEBUG_PRINT(MSG_DEBUG, "dNoOfBytesWritten = %d", dNoOfBytesWritten);

				ResetEvent(ol_write.hEvent);
				CloseHandle(ol_write.hEvent);
			}
		}
		else
		{
			PSU_DEBUG_PRINT(MSG_FATAL, "ERROR in Send, Error = %d", send_err);
			// Get Error Information
			DumpComStat();
			
			ResetEvent(ol_write.hEvent);
			CloseHandle(ol_write.hEvent);
			return -1;
		}

	}

	return dNoOfBytesWritten;
}

//#define WAIT_INFINITE                  // Wait Infinite for Overlapped Operation

#define NUMBER_OF_BYTES_TO_READ    1   // Number of Bytes To Read
#define WAITCOMMEVENT_TIMEOUT    300   // Milliseconds
#define READ_OVERLAPPED_TIMEOUT  500   // Milliseconds
#define STATUS_CHECK_TIMEOUT      50   // Milliseconds
int SerialReadData(unsigned char* buff, unsigned int bytesToRead){
	//wxString outputMsg("");                // Output Messages
	BOOL  Status;                          // Status of the various operations
	int ReadFileStatus;                    //
	DWORD dwEventMask;                     // Event mask to trigger
	unsigned char TempChar;                // Temperory Character
	unsigned char RcvBuf[1024];            //
	//char  SerialBuffer[256];             // Buffer Containing Rxed Data
	DWORD endtime;                         // For Compute Timeout
	DWORD NoBytesRead;                     // Bytes read by ReadFile()
	//OVERLAPPED g_ol;                       // Overlapped Sructure */
	//OVERLAPPED g_ol2;                      // Overlapped Sructure */
	DWORD dwErrors;
	COMSTAT ComStat;
	BOOL bWaitForSingle;                   //
	BOOL bWaitRxCharEvent;                 //
	DWORD lastError;                       // Last Error
	DWORD dwRes;
	unsigned int i = 0;
	BOOL WaitCommEventTimeOutFlag = FALSE;
	BOOL ReadFileOverlappedTimeOutFlag = FALSE;
	int InQueue;


	dwEventMask = 0x00000000;

	bWaitForSingle = false;
	bWaitRxCharEvent = false;

	InQueue = 0;
	//
	memset(&ol_wait, 0, sizeof(OVERLAPPED));
	ol_wait.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//
	memset(&ol_read, 0, sizeof(OVERLAPPED));
	ol_read.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	/*------------------------------------ Setting Receive Mask ----------------------------------------------*/
#if 0
	Status = SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception

	if (Status == FALSE){
		PSU_DEBUG_PRINT(MSG_FATAL, "Error! in Setting CommMask");
	}
	else{
		PSU_DEBUG_PRINT(MSG_DEBUG, "Setting CommMask successfull");
	}
#endif

	/*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/

	PSU_DEBUG_PRINT(MSG_DEBUG, "Waiting for Data Reception");

	do {

		//Sleep(25);
#if 1
		Status = SetCommMask(hComm, EV_RXCHAR);

		if (Status == FALSE){
			PSU_DEBUG_PRINT(MSG_FATAL, "Error! in Setting CommMask");
		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "Setting CommMask successfull");
		}
#endif

		//ClearCommError(hComm, &dwErrors, &ComStat);

		//DWORD RcvLen = ComStat.cbInQue;

		//PSU_DEBUG_PRINT(MSG_DEBUG, "RcvLen=%d Begin", RcvLen);


		dwEventMask = 0x00000000;
		//ResetEvent(g_ol.hEvent);
		//ResetEvent(g_ol2.hEvent);
		Status = WaitCommEvent(hComm, &dwEventMask, &ol_wait); //Wait for the character to be received

		lastError = GetLastError();

		if (lastError == ERROR_IO_PENDING){
			PSU_DEBUG_PRINT(MSG_DEBUG, "WaitCommEvent : ERROR_IO_PENDING");
			PSU_DEBUG_PRINT(MSG_DEBUG, "WaitForSingleObject");

#ifdef WAIT_INFINITE
			dwRes = WaitForSingleObject(g_ol.hEvent, INFINITE);

			if (dwRes != WAIT_OBJECT_0){
				PSU_DEBUG_PRINT(MSG_ALERT, "dwRes != WAIT_OBJECT_0");
				continue;
			}
#else

			dwRes = WaitForSingleObject(ol_wait.hEvent, WAITCOMMEVENT_TIMEOUT);

			switch (dwRes){

			case WAIT_TIMEOUT:
				PSU_DEBUG_PRINT(MSG_ALERT, "WaitForSingleObject WAIT_TIMEOUT");
				InQueue = DumpComStat();
				if (InQueue != bytesToRead){
					WaitCommEventTimeOutFlag = TRUE;
					PSU_DEBUG_PRINT(MSG_ALERT, "WaitForSingleObject WAIT_TIMEOUT InQueue != bytesToRead");
				}
				else{
					WaitCommEventTimeOutFlag = TRUE;
					PSU_DEBUG_PRINT(MSG_ALERT, "WaitForSingleObject WAIT_TIMEOUT InQueue = bytesToRead");
				}
				break;

			case WAIT_OBJECT_0:
				PSU_DEBUG_PRINT(MSG_DEBUG, "dwRes  = WAIT_OBJECT_0");
				break;

			default:
				PSU_DEBUG_PRINT(MSG_ALERT, "dwRes != WAIT_OBJECT_0,dwRes=%ld", dwRes);
				WaitCommEventTimeOutFlag = TRUE;
				DumpComStat();
				break;
			}
#endif

		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "WaitCommEvent : LastError = %d", lastError);
		}

		if (WaitCommEventTimeOutFlag==TRUE){

			break;// while (bWaitRxCharEvent == false)
		}
		else{
			PSU_DEBUG_PRINT(MSG_DEBUG, "WaitCommEventTimeOutFlag = False");
		}

		/*-------------------------- Program will Wait here till a Character is received ------------------------*/

		if (dwEventMask != 0)
		{
			if ((dwEventMask & EV_RXCHAR) != EV_RXCHAR){
				PSU_DEBUG_PRINT(MSG_ALERT, "dwEventMask != EV_RXCHAR");
				continue;
			}
			else{
				PSU_DEBUG_PRINT(MSG_DETAIL, "dwEventMask=%d", dwEventMask);
			}


			//ClearCommError(hComm, &dwErrors, &ComStat);

			//if (ComStat.fEof == TRUE){
				//PSU_DEBUG_PRINT(MSG_ALERT,"ComStat.fEof == TRUE");
			//}

			//DWORD RcvLen = ComStat.cbInQue;

			//PSU_DEBUG_PRINT(MSG_DETAIL, "RcvLen=%d Begin", RcvLen);

			//if (RcvLen > 0){// Char in Queue

				//do { // Read Until No Data Can be Read

				SetSerialPortTimeouts();
				do{
					//NoBytesRead = 0;

					// ReadFile return 0 if Operation failure
					ReadFileStatus = ReadFile(hComm, buff + i, 1, &NoBytesRead, &ol_read);
					//ReadFileStatus = ReadFile(hComm, buff, bytesToRead, &NoBytesRead, &g_ol2);
					if (ReadFileStatus == 0){

						lastError = GetLastError();

						if (lastError == ERROR_IO_PENDING){
							PSU_DEBUG_PRINT(MSG_DETAIL, "ReadFile IO PENDING Wait GetOverlappedResult");
#ifdef WAIT_INFINITE
							GetOverlappedResult(hComm, &g_ol2, &NoBytesRead, TRUE);
#else
							
                            //#define USE_WaitForSingleObject_READ_FILE
							#ifdef USE_WaitForSingleObject_READ_FILE
							dwRes = WaitForSingleObject(g_ol2.hEvent, WAITCOMMEVENT_TIMEOUT);

							switch (dwRes){

							case WAIT_TIMEOUT:
								PSU_DEBUG_PRINT(MSG_ALERT, "ReadFile : WaitForSingleObject WAIT_TIMEOUT");
								//WaitCommEventTimeOutFlag = TRUE;
								ReadFileOverlappedTimeOutFlag = TRUE;
								DumpComStat();
								break;

							case WAIT_OBJECT_0:
								PSU_DEBUG_PRINT(MSG_ALERT, "ReadFile : dwRes  = WAIT_OBJECT_0");
								PSU_DEBUG_PRINT(MSG_ALERT, "ReadFile : Again");
								//ReadFile(hComm, buff + i, 1, &NoBytesRead, NULL);
								break;

							default:
								PSU_DEBUG_PRINT(MSG_ALERT, "ReadFile : dwRes != WAIT_OBJECT_0,dwRes=%ld", dwRes);
								ReadFileOverlappedTimeOutFlag = TRUE;
								DumpComStat();
								break;
						    }
							#endif
							
							#define USE_GETOVERLAPPEDRESULT_READ_FILE
                            #ifdef USE_GETOVERLAPPEDRESULT_READ_FILE
							endtime = GetTickCount() + READ_OVERLAPPED_TIMEOUT;
							while (!GetOverlappedResult(hComm, &ol_read, &NoBytesRead, FALSE)){
								
								if (GetTickCount() > endtime)
								{
									PSU_DEBUG_PRINT(MSG_ALERT, "GetOverlappedResult Timeout");
									PSU_DEBUG_PRINT(MSG_ALERT, "NoBytesRead=%d", NoBytesRead);
									ReadFileOverlappedTimeOutFlag = TRUE;
									DumpComStat();

									break;
								}
							};
							#endif
#endif
						}
						else{// if (lastError == ERROR_IO_PENDING)
							PSU_DEBUG_PRINT(MSG_FATAL, "ReadFile lastError=%d", lastError);
							NoBytesRead = 0;
							DumpComStat();
							break; // break while (i < bytesToRead);
						}

						// If Overlapped Timeout Occurs
						if (ReadFileOverlappedTimeOutFlag == TRUE){
							PSU_DEBUG_PRINT(MSG_ALERT, "ReadFile Overlapped Timeout Occurs ! break while loop");
							break; // break while (i < bytesToRead);
						}

					}
					else{// if (ReadFileStatus == 0)
						PSU_DEBUG_PRINT(MSG_DEBUG, "Return of ReadFile = %d, NoBytesRead = %d", ReadFileStatus, NoBytesRead);
						if (NoBytesRead == 0){
							PSU_DEBUG_PRINT(MSG_ALERT, "ReadFile Return Success ! But NoBytesRead = %d", NoBytesRead);
							break; // break while (i < bytesToRead);
						}
					}

					PSU_DEBUG_PRINT(MSG_DEBUG, "NoBytesRead = %d", NoBytesRead);

					if (NoBytesRead < bytesToRead){
						;
					}

					//if (NoBytesRead > 0) {
					//buff[i] = TempChar;
					//i++;
					//}

					if (NoBytesRead > 0) {
						PSU_DEBUG_PRINT(MSG_DEBUG, "NoBytesRead = %d", NoBytesRead);
						i += NoBytesRead;
					}

					//} while (NoBytesRead < 8);// NoBytesRead > 0);
					//} while (NoBytesRead > 0);
				} while (i < bytesToRead);

				ResetEvent(ol_wait.hEvent);
				ResetEvent(ol_read.hEvent);

				bWaitRxCharEvent = true;

				//ClearCommError(hComm, &dwErrors, &ComStat);
				//RcvLen = ComStat.cbInQue;

				//if (RcvLen == 0) {
				//PSU_DEBUG_PRINT("RcvLen=%d, End \n", RcvLen);
				//}

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
			//}// if (RcvLen > 0)
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
	else//If dwEventMask !=0
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
#endif
	}

	} while (bWaitRxCharEvent == false);//i < 14);


	ResetEvent(ol_wait.hEvent);
	ResetEvent(ol_read.hEvent);
	CloseHandle(ol_wait.hEvent);
	CloseHandle(ol_read.hEvent);

	return i;// Return how many bytes data readed
}


int CloseSerialPort(void){
	int ret = SUCCESS;

	PSU_DEBUG_PRINT(MSG_DEBUG ,"Close Serial Port %p", hComm);
	CloseHandle(hComm);//Closing the Serial Port

	hComm = INVALID_HANDLE_VALUE;

	return ret;
}