/**
 * @file PMBUSCMD.h
 * @brief Define PMBUS Command.
 */
#ifndef _PMBUSCMD_H_
#define _PMBUSCMD_H_

// 00h PAGE
#define PMBUSCMD_00H_PAGE                       0x00

// 01h OPERATION
#define PMBUSCMD_01H_OPERATION                  0x01

// 02h ON_FF_CONFIG
#define PMBUSCMD_02H_ON_FF_CONFIG               0x02

// 03h CLEAR_FAULTS
#define PMBUSCMD_03H_CLEAR_FAULTS               0x03

// 04h PHASE
#define PMBUSCMD_04H_PHASE                      0x04

// 05h PAGE_PLUS_WRITE
#define PMBUSCMD_05H_PAGE_PLUS_WRITE            0x05

// 06h PAGE_PLUS_READ
#define PMBUSCMD_06H_PAGE_PLUS_READ             0x06

// 07h Reserved
#define PMBUSCMD_07H_Reserved                   0x07

// 08h Reserved
#define PMBUSCMD_08H_Reserved                   0x08

// 09h Reserved
#define PMBUSCMD_09H_Reserved                   0x09

// 0Ah Reserved
#define PMBUSCMD_0AH_Reserved                   0x0a

// 0Bh Reserved
#define PMBUSCMD_0BH_Reserved                   0x0b

// 0Ch Reserved
#define PMBUSCMD_0CH_Reserved                   0x0c

// 0Dh Reserved
#define PMBUSCMD_0DH_Reserved                   0x0d

// 0Eh Reserved
#define PMBUSCMD_0EH_Reserved                   0x0e

// 0Fh Reserved
#define PMBUSCMD_0FH_Reserved                   0x0f

// 10h WRITE_PROTECT
#define PMBUSCMD_10H_WRITE_PROTECT              0x10

// 11h STORE_DEFAULT_ALL
#define PMBUSCMD_11H_STORE_DEFAULT_ALL          0x11

// 12h RESTORE_DEFAULT_ALL
#define PMBUSCMD_12H_RESTORE_DEFAULT_ALL        0x12

// 13h STORE_DEFAULT_CODE
#define PMBUSCMD_13H_STORE_DEFAULT_CODE         0x13

// 14h RESTORE_DEFAULT_CODE
#define PMBUSCMD_14H_RESTORE_DEFAULT_CODE       0x14

// 15h STORE_USER_ALL
#define PMBUSCMD_15H_STORE_USER_ALL             0x15

// 16h RESTORE_USER_ALL
#define PMBUSCMD_16H_RESTORE_USER_ALL           0x16

// 17h STORE_USER_CODE
#define PMBUSCMD_17H_STORE_USER_CODE            0x17

// 18h RESTORE_USER_CODE
#define PMBUSCMD_18H_RESTORE_USER_CODE          0x18

// 19h CAPABILITY
#define PMBUSCMD_19H_CAPABILITY                 0x19

// 1Ah QUERY
#define PMBUSCMD_1AH_QUERY                      0x1a

// 1Bh SMBALERT_MASK
#define PMBUSCMD_1BH_SMBALERT_MASK              0x1b

// 1Ch Reserved
#define PMBUSCMD_1CH_Reserved                   0x1c

// 1Dh Reserved
#define PMBUSCMD_1DH_Reserved                   0x1d

// 1Eh Reserved
#define PMBUSCMD_1EH_Reserved                   0x1e

// 1Fh Reserved
#define PMBUSCMD_1FH_Reserved                   0x1f

// 20h VOUT_MODE
#define PMBUSCMD_20H_VOUT_MODE                  0x20

// 21h VOUT_COMMAND
#define PMBUSCMD_21H_VOUT_COMMAND               0x21

// 22h VOUT_TRIM
#define PMBUSCMD_22H_VOUT_TRIM                  0x22

// 23h VOUT_CAL_OFFSET
#define PMBUSCMD_23H_VOUT_CAL_OFFSET            0x23

// 24h VOUT_MAX
#define PMBUSCMD_24H_VOUT_MAX                   0x24

// 25h VOUT_MARGIN_HIGH
#define PMBUSCMD_25H_VOUT_MARGIN_HIGH           0x25

// 26h VOUT_MARGIN_LOW
#define PMBUSCMD_26H_VOUT_MARGIN_LOW            0x26

