/**
 * @file AppSettings.h
 */
#ifndef _APPSETTINGS_H_
#define _APPSETTINGS_H_

#ifdef _WIN32
#include <Windows.h>
#endif

#include <wx/wx.h>

#include "Customers.h"
#include "Models.h"
#include "PMBUSCommandType.h"
#include "ISPDefine.h"

enum {
	RunMode_Iterations = 0,
	RunMode_Continually,
	RunMode_StopAnError
};

enum {
	Log_Mode_Log_ALL = 0,
	Log_Mode_Log_Error_Only
};

enum {
	Generic_Disable = 0,
	Generic_Enable
};

enum {
	Generic_Unchecked = 0,
	Generic_Checked
};

enum {
	PMBUS_ReadMethod_1_1 = 0,
	PMBUS_ReadMethod_1_2
};

enum {
	I2C_AdaptorModuleBoard_PICKIT_SERIAL = 0,
	I2C_AdaptorModuleBoard_R90000_95611,
	I2C_AdaptorModuleBoard_R90000_9271_USB,
	I2C_AdaptorModuleBoard_TOTALPHASE,
	I2C_AdaptorModuleBoard_TRC2I2CAdapter
};

enum {
	TOTALPHASE_I2C_BITRATE_100KHZ = 100,
	TOTALPHASE_I2C_BITRATE_400KHZ = 400
};

#define DEFAULT_CUSTOMER            (unsigned long)Customer_GIGABYTE//Customer_NEC
#define DEFAULT_MODEL               (unsigned long)GIGABYTE_Model_CRPS001//NEC_Model_FSG003_000G

#define DEFAULT_I2C_ADAPTOR_MODULE  (unsigned long)I2C_AdaptorModuleBoard_R90000_9271_USB
#define DEFAULT_I2C_SLAVEADDRESS    0xb6
#define DEFAULT_RUN_MODE            (unsigned long)(RunMode_Continually)
#define DEFAULT_POLLING_INTERVAL    20
#define DEFAULT_ITERATIONS_VALUE    10000
#define DEFAULT_ENABLE_CHECKSUM     (unsigned long)Generic_Enable

#define DEFAULT_LOG_MODE            (unsigned long)Log_Mode_Log_ALL
#define DEFAULT_LOG_TO_FILE         (unsigned long)Generic_Disable
#define DEFAULT_LOG_FILE_PATH       ""

#define DEFAULT_PMBUS_READ_METHOD     (unsigned long)PMBUS_ReadMethod_1_1

#define DEFAULT_ACS_SETPOINT_INPUT_MAX  2400
#define DEFAULT_ACS_SETPOINT_INPUT_MIN  2000

#define DEFAULT_PFC_ISP_F3_CMD_DELAY_SLEEP_TIME                   25// 6 //(Unit : millisecond)
#define DEFAULT_PFC_ISP_F3_CMD_TOTALPHASE_DELAY_SLEEP_TIME        30//12 //(Unit : millisecond)

#define DEFAULT_RUNIN_TIMES  10

#define DEFAULT_ONLY_POLLING_SUPPORT_CMD       (unsigned long)Generic_Disable
#define DEFAULT_CLEAR_LOG_BEFORE_MONITOR_RUN   (unsigned long)Generic_Enable
#define DEFAULT_AUTO_QUERY_CMD_ON_IO_OPEN      (unsigned long)Generic_Disable
#define DEFAULT_QUERY_CMD_BEFORE_POLLING       (unsigned long)Generic_Enable

#define DEFAULT_INCREASE_CPU_OVERHEAD     (unsigned long)Generic_Disable

#ifdef __GNUC__
#define CBR_9600     9600
#define ONESTOPBIT      1 
#define NOPARITY        0
#endif

#define DEFAULT_COMPORT_NUM           0x01
#define DEFAULT_COMPORT_BUADRATE      CBR_9600
#define DEFAULT_COMPORT_BYTESIZE      8
#define DEFAULT_COMPORT_STOPBITS      ONESTOPBIT
#define DEFAULT_COMPORT_PARITYCHECK   NOPARITY

