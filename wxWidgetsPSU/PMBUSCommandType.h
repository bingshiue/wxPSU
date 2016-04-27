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


#define CMD_DATA_SIZE 10/**< Command Data Size */

/**
 * @brief Structure for PMBus Command.
 */
typedef struct pmbuscmd_tag {
	unsigned int  mCommand;/**< Command */
	unsigned char mData[CMD_DATA_SIZE];/**< Data */

}PMBUSCommand;


#define PMBUSCOMMAND_SIZE  62/**< Count for total PMBus command */

/**
 * @brief Struct for Receive Buff 
 */
typedef struct recvbuff_t {
	unsigned int m_length;/**< Receive Data length */
	unsigned char m_recvBuff[SERIALPORT_RECV_BUFF_SIZE];/**< Receive Data Buff */
}RECVBUFF_t;



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


	RECVBUFF_t      m_recvBuff;/**< Receive Data Buffer */

}PMBUSCOMMAND_t;

#define TOTAL_CMD_CNT 2 /**< Total Command Count */

#if 0
PMBUSCommand pmbusCommand[TOTAL_CMD_CNT] = {
	{ 0x01, { 0x41, 0x44, 0xb6, 0x01, 0x0d, 0x0a, 0xb7, 0x02, 0x0d, 0x0a } },
	{ 0x3a, { 0x41, 0x44, 0xb6, 0x3a, 0x0d, 0x0a, 0xb7, 0x02, 0x0d, 0x0a } },
};
#endif

#endif