// 27h VOUT_TRANSITION_RATE
#define PMBUSCMD_27H_VOUT_TRANSITION_RATE       0x27

// 28h VOUT_DROOP
#define PMBUSCMD_28H_VOUT_DROOP                 0x28

// 29h VOUT_SCALE_LOOP
#define PMBUSCMD_29H_VOUT_SCALE_LOOP            0x29

// 2Ah VOUT_SCALE_MONITOR
#define PMBUSCMD_2AH_VOUT_SCALE_MONITOR         0x2a

// 2Bh Reserved
#define PMBUSCMD_2BH_Reserved                   0x2b

// 2Ch Reserved
#define PMBUSCMD_2CH_Reserved                   0x2c

// 2Dh Reserved
#define PMBUSCMD_2DH_Reserved                   0x2d

// 2Eh Reserved
#define PMBUSCMD_2EH_Reserved                   0x2e

// 2Fh Reserved
#define PMBUSCMD_2FH_Reserved                   0x2f

// 30h COEFFICIENTS
#define PMBUSCMD_30H_COEFFICIENTS               0x30

// 31h POUT_MAX                                
#define PMBUSCMD_31H_POUT_MAX                   0x31

// 32h MAX_DUTY
#define PMBUSCMD_32H_MAX_DUTY                   0x32

// 33h FREQUENCY_SWITCH
#define PMBUSCMD_33H_FREQUENCY_SWITCH           0x33

// 34h Reserved
#define PMBUSCMD_34H_Reserved                   0x34

// 35h VIN_ON
#define PMBUSCMD_35H_VIN_ON                     0x35

// 36h VIN_OFF
#define PMBUSCMD_36H_VIN_OFF                    0x36

// 37h INTERLEAVE
#define PMBUSCMD_37H_INTERLEAVE                 0x37

// 38h IOUT_CAL_GAIN
#define PMBUSCMD_38H_IOUT_CAL_GAIN              0x38

// 39h IOUT_CAL_OFFSET
#define PMBUSCMD_39H_IOUT_CAL_OFFSET            0x39

// 3Ah FAN_CONFIG_1_2
#define PMBUSCMD_3AH_FAN_CONFIG_1_2             0x3a

// 3Bh FAN_COMMAND_1
#define PMBUSCMD_3BH_FAN_COMMAND_1              0x3b

// 3Ch FAN_COMMAND_2
#define PMBUSCMD_3CH_FAN_COMMAND_2              0x3c

// 3Dh FAN_CONFIG_3_4
#define PMBUSCMD_3DH_FAN_CONFIG_3_4             0x3d

// 3Eh FAN_COMMAND_3
#define PMBUSCMD_3EH_FAN_COMMAND_3              0x3e

// 3Fh FAN_COMMAND_4
#define PMBUSCMD_3FH_FAN_COMMAND_4              0x3f

// 40h VOUT_OV_FAULT_LIMIT
#define PMBUSCMD_40H_VOUT_OV_FAULT_LIMIT        0x40

// 41h VOUT_OV_FAULT_RESPONSE
#define PMBUSCMD_41H_VOUT_OV_FAULT_RESPONSE     0x41

// 42h VOUT_OV_WARN_LIMIT
#define PMBUSCMD_42H_VOUT_OV_WARN_LIMIT         0x42

// 43h VOUT_UV_WARN_LIMIT
#define PMBUSCMD_43H_VOUT_UV_WARN_LIMIT         0x43

// 44h VOUT_UV_FAULT_LIMIT
#define PMBUSCMD_44H_VOUT_UV_FAULT_LIMIT        0x44

// 45h VOUT_UV_FAULT_RESPONSE
#define PMBUSCMD_45H_VOUT_UV_FAULT_RESPONSE     0x45

// 46h IOUT_OC_FAULT_LIMIT
#define PMBUSCMD_46H_IOUT_OC_FAULT_LIMIT        0x46

// 47h IOUT_OC_FAULT_RESPONSE
#define PMBUSCMD_47H_IOUT_OC_FAULT_RESPONSE     0x47

// 48h IOUT_OC_LV_FAULT_LIMIT
#define PMBUSCMD_48H_IOUT_OC_LV_FAULT_LIMIT     0x48

// 49h IOUT_OC_LV_FAULT_RESPONSE
#define PMBUSCMD_49H_IOUT_OC_LV_FAULT_RESPONSE  0x49