#define DEFAULT_TOTALPHASE_I2C_BITRATE (unsigned long)TOTALPHASE_I2C_BITRATE_100KHZ

/* --- USB ADAPTOR Setting ---- */
#define DEFAULT_USB_ADAPTOR_I2C_BIT_RATE_SPEED            100
#define DEFAULT_USB_ADAPTOR_I2C_SMBUS                     (unsigned long)Generic_Checked
#define DEFAULT_USB_ADAPTOR_I2C_COMM                      200
#define DEFAULT_USB_ADAPTOR_I2C_BUS_TIMEOUT               20
#define DEFAULT_USB_ADAPTOR_I2C_RECEIVE_BUFFER_SIZE       512

#define DEFAULT_USB_ADAPTOR_SPI_BIT_RATE_SPEED            1000
#define DEFAULT_USB_ADAPTOR_SPI_RECEIVED_TIMEOUT          40
#define DEFAULT_USB_ADAPTOR_SPI_RECEIVE_BUFFER_SIZE       512

#define DEFAULT_USB_ADAPTOR_CAN_BIT_RATE_SPEED            500
#define DEFAULT_USB_ADAPTOR_CAN_RECEIVED_MSGSIZE          20
#define DEFAULT_USB_ADAPTOR_CAN_RECEIVED_TIMEOUT          2
#define DEFAULT_USB_ADAPTOR_CAN_RECEIVE_BUFFER_SIZE       256


#define USB_ADAPTOR_UART_SIZE                             4

#define DEFAULT_USB_ADAPTOR_UART_NUM                      0x00
#define DEFAULT_USB_ADAPTOR_UART_BUADRATE                 CBR_9600
#define DEFAULT_USB_ADAPTOR_UART_BYTESIZE                 8
#define DEFAULT_USB_ADAPTOR_UART_STOPBITS                 ONESTOPBIT
#define DEFAULT_USB_ADAPTOR_UART_PARITYCHECK              NOPARITY
#define DEFAULT_USB_ADAPTOR_UART_RECEIVE_BUFFER_SIZE      1024

#define DEFAULT_ADAPTOR_GPIO_AUTO_REPORT                  (unsigned long)Generic_Unchecked
#define DEFAULT_ADAPTOR_GPIO_ENABLE_PWM					  (unsigned long)Generic_Unchecked
#define DEFAULT_ADAPTOR_GPIO_CLOCK_IN_DI6                 (unsigned long)Generic_Unchecked
#define DEFAULT_ADAPTOR_GPIO_CLOCK_IN_DI7                 (unsigned long)Generic_Unchecked

#define DEFAULT_ADAPTOR_GPIO_DIGITAL_OUTPUT               0xff
#define DEFAULT_ADAPTOR_GPIO_PWM_FREQUENCE                0
#define DEFAULT_ADAPTOR_GPIO_PWM_DUTY                     50

typedef struct comport_setting {
	unsigned long m_comportNumber;
	unsigned long m_buadRate;
	unsigned long m_byteSize;
	unsigned long m_stopBits;
	unsigned long m_parityCheck;


	void Reset(void){
		m_comportNumber = DEFAULT_COMPORT_NUM;
		m_buadRate      = DEFAULT_COMPORT_BUADRATE;
		m_byteSize      = DEFAULT_COMPORT_BYTESIZE;
		m_stopBits      = DEFAULT_COMPORT_STOPBITS;
		m_parityCheck   = DEFAULT_COMPORT_PARITYCHECK;
	}


} COMPORT_SETTING_t;

typedef struct usb_adaptor_i2c_setting {
	unsigned long m_bitRateSpeed;
	unsigned long m_smBus;
	unsigned long m_comm;
	unsigned long m_busTimeout;
	unsigned long m_receiveBufferSize;

	unsigned long m_previous_bitRateSpeed;
	unsigned long m_previous_smBus;
	unsigned long m_previous_comm;
	unsigned long m_previous_busTimeout;
	unsigned long m_previous_receiveBufferSize;

	usb_adaptor_i2c_setting(){
		Reset();
	}

	void Reset(void){
		m_previous_bitRateSpeed = m_bitRateSpeed = DEFAULT_USB_ADAPTOR_I2C_BIT_RATE_SPEED;
		m_previous_smBus = m_smBus = DEFAULT_USB_ADAPTOR_I2C_SMBUS;
		m_previous_comm = m_comm = DEFAULT_USB_ADAPTOR_I2C_COMM;
		m_previous_busTimeout = m_busTimeout = DEFAULT_USB_ADAPTOR_I2C_BUS_TIMEOUT;
		m_previous_receiveBufferSize = m_receiveBufferSize = DEFAULT_USB_ADAPTOR_I2C_RECEIVE_BUFFER_SIZE;
	}


} USB_ADAPTOR_I2C_SETTING_t;

