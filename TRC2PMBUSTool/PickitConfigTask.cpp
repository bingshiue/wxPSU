/**
 * @file PickitConfigTask.cpp
 */
#include "Task.h"

PickitConfigTask::PickitConfigTask(
	IOACCESS*      ioaccess,
	unsigned int*  currentUseIO)
{

	this->m_id = task_ID_PickitConfigTask;

	this->m_IOAccess = ioaccess;
	this->m_currentUseIO = currentUseIO;

}


PickitConfigTask::~PickitConfigTask(void){

}

void PickitConfigTask::Draw(void){

}

int PickitConfigTask::Main(double elapsedTime){

	unsigned char sendBuffer[256] = { 0 };
	unsigned char recvBuffer[256] = { 0 };
	unsigned int offset;

	// INIT PicKit Start

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

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
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceSendData(sendBuffer, 65);

	// Receive Response
	this->m_IOAccess[*this->m_currentUseIO].m_DeviceReadData(recvBuffer, 64);

#endif

	// INIT Pickit End

	// Delete 
	delete this;

	return 0;
}

