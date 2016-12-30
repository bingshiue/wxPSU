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

#define IO_SIZE  3/**< Current 3 Kinds : 1.Serial Port 2.USBHID 3.Total Phase I2C Host Adaptor */

#define BASE_RESPONSE_DATA_LENGTH 6

/**
 * @brief IO Port Kind.
 */
enum {
	IOACCESS_SERIALPORT = 0,/**< I/O is Serial Port */
	IOACCESS_HID,/**< I/O is USB HID */
	IOACCESS_TOTALPHASE/**< I/O is Total Phase I2C Host Adaptor */
};

/**
 * @brief IO Port Status.
 */
enum {
	IODEVICE_CLOSE = 0,/**< Indicates I/O is close */
	IODEVICE_OPEN/**< Indicates I/O is open */
};

#endif