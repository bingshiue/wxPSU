/**
 * @brief FRU.h.
 */
#ifndef __fru_tools__
#define __fru_tools__

#include <stdbool.h>
#include <time.h>

#ifndef UNUSED
#  ifdef __GNUC__
#    define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#  else
#    define UNUSED(x) UNUSED_ ## x
#  endif
#endif

/*
* These structures/data are based from:
* Platform Management FRU Information
* Storage Definition
* Document Revision 1.1, September 27, 1999
* http://download.intel.com/design/servers/ipmi/FRU1011.pdf
*
*/

#define CUSTOM_FIELDS 10

/* Defines from section 13 "TYPE/LENGTH BYTE FORMAT"  of FRU spec) */
#define FRU_STRING_BINARY  0
#define FRU_STRING_BCD     1
#define FRU_STRING_SIXBIT  2
#define FRU_STRING_ASCII   3

#define TYPE_CODE(x)  ((x[0] >> 6) & 0x3)
#define FIELD_LEN(x)  (x[0] & 0x3F)
#define FRU_FREE(x) if(x) free(x)

struct BOARD_INFO {
	unsigned char language_code;
	unsigned int mfg_date;
	unsigned char *manufacturer;
	unsigned char *product_name;
	unsigned char *serial_number;
	unsigned char *part_number;
	unsigned char *FRU_file_ID;
	unsigned char *custom[CUSTOM_FIELDS];
};

struct PRODUCT_INFO {
	unsigned char language_code;
	unsigned char *manufacturer_name;
	unsigned char *product_name;
	unsigned char *model_number;
	unsigned char *version;
	unsigned char *serial_number;
	unsigned char *asset_tag;
	unsigned char *FRU_file_ID;
	unsigned char *custom[CUSTOM_FIELDS];
};

#define NUM_MULTI     3
#define NUM_SUPPLIES 12

struct MULTIRECORD_INFO {
	unsigned char *power_supply_info;/**< Power Supply Information, Record Type 0x00 */
	unsigned char *supplies[NUM_SUPPLIES];/**< DC Output, Record Type 0x01 */
	unsigned char *connector;
	unsigned char *i2c_devices;
};

#define MULTIRECORD_I2C 1
#define MULTIRECORD_CONNECTOR 0

#define MULTIRECORD_POWER_SUPPLY_INFO 0
#define MULTIRECORD_DC_OUTPUT 1
#define MULTIRECORD_DC_INPUT  2
/* 0xfa is the FMC-specific MultiRecords, see Rule Rule 5.77 in the FMC spec */
#define MULTIRECORD_FMC       0xFA
/* VITA¡¦s Organizationally Unique Identifier - see rule 5.77 in the FMC spec */
#define VITA_OUI 0x0012A2

struct FRU_DATA {
	char *Internal_Area;
	char *Chassis_Info;
	struct BOARD_INFO *Board_Area;
	struct PRODUCT_INFO *Product_Area;
	//char *Product_Info;
	struct MULTIRECORD_INFO *MultiRecord_Area;
};

extern void printf_err(const char *, ...);
extern void printf_warn(const char *, ...);
extern void printf_info(const char *, ...);
extern struct FRU_DATA * parse_FRU(unsigned char *);
extern void free_FRU(struct FRU_DATA * fru);
extern unsigned char * build_FRU_blob(struct FRU_DATA *, size_t *, bool);
extern time_t min2date(unsigned int mins);
extern void * x_calloc(size_t, size_t);

#endif  /* __fru_tools__ */