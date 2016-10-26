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

//#define PMBUSCOMMAND_SIZE  62/**< Count for total PMBus command */

#define SEND_BUFFER_MAX_SIZE  64/**< Send Buffer Maximum Size */
#define SERIALPORT_RECV_BUFF_SIZE  256 /**< Seroal Port Receive Buufer Maximum Size */

typedef struct pmbuscmd_t;

/**
 * @brief Struct for Receive Buff 
 */
typedef struct recvbuff_t {
	unsigned int m_length;/**< Receive Data length */
	unsigned char m_recvBuff[SERIALPORT_RECV_BUFF_SIZE];/**< Receive Data Buff */
	unsigned char m_dataBuff[SERIALPORT_RECV_BUFF_SIZE];/**< Data Buff (Only contain the data bytes) */
}RECVBUFF_t;

/**
 * @brief Struct for CMD Status
 */
typedef struct cmdstatus_t {
	unsigned char m_status;/**< Status of CMD (running, success, failure) */
	unsigned char m_alsoSendWriteData;/**< Also Send Write Data */
	unsigned char m_AddtionalDataLength;/**< Additional Data Length */
	unsigned char m_AddtionalData[3];/**< Addition Data */
	unsigned char m_NeedChangePage;/**< Need Change Page */
	unsigned char m_cmdPage;/**< Command Page */

}CMDSTATUS_t;

/**
 * @brief Command Query Call Back Function.
 */
typedef int(*CMDQueryCBFunc)(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);

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
	CMDQueryCBFunc m_queryCBFunc;/**< Query CB Function */
	CMDCookCBFunc  m_cookCBFunc;/**< Query CB Function */
	CMDRawCBFunc   m_rawCBFunc;/**< Query CB Function */

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

} PMBUSCOMMAND_t;

typedef struct pmbusSendcmd_t {
	unsigned char m_sendData[256];

	unsigned int m_sendDataLength;

	unsigned int m_bytesToRead;

} PMBUSSendCOMMAND_t;

#endif