typedef struct usb_adaptor_spi_setting {
	unsigned long m_bitRateSpeed;
	unsigned long m_receivedTimeout;
	unsigned long m_receiveBufferSize;

	unsigned long m_previous_bitRateSpeed;
	unsigned long m_previous_receivedTimeout;
	unsigned long m_previous_receiveBufferSize;

	usb_adaptor_spi_setting(){
		Reset();
	}

	void Reset(void){
		m_previous_bitRateSpeed = m_bitRateSpeed = DEFAULT_USB_ADAPTOR_SPI_BIT_RATE_SPEED;
		m_previous_receivedTimeout = m_receivedTimeout = DEFAULT_USB_ADAPTOR_SPI_RECEIVED_TIMEOUT;
		m_previous_receiveBufferSize = m_receiveBufferSize = DEFAULT_USB_ADAPTOR_SPI_RECEIVE_BUFFER_SIZE;
	}

} USB_ADAPTOR_SPI_SETTING_t;

typedef struct usb_adaptor_can_setting {
	unsigned long m_bitRateSpeed;
	unsigned long m_receivedMSGSize;
	unsigned long m_receivedTimeout;
	unsigned long m_receiveBufferSize;

	unsigned long m_previous_bitRateSpeed;
	unsigned long m_previous_receivedMSGSize;
	unsigned long m_previous_receivedTimeout;
	unsigned long m_previous_receiveBufferSize;

	usb_adaptor_can_setting(){
		Reset();
	}

	void Reset(void){
		m_previous_bitRateSpeed = m_bitRateSpeed = DEFAULT_USB_ADAPTOR_CAN_BIT_RATE_SPEED;
		m_previous_receivedMSGSize = m_receivedMSGSize = DEFAULT_USB_ADAPTOR_CAN_RECEIVED_MSGSIZE;
		m_previous_receivedTimeout = m_receivedTimeout = DEFAULT_USB_ADAPTOR_CAN_RECEIVED_TIMEOUT;
		m_previous_receiveBufferSize = m_receiveBufferSize = DEFAULT_USB_ADAPTOR_CAN_RECEIVE_BUFFER_SIZE;
	}

} USB_ADAPTOR_CAN_SETTING_t;

typedef struct usb_adaptor_uart_setting {
	unsigned long m_uartNumber;
	unsigned long m_buadRate;
	unsigned long m_byteSize;
	unsigned long m_stopBits;
	unsigned long m_parityCheck;
	unsigned long m_receiveBufferSize;

	unsigned long m_previous_uartNumber;
	unsigned long m_previous_buadRate;
	unsigned long m_previous_byteSize;
	unsigned long m_previous_stopBits;
	unsigned long m_previous_parityCheck;
	unsigned long m_previous_receiveBufferSize;

	usb_adaptor_uart_setting() {
		Reset();
	}

	void Reset(void){
		m_previous_uartNumber = m_uartNumber = DEFAULT_USB_ADAPTOR_UART_NUM;
		m_previous_buadRate = m_buadRate = DEFAULT_USB_ADAPTOR_UART_BUADRATE;
		m_previous_byteSize = m_byteSize = DEFAULT_USB_ADAPTOR_UART_BYTESIZE;
		m_previous_stopBits = m_stopBits = DEFAULT_USB_ADAPTOR_UART_STOPBITS;
		m_previous_parityCheck = m_parityCheck = DEFAULT_USB_ADAPTOR_UART_PARITYCHECK;
		m_previous_receiveBufferSize = m_receiveBufferSize = DEFAULT_USB_ADAPTOR_UART_RECEIVE_BUFFER_SIZE;
	}

}USB_ADAPTOR_UART_SETTING_t;

