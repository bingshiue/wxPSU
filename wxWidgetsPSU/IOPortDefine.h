/**
 * @file IOPortDefine.h
 */
#ifndef _IOPORTDEFINE_H_
#define _IOPORTDEFINE_H_

#define SEND_BUFFER_MAX_SIZE  64/**< Send Buffer Maximum Size */
#define SERIALPORT_RECV_BUFF_SIZE  256 /**< Seroal Port Receive Buufer Maximum Size */

#define SERIAL_SEND_DATA_SIZE  10/**< Serial Send Data Size */
#define HID_SEND_DATA_SIZE  64/**< HID Send Data Size */

#define IO_PORT_MAX_COUNT  255/**< Max Count of IO Device */     

#define SERIAL_PORT_SEND_SEMAPHORE_WAITTIMEOUT  1000/**< Timeout of Serial Port Send Semaphore */
#define SERIAL_PORT_SEND_POLLING_INTERVAL  20/**< Interval of Serial Port Send Polling (Milliseconds) */

#define IO_SIZE  2/**< Current 2 Kind : Serial Port & HID */

/**
* @brief IO Port Kind.
*/
enum {
	IOACCESS_SERIALPORT = 0,
	IOACCESS_HID
};

/**
* @brief IO Port Status.
*/
enum {
	IODEVICE_CLOSE = 0,
	IODEVICE_OPEN
};

#endif