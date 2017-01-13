/**
 * @file QUERYSequenceThread.cpp
 */
#include "QUERYSequenceThread.h"

QUERYSequenceThread::QUERYSequenceThread(
	IOACCESS*    ioaccess,
	unsigned int* currentIO,
	wxEvtHandler* evtHandlerMain,
	wxEvtHandler* evtHandler,
	wxProgressDialog *progressDialog
	) : wxThread(wxTHREAD_JOINABLE){


	this->m_ioaccess = ioaccess;

	this->m_currentIO = currentIO;

	this->m_evtHandlerMain = evtHandlerMain;

	this->m_evtHandler = evtHandler;

	this->m_progressDialog = progressDialog;

	this->m_rxTxSemaphore = new wxSemaphore(0, 0);

	// Reset Query Status
	for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize(); idx++){
		PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_queried = cmd_query_not_yet;
		PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_status = cmd_status_not_run;
	}

}

QUERYSequenceThread::~QUERYSequenceThread(){
	wxDELETE(this->m_rxTxSemaphore);
}

#define BASE_RESPONSE_DATA_LENGTH  6
#define STR_LENGTH  256
wxThread::ExitCode QUERYSequenceThread::Entry() {
	int ret;
	int retry = 0;
	int sendDataLength = 0;
	int sendResult = 0;
	int ExpectReceiveDataLength = 0;
	int QueryCMDIndex = 0;
	int CoefficientsCMDIndex = 0;
	int PreviousQueryAdditionalCMD = 0;
	int PreviousCoefficientsAdditionalCMD = 0;
	int PreviousCoefficientsAdditionalRW = 0;
	bool sendRetryStillFailed = false;
	bool receiveFailed = false;
	bool i2cNotFound = false;
	wchar_t QueryStr[STR_LENGTH];
	wchar_t CoefficientsStr[STR_LENGTH];

	PSU_DEBUG_PRINT(MSG_DEBUG, "");

	m_running = true;

	while (m_running && this->TestDestroy() == false){

		for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize() && m_running == true; idx++){

			PSU_DEBUG_PRINT(MSG_DEBUG, "QUERY Command %02xH Start", PMBUSHelper::getPMBUSCMDData()[idx].m_register);

			/*** Query Command (0x1A) ***/
			if (PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_queried == cmd_query_not_yet){

				// Find Query Command (0x1A)'s Index
				QueryCMDIndex = -1;
				for (unsigned int local = 0; local < PMBUSHelper::GetCurrentCMDTableSize(); local++){
					if (PMBUSHelper::getPMBUSCMDData()[local].m_register == PMBUSCMD_1AH_QUERY){
						QueryCMDIndex = local;
						break;
					}
				}

				if (QueryCMDIndex >= 0){
					// Prepare Send Buffer
					PreviousQueryAdditionalCMD = PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1];
					PSU_DEBUG_PRINT(MSG_DEBUG, "PreviousAdditionalCMD=%xH", PreviousQueryAdditionalCMD);
					PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1] = PMBUSHelper::getPMBUSCMDData()[idx].m_register;
					sendDataLength = PMBUSHelper::ProductReadCMDBuffer(PMBUSHelper::getPMBUSCMDData(), this->m_sendBuffer, this->m_currentIO, QueryCMDIndex, PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_register, PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_responseDataLength);
					//this->productSendBuff(QueryCMDIndex, this->m_pmBusCommand[QueryCMDIndex].m_register, this->m_pmBusCommand[QueryCMDIndex].m_responseDataLength);

					// Send Query Command
					retry = 0;
					do {
						// Decide Send Data Length
						if (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE){
							if (PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
								//sendDataLength = SERIAL_SEND_DATA_SIZE;
							}
							else if (PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
								//sendDataLength = SERIAL_SEND_DATA_SIZE + PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_AddtionalDataLength;
							}
						}
						else{// HID
							sendDataLength = HID_SEND_DATA_SIZE;
						}

						PSU_DEBUG_PRINT(MSG_DEBUG, "Send Data Length =%d", sendDataLength);

						// Send Data
						sendResult = this->m_ioaccess[*this->m_currentIO].m_DeviceSendData(this->m_sendBuffer, sendDataLength);
						if (sendResult <= 0){
							PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
							// Retry 
							retry++;
							if (retry >= 3){
								PSU_DEBUG_PRINT(MSG_DEBUG, "Still Send Failed, Retry Times = %d", retry);
								sendRetryStillFailed = true;
								break;
							}
							else{
								PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
							}

						}
						else{
#ifdef OUTPUT_SEND_DATA
							wxString sentData(wxT("Sent Data : "));
							for (int idx = 0; idx < sendDataLength; idx++){
								sentData += wxString::Format(" %02x ", this->m_sendBuff[idx]);
							}
							PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sentData.c_str());
#endif
							PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
						}

					} while (sendResult <= 0);

					if (sendRetryStillFailed == true){
						PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Send Still Failed, Exit Send Thread");
						m_running = false;
						break;
					}

					// Read Query Result
					unsigned int bytesToRead = PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH;
					this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_ioaccess, this->m_currentIO, this->m_rxTxSemaphore, &PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex], &this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, bytesToRead);

					// If Create Thread Success
					if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
						PSU_DEBUG_PRINT(MSG_ERROR, "Can't create read thread!");
					}
					else{
						this->m_IOPortReadCMDThread->Run();
					}

					// Semaphore Wait for Read Thread Complete
					PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout, CMD = %02xH", PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_register);
					ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);

					if (ret != wxSEMA_NO_ERROR){
						PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore wait timout occurs : error = %d", ret);
					}
					else{

						if (this->m_recvBuff.m_length == 0){
							PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length = %d, CMD = %02xH", this->m_recvBuff.m_length, PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_register);
							PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_status = cmd_status_failure;
							//timeout++;
							receiveFailed = true;
						}
						else{
							// Get Expect Data Length
							//ExpectReceiveDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH : PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH + 2;
							ExpectReceiveDataLength = PMBUSHelper::getExpectedDataLengthByIO(*this->m_currentIO, PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_responseDataLength, BASE_RESPONSE_DATA_LENGTH);
							PSU_DEBUG_PRINT(MSG_DEBUG, "ExpectReceiveDataLength=%d", ExpectReceiveDataLength);

							//
							if (this->m_recvBuff.m_length == ExpectReceiveDataLength){

								PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data of CMD %2x, Length = %d", PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_register, this->m_recvBuff.m_length);
								//success++;

								// copy data to PMBus Command Structure
								PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_recvBuff.m_length = this->m_recvBuff.m_length;
								for (unsigned int idx2 = 0; idx2 < this->m_recvBuff.m_length; idx2++){
									PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_recvBuff.m_recvBuff[idx2] = this->m_recvBuff.m_recvBuff[idx2];
									PSU_DEBUG_PRINT(MSG_DETAIL, "%d,%d", PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_recvBuff.m_recvBuff[idx2], this->m_recvBuff.m_recvBuff[idx2]);
								}

								// Prepare Data Buffer
								PMBUSHelper::ProductDataBuffer(PMBUSHelper::getPMBUSCMDData(), this->m_currentIO, QueryCMDIndex, PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_responseDataLength);
								//this->productDataBuff(QueryCMDIndex, PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_responseDataLength);

#ifdef OUTPUT_RECEIVE_DATA
								wxString recvBytes("");
								for (unsigned int idx3 = 0; idx3 < this->m_recvBuff.m_length; idx3++){
									recvBytes += wxString::Format(" %02x ", this->m_recvBuff.m_recvBuff[idx3]);
								}

								PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Bytes : %s", recvBytes.c_str());

#endif

								// Check I2C BUS Not Acknowledge
								unsigned char i2cBusAck = PMBUSHelper::IsI2CBusNotAcknowlwdge(this->m_currentIO, this->m_recvBuff.m_recvBuff, this->m_recvBuff.m_length);
								if (i2cBusAck == PMBUSHelper::response_ng){
									PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_status = cmd_status_i2c_bus_not_acknowledge;
									i2cNotFound = true;
								}

								if (PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_status != cmd_status_checksum_error && PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_status != cmd_status_i2c_bus_not_acknowledge){
									PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_status = cmd_status_success;
									//success++;
								}

								bool PreUpdateQuery = true;

								if (PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_status == cmd_status_success){

									// Get Query CMD
									int queryCMD;
									queryCMD = PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1];

									// Get Index of Query CMD 
									int queryCMDIndex = -1;
									queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_cmdPage);

									if (queryCMDIndex < 0){
										PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
										PreUpdateQuery = false;
									}
									else{
										PSU_DEBUG_PRINT(MSG_DEBUG, "Find Index of Query CMD %02x is %d", queryCMD, queryCMDIndex);
									}

									if (PreUpdateQuery == true){
										// Call Query Data CB Function
										memset(QueryStr, 0, STR_LENGTH * sizeof(wchar_t));                                                              // CMD's Page
										PMBUSHelper::getPMBUSCMDData()[queryCMDIndex].m_cmdCBFunc.m_queryCBFunc(&(PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex]), QueryStr, PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_cmdPage);

										wxString QueryMsg(QueryStr);

										wxThreadEvent* threadquery_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_QUERY);
										threadquery_evt->SetInt(queryCMDIndex);
										threadquery_evt->SetString(QueryMsg);
										wxQueueEvent(this->m_evtHandlerMain, threadquery_evt);

										PSU_DEBUG_PRINT(MSG_DEBUG, "%s", QueryMsg.c_str());

										/*** If Data Format is Direct Data Format Type, Call Coefficients CMD�@(0x30) To Get Coefficients ***/

										// Find Coefficients Command (0x1A)'s Index
										CoefficientsCMDIndex = -1;
										for (unsigned int local2 = 0; local2 < PMBUSHelper::GetCurrentCMDTableSize(); local2++){
											if (PMBUSHelper::getPMBUSCMDData()[local2].m_register == PMBUSCMD_30H_COEFFICIENTS){
												CoefficientsCMDIndex = local2;
												break;
											}
										}

										if (PMBUSHelper::getPMBUSCMDData()[idx].m_dataFormat.m_formatType == cmd_data_format_DirectData_Format
											/* || this->m_pmBusCommand[idx].m_dataFormat.m_formatType == cmd_data_format_8bit_Unsigned_Number */){

											if (CoefficientsCMDIndex >= 0){
												// Prepare Send Buffer
												PreviousCoefficientsAdditionalCMD = PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[DEF_30H_READ_CMD_INDEX];
												PreviousCoefficientsAdditionalRW = PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[DEF_30H_READ_RW_INDEX];

												PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[DEF_30H_READ_CMD_INDEX] = PMBUSHelper::getPMBUSCMDData()[idx].m_register;
												PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[DEF_30H_READ_RW_INDEX] = rw_read_coefficients;

												sendDataLength = PMBUSHelper::ProductReadCMDBuffer(PMBUSHelper::getPMBUSCMDData(), this->m_sendBuffer, this->m_currentIO, CoefficientsCMDIndex, PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_register, PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_responseDataLength);
												//this->productSendBuff(CoefficientsCMDIndex, this->m_pmBusCommand[CoefficientsCMDIndex].m_register, this->m_pmBusCommand[CoefficientsCMDIndex].m_responseDataLength);

												// Send Query Command
												retry = 0;
												do {
													// Decide Send Data Length
													if (*this->m_currentIO == IOACCESS_SERIALPORT || *this->m_currentIO == IOACCESS_TOTALPHASE){
														if (PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_normal_read_data){
															//sendDataLength = SERIAL_SEND_DATA_SIZE;
														}
														else if (PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_alsoSendWriteData == cmd_also_send_write_data){
															//sendDataLength = SERIAL_SEND_DATA_SIZE + PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalDataLength;
														}
													}
													else{// HID
														sendDataLength = HID_SEND_DATA_SIZE;
													}

													PSU_DEBUG_PRINT(MSG_DEBUG, "Send Data Length =%d", sendDataLength);

													// Send Data
													sendResult = this->m_ioaccess[*this->m_currentIO].m_DeviceSendData(this->m_sendBuffer, sendDataLength);
													if (sendResult <= 0){
														PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Failed, sendResult=%d", sendResult);
														// Retry 
														retry++;
														if (retry >= 3){
															PSU_DEBUG_PRINT(MSG_DEBUG, "Still Send Failed, Retry Times = %d", retry);
															sendRetryStillFailed = true;
															break;
														}
														else{
															PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Times = %d", retry);
														}

													}
													else{
#ifdef OUTPUT_SEND_DATA
														wxString sentData(wxT("Sent Data : "));
														for (int idx = 0; idx < sendDataLength; idx++){
															sentData += wxString::Format(" %02x ", this->m_sendBuff[idx]);
														}
														PSU_DEBUG_PRINT(MSG_DEBUG, "%s", sentData.c_str());
#endif
														PSU_DEBUG_PRINT(MSG_DEBUG, "IO Send Success");
													}

												} while (sendResult <= 0);

												if (sendRetryStillFailed == true){
													PSU_DEBUG_PRINT(MSG_DEBUG, "Retry Send Still Failed, Exit Send Thread");
													m_running = false;
													break;
												}

												// Read Quert Result
												unsigned int bytesToRead = PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH;
												this->m_IOPortReadCMDThread = new IOPortReadCMDThread(this->m_ioaccess, this->m_currentIO, this->m_rxTxSemaphore, &PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex], &this->m_recvBuff, SERIALPORT_RECV_BUFF_SIZE, bytesToRead);

												// If Create Thread Success
												if (this->m_IOPortReadCMDThread->Create() != wxTHREAD_NO_ERROR){
													PSU_DEBUG_PRINT(MSG_ERROR, "Can't create read thread!");
												}
												else{
													this->m_IOPortReadCMDThread->Run();
												}

												// Semaphore Wait for Read Thread Complete
												PSU_DEBUG_PRINT(MSG_DEBUG, "Semaphore WaitTimeout, CMD = %02xH", PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_register);
												ret = m_rxTxSemaphore->Wait();//Timeout(SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT);

												if (ret != wxSEMA_NO_ERROR){
													PSU_DEBUG_PRINT(MSG_ALERT, "Semaphore wait timout occurs : error = %d", ret);
												}
												else{
													if (this->m_recvBuff.m_length == 0){
														PSU_DEBUG_PRINT(MSG_ALERT, "RecvBuff's Length = %d, CMD = %02xH", this->m_recvBuff.m_length, PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_register);
														PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_status = cmd_status_failure;
														//timeout++;
														receiveFailed = true;
													}
													else{
														// Get Expect Data Length
														//ExpectReceiveDataLength = (*this->m_currentIO == IOACCESS_SERIALPORT) ? PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH : PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_responseDataLength + BASE_RESPONSE_DATA_LENGTH + 2;
														ExpectReceiveDataLength = PMBUSHelper::getExpectedDataLengthByIO(*this->m_currentIO, PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_responseDataLength, BASE_RESPONSE_DATA_LENGTH);
														PSU_DEBUG_PRINT(MSG_DEBUG, "ExpectReceiveDataLength=%d", ExpectReceiveDataLength);

														//
														if (this->m_recvBuff.m_length == ExpectReceiveDataLength){

															PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Data of CMD %2x, Length = %d", PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_register, this->m_recvBuff.m_length);
															//success++;

															// copy data to PMBus Command Structure
															PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_recvBuff.m_length = this->m_recvBuff.m_length;
															for (unsigned int idx2 = 0; idx2 < this->m_recvBuff.m_length; idx2++){
																PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_recvBuff.m_recvBuff[idx2] = this->m_recvBuff.m_recvBuff[idx2];
																PSU_DEBUG_PRINT(MSG_DETAIL, "%d,%d", PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_recvBuff.m_recvBuff[idx2], this->m_recvBuff.m_recvBuff[idx2]);
															}

															// Prepare Data Buffer
															PMBUSHelper::ProductDataBuffer(PMBUSHelper::getPMBUSCMDData(), this->m_currentIO, CoefficientsCMDIndex, PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_responseDataLength);
															//this->productDataBuff(CoefficientsCMDIndex, this->m_pmBusCommand[CoefficientsCMDIndex].m_responseDataLength);

#ifdef OUTPUT_RECEIVE_DATA
															wxString recvBytes("");
															for (unsigned int idx3 = 0; idx3 < this->m_recvBuff->m_length; idx3++){
																recvBytes += wxString::Format(" %02x ", this->m_recvBuff->m_recvBuff[idx3]);
															}

															PSU_DEBUG_PRINT(MSG_DEBUG, "Receive Bytes : %s", recvBytes.c_str());

#endif

															// Check I2C BUS Not Acknowledge
															unsigned char i2cBusAck = PMBUSHelper::IsI2CBusNotAcknowlwdge(this->m_currentIO, this->m_recvBuff.m_recvBuff, this->m_recvBuff.m_length);
															if (i2cBusAck == PMBUSHelper::response_ng){
																PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_status = cmd_status_i2c_bus_not_acknowledge;
																i2cNotFound = true;
															}

															if (PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_status != cmd_status_checksum_error && PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_status != cmd_status_i2c_bus_not_acknowledge){
																PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_status = cmd_status_success;
																//success++;
															}

															bool PreUpdateCoefficients = true;

															if (PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_status == cmd_status_success){

																// Get Query CMD
																int queryCMD;
																queryCMD = PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[1];

																// Get Index of Query CMD 
																int queryCMDIndex = -1;

																queryCMDIndex = PMBUSHelper::getIndexOfCMD(queryCMD, PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_cmdPage);

#if 0
																for (int idx2 = 0; idx2 < (signed)PMBUSHelper::CurrentCMDTableSize; idx2++){
																	if (PMBUSHelper::getPMBUSCMDData()[idx2].m_register == queryCMD){
																		queryCMDIndex = idx2;
																		break;
																	}
																}
#endif

																if (queryCMDIndex < 0){
																	PSU_DEBUG_PRINT(MSG_DEBUG, "Can't Find Index of Query CMD");
																	PreUpdateCoefficients = false;
																}

																if (PreUpdateCoefficients == true){
																	// Call Coefficients Data CB Function
																	memset(CoefficientsStr, 0, STR_LENGTH * sizeof(wchar_t));																			 // CMD's Page
																	PMBUSHelper::getPMBUSCMDData()[queryCMDIndex].m_cmdCBFunc.m_coefficientsCBFunc(&(PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex]), CoefficientsStr, PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_cmdPage);

																	wxString CoefficientsMsg(CoefficientsStr);

																	wxThreadEvent* threadcoefficients_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS);
																	threadcoefficients_evt->SetInt(queryCMDIndex);
																	threadcoefficients_evt->SetString(CoefficientsMsg);
																	wxQueueEvent(this->m_evtHandlerMain, threadcoefficients_evt);

																	PSU_DEBUG_PRINT(MSG_DEBUG, "%s", CoefficientsMsg.c_str());
																}

																
															}

														}

													}

												}

												PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[DEF_30H_READ_CMD_INDEX] = PreviousCoefficientsAdditionalCMD;
												PMBUSHelper::getPMBUSCMDData()[CoefficientsCMDIndex].m_cmdStatus.m_AddtionalData[DEF_30H_READ_RW_INDEX] = PreviousCoefficientsAdditionalRW;

											}

										}// if (this->m_pmBusCommand[idx].m_dataFormat.m_formatType == cmd_data_format_DirectData_Format)
										else{
											wxString PaddingStr(wxT("---"));

											wxThreadEvent* threadcoefficients_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_SENDTHREAD_UPDATE_COEFFICIENTS);
											threadcoefficients_evt->SetInt(queryCMDIndex);
											threadcoefficients_evt->SetString(PaddingStr);
											wxQueueEvent(this->m_evtHandlerMain, threadcoefficients_evt);
										}

									}// if (PreUpdateQuery == true)

								}// if (this->m_pmBusCommand[idx].m_cmdStatus.m_status == cmd_status_success)

							}// if (this->m_recvBuff->m_length == ExpectReceiveDataLength) 

						}// else (if (this->m_recvBuff->m_length == 0))

					} // else if (ret != wxSEMA_NO_ERROR)

					PMBUSHelper::getPMBUSCMDData()[QueryCMDIndex].m_cmdStatus.m_AddtionalData[1] = PreviousQueryAdditionalCMD;

				}// if (QueryCMDIndex >= 0)

				PMBUSHelper::getPMBUSCMDData()[idx].m_cmdStatus.m_queried = cmd_query_done;

			}// if (this->m_pmBusCommand[idx].m_cmdStatus.m_queried == cmd_query_not_yet)

			// Emit 'wxEVT_COMMAND_QUERY_SEQUENCE_UPDATE' Event
			wxThreadEvent* threadUpdateDialog_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_QUERY_SEQUENCE_UPDATE);
			threadUpdateDialog_evt->SetInt(idx);
			wxQueueEvent(this->m_evtHandler, threadUpdateDialog_evt);

			PSU_DEBUG_PRINT(MSG_DEBUG, "QUERY Command %02xH End", PMBUSHelper::getPMBUSCMDData()[idx].m_register);

		}// for (unsigned int idx = 0; idx < PMBUSHelper::GetCurrentCMDTableSize() && m_running == true; idx++)

		m_running = false;

		// Emit 'wxEVT_COMMAND_QUERY_SEQUENCE_END' Event
		wxThreadEvent* threadEndDialog_evt = new wxThreadEvent(wxEVT_THREAD, wxEVT_COMMAND_QUERY_SEQUENCE_END);
		if (sendRetryStillFailed == true || receiveFailed == true || i2cNotFound == true){
			threadEndDialog_evt->SetInt(1);
		}
		wxQueueEvent(this->m_evtHandler, threadEndDialog_evt);
	};

	PSU_DEBUG_PRINT(MSG_DEBUG, "QUERYSequenceThread Exit");

	return (wxThread::ExitCode)1;
}