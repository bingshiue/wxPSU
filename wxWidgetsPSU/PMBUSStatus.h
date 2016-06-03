 /**
  * @file PMBUSStatus.h
  */

/* 78H STATUS_BYTE */
/*
Bit Number      Status Bit Name                     Meaning
7                  BUSY              A fault was declared because the device was busy and unable to respond.
6                  OFF               This bit is asserted if the unit is not providing power to the output, regardless of the reason, including simply not being enabled.
5               VOUT_OV_FAULT        An output overvoltage fault has occurred
4               IOUT_OC_FAULT        An output overcurrent fault has occurred
3               VIN_UV_FAULT         An input undervoltage fault has occurred
2               TEMPERATURE          A temperature fault or warning has occurred
1                  CML               A communications, memory or logic fault has occurred
0               NONE OF THE ABOVE    A fault or warning not listed in bits [7:1] has occurred
*/
#define STATUS_BYTE_BUSY               (0x80)
#define STATUS_BYTE_OFF                (0x40)
#define STATUS_BYTE_VOUT_OV_FAULT      (0x20)
#define STATUS_BYTE_IOUT_OC_FAULT      (0x10)
#define STATUS_BYTE_VIN_UV_FAULT       (0x08)
#define STATUS_BYTE_TEMPERATURE        (0x04)
#define STATUS_BYTE_CML                (0x02)
#define STATUS_BYTE_NONE_OF_THE_ABOVE  (0x01)
#define STATUS_BYTE_NONE               (0x00)

#define STATUS_BYTE_BUSY_STRING               "BUSY"
#define STATUS_BYTE_OFF_STRING                "OFF"
#define STATUS_BYTE_VOUT_OV_FAULT_STRING      "VOUT_OV_FAULT"
#define STATUS_BYTE_IOUT_OC_FAULT_STRING      "IOUT_OC_FAULT"
#define STATUS_BYTE_VIN_UV_FAULT_STRING       "VIN_UV_FAULT"
#define STATUS_BYTE_TEMPERATURE_STRING        "TEMPERATURE"
#define STATUS_BYTE_CML_STRING                "CML"
#define STATUS_BYTE_NONE_OF_THE_ABOVE_STRING  "NONE_OF_THE_ABOVE"
#define STATUS_BYTE_NONE_STRING               " "

/* 79H STATUS_WORD */
/*
High Byte, Low Byte is the same as 0x78H
Bit Number      Status Bit Name                     Meaning
7               VOUT                 An output voltage fault or warning has occurred
6               IOUT/POUT            An output current or output power fault or warning has occurred
5               INPUT                An input voltage, input current, or input power fault or warning has occurred
4               MFR_SPECIFIC         A manufacturer specific fault or warning has occurred
3               POWER_GOOD#          The POWER_GOOD signal, if present, is negated
2               FANS                 A fan or airflow fault or warning has occurred
1               OTHER                A bit in STATUS_OTHER is set
0               UNKNOWN              A fault type not given in bits [15:1] of of the SATUS_WORD has been detected
*/
#define STATUS_WORD_HIGH_VOUT              (0x8000)
#define STATUS_WORD_HIGH_IOUTPOUT          (0x4000)
#define STATUS_WORD_HIGH_INPUT             (0x2000)
#define STATUS_WORD_HIGH_MFR_SPECIFIC      (0x1000)
#define STATUS_WORD_HIGH_POWERGOOD         (0x0800)
#define STATUS_WORD_HIGH_FANS              (0x0400)
#define STATUS_WORD_HIGH_OTHER             (0x0200)
#define STATUS_WORD_HIGH_UNKNOWN           (0x0100)
#define STATUS_WORD_HIGH_NONE              (0x0000)

#define STATUS_WORD_LOW_BUSY               (0x0080)
#define STATUS_WORD_LOW_OFF                (0x0040)
#define STATUS_WORD_LOW_VOUT_OV_FAULT      (0x0020)
#define STATUS_WORD_LOW_IOUT_OC_FAULT      (0x0010)
#define STATUS_WORD_LOW_VIN_UV_FAULT       (0x0008)
#define STATUS_WORD_LOW_TEMPERATURE        (0x0004)
#define STATUS_WORD_LOW_CML                (0x0002)
#define STATUS_WORD_LOW_NONE_OF_THE_ABOVE  (0x0001)
#define STATUS_WORD_LOW_NONE               (0x0000)