typedef struct usb_adaptor_gpio_setting {
	unsigned long m_autoReport;
	unsigned long m_enablePWM;
	unsigned long m_clockInDI6;
	unsigned long m_clockInDI7;
	unsigned long m_digitalOutput;
	unsigned long m_pwmFreq;
	unsigned long m_pwmDuty;

	unsigned long m_previous_autoReport;
	unsigned long m_previous_enablePWM;
	unsigned long m_previous_clockInDI6;
	unsigned long m_previous_clockInDI7;
	unsigned long m_previous_digitalOutput;
	unsigned long m_previous_pwmFreq;
	unsigned long m_previous_pwmDuty;

	usb_adaptor_gpio_setting(){
		Reset();
	}

	void Reset(){
		m_previous_autoReport = m_autoReport = DEFAULT_ADAPTOR_GPIO_AUTO_REPORT;
		m_previous_enablePWM = m_enablePWM = DEFAULT_ADAPTOR_GPIO_ENABLE_PWM;
		m_previous_clockInDI6 = m_clockInDI6 = DEFAULT_ADAPTOR_GPIO_CLOCK_IN_DI6;
		m_previous_clockInDI7 = m_clockInDI7 = DEFAULT_ADAPTOR_GPIO_CLOCK_IN_DI7;
		m_previous_digitalOutput = m_digitalOutput = DEFAULT_ADAPTOR_GPIO_DIGITAL_OUTPUT;
		m_previous_pwmFreq = m_pwmFreq = DEFAULT_ADAPTOR_GPIO_PWM_FREQUENCE;
		m_previous_pwmDuty = m_pwmDuty = DEFAULT_ADAPTOR_GPIO_PWM_DUTY;
	}

}USB_ADAPTOR_GPIO_SETTING_t;

