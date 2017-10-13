/**
 * @file PMBUSCommandType.h
 */
#ifndef _PMBUSCOMMANDTYPE_H_
#define _PMBUSCOMMANDTYPE_H_

#ifdef _MSC_VER
#pragma warning(disable:4091)
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "IOPortDefine.h"

enum {
	cmd_access_read = 0,
	cmd_access_br,// = cmd_access_read,
	cmd_access_write,
	cmd_access_bw,// = cmd_access_write,
	cmd_access_readwrite,
	cmd_access_brbw,// = cmd_access_readwrite
	cmd_access_bwr_read,// Block Write - Block Read Process Call
	cmd_access_bwr_readwrite,//  Block Write - Block Read Process Call, Also have write operation 
};

enum {
	cmd_status_not_run = 0,
	cmd_status_running,
	cmd_status_success,
	cmd_status_failure,
	cmd_status_checksum_error,
	cmd_status_i2c_bus_not_acknowledge,
};

enum {
	cmd_normal_read_data = 0,
	cmd_also_send_write_data
};

enum {
	cmd_no_need_change_page = 0,
	cmd_need_change_page
};

enum {
	cmd_data_format_LinearData_Format =0,
	cmd_data_format_16bit_Signed_Number,
	cmd_data_format_Reserved,
	cmd_data_format_DirectData_Format,
	cmd_data_format_8bit_Unsigned_Number,
	cmd_data_format_VID_Mode,
	cmd_data_format_Manufacturer_Specific,
	cmd_data_format_Don_t_Return_Numeric_Data
};

enum {
	cmd_unsupport = 0,
	cmd_support
};

enum {
	cmd_query_not_yet = 0,
	cmd_query_done
};

enum {
	rw_write_coefficients = 0,
	rw_read_coefficients = 1,
};

typedef struct pmbuscmd_t PMBUSCOMMAND_t;

/**
 * @brief Struct for Receive Buff 
 */
typedef struct recvbuff_t {
	unsigned int m_length;/**< Receive Data length */
	unsigned char m_recvBuff[SERIALPORT_RECV_BUFF_SIZE];/**< Receive Data Buff */
	unsigned char m_dataBuff[SERIALPORT_RECV_BUFF_SIZE];/**< Data Buff (Only contain the data bytes) */

	recvbuff_t(){
		m_length = 0;
		memset(m_recvBuff, 0, SERIALPORT_RECV_BUFF_SIZE);
		memset(m_dataBuff, 0, SERIALPORT_RECV_BUFF_SIZE);
	}

	recvbuff_t(int init){
		m_length = 0;
		memset(m_recvBuff, 0, SERIALPORT_RECV_BUFF_SIZE);
		memset(m_dataBuff, 0, SERIALPORT_RECV_BUFF_SIZE);
	}

}RECVBUFF_t;

/**
 * @brief Direct Data Format
 */
typedef struct directFormatCoefficients_t {
	short m_M;/**< M */
	short m_B;/**< B */
	char  m_R;/**< R */

	directFormatCoefficients_t(){
		m_M = 0;
		m_B = 0;
		m_R = 0;
	}

	directFormatCoefficients_t(short M, short B, char R){
		m_M = M;
		m_B = B;
		m_R = R;
	}

}DirectFormatCoefficients_t;

/**
 * @brief Struct for CMD Data Format.
 */
typedef struct dataFormat_t {
	unsigned char m_formatType;/**< Data Format Type */
	DirectFormatCoefficients_t m_ReadCoefficients;/**< Direct Data Format Read Coefficients */
	DirectFormatCoefficients_t m_WriteCoefficients;/**< Direct Data Format Write Coefficients */

	dataFormat_t(){
		this->m_formatType = 0;// 0 is the linear data format
		//this->m_ReadCoefficients = {};
		//this->m_WriteCoefficients = {};
	}

	dataFormat_t(int init){
		this->m_formatType = 0;// 0 is the linear data format
		//this->m_ReadCoefficients = {};
		//this->m_WriteCoefficients = {};
	}

	// For <brace-enclosed initializer list>
	dataFormat_t(unsigned char formatType, DirectFormatCoefficients_t ReadCoefficients, DirectFormatCoefficients_t m_WriteCoefficients){
		this->m_formatType = formatType;// 0 is the linear data format
		this->m_ReadCoefficients = ReadCoefficients;
		this->m_WriteCoefficients = m_WriteCoefficients;
	}

}DataFormat_t;

/**
 * @brief Struct for CMD Status
 */
typedef struct cmdstatus_t {
	unsigned char m_support;/**< Support */
	unsigned char m_status;/**< Status of CMD (running, success, failure) */
	unsigned char m_alsoSendWriteData;/**< Also Send Write Data */
	unsigned char m_AddtionalDataLength;/**< Additional Data Length */
	unsigned char m_AddtionalData[4];/**< Addition Data */
	unsigned char m_NeedChangePage;/**< Need Change Page */
	unsigned char m_cmdPage;/**< Command Page */
	unsigned char m_queried;/**< Queried */

}CMDSTATUS_t;

/**
 * @brief Command Query Call Back Function.
 */