// 4Ah IOUT_OC_WARN_LIMIT
#define PMBUSCMD_4AH_IOUT_OC_WARN_LIMIT         0x4a

// 4Bh IOUT_UC_FAULT_LIMIT
#define PMBUSCMD_4BH_IOUT_UC_FAULT_LIMIT        0x4b

// 4Ch IOUT_UC_FAULT_RESPONSE
#define PMBUSCMD_4CH_IOUT_UC_FAULT_RESPONSE     0x4c

// 4Dh Reserved
#define PMBUSCMD_4DH_Reserved                   0x4d

// 4Eh Reserved
#define PMBUSCMD_4EH_Reserved                   0x4e

// 4Fh OT_FAULT_LIMIT
#define PMBUSCMD_4FH_Reserved                   0x4f

// 50h OT_FAULT_RESPONSE
#define PMBUSCMD_50H_OT_FAULT_RESPONSE          0x50

// 51h OT_WARN_LIMIT
#define PMBUSCMD_51H_OT_WARN_LIMIT              0x51

// 52h UT_WARN_LIMIT
#define PMBUSCMD_52H_UT_WARN_LIMIT              0x52

// 53h UT_FAULT_LIMIT
#define PMBUSCMD_53H_UT_FAULT_LIMIT             0x53

// 54h UT_FAULT_RESPONSE
#define PMBUSCMD_54H_UT_FAULT_RESPONSE          0x54

// 55h VIN_OV_FAULT_LIMIT
#define PMBUSCMD_55H_VIN_OV_FAULT_LIMIT         0x55

// 56h VIN_OV_FAULT_RESPONSE
#define PMBUSCMD_56H_VIN_OV_FAULT_RESPONSE      0x56

// 57h VIN_OV_WARN_LIMIT
#define PMBUSCMD_57H_VIN_OV_WARN_LIMIT          0x57

// 58h VIN_UV_WARN_LIMIT
#define PMBUSCMD_58H_VIN_UV_WARN_LIMIT          0x58

// 59h VIN_UV_FAULT_LIMIT
#define PMBUSCMD_59H_VIN_UV_FAULT_LIMIT         0x59

// 5Ah VIN_UV_FAULT_RESPONSE
#define PMBUSCMD_5AH_VIN_UV_FAULT_RESPONSE      0x5a

// 5Bh IIN_OC_FAULT_LIMIT
#define PMBUSCMD_5BH_IIN_OC_FAULT_LIMIT         0x5b

// 5Ch IIN_OC_FAULT_RESPONSE
#define PMBUSCMD_5CH_IIN_OC_FAULT_RESPONSE      0x5c

// 5Dh IIN_OC_WARN_LIMIT
#define PMBUSCMD_5DH_IIN_OC_WARN_LIMIT          0x5d

// 5Eh POWER_GOOD_ON
#define PMBUSCMD_5EH_POWER_GOOD_ON              0x5e

// 5Fh POWER_GOOD_OFF
#define PMBUSCMD_5FH_POWER_GOOD_OFF             0x5f

// 60h TON_DELAY
#define PMBUSCMD_60H_TON_DELAY                  0x60

// 61h TON_RISE 
#define PMBUSCMD_61H_TON_RISE                   0x61

// 62h TON_MAX_FAULT_LIMIT
#define PMBUSCMD_62H_TON_MAX_FAULT_LIMIT        0x62

// 63h TON_MAX_FAULT_RESPONSE
#define PMBUSCMD_63H_TON_MAX_FAULT_RESPONSE     0x63

// 64h TOFF_DELAY
#define PMBUSCMD_64H_TOFF_DELAY                 0x64

// 65h TOFF_FALL
#define PMBUSCMD_65H_TOFF_FALL                  0x65

// 66h TOFF_MAX_WARN_LIMIT
#define PMBUSCMD_66H_TOFF_MAX_WARN_LIMIT        0x66

// 67h Reserved
#define PMBUSCMD_67H_Reserved                   0x67

// 68h POUT_OP_FAULT_LIMIT
#define PMBUSCMD_68H_POUT_OP_FAULT_LIMIT        0x68

// 69h POUT_OP_FAULT_RESPONSE
#define PMBUSCMD_69H_POUT_OP_FAULT_RESPONSE     0x69

