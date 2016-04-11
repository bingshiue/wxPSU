/**
 * @file PMBUSCommand.h
 */
#ifndef _PMBUSCOMMAND_H_
#define _PMBUSCOMMAND_H_

#define CMD_DATA_SIZE 10/**< Command Data Size */

/**
 * @brief Structure for PMBus Command.
 */
typedef struct pmbuscmd_tag {
	unsigned int  mCommand;/**< Command */
	unsigned char mData[CMD_DATA_SIZE];/**< Data */

}PMBUSCommand;

#define TOTAL_CMD_CNT 2 /**< Total Command Count */

PMBUSCommand pmbusCommand[TOTAL_CMD_CNT] = {
	{ 0x01, { 0x41, 0x44, 0xb6, 0x01, 0x0d, 0x0a, 0xb7, 0x02, 0x0d, 0x0a } },
	{ 0x3a, { 0x41, 0x44, 0xb6, 0x3a, 0x0d, 0x0a, 0xb7, 0x02, 0x0d, 0x0a } },
};

#endif