#define STATUS_WORD_HIGH_VOUT_STRING              "VOUT"
#define STATUS_WORD_HIGH_IOUTPOUT_STRING          "IOUT/POUT"
#define STATUS_WORD_HIGH_INPUT_STRING             "INPUT"
#define STATUS_WORD_HIGH_MFR_SPECIFIC_STRING      "MFR_SPECIFIC"
#define STATUS_WORD_HIGH_POWERGOOD_STRING         "POWERGOOD"
#define STATUS_WORD_HIGH_FANS_STRING              "FANS"
#define STATUS_WORD_HIGH_OTHER_STRING             "OTHER"
#define STATUS_WORD_HIGH_UNKNOWN_STRING           "UNKNOWN"
#define STATUS_WORD_HIGH_NONE_STRING              " "

#define STATUS_BYTE_BUSY_LOW_STRING               "BUSY"
#define STATUS_BYTE_OF_LOWF_STRING                "OFF"
#define STATUS_BYTE_VOUT_OV_FAULT_LOW_STRING      "VOUT_OV_FAULT"
#define STATUS_BYTE_IOUT_OC_FAULT_LOW_STRING      "IOUT_OC_FAULT"
#define STATUS_BYTE_VIN_UV_FAULT_LOW_STRING       "VIN_UV_FAULT"
#define STATUS_BYTE_TEMPERATURE_LOW_STRING        "TEMPERATURE"
#define STATUS_BYTE_CML__LOWSTRING                "CML"
#define STATUS_BYTE_NONE_OF_THE_ABOVE_LOW_STRING  "NONE_OF_THE_ABOVE"
#define STATUS_BYTE_NONE_LOW_STRING               " "

/* 80H STATUS_VOUT */
/*
Bit      Meaning
7     VOUT_OV_FAULT (Output Overvoltage Fault)
6     VOUT_OV_WARNING (Output Overvoltage Warning)
5     VOUT_UV_WARNING (Output Undervoltage Warning)
4     VOUT_UV_FAULT (Output Undervoltage Fault)
3     VOUT_MAX Warning (An attempt has been made to set the output voltage to value higher than allowed by the VOUT_MAX command(Section 13.5).
2     TON_MAX_FAULT
1     TOFF_MAX_WARNING
0     VOUT Tracking Error
*/
#define STATUS_VOUT_VOUT_OV_FAULT        (0x80)
#define STATUS_VOUT_VOUT_OV_WARNING      (0x40)
#define STATUS_VOUT_VOUT_UV_WARNING      (0x20)
#define STATUS_VOUT_VOUT_UV_FAULT        (0x10)
#define STATUS_VOUT_VOUT_MAX             (0x08)
#define STATUS_VOUT_TON_MAX_FAULT        (0x04)
#define STATUS_VOUT_TOFF_MAX_WARNING     (0x02)
#define STATUS_VOUT_VOUT_Tracking_Error  (0x01)
#define STATUS_VOUT_NONE                 (0x00)

#define STATUS_VOUT_VOUT_OV_FAULT_STRING        "VOUT_OV_FAULT"
#define STATUS_VOUT_VOUT_OV_WARNING_STRING      "VOUT_OV_WARNING"
#define STATUS_VOUT_VOUT_UV_WARNING_STRING      "VOUT_UV_WARNING"
#define STATUS_VOUT_VOUT_UV_FAULT_STRING        "VOUT_UV_FAULT"
#define STATUS_VOUT_VOUT_MAX_STRING             "VOUT_MAX"
#define STATUS_VOUT_TON_MAX_FAULT_STRING        "TON_MAX_FAULT"
#define STATUS_VOUT_TOFF_MAX_WARNING_STRING     "TOFF_MAX_WARNING"
#define STATUS_VOUT_VOUT_Tracking_Error_STRING  "VOUT Tracking Error"
#define STATUS_VOUT_NONE_STRING                 " "