// 6Ah POUT_OP_WARN_LIMIT
#define PMBUSCMD_6AH_POUT_OP_WARN_LIMIT         0x6a

// 6Bh PIN_OP_WARN_LIMIT
#define PMBUSCMD_6BH_PIN_OP_WARN_LIMIT          0x6b

// 6Ch Reserved
#define PMBUSCMD_6CH_Reserved                   0x6c

// 6Dh Reserved
#define PMBUSCMD_6DH_Reserved                   0x6d

// 6Eh Reserved
#define PMBUSCMD_6EH_Reserved                   0x6e

// 6Fh Reserved
#define PMBUSCMD_6FH_Reserved                   0x6f

// 70h Reserved
#define PMBUSCMD_70H_Reserved                   0x70

// 71h Reserved
#define PMBUSCMD_71H_Reserved                   0x71

// 72h Reserved
#define PMBUSCMD_72H_Reserved                   0x72

// 73h Reserved
#define PMBUSCMD_73H_Reserved                   0x73

// 74h Reserved
#define PMBUSCMD_74H_Reserved                   0x74

// 75h Reserved
#define PMBUSCMD_75H_Reserved                   0x75

// 76h Reserved
#define PMBUSCMD_76H_Reserved                   0x76

// 77h Reserved
#define PMBUSCMD_77H_Reserved                   0x77

// 78h STATUS_BYTE
#define PMBUSCMD_78H_STATUS_BYTE                0x78

// 79h STATUS_WORD
#define PMBUSCMD_79H_STATUS_WORD                0x79

// 7Ah STATUS_VOUT
#define PMBUSCMD_7AH_STATUS_VOUT                0x7a

// 7Bh STATUS_IOUT
#define PMBUSCMD_7BH_STATUS_IOUT                0x7b

// 7Ch STATUS_INPUT
#define PMBUSCMD_7CH_STATUS_INPUT               0x7c

// 7Dh STATUS_TEMPERATURE
#define PMBUSCMD_7DH_STATUS_TEMPERATURE         0x7d

// 7Eh STATUS_CML
#define PMBUSCMD_7EH_STATUS_CML                 0x7e

// 7Fh STATUS_OTHER
#define PMBUSCMD_7FH_STATUS_OTHER               0x7f

// 80h STATUS_MFR_SPECIFIC
#define PMBUSCMD_80H_STATUS_MFR_SPECIFIC        0x80

// 81h STATUS_FANS_1_2
#define PMBUSCMD_81H_STATUS_FANS_1_2            0x81

// 82h STATUS_FANS_3_4
#define PMBUSCMD_82H_STATUS_FANS_3_4            0x82

// 83h Reserved
#define PMBUSCMD_83H_Reserved                   0x83

// 84h Reserved
#define PMBUSCMD_84H_Reserved                   0x84

// 85h Reserved
#define PMBUSCMD_85H_Reserved                   0x85

// 86h READ_EIN
#define PMBUSCMD_86H_READ_EIN                   0x86

// 87h READ_EOUT
#define PMBUSCMD_87H_READ_EOUT                  0x87

// 88h READ_VIN
#define PMBUSCMD_88H_READ_VIN                   0x88

// 89h READ_IIN
#define PMBUSCMD_89H_READ_IIN                   0x89

// 8Ah READ_VCAP
#define PMBUSCMD_8AH_READ_VCAP                  0x8a

// 8Bh READ_VOUT
#define PMBUSCMD_8BH_READ_VOUT                  0x8b

// 8Ch READ_IOUT
#define PMBUSCMD_8CH_READ_IOUT                  0x8c

// 8Dh READ_TEMPERATURE_1
#define PMBUSCMD_8DH_READ_TEMPERATURE_1         0x8d

// 8Eh READ_TEMPERATURE_2
#define PMBUSCMD_8EH_READ_TEMPERATURE_2         0x8e

// 8Fh READ_TEMPERATURE_3
#define PMBUSCMD_8FH_READ_TEMPERATURE_3         0x8f

// 90h READ_FAN_SPEED_1
#define PMBUSCMD_90H_READ_FAN_SPEED_1           0x90

// 91h READ_FAN_SPEED_2
#define PMBUSCMD_91H_READ_FAN_SPEED_2           0x91

// 92h READ_FAN_SPEED_3
#define PMBUSCMD_92H_READ_FAN_SPEED_3           0x92

