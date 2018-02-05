/**
 * @file ISPDefine.h
 */
#ifndef _ISPDEFINE_H_
#define _ISPDEFINE_H_

#define DEFAULT_FW_UPLOAD_MODE_CMD       0xf0 /**< Default FW Upload Mode Command */
#define DEFAULT_FW_UPLOAD_CMD            0xf1 /**< Default FW Upload Command */
#define DEFAULT_FW_UPLOAD_STATUS_CMD     0xf3 /**< Default FW Upload Status Command */

#define GIGABYTE_FW_UPLOAD_MODE_CMD      0xd6 /**< Gigabyte FW Upload Mode Command */
#define GIGABYTE_FW_UPLOAD_CMD           0xd7 /**< Gigabyte FW Upload Mode Command */
#define GIGABYTE_FW_UPLOAD_STATUS_CMD    0xd8 /**< Gigabyte FW Upload Mode Command */

#define UPDATE_PRIMARY_FW_TARGET    0x50 /**< Primary FW Update Target code */
#define UPDATE_SECONDARY_FW_TARGET  0x60 /**< Secondary FW Update Target code */

#define ISP_HANDLE_0D /**< Handle '0x0d' as special character in ISP */

#define ISP_PFC_START_VERIFY_DELAY_TIME    100/**< ISP PFC Start Verify Delay Time */
#define ISP_DD_START_VERIFY_DELAY_TIME     100/**< ISP DD Start Verify Delay Time */

//#define ISP_SLEEP /**< Sleep Between F3(F1) Command */
#ifdef ISP_SLEEP
#define ISP_SLEEP_TIME  10  /**< Sleep Time Between F3(F1) Command (MilliSecond) */
#endif

#define ISP_START_VERIFY_RETRY  20 /**< ISP Start Verify(F0) Command Fail Retry Times */

#define ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP /**< Sleep before Start Verify Command Failed Retry */
#ifdef ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP 
#define ISP_START_VERIFY_CMD_FAILED_RETRY_SLEEP_TIME 50 /**< Sleep Time before Start Verify Command Failed Retry (MilliSecond) */
#endif


#define ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY /**< Delay After Primary Firmware Receive Start Verify CMD Success */
#ifdef ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY
#define ISP_PRIMARY_FW_UPDATE_VERIFY_SUCCESS_DELAY_TIME  4500 /**< Delay Time After Primary Firmware Receive Start Verify CMD Success */
#endif

#define ISP_CHECK_STATUS_RETRY  5 /**< ISP Check Status(F3) Command Fail Retry Times */

#define PFC_ISP_F3_CMD_DELAY /**< PFC ISP Sleep before Send F3 Command */

#define ISP_F3_CMD_FAILED_RETRY_SLEEP /**< Sleep before F3 Command Check Failed Retry */
#ifdef ISP_F3_CMD_FAILED_RETRY_SLEEP 
#define ISP_F3_CMD_FAILED_RETRY_SLEEP_TIME 50 /**< Sleep Time before F3 Command Check Failed Retry (MilliSecond) */
#endif

#define WAIT_PFC_REBOOT_TIME  7000 /**< Wait for PFC DSP Reboot Time (MilliSecond) */
#define WAIT_DD_REBOOT_TIME  10000 /**< Wait for DD DSP Reboot Time (MilliSecond) */

#define UserCancelISP_POST_DELAY_TIME 7000 /**< User Cancel ISP Post Delay Time */

#define ISP_SEND_FULL_ADDRESS /**< Send Full Address Instead of Offset */

/* ----- Below is for debug only ------ */

//#define ISP_DONT_WAIT_RESPONSE /**< For debug, Do ISP Sequence without waiting DSP's response */
//#define IGNORE_ISP_RESPONSE_ERROR /**< For debug, Ignore ISP response error */

/**
 * @brief ISP Sequence Status.
 */
enum {
	ISP_Status_InProgress = 0x00,
	ISP_Status_VerifyBeforeStart = 0x01,
	ISP_Status_ALLDone = 0x02,
	ISP_Status_UserRequestCancel = 0x04,
	ISP_Status_SendDataFailed = 0x08,
	ISP_Status_ResponseDataError = 0x10,
	ISP_Status_RebootCheckError = 0x20,
	ISP_Status_UnknownErrorOccurs = 0x80
};

#endif