/* 81H STATUS_IOUT */
/*
Bit     Meaning
7    IOUT_OC_FAULT (Output Overcurrent Fault)
6    IOUT_OC_LV_FAULT (Output Overcurrent And Low Voltage Fault)
5    IOUT_OC_WARNING (Output Overcurrent Warning)
4    IOUT_UC_FAULT (Output Undercurrent Fault)
3    Current Share Fault
2    In Power Limiting Mode
1    POUT_OP_FAULT (Output Overpower Fault)
0    POUT_OP_WARNING (Output Overpower Warning)
*/
#define STATUS_IOUT_IOUT_OC_FAULT           (0x80)
#define STATUS_IOUT_IOUT_OC_LV_FAULT        (0x40)
#define STATUS_IOUT_IOUT_OC_WARNING         (0x20)
#define STATUS_IOUT_IOUT_UC_FAULT           (0x10)
#define STATUS_IOUT_Current_Share_Fault     (0x08)
#define STATUS_IOUT_In_Power_Limiting_Mode  (0x04)
#define STATUS_IOUT_POUT_OP_FAULT           (0x02)
#define STATUS_IOUT_POUT_OP_WARNING         (0x01)
#define STATUS_IOUT_NONE                    (0x00)

#define STATUS_IOUT_IOUT_OC_FAULT_STRING           "IOUT_OC_FAULT"
#define STATUS_IOUT_IOUT_OC_LV_FAULT_STRING        "IOUT_OC_LV_FAULT"
#define STATUS_IOUT_IOUT_OC_WARNING_STRING         "IOUT_OC_WARNING"
#define STATUS_IOUT_IOUT_UC_FAULT_STRING           "IOUT_UC_FAULT"
#define STATUS_IOUT_Current_Share_Fault_STRING     "Current Share Fault"
#define STATUS_IOUT_In_Power_Limiting_Mode_STRING  "In Power Limiting Mode"
#define STATUS_IOUT_POUT_OP_FAULT_STRING           "POUT_OP_FAULT"
#define STATUS_IOUT_POUT_OP_WARNING_STRING         "POUT_OP_WARNING"
#define STATUS_IOUT_NONE_STRING                    " "

/* 82H STATUS_INPUT */
/*
Bit      Meaning
7     VIN_OV_FAULT (Input Overvoltage Fault)
6     VIN_OV_WARNING (Input Overvoltage Warning)
5     VIN_UV_WARNING (Input Undervoltage Warning)
4     VIN_UV_FAULT (Input Undervoltage Fault)
3     Unit Off For Insufficient Input Voltage [1]
2     IIN_OC_FAULT (Input Overcurrent Fault)
1     IIN_OC_WARNING (Input Overcurrent Warning)
0     PIN_OP_WARNING (Input Overpower Warning)
*/
#define STATUS_INPUT_VIN_OV_FAULT                                (0x80)
#define STATUS_INPUT_VIN_OV_WARNING                              (0x40)
#define STATUS_INPUT_VIN_UV_WARNING                              (0x20)
#define STATUS_INPUT_VIN_UV_FAULT                                (0x10)
#define STATUS_INPUT_Unit_Off_For_Insufficient_Input_Voltage     (0x08)
#define STATUS_INPUT_IIN_OC_FAULT                                (0x04)
#define STATUS_INPUT_IIN_OC_WARNING                              (0x02)
#define STATUS_INPUT_PIN_OP_WARNING                              (0x01)
#define STATUS_INPUT_NONE                                        (0x00)

#define STATUS_INPUT_VIN_OV_FAULT_STRING                             "VIN_OV_FAULT"
#define STATUS_INPUT_VIN_OV_WARNING_STRING                           "VIN_OV_WARNING"
#define STATUS_INPUT_VIN_UV_WARNING_STRING                           "VIN_UV_WARNING"
#define STATUS_INPUT_VIN_UV_FAULT_STRING                             "VIN_UV_FAULT"
#define STATUS_INPUT_Unit_Off_For_Insufficient_Input_Voltage_STRING  "Unit Off For Insufficient Input Voltage"
#define STATUS_INPUT_IIN_OC_FAULT_STRING                             "IIN_OC_FAULT"
#define STATUS_INPUT_IIN_OC_WARNING_STRING                           "IIN_OC_WARNING"
#define STATUS_INPUT_PIN_OP_WARNING_STRING                           "PIN_OP_WARNING"
#define STATUS_INPUT_NONE_STRING                                     " "