// 93h READ_FAN_SPEED_4
#define PMBUSCMD_93H_READ_FAN_SPEED_4           0x93

// 94h READ_DUTY_CYCLE
#define PMBUSCMD_94H_READ_DUTY_CYCLE            0x94

// 95h READ_FREQUENCY
#define PMBUSCMD_95H_READ_FREQUENCY             0x95

// 96h READ_POUT
#define PMBUSCMD_96H_READ_POUT                  0x96

// 97h READ_PIN
#define PMBUSCMD_97H_READ_PIN                   0x97

// 98h PMBUS_REVISION
#define PMBUSCMD_98H_PMBUS_REVISION             0x98

// 99h MFR_ID
#define PMBUSCMD_99H_MFR_ID                     0x99

// 9Ah MFR_MODEL
#define PMBUSCMD_9AH_MFR_MODEL                  0x9a

// 9Bh MFR_REVISION        
#define PMBUSCMD_9BH_MFR_REVISION               0x9b

// 9Ch MFR_LOCATION
#define PMBUSCMD_9CH_MFR_LOCATION               0x9c

// 9Dh MFR_DATE
#define PMBUSCMD_9DH_MFR_DATE                   0x9d

// 9Eh MFR_SERIAL
#define PMBUSCMD_9EH_MFR_SERIAL                 0x9e

// 9Fh APP_PROFILE_SUPPORT
#define PMBUSCMD_9FH_APP_PROFILE_SUPPORT        0x9f

// A0h MFR_VIN_MIN
#define PMBUSCMD_A0H_MFR_VIN_MIN                0xa0

// A1h MFR_VIN_MAX
#define PMBUSCMD_A1H_MFR_VIN_MAX                0xa1

// A2h MFR_IIN_MAX
#define PMBUSCMD_A2H_MFR_IIN_MAX                0xa2

// A3h MFR_PIN_MAX
#define PMBUSCMD_A3H_MFR_PIN_MAX                0xa3

// A4h MFR_VOUT_MIN
#define PMBUSCMD_A4H_MFR_VOUT_MIN               0xa4

// A5h MFR_VOUT_MAX
#define PMBUSCMD_A5H_MFR_VOUT_MAX               0xa5

// A6h MFR_IOUT_MAX
#define PMBUSCMD_A6H_MFR_IOUT_MAX               0xa6

// A7h MFR_POUT_MAX
#define PMBUSCMD_A7H_MFR_POUT_MAX               0xa7

// A8h MFR_TAMBIENT_MAX
#define PMBUSCMD_A8H_MFR_TAMBIENT_MAX           0xa8

// A9h MFR_TAMBIENT_MIN
#define PMBUSCMD_A9H_MFR_TAMBIENT_MIN           0xa9

// AAh MFR_EFFICIENCY_LL
#define PMBUSCMD_AAH_MFR_EFFICIENCY_LL          0xaa

// ABh MFR_EFFICIENCY_HL
#define PMBUSCMD_ABH_MFR_EFFICIENCY_HL          0xab

// ACh MFR_PIN_ACCURACY
#define PMBUSCMD_ACH_MFR_PIN_ACCURACY           0xac

// ADh IC_DEVICE_ID
#define PMBUSCMD_ADH_IC_DEVICE_ID               0xad

// AEh IC_DEVICE_REV
#define PMBUSCMD_AEH_IC_DEVICE_REV              0xae

// AFh Reserved
#define PMBUSCMD_AFH_Reserved                   0xaf

// B0h USER_DATA_00
#define PMBUSCMD_B0H_USER_DATA_00               0xb0

// B1h USER_DATA_01
#define PMBUSCMD_B1H_USER_DATA_01               0xb1

// B2h USER_DATA_02
#define PMBUSCMD_B2H_USER_DATA_02               0xb2

// B3h USER_DATA_03
#define PMBUSCMD_B3H_USER_DATA_03               0xb3

// B4h USER_DATA_04
#define PMBUSCMD_B4H_USER_DATA_04               0xb4

// B5h USER_DATA_05
#define PMBUSCMD_B5H_USER_DATA_05               0xb5

// B6h USER_DATA_06
#define PMBUSCMD_B6H_USER_DATA_06               0xb6

// B7h USER_DATA_07
#define PMBUSCMD_B7H_USER_DATA_07               0xb7