typedef int(*CMDQueryCBFunc)(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

/**
 * @brief Command Coefficients Call Back Function.
 */
typedef int(*CMDCoefficientsCBFunc)(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

/**
 * @brief Command Cook Call Back Function.
 */
typedef int(*CMDCookCBFunc)(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int sizeOfstr);

/**
 * @brief Command Raw Call Back Function.
 */
typedef int(*CMDRawCBFunc)(pmbuscmd_t* pmbuscmd, wchar_t* string, unsigned int dataBytesLength);

/**
 * @brief Struct for CB Functions
 */
typedef struct cmdcbfunc_t {
	CMDQueryCBFunc        m_queryCBFunc;/**< Query CB Function */
	CMDCoefficientsCBFunc m_coefficientsCBFunc;/**< Coefficients CB Function */
	CMDCookCBFunc         m_cookCBFunc;/**< Query Cook Function */
	CMDRawCBFunc          m_rawCBFunc;/**< Query Raw Function */

	cmdcbfunc_t(){
		m_queryCBFunc = NULL;
		m_coefficientsCBFunc = NULL;
		m_cookCBFunc = NULL;
		m_rawCBFunc = NULL;
	}

	cmdcbfunc_t(int init){
		m_queryCBFunc = NULL;
		m_coefficientsCBFunc = NULL;
		m_cookCBFunc = NULL;
		m_rawCBFunc = NULL;
	}

}CMDCBFUNC_t;

#define LABEL_SIZE 16
#define NAME_SIZE  64
#define RAW_SIZE    8
/**
 * @brief Structure for PMBus Command.
 */
typedef struct pmbuscmd_t {
	bool            m_toggle;/**< Enable/Disable */
	char            m_label[LABEL_SIZE];/**< Label */
	unsigned int    m_register;/**< Register */
	char            m_name[NAME_SIZE];/**< Name */
	unsigned int    m_access;/**< Access */
	unsigned int    m_query;/**< Query */
	unsigned int    m_cook;/**< Cook */
	unsigned char   m_raw[RAW_SIZE];/**< Raw */

	unsigned int    m_responseDataLength;/**< Response Data Length */


	RECVBUFF_t      m_recvBuff;/**< Receive Data Buffer */
	CMDSTATUS_t     m_cmdStatus;/**< CMD Status */

	CMDCBFUNC_t     m_cmdCBFunc;/**< CallBack Function */

	wxPanel        *m_writePage;/**< Write Page */
	wxPanel        *m_readPage;/**< Read Page */
	DataFormat_t    m_dataFormat;/**< Data Format */

} PMBUSCOMMAND_t;

typedef struct pmbusSendcmd_t {
	unsigned char m_sendData[256];

	unsigned int m_sendDataLength;

	unsigned int m_bytesToRead;

	unsigned short m_sendCommand;

} PMBUSSendCOMMAND_t;

typedef struct pmbusReadCMD_t {

	unsigned char m_slaveAddr;/**< Slave Address */
	unsigned char m_cmd;/**< Command */
	unsigned char m_numOfReadBytes;/**< Number Of Read Bytes */

} PMBUSReadCMD_t;

typedef struct pmbusWriteCMD_t {

	unsigned char m_slaveAddr;/**< Slave Address */
	unsigned char m_cmd;/**< Command */
	unsigned char m_numOfSendBytes;/**< Number Of Send Bytes */

	unsigned char m_sendBytes[256];

} PMBUSWriteCMD_t;

typedef struct pmbusBlockWRCMD_t {

	unsigned char m_slaveAddr;/**< Slave Address */
	unsigned char m_cmd;/**< Command */
	unsigned char m_numOfWriteBytes;/**< Number Of Write Bytes */

	unsigned char m_writeBytes[256];
	unsigned char m_numOfReadBytes;/**< Number Of Read Bytes */

} PMBUSBlockWRCMD_t;

/**
 * @brief PMBUS Read CMD Buffer Maker Function.
 */
typedef int (*PMBUSReadCMDBufferMakerFunc)(PMBUSCOMMAND_t* pmBusCommand, unsigned char* sendBuffer, unsigned int* currentIO, unsigned int idx, unsigned int command, unsigned int responseDataLength);

/**
 * @brief PMBUS Write CMD Buffer Maker Function.
 */
typedef int (*PMBUSWriteCMDBufferMakerFunc)(unsigned int *currentIO, unsigned char *buff, unsigned int sizeOfBuffer, unsigned int cmd, unsigned char *dataBuffer, unsigned int sizeOfDataBuffer);

/**
 * @brief PMBUS CMD Buffer Provider.
 */
typedef struct pmbusCMDBufferProvider_t {

	PMBUSReadCMDBufferMakerFunc m_pmbusdReadCMDBufferMaker;

	PMBUSWriteCMDBufferMakerFunc m_pmbusdWriteCMDBufferMaker;

	pmbusCMDBufferProvider_t(PMBUSReadCMDBufferMakerFunc readCMDBufferMakerFunc, PMBUSWriteCMDBufferMakerFunc writeCMDBufferMakerFunc) {
		m_pmbusdReadCMDBufferMaker = readCMDBufferMakerFunc;
		m_pmbusdWriteCMDBufferMaker = writeCMDBufferMakerFunc;
	}

} PMBUSCMDBufferProvider_t;

#endif