/* 83H STATUS_TEMPERATURE */
/*
Bit      Meaning
7     OT_FAULT (Overtemperature Fault)
6     OT_WARNING (Overtemperature Warning)
5     UT_WARNING (Undertemperature Warning)
4     UT_FAULT (Undertemperature Fault)
3     Reserved
2     Reserved
1     Reserved
0     Reserved
*/
#define STATUS_TEMPERATURE_OT_FAULT    (0x80)
#define STATUS_TEMPERATURE_OT_WARNING  (0x40)
#define STATUS_TEMPERATURE_UT_WARNING  (0x20)
#define STATUS_TEMPERATURE_UT_FAULT    (0x10)
#define STATUS_TEMPERATURE_Reserved_3  (0x08)
#define STATUS_TEMPERATURE_Reserved_2  (0x04)
#define STATUS_TEMPERATURE_Reserved_1  (0x02)
#define STATUS_TEMPERATURE_Reserved_0  (0x01)
#define STATUS_TEMPERATURE_NONE        (0x00)

#define STATUS_TEMPERATURE_OT_FAULT_STRING    "OT_FAULT"
#define STATUS_TEMPERATURE_OT_WARNING_STRING  "OT_WARNING"
#define STATUS_TEMPERATURE_UT_WARNING_STRING  "UT_WARNING"
#define STATUS_TEMPERATURE_UT_FAULT_STRING    "UT_FAULT"
#define STATUS_TEMPERATURE_Reserved_3_STRING  "Reserved 3"
#define STATUS_TEMPERATURE_Reserved_2_STRING  "Reserved 2"
#define STATUS_TEMPERATURE_Reserved_1_STRING  "Reserved 1"
#define STATUS_TEMPERATURE_Reserved_0_STRING  "Reserved 0"
#define STATUS_TEMPERATURE_NONE_STRING        " "

/* 84H STATUS_CML */
/*
Bit     Meaning
7    Invalid Or Unsupported Command Received
6    Invalid Or Unsupported Data Received
5    Packet Error Check Failed
4    Memory Fault Detected [1]
3    Processor Fault Detected [2]
2    Reserved
1    A communication fault other than the ones listed in this table has occurred
0    Other Memory Or Logic Fault has occurred. [3]
*/
#define STATUS_CML_Invalid_Or_Unsupported_Command_Received  (0x80)
#define STATUS_CML_Invalid_Or_Unsupported_Data_Received     (0x40)
#define STATUS_CML_Packet_Error_Check_Failed                (0x20)
#define STATUS_CML_Memory_Fault_Detected                    (0x10)
#define STATUS_CML_Processor_Fault_Detected                 (0x08)
#define STATUS_CML_Reserved                                 (0x04)
#define STATUS_CML_A_communication_fault                    (0x02)
#define STATUS_CML_Other_Memory_Or_Logic_Fault              (0x01)
#define STATUS_CML_NONE                                     (0x00)

#define STATUS_CML_Invalid_Or_Unsupported_Command_Received_STRING  "Invalid Or Unsupported Command Received"
#define STATUS_CML_Invalid_Or_Unsupported_Data_Received_STRING     "Invalid Or Unsupported Data Received"
#define STATUS_CML_Packet_Error_Check_Failed_STRING                "Packet Error Check Failed"
#define STATUS_CML_Memory_Fault_Detected_STRING                    "Memory Fault Detected"
#define STATUS_CML_Processor_Fault_Detected_STRING                 "Processor Fault Detected"
#define STATUS_CML_Reserved_STRING                                 "Reserved"
#define STATUS_CML_A_communication_fault_STRING                    "A communication fault other than the ones listed in this table has occurred"
#define STATUS_CML_Other_Memory_Or_Logic_Fault_STRING              "Other Memory Or Logic Fault"
#define STATUS_CML_NONE_STRING                                     " "

