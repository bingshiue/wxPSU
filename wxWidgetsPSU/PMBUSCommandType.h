/**
 * @file PMBUSCommandType.h
 */
#ifndef _PMBUSCOMMANDTYPE_H_
#define _PMBUSCOMMANDTYPE_H_

#include "CommonDef.h"

enum {
	cmd_access_read = 0,
	cmd_access_br = cmd_access_read,
	cmd_access_write,
	cmd_access_bw = cmd_access_write,
	cmd_access_readwrite,
	cmd_access_brbw = cmd_access_readwrite
};

enum {
	cmd_status_not_run = 0,
	cmd_status_running,
	cmd_status_success,
	cmd_status_failure,
};

#define PMBUSCOMMAND_SIZE  62/**< Count for total PMBus command */

/**
 * @brief Struct for Receive Buff 
 */
typedef struct recvbuff_t {
	unsigned int m_length;/**< Receive Data length */
	unsigned char m_recvBuff[SERIALPORT_RECV_BUFF_SIZE];/**< Receive Data Buff */
}RECVBUFF_t;

/**
 * @brief Struct for CMD Status
 */
typedef struct cmdstatus_t {
	unsigned char m_status;/**< Status of CMD */
}CMDSTATUS_t;

/**
 * @brief Command Query Call Back Function.
 */
typedef int(*CMDQueryCBFunc)(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);

/**
 * @brief Command Cook Call Back Function.
 */
typedef int(*CMDCookCBFunc)(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);

/**
 * @brief Command Raw Call Back Function.
 */
typedef int(*CMDRawCBFunc)(RECVBUFF_t* recvBuff_t, wchar_t* string, unsigned int sizeOfstr);

/**
 * @brief Struct for CB Functions
 */
typedef struct cmdcbfunc_t {
	CMDQueryCBFunc m_quertCBFunc;/**< Query CB Function */
	CMDCookCBFunc  m_cookCBFunc;/**< Query CB Function */
	CMDRawCBFunc   m_rawCBFunc;/**< Query CB Function */

}CMDCBFUNC_t;

#define NAME_SIZE  64
#define RAW_SIZE    8
/**
 * @brief Structure for PMBus Command.
 */
typedef struct pmbuscmd_t {
	bool            m_toggle;/**< Enable/Disable */
	unsigned int    m_register;/**< Register */
	         char   m_name[NAME_SIZE];/**< Name */
	unsigned int    m_access;/**< Access */
	unsigned int    m_query;/**< Query */
	unsigned int    m_cook;/**< Cook */
	unsigned char   m_raw[RAW_SIZE];/**< Raw */

	unsigned int    m_responseDataLength;/**< Response Data Length */


	RECVBUFF_t      m_recvBuff;/**< Receive Data Buffer */
	CMDSTATUS_t     m_cmdStatus;/**< CMD Status */

	CMDCBFUNC_t     m_cmdCBFunc;/**< CallBack Function */

}PMBUSCOMMAND_t;

#endif