typedef struct appSettings_t {

	unsigned long m_currentUseCustomer;/**< Current Use Customer */
	unsigned long m_previousUseCustomer;/**< Previous Use Customer */
	unsigned long m_currentUseModel;/**< Current Use Model */
	unsigned long m_previousUseModel;/**< Previous Use Model */

	COMPORT_SETTING_t m_comportSetting;/**< Serial Port Settings */
	
	unsigned long m_I2CAdaptorModuleBoard;/**< I2C Adaptor Module Board */
	unsigned long m_I2CSlaveAddress;/**< I2C Slave Address */
	unsigned long m_runMode;/**< Run Mode */
	unsigned long m_pollingInterval;/**< Polling Interval */
	unsigned long m_IterationsValue;/**< Iteration Value */
	unsigned long m_EnableChecksum;/**< Enable Checksum */
	unsigned long m_logMode;/**< Log Mode */
	unsigned long m_logToFile;/**< Log To File */
	     wxString m_logFilePath;/**< Log File Path */
	unsigned long m_pmbusReadMethod;/**< PM Bus Read Method */
	unsigned long m_acsSetPointMin;/**< ACE Set Point Minimum Value */
	unsigned long m_acsSetPointMax;/**< ACE Set Point Maximum Value */
	unsigned long m_pfcIspF3CMDDelayTime;/**< PFC ISP F3 CMD Delay Time */
	unsigned long m_pfcIspF3CMDTotalPhaseDelayTime;/**< PFC ISP F3 CMD Total Phase Delay Time */
	unsigned long m_onlyPollingSupportCMD;/**< Only Polling Support CMD */
	unsigned long m_clearLogBeforeMonitorRun;/**< Clear Log Before Monitor Run */
	unsigned long m_ISPPFCWaitRootTime; /**< ISP PFC Wait Reboot Time */
	unsigned long m_ISPDDWaitRootTime;/**< ISP DD Wait Reboot Time */
	unsigned long m_autoQueryCMDOnIOOpen;/**< Auto Query Command On I/O Open */
	unsigned long m_queryCMDBeforePolling;/**< Query CMD Before Polling */
	unsigned long m_increaseCPUOverhead;/**< Increase CPU Overhead */
	unsigned long m_totalPhase_I2C_Bitrate;/**< Total Phase I2C Bitrate */

	USB_ADAPTOR_I2C_SETTING_t m_usbAdaptorI2CSetting;
	USB_ADAPTOR_SPI_SETTING_t m_usbAdaptorSPISetting;
	USB_ADAPTOR_CAN_SETTING_t m_usbAdaptorCANSetting;
	USB_ADAPTOR_UART_SETTING_t m_usbAdaptorUARTSetting[USB_ADAPTOR_UART_SIZE];
	USB_ADAPTOR_GPIO_SETTING_t m_usbAdaptorGPIOSetting;

	wxString m_mfr_id;
	wxString m_mfr_model;
	wxString m_mfr_revision;
	wxString m_mfr_location;
	wxString m_mfr_date;
	wxString m_mfr_serial;

	/* ----- Developer Setting ----- */
	unsigned long m_developerMode;/**< Developer Mode */

	void Reset(void){
		
		this->m_currentUseCustomer = DEFAULT_CUSTOMER;
		this->m_previousUseCustomer = this->m_currentUseCustomer;

		this->m_currentUseModel = DEFAULT_MODEL;
		this->m_previousUseModel = this->m_currentUseModel;
		
		this->m_comportSetting.Reset();

		this->m_I2CAdaptorModuleBoard = DEFAULT_I2C_ADAPTOR_MODULE;
		this->m_I2CSlaveAddress = DEFAULT_I2C_SLAVEADDRESS;
		this->m_runMode = DEFAULT_RUN_MODE;
		this->m_pollingInterval = DEFAULT_POLLING_INTERVAL;
		this->m_IterationsValue = DEFAULT_ITERATIONS_VALUE;
		this->m_EnableChecksum = Generic_Enable;
		this->m_logMode = DEFAULT_LOG_MODE;/**< Log Mode */
		this->m_logToFile = DEFAULT_LOG_TO_FILE;/**< Log To File */
		this->m_logFilePath = wxString::Format("%s", DEFAULT_LOG_FILE_PATH);
		this->m_pmbusReadMethod = DEFAULT_PMBUS_READ_METHOD;
		this->m_acsSetPointMax = DEFAULT_ACS_SETPOINT_INPUT_MAX;
		this->m_acsSetPointMin = DEFAULT_ACS_SETPOINT_INPUT_MIN;

		this->m_pfcIspF3CMDDelayTime = DEFAULT_PFC_ISP_F3_CMD_DELAY_SLEEP_TIME;
		this->m_pfcIspF3CMDTotalPhaseDelayTime = DEFAULT_PFC_ISP_F3_CMD_TOTALPHASE_DELAY_SLEEP_TIME;

		this->m_onlyPollingSupportCMD = DEFAULT_ONLY_POLLING_SUPPORT_CMD;
		this->m_clearLogBeforeMonitorRun = DEFAULT_CLEAR_LOG_BEFORE_MONITOR_RUN;
		this->m_autoQueryCMDOnIOOpen = DEFAULT_AUTO_QUERY_CMD_ON_IO_OPEN;
		this->m_queryCMDBeforePolling = DEFAULT_QUERY_CMD_BEFORE_POLLING;
		this->m_increaseCPUOverhead = DEFAULT_INCREASE_CPU_OVERHEAD;
		this->m_ISPPFCWaitRootTime = WAIT_PFC_REBOOT_TIME;
		this->m_ISPDDWaitRootTime = WAIT_DD_REBOOT_TIME;

		this->m_totalPhase_I2C_Bitrate = DEFAULT_TOTALPHASE_I2C_BITRATE;

		this->m_usbAdaptorI2CSetting.Reset();
		this->m_usbAdaptorSPISetting.Reset();
		this->m_usbAdaptorCANSetting.Reset();

		for (int idx = 0; idx < USB_ADAPTOR_UART_SIZE; idx++){
			m_usbAdaptorUARTSetting[idx].Reset();
		}

		this->m_usbAdaptorGPIOSetting.Reset();

		this->m_developerMode = Generic_Disable;
	}

} AppSettings_t;

#endif