/* 85H STATUS_OTHER */
/*
Bit      Meaning
7     Reserved (Replaced by STATUS_FANS)
6     Reserved (Replaced By STATUS_FANS)
5     Input A Fuse Or Circuit Breaker Fault [1]
4     Input B Fuse Or Circuit Breaker Fault [1]
3     Input A OR-ing Device Fault [2]
2     Input B OR-ing Device Fault [2]
1     Output OR-ing Device Fault [3]
0     Reserved
*/
#define STATUS_OTHER_Reserved_2                             (0x80)
#define STATUS_OTHER_Reserved_1                             (0x40)
#define STATUS_OTHER_Input_A_Fuse_Or_Circuit_Breaker_Fault  (0x20)
#define STATUS_OTHER_Input_B_Fuse_Or_Circuit_Breaker_Fault  (0x10)
#define STATUS_OTHER_Input_A_ORing_Device_Fault             (0x08)
#define STATUS_OTHER_Input_B_ORing_Device_Fault             (0x04)
#define STATUS_OTHER_Output_ORing_Device_Fault              (0x02)
#define STATUS_OTHER_Reserved_0                             (0x01)
#define STATUS_OTHER_NONE                                   (0x00)

#define STATUS_OTHER_Reserved_2_STRING                             "Reserved 2"
#define STATUS_OTHER_Reserved_1_STRING                             "Reserved 1"
#define STATUS_OTHER_Input_A_Fuse_Or_Circuit_Breaker_Fault_STRING  "Input A Fuse Or Circuit Breaker Fault"
#define STATUS_OTHER_Input_B_Fuse_Or_Circuit_Breaker_Fault_STRING  "Input B Fuse Or Circuit Breaker Fault"
#define STATUS_OTHER_Input_A_ORing_Device_Fault_STRING             "Input A OR-ing Device Fault"
#define STATUS_OTHER_Input_B_ORing_Device_Fault_STRING             "Input B OR-ing Device Fault"
#define STATUS_OTHER_Output_ORing_Device_Fault_STRING              "Output OR-ing Device Faul"
#define STATUS_OTHER_Reserved_0_STRING                             "Reserved 0"
#define STATUS_OTHER_NONE_STRING                                   " "

/* 86H STATUS_FAN_1_2 */
/*
Bit      Meaning
7     Fan 1 Fault [1]
6     Fan 2 Fault [1]
5     Fan 1 Warning [2]
4     Fan 2 Warning [2]
3     Fan 1 Speed Overridden [3]
2     Fan 2 Speed Overridden [3]
1     Airflow Fault [4]
0     Airflow Warning [4]
*/
#define STATUS_FAN_1_2_Fan_1_Fault                (0x80)
#define STATUS_FAN_1_2_Fan_2_Fault                (0x40)
#define STATUS_FAN_1_2_Fan_1_Warning              (0x20)
#define STATUS_FAN_1_2_Fan_2_Warning              (0x10)
#define STATUS_FAN_1_2_Fan_1_Speed_Overridden     (0x08)
#define STATUS_FAN_1_2_Fan_2_Speed_Overridden     (0x04)
#define STATUS_FAN_1_2_Airflow_Fault              (0x02)
#define STATUS_FAN_1_2_Airflow_Warning            (0x01)
#define STATUS_FAN_1_2_NONE                       (0x00)

#define STATUS_FAN_1_2_Fan_1_Fault_STRING                "Fan 1 Fault"
#define STATUS_FAN_1_2_Fan_2_Fault_STRING                "Fan 2 Fault"
#define STATUS_FAN_1_2_Fan_1_Warning_STRING              "Fan 1 Warnin"
#define STATUS_FAN_1_2_Fan_2_Warning_STRING              "Fan 2 Warnin"
#define STATUS_FAN_1_2_Fan_1_Speed_Overridden_STRING     "Fan 1 Speed Overridden"
#define STATUS_FAN_1_2_Fan_2_Speed_Overridden_STRING     "Fan 2 Speed Overridden"
#define STATUS_FAN_1_2_Airflow_Fault_STRING              "Airflow Fault"
#define STATUS_FAN_1_2_Airflow_Warning_STRING            "Airflow Warning"
#define STATUS_FAN_1_2_NONE_STRING                       " "


/**
 * @brief STATUS_BYTE.
 */
typedef  struct status_byte_t {

	status_byte_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;


	void Save(unsigned char _status){
		status = _status;
		//status_dch |= _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_byte_t));
	}

}STATUS_BYTE_t;