// B8h USER_DATA_08
#define PMBUSCMD_B8H_USER_DATA_08               0xb8

// B9h USER_DATA_09
#define PMBUSCMD_B9H_USER_DATA_09               0xb9

// BAh USER_DATA_10
#define PMBUSCMD_BAH_USER_DATA_10               0xba

// BBh USER_DATA_11
#define PMBUSCMD_BBH_USER_DATA_11               0xbb

// BCh USER_DATA_12
#define PMBUSCMD_BCH_USER_DATA_12               0xbc

// BDh USER_DATA_13
#define PMBUSCMD_BDH_USER_DATA_13               0xbd

// BEh USER_DATA_14
#define PMBUSCMD_BEH_USER_DATA_14               0xbe

// BFh USER_DATA_15
#define PMBUSCMD_BFH_USER_DATA_15               0xbf

// C0h MFR_MAX_TEMP_1
#define PMBUSCMD_C0H_MFR_MAX_TEMP_1             0xc0

// C1h MFR_MAX_TEMP_2
#define PMBUSCMD_C1H_MFR_MAX_TEMP_2             0xc1

// C2h MFR_MAX_TEMP_3
#define PMBUSCMD_C2H_MFR_MAX_TEMP_3             0xc2

// C3h Reserved
#define PMBUSCMD_C3H_Reserved                   0xc3

// C4h Reserved
#define PMBUSCMD_C4H_Reserved                   0xc4

// C5h Reserved
#define PMBUSCMD_C5H_Reserved                   0xc5

// C6h Reserved
#define PMBUSCMD_C6H_Reserved                   0xc6

// C7h Reserved
#define PMBUSCMD_C7H_Reserved                   0xc7

// C8h Reserved
#define PMBUSCMD_C8H_Reserved                   0xc8

// C9h Reserved
#define PMBUSCMD_C9H_Reserved                   0xc9

// CAh Reserved
#define PMBUSCMD_CAH_Reserved                   0xca

// CBh Reserved
#define PMBUSCMD_CBH_Reserved                   0xcb

// CCh Reserved
#define PMBUSCMD_CCH_Reserved                   0xcc

// CDh Reserved
#define PMBUSCMD_CDH_Reserved                   0xcd

// CEh Reserved
#define PMBUSCMD_CEH_Reserved                   0xce

// CFh Reserved 
#define PMBUSCMD_CFH_Reserved                   0xcf

// D0h MFR_SPECIFIC_00
#define PMBUSCMD_D0H_MFR_SPECIFIC_00            0xd0

// D1h MFR_SPECIFIC_01
#define PMBUSCMD_D1H_MFR_SPECIFIC_01            0xd1

// D2h MFR_SPECIFIC_02
#define PMBUSCMD_D2H_MFR_SPECIFIC_02            0xd2

// D3h MFR_SPECIFIC_03
#define PMBUSCMD_D3H_MFR_SPECIFIC_03            0xd3

// D4h MFR_SPECIFIC_04
#define PMBUSCMD_D4H_MFR_SPECIFIC_04            0xd4

// D5h MFR_SPECIFIC_05
#define PMBUSCMD_D5H_MFR_SPECIFIC_05            0xd5

// D6h MFR_SPECIFIC_06
#define PMBUSCMD_D6H_MFR_SPECIFIC_06            0xd6

// D7h MFR_SPECIFIC_07
#define PMBUSCMD_D7H_MFR_SPECIFIC_07            0xd7

// D8h MFR_SPECIFIC_08
#define PMBUSCMD_D8H_MFR_SPECIFIC_08            0xd8

// D9h MFR_SPECIFIC_09
#define PMBUSCMD_D9H_MFR_SPECIFIC_09            0xd9

// DAh MFR_SPECIFIC_10
#define PMBUSCMD_DAH_MFR_SPECIFIC_10            0xda

// DBh MFR_SPECIFIC_11
#define PMBUSCMD_DBH_MFR_SPECIFIC_11            0xdb

// DCh MFR_SPECIFIC_12
#define PMBUSCMD_DCH_MFR_SPECIFIC_12            0xdc

// DDh MFR_SPECIFIC_13
#define PMBUSCMD_DDH_MFR_SPECIFIC_13            0xdd

// DEh MFR_SPECIFIC_14
#define PMBUSCMD_DEH_MFR_SPECIFIC_14            0xde