/**
 * @brief STATUS_WORD.
 */
typedef  struct status_word_t {

	status_word_t(){ this->Clear(); }

	unsigned short status;

	unsigned short status_dch;

	void Save(unsigned short _status){
		status = _status;
		//status_dch |= _status;
	}

	void SaveDCH(unsigned short _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_word_t));
	}
}STATUS_WORD_t;

/**
 * @brief STATUS_VOUT.
 */
typedef  struct status_vout_t {

	status_vout_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;

	void Save(unsigned char _status){
		status = _status;
		//status_dch |= _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_vout_t));
	}
}STATUS_VOUT_t;

/**
 * @brief STATUS_IOUT.
 */
typedef  struct status_iout_t {

	status_iout_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;

	void Save(unsigned char _status){
		status = _status;
		//status_dch |= _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_iout_t));
	}
}STATUS_IOUT_t;

/**
 * @brief STATUS_INPUT.
 */
typedef  struct status_input_t {

	status_input_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;

	void Save(unsigned char _status){
		status = _status;
		//status_dch |= _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_input_t));
	}
}STATUS_INPUT_t;

/**
 * @brief STATUS_TEMPERATURE.
 */
typedef  struct status_temperature_t {

	status_temperature_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;

	void Save(unsigned char _status){
		status = _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_temperature_t));
	}
}STATUS_TEMPERATURE_t;

/**
 * @brief STATUS_CML.
 */
typedef  struct status_cml_t {

	status_cml_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;

	void Save(unsigned char _status){
		status = _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_cml_t));
	}
}STATUS_CML_t;

/**
 * @brief STATUS_OTHER.
 */
typedef  struct status_other_t {

	status_other_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;

	void Save(unsigned char _status){
		status = _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_other_t));
	}
}STATUS_OTHER_t;

/**
 * @brief STATUS_FAN_1_2.
 */
typedef  struct status_fan_1_2_t {

	status_fan_1_2_t(){ this->Clear(); }

	unsigned char status;

	unsigned char status_dch;

	void Save(unsigned char _status){
		status = _status;
	}

	void SaveDCH(unsigned char _status){
		status_dch = _status;
	}

	void Clear(void){
		memset(this, 0, sizeof(status_fan_1_2_t));
	}
}STATUS_FAN_1_2_t;


/**
 * @brief PMBUS STATUS.
 */
typedef struct pmbusStatus_t {

	pmbusStatus_t(){
		memset(this, 0, sizeof(pmbusStatus_t));
	}

	STATUS_BYTE_t m_status_byte;
	STATUS_WORD_t m_status_word;
	STATUS_VOUT_t m_status_vout;
	STATUS_VOUT_t m_status_vout2;
	STATUS_IOUT_t m_status_iout;
	STATUS_IOUT_t m_status_iout2;
	STATUS_INPUT_t m_status_input;
	STATUS_TEMPERATURE_t m_status_temperature;
	STATUS_CML_t m_status_cml;
	STATUS_OTHER_t m_status_other;
	STATUS_FAN_1_2_t m_status_fan_1_2;

	char m_currentPage;
	double m_vout_mode_exponent;

	double m_VIN;
	double m_IIN;
	
	double m_PIN;
	double m_POUT;

	double m_VOUT;
	double m_IOUT;

	double m_VoSBY;
	double m_IoSBY;

	double m_VCAP;
	double m_AMD_8D;

	double m_SEC_8E;
	double m_PRI_8F;

	double m_FAN1;
	double m_FAN2;

	double m_FAN3;
	double m_FAN4;


	double m_VIN_Max;
	double m_VIN_Min;
	char   m_VIN_Set;

	double m_IIN_Max;
	double m_IIN_Min;
	char   m_IIN_Set;

	double m_VCAP_Max;
	double m_VCAP_Min;
	char   m_VCAP_Set;

	double m_AMD_8D_Max;
	double m_AMD_8D_Min;
	char   m_AMD_8D_Set;

	double m_SEC_8E_Max;
	double m_SEC_8E_Min;
	char   m_SEC_8E_Set;

	double m_PRI_8F_Max;
	double m_PRI_8F_Min;
	char   m_PRI_8F_Set;

	double m_FAN1_Max;
	double m_FAN1_Min;
	char   m_FAN1_Set;

	double m_POUT_Max;
	double m_POUT_Min;
	char   m_POUT_Set;

	double m_PIN_Max;
	double m_PIN_Min;
	char   m_PIN_Set;

	double m_VOUT_Max;
	double m_VOUT_Min;
	char   m_VOUT_Set;

	double m_IOUT_Max;
	double m_IOUT_Min;
	char   m_IOUT_Set;

	double m_VoSBY_Max;
	double m_VoSBY_Min;
	char   m_VoSBY_Set;

	double m_IoSBY_Max;
	double m_IoSBY_Min;
	char   m_IoSBY_Set;

	void ResetMaxMin(void){
		this->m_VIN_Max = 0;
		this->m_VIN_Min = 0;
		this->m_VIN_Set = 0;

		this->m_IIN_Max = 0;
		this->m_IIN_Min = 0;
		this->m_IIN_Set = 0;

		this->m_VCAP_Max = 0;
		this->m_VCAP_Min = 0;
		this->m_VCAP_Set = 0;

		this->m_AMD_8D_Max = 0;
		this->m_AMD_8D_Min = 0;
		this->m_AMD_8D_Set = 0;

		this->m_SEC_8E_Max = 0;
		this->m_SEC_8E_Min = 0;
		this->m_SEC_8E_Set = 0;

		this->m_PRI_8F_Max = 0;
		this->m_PRI_8F_Min = 0;
		this->m_PRI_8F_Set = 0;

		this->m_FAN1_Max = 0;
		this->m_FAN1_Min = 0;
		this->m_FAN1_Set = 0;

		this->m_POUT_Max = 0;
		this->m_POUT_Min = 0;
		this->m_POUT_Set = 0;

		this->m_PIN_Max = 0;
		this->m_PIN_Min = 0;
		this->m_PIN_Set = 0;

		this->m_VOUT_Max = 0;
		this->m_VOUT_Min = 0;
		this->m_VOUT_Set = 0;

		this->m_IOUT_Max = 0;
		this->m_IOUT_Min = 0;
		this->m_IOUT_Set = 0;

		this->m_VoSBY_Max = 0;
		this->m_VoSBY_Min = 0;
		this->m_VoSBY_Set = 0;

		this->m_IoSBY_Max = 0;
		this->m_IoSBY_Min = 0;
		this->m_IoSBY_Set = 0;
	}

	void SaveIoSBY(double ioSBY){
		this->m_IoSBY = ioSBY;
		// Maximun
		if (this->m_IoSBY > this->m_IoSBY_Max){
			this->m_IoSBY_Max = this->m_IoSBY;
		}
		// Mininum
		if (this->m_IoSBY < this->m_IoSBY_Min || m_IoSBY_Set == 0){
			this->m_IoSBY_Min = this->m_IoSBY;
			m_IoSBY_Set = 1;
		}
	}

	void SaveVoSBY(double voSBY){
		this->m_VoSBY = voSBY;
		// Maximun
		if (this->m_VoSBY > this->m_VoSBY_Max){
			this->m_VoSBY_Max = this->m_VoSBY;
		}
		// Mininum
		if (this->m_VoSBY < this->m_VoSBY_Min || m_VoSBY_Set == 0){
			this->m_VoSBY_Min = this->m_VoSBY;
			m_VoSBY_Set = 1;
		}
	}

	void SaveIOUT(double iout){
		this->m_IOUT = iout;
		// Maximun
		if (this->m_IOUT > this->m_IOUT_Max){
			this->m_IOUT_Max = this->m_IOUT;
		}
		// Mininum
		if (this->m_IOUT < this->m_IOUT_Min || m_IOUT_Set == 0){
			this->m_IOUT_Min = this->m_IOUT;
			m_IOUT_Set = 1;
		}
	}

	void SaveVOUT(double vout){
		this->m_VOUT = vout;
		// Maximun
		if (this->m_VOUT > this->m_VOUT_Max){
			this->m_VOUT_Max = this->m_VOUT;
		}
		// Mininum
		if (this->m_VOUT < this->m_VOUT_Min || m_VOUT_Set == 0){
			this->m_VOUT_Min = this->m_VOUT;
			m_VOUT_Set = 1;
		}
	}

	void SaveVIN(double vin){
		this->m_VIN = vin;
		// Maximun
		if (this->m_VIN > this->m_VIN_Max){
			this->m_VIN_Max = this->m_VIN;
		}
		// Mininum
		if (this->m_VIN < this->m_VIN_Min || m_VIN_Set == 0){
			this->m_VIN_Min = this->m_VIN;
			m_VIN_Set = 1;
		}
	}

	void SaveIIN(double iin){
		this->m_IIN = iin;
		// Maximun
		if (this->m_IIN > this->m_IIN_Max){
			this->m_IIN_Max = this->m_IIN;
		}
		// Mininum
		if (this->m_IIN < this->m_IIN_Min || m_IIN_Set == 0){
			this->m_IIN_Min = this->m_IIN;
			m_IIN_Set = 1;
		}
	}

	void SaveVCAP(double vcap){
		this->m_VCAP = vcap;
		// Maximun
		if (this->m_VCAP > this->m_VCAP_Max){
			this->m_VCAP_Max = this->m_VCAP;
		}
		// Mininum
		if (this->m_VCAP < this->m_VCAP_Min || m_VCAP_Set == 0){
			this->m_VCAP_Min = this->m_VCAP;
			m_VCAP_Set = 1;
		}
	}

	void SaveAMD_8D(double amd8d){
		this->m_AMD_8D = amd8d;
		// Maximun
		if (this->m_AMD_8D > this->m_AMD_8D_Max){
			this->m_AMD_8D_Max = this->m_AMD_8D;
		}
		// Mininum
		if (this->m_AMD_8D < this->m_AMD_8D_Min || m_AMD_8D_Set == 0){
			this->m_AMD_8D_Min = this->m_AMD_8D;
			m_AMD_8D_Set = 1;
		}
	}

	void SaveSEC_8E(double sec8e){
		this->m_SEC_8E = sec8e;
		// Maximun
		if (this->m_SEC_8E > this->m_SEC_8E_Max){
			this->m_SEC_8E_Max = this->m_SEC_8E;
		}
		// Mininum
		if (this->m_SEC_8E < this->m_SEC_8E_Min || m_SEC_8E_Set == 0){
			this->m_SEC_8E_Min = this->m_SEC_8E;
			m_SEC_8E_Set = 1;
		}
	}

	void SavePRI_8F(double pri8f){
		this->m_PRI_8F = pri8f;
		// Maximun
		if (this->m_PRI_8F > this->m_PRI_8F_Max){
			this->m_PRI_8F_Max = this->m_PRI_8F;
		}
		// Mininum
		if (this->m_PRI_8F < this->m_PRI_8F_Min || m_PRI_8F_Set == 0){
			this->m_PRI_8F_Min = this->m_PRI_8F;
			m_PRI_8F_Set = 1;
		}
	}

	void SaveFAN1(double fan1){
		this->m_FAN1 = fan1;
		// Maximun
		if (this->m_FAN1 > this->m_FAN1_Max){
			this->m_FAN1_Max = this->m_FAN1;
		}
		// Mininum
		if (this->m_FAN1 < this->m_FAN1_Min || m_FAN1_Set == 0){
			this->m_FAN1_Min = this->m_FAN1;
			m_FAN1_Set = 1;
		}
	}

	void SavePOUT(double pout){
		this->m_POUT = pout;
		// Maximun
		if (this->m_POUT > this->m_POUT_Max){
			this->m_POUT_Max = this->m_POUT;
		}
		// Mininum
		if (this->m_POUT < this->m_POUT_Min || m_POUT_Set == 0){
			this->m_POUT_Min = this->m_POUT;
			m_POUT_Set = 1;
		}
	}

	void SavePIN(double pin){
		this->m_PIN = pin;
		// Maximun
		if (this->m_PIN > this->m_PIN_Max){
			this->m_PIN_Max = this->m_PIN;
		}
		// Mininum
		if (this->m_PIN < this->m_PIN_Min || m_PIN_Set == 0){
			this->m_PIN_Min = this->m_PIN;
			m_PIN_Set = 1;
		}
	}


} PMBUSSTATUS_t;