// DFh MFR_SPECIFIC_15
#define PMBUSCMD_DFH_MFR_SPECIFIC_15            0xdf

// E0h MFR_SPECIFIC_16
#define PMBUSCMD_E0H_MFR_SPECIFIC_16            0xe0

// E1h MFR_SPECIFIC_17
#define PMBUSCMD_E1H_MFR_SPECIFIC_17            0xe1

// E2h MFR_SPECIFIC_18
#define PMBUSCMD_E2H_MFR_SPECIFIC_18            0xe2

// E3h MFR_SPECIFIC_19
#define PMBUSCMD_E3H_MFR_SPECIFIC_19            0xe3

// E4h MFR_SPECIFIC_20
#define PMBUSCMD_E4H_MFR_SPECIFIC_20            0xe4

// E5h MFR_SPECIFIC_21
#define PMBUSCMD_E5H_MFR_SPECIFIC_21            0xe5

// E6h MFR_SPECIFIC_22
#define PMBUSCMD_E6H_MFR_SPECIFIC_22            0xe6

// E7h MFR_SPECIFIC_23
#define PMBUSCMD_E7H_MFR_SPECIFIC_23            0xe7

// E8h MFR_SPECIFIC_24
#define PMBUSCMD_E8H_MFR_SPECIFIC_24            0xe8

// E9h MFR_SPECIFIC_25
#define PMBUSCMD_E9H_MFR_SPECIFIC_25            0xe9

// EAh MFR_SPECIFIC_26
#define PMBUSCMD_EAH_MFR_SPECIFIC_26            0xea

// EBh MFR_SPECIFIC_27
#define PMBUSCMD_EBH_MFR_SPECIFIC_27            0xeb

// ECh MFR_SPECIFIC_28
#define PMBUSCMD_ECH_MFR_SPECIFIC_28            0xec

// EDh MFR_SPECIFIC_29
#define PMBUSCMD_EDH_MFR_SPECIFIC_29            0xed

// EEh MFR_SPECIFIC_30
#define PMBUSCMD_EEH_MFR_SPECIFIC_30            0xee

// EFh MFR_SPECIFIC_31
#define PMBUSCMD_EFH_MFR_SPECIFIC_31            0xef

// F0h MFR_SPECIFIC_32
#define PMBUSCMD_F0H_MFR_SPECIFIC_32            0xf0

// F1h MFR_SPECIFIC_33 
#define PMBUSCMD_F1H_MFR_SPECIFIC_33            0xf1

// F2h MFR_SPECIFIC_34 
#define PMBUSCMD_F2H_MFR_SPECIFIC_34            0xf2

// F3h MFR_SPECIFIC_35 
#define PMBUSCMD_F3H_MFR_SPECIFIC_35            0xf3

// F4h MFR_SPECIFIC_36
#define PMBUSCMD_F4H_MFR_SPECIFIC_36            0xf4

// F5h MFR_SPECIFIC_37
#define PMBUSCMD_F5H_MFR_SPECIFIC_37            0xf5

// F6h MFR_SPECIFIC_38
#define PMBUSCMD_F6H_MFR_SPECIFIC_38            0xf6

// F7h MFR_SPECIFIC_39
#define PMBUSCMD_F7H_MFR_SPECIFIC_39            0xf7

// F8h MFR_SPECIFIC_40
#define PMBUSCMD_F8H_MFR_SPECIFIC_40            0xf8

// F9h MFR_SPECIFIC_41
#define PMBUSCMD_F9H_MFR_SPECIFIC_41            0xf9

// FAh MFR_SPECIFIC_42
#define PMBUSCMD_FAH_MFR_SPECIFIC_42            0xfa

// FBh MFR_SPECIFIC_43
#define PMBUSCMD_FBH_MFR_SPECIFIC_43            0xfb

// FCh MFR_SPECIFIC_44
#define PMBUSCMD_FCH_MFR_SPECIFIC_44            0xfc

// FDh MFR_SPECIFIC_45
#define PMBUSCMD_FDH_MFR_SPECIFIC_45            0xfd

// FEh MFR_SPECIFIC_COMMAND
#define PMBUSCMD_FEH_MFR_SPECIFIC_COMMAND       0xfe

// FFh PMBUS_COMMAND_EXT
#define PMBUSCMD_FFH_PMBUS_COMMAND_EXT          0xff

#endif