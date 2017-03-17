/**
 * @file FRU.cpp
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <strings.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <limits.h>

#if defined(__APPLE__)
#include <libkern/OSByteOrder.h>
#define __bswap_32 OSSwapInt32
#endif

#if 0
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "CommonDef.h"

#include "FRU.h"

/*
* This code is based from:
* Platform Management FRU Information
* Storage Definition
* Document Revision 1.1, September 27, 1999
* Available at zero cost at:
* http://download.intel.com/design/servers/ipmi/FRU1011.pdf
*
*/

#if CHAR_BIT != 8
#error "unsupported char size"
#endif


int quiet = 0;
int verbose = 0;

void * x_calloc(size_t nmemb, size_t size)
{
	unsigned int *ptr;

	ptr = (unsigned int*)calloc(nmemb, size);
	if (ptr == NULL)
		printf_err("memory error - calloc returned zero\n");

	return (void *)ptr;
}

void printf_err(const char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	//printf("fru_dump %s, built %s\n", VERSION, VERSION_DATE);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void printf_warn(const char * fmt, ...)
{
	va_list ap;

	if (quiet || !verbose)
		return;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}

void printf_info(const char * fmt, ...)
{
	va_list ap;

	if (quiet)
		return;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
}


/*
* FRU information uses a zero checksum everywhere.
* The modulo 256 sum of the preceding bytes (starting with the first byte
* of the header) plus the checksum byte equals zero.
* Platform Management FRU Information Storage Definition : section 16.2.[56]
*/
unsigned char calc_zero_checksum(unsigned char *data, size_t len)
{
	size_t i;
	unsigned char tmp = 0;

	for (i = 0; i <= len; i++)
		tmp += data[i];

	return tmp;
}

/*
* FRU Board Area Mfg. Date / Time is the
* number of _minutes_ from 0:00 hrs 01Jan1996
* Max is 0xFFFFFF (3 bytes worth) or
* 16777215 minutes; or
*   279620 hours, 15 minutes; or
*   11650 days, 20 hours, 15 minutes; or
*   31 years, 328 days, 7 hours, 56 minutes (assuming 525949 minutes in a year); or
*   up to : Wed Nov 24 07:56 2027
* See:
*   section 11, Platform Management FRU Information Storage Definition
*/
time_t min2date(unsigned int mins)
{
	struct tm tm;
	time_t tmp;

	/* Set up 01-Jan-1996 , and add the number of minutes to it */
	memset(&tm, 0, sizeof(struct tm));
	tm.tm_year = 96;
	tm.tm_mday = 1;
	tm.tm_min += mins;
	tmp = mktime(&tm);
	return tmp;
}

#ifdef DEBUG
/*
* Used for debugging
*/
static void dump_str(unsigned char * p, unsigned int size, unsigned int space)
{
	size_t i, j = 0, k, m, shift;
	unsigned char *t, this = 0, last = 0;

	t = p;
	k = 8 - space;
	for (i = 0; i < size; i++) {
		m = 0;
		printf("%02zi: %02x : ", i, *t);
		last = this;
		this = *t;
		for (shift = 0x80; shift > 0; shift >>= 1) {
			printf("%s", ((*t & shift) == shift) ? "1" : "0");
			j++, m++;
			if (k == m) {
				printf(" ");
				k = 8 - space + m;
				if (k >= 8)
					k -= space;
				m = space + 100;
			}
		}
		if (space == 8) {
			if (*t)
				printf(" (%c) %02x", *t, *t - 0x20);
			else
				printf(" (term) NULL");
		}
		if (space == 6) {
			unsigned char x = 0, y = 0;

			if (k == 2) {
				y = (this >> 2) & 0x3F;
				x = (last >> 4) | ((this & 0x3) << 4);
			}
			else if (k == 4) {
				x = this & 0x3F;
			}
			else if (k == 6) {
				x = (last >> 6) | ((this & 0xF) << 2);
			}

			if (k == 4 || k == 6)
				printf(" (%02x) %02x '%c'", x, x + 0x20, x + 0x20);
			if (k == 2)
				printf(" (%02x) %02x '%c' | (%02x) %02x '%c'", x, x + 0x20, x + 0x20, y, y + 0x20, y + 0x20);
		}
		++t;
		printf("\n");
	}
}
#else
static void dump_str(unsigned char * UNUSED(p), unsigned int UNUSED(size), unsigned int UNUSED(space))
{
	return;
}
#endif
/*
* 6-bit ASCII Packing
* Platform Management FRU Information Storage Definition:  Section 13.[23]
*/
int ascii2six(unsigned char **dest, unsigned char *src, size_t size)
{
	size_t i = 0;
	ssize_t j;
	unsigned int k, m = 0;
	unsigned char *p, *d, *e;

	if (!src || !size)
		return 0;

	e = d = (unsigned char*)x_calloc(1, size);

	p = src;
	/*
	* 6-bit requires uppercase chars, between 0 and 0x3f
	*/
	while (*p != '\0' && i <= size) {
		j = toupper(*p) - 0x20;
		if (j < 0 || j >= 0x40) {
			printf_warn("%s : trying to convert a string '%s'\n"
				"\t\twhich includes char '%c (0x%x)', which can't be converted\n",
				__FUNCTIONW__, src, *p, *p);
			free(e);
			return -1;
		}
		*d = j;
		++p, ++d, i++;
	}
	/* dump_str(d, size, 4); */

	/* the length of dest, should be 3/4 of size, it's zero padded at the end */
	*dest = (unsigned char*)x_calloc(1, size + 1);
	p = *dest;

	for (i = 0; i <= size; i += 4) {
		k = e[i];
		m++;
		if ((i + 1) < size) {
			k |= e[i + 1] << 6;
			m++;
		}
		if ((i + 2) < size) {
			k |= e[i + 2] << 12;
			m++;
		}
		if ((i + 3) < size) {
			k |= e[i + 3] << 18;
		}
#ifndef __MINGW32__
#if __BYTE_ORDER == __BIG_ENDIAN
		k = _byteswap_ulong(k);//__bswap_32(k);
#endif
#endif
		memcpy(p, &k, 3);
		p += 3;
	}

	/* dump_str(*dest, m, 6); */
	free(e);

	return  m;
}

/*
*  * 6-bit ASCII Unpacking
*   * Platform Management FRU Information Storage Definition:  Section 13.[23]
*/
unsigned char * six2ascii(unsigned char *buf, size_t size)
{
	unsigned char *p, *dest;
	size_t i;

	if (!size)
		return NULL;

	dump_str(buf, size, 6);
	/* the length of dest, should be 4/3 of size + 1 for null termination char*/
	dest = (unsigned char*)x_calloc(1, ((size * 4) / 3) + 2);
	p = dest;

	for (i = 0; i < size; i += 3) {
		*dest = (buf[i] & 0x3F) + 0x20;
		/* printf("1: %i: 0x%x (%c)\n", i, *dest, *dest); */
		dest++;
		if ((i + 1) < size) {
			*dest = ((buf[i] & 0xC0) >> 6 | (buf[i + 1] & 0x0F) << 2) + 0x20;
			/* printf("2: %i: 0x%x (%c)\n", i, *dest, *dest); */
			dest++;
		}
		if ((i + 2) < size) {
			*dest = ((buf[i + 1] & 0xF0) >> 4 | (buf[i + 2] & 0x03) << 4) + 0x20;
			/* printf("3: %i: 0x%x (%c)\n", i, *dest, *dest); */
			dest++;
		}
		if ((i + 3) < size) {
			*dest = ((buf[i + 2] & 0xFC) >> 2) + 0x20;
			/* printf("4: %i: 0x%x (%c)\n", i, *dest, *dest); */
			dest++;
		}
	}
	/* make sure strings are null terminated */
	*dest = 0;

	/* Drop trailing spaces & null chars */
	dest--;
	while ((*dest == 0 || *dest == ' ') && size) {
		*dest = 0;
		dest--;
		size--;
	}

	return p;
}

/*
* Extract strings from fields
* Section 13 TYPE/LENGTH BYTE FORMAT
* Platform Management FRU Information Storage Definition
*/
unsigned int parse_string(unsigned char *p, unsigned char **str, const char * field)
{
	size_t len, i, j;

	len = p[0] & 0x3F;

	if (!len) {
		*str = (unsigned char*)x_calloc(1, 3);
		*str[0] = (FRU_STRING_ASCII << 6);
		return 1;
	}

	printf_info("FRU STRING TYPE = %d \n", (p[0] >> 6) & 0x3);
	switch ((p[0] >> 6) & 0x3) {
	case FRU_STRING_BINARY:
		/* binary or unspecified */
		*str = (unsigned char*)x_calloc(1, len + 2);
		memcpy(*str, p, len + 1);
		break;
	case FRU_STRING_BCD:
		/* BCD plus */
		printf_err("BCD - sorry\n");
		break;
	case FRU_STRING_SIXBIT:
		/* 6-bit ASCII, packed */
	{
		unsigned char *tmp1, *tmp2;
		size_t tlen;

		tmp1 = six2ascii(&p[1], p[0] & 0x3F);
		/* printf("str: %s\n", foo); */
		/* dump_str(foo, strlen(foo) + 1, 8); */
		tlen = strlen((char *)tmp1);
		*str = (unsigned char*)x_calloc(1, tlen + 2);

		tmp2 = *str;
		tmp2++;
		memcpy(tmp2, tmp1, tlen + 1);
		if (tlen > 0x3F)
			tlen = 0x3F;

		*str[0] = (FRU_STRING_ASCII << 6) | tlen;
		free(tmp1);
	}
	break;
	case FRU_STRING_ASCII:
		/* 8-bit ASCII */
		*str = (unsigned char*)x_calloc(1, len + 2);
		printf_info("Allocate Size = %d \n", len + 2);
		memcpy(*str, p, len + 1);
		for (i = 1; i < len; i++) {
			if (p[i] < 0x20 || p[i] == 0x7F) {
				printf_warn("Field '%s' marked as ASCII, but contains non-printable "
					"characters:\n", field);
				printf_warn("  Length/Type : 0x%x (length:%i; type:ASCII(%i)\n",
					p[0], p[0] & 0x3F, FRU_STRING_ASCII);
				printf_warn("  Contents : ");
				for (j = 1; j < len + 1; j++)
					printf_warn("0x%02x ", p[j]);
				printf_warn(" |");
				for (j = 0; j < len + 1; j++)
					printf_warn("%c", ((p[j] < 32) || (p[j] >= 127)) ? '.' : p[j]);
				printf_warn("|\n");
			}
		}
		break;
	}
	return len + 1;
}

/*
* Board Info Area Format
* Platform Management FRU Information Storage Definition: Section 11
*/
struct BOARD_INFO * parse_board_area(unsigned char *data)
{

	struct BOARD_INFO *fru;
	unsigned char *p;
	unsigned int len, i, j;

	fru = (BOARD_INFO*)x_calloc(1, sizeof(struct BOARD_INFO));

	if (data[0] != 0x01) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Board Area Format Version mismatch: 0x%02x should be 0x01", data[0]);
		goto err;
	}

	len = (data[1] * 8) - 1;
	if (calc_zero_checksum(data, len)) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Board Area Checksum failed");
		goto err;
	}

	if (data[2] != 0 && data[2] != 25) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Board Area is non-English - sorry: Lang code = %i", data[2]);
		goto err;
	}

	len--;
	while ((data[len] == 0x00) && (len != 0))
		len--;
	if (len == 0 || data[len] != 0xC1) {
		PSU_DEBUG_PRINT(MSG_ERROR, "BOARD INFO not terminated properly, walking backwards len: "
			"%i:0x%02x should be 0xC1", len, data[len]);
		goto err;
	}

	fru->mfg_date = data[3] | (data[4] << 8) | (data[5] << 16);

	p = &data[6];
	len -= 6;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Manufacturer String");
	i = parse_string(p, &fru->manufacturer, "Manufacturer");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Product Name String");
	i = parse_string(p, &fru->product_name, "Product Name");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Serial Number String");
	i = parse_string(p, &fru->serial_number, "Serial Number");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Part Number String");
	i = parse_string(p, &fru->part_number, "Part Number");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse File ID String");
	i = parse_string(p, &fru->FRU_file_ID, "FRU File ID");
	p += i, len -= i;

	j = 0;
	while (len != 0 && j < CUSTOM_FIELDS) {
		PSU_DEBUG_PRINT(MSG_DEBUG, "Parse CUSTOM_FIELDS %d String", j);
		i = parse_string(p, &fru->custom[j], "Custom Field");
		p += i, len -= i, j++;
	}

	if (*p != 0xC1) {
		PSU_DEBUG_PRINT(MSG_ERROR, "BOARD INFO not terminated properly, "
			"offset %02i(0x%02x) : %02i(0x%02x) should be 0xC1",
			p - data, p - data, *p, *p);
		goto err;
	}

	return fru;

err:
	if (fru->manufacturer) free(fru->manufacturer);
	if (fru->product_name) free(fru->product_name);
	if (fru->serial_number) free(fru->serial_number);
	if (fru->part_number) free(fru->part_number);
	if (fru->FRU_file_ID) free(fru->FRU_file_ID);
	for (j = 0; j < CUSTOM_FIELDS; j++)
		if (fru->custom[j]) free(fru->custom[j]);
	free(fru);
	return NULL;
}

/*
* Product Info Area Format
* Platform Management FRU Information Storage Definition: Section 12
*/
struct PRODUCT_INFO * parse_product_area(unsigned char *data)
{
	struct PRODUCT_INFO *fru;
	unsigned char *p;
	unsigned int len, i, j;

	fru = (PRODUCT_INFO*)x_calloc(1, sizeof(struct PRODUCT_INFO));

	if (data[0] != 0x01) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Product Area Format Version mismatch: 0x%02x should be 0x01", data[0]);
		goto err;
	}

	len = (data[1] * 8) - 1;
	if (calc_zero_checksum(data, len)) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Product Area Checksum failed");
		goto err;
	}

	if (data[2] != 0 && data[2] != 25) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Product Area is non-English - sorry: Lang code = %i", data[2]);
		goto err;
	}

	len--;
	while ((data[len] == 0x00) && (len != 0))
		len--;
	if (len == 0 || data[len] != 0xC1) {
		PSU_DEBUG_PRINT(MSG_ERROR, "PRODUCT INFO not terminated properly, walking backwards len: "
			"%i:0x%02x should be 0xC1", len, data[len]);
		goto err;
	}

	p = &data[3];
	len -= 3;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Manufacturer Name String");
	i = parse_string(p, &fru->manufacturer_name, "Manufacturer Name");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Product Name String");
	i = parse_string(p, &fru->product_name, "Product Name");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Model Number String");
	i = parse_string(p, &fru->model_number, "Model Number");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Version String");
	i = parse_string(p, &fru->version, "Version");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Serial Number String");
	i = parse_string(p, &fru->serial_number, "Serial Number");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Asset Tag String");
	i = parse_string(p, &fru->asset_tag, "Asset Tag");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse File ID String");
	i = parse_string(p, &fru->FRU_file_ID, "FRU File ID");
	p += i, len -= i;

	PSU_DEBUG_PRINT(MSG_DEBUG, "Parse Custom FIELDS");
	j = 0;
	while (len != 0 && j < CUSTOM_FIELDS) {
		PSU_DEBUG_PRINT(MSG_DEBUG, "Parse CUSTOM_FIELDS %d String", j);
		i = parse_string(p, &fru->custom[j], "Custom Field");
		p += i, len -= i, j++;
	}

	if (*p != 0xC1) {
		PSU_DEBUG_PRINT(MSG_ERROR, "PRODUCT INFO not terminated properly, "
			"offset %02i(0x%02x) : %02i(0x%02x) should be 0xC1",
			p - data, p - data, *p, *p);
		goto err;
	}

	return fru;

err:
	if (fru->manufacturer_name) free(fru->manufacturer_name);
	if (fru->product_name) free(fru->product_name);
	if (fru->model_number) free(fru->model_number);
	if (fru->version) free(fru->version);
	if (fru->serial_number) free(fru->serial_number);
	if (fru->asset_tag) free(fru->asset_tag);
	if (fru->FRU_file_ID) free(fru->FRU_file_ID);
	for (j = 0; j < CUSTOM_FIELDS; j++)
		if (fru->custom[j]) free(fru->custom[j]);
	free(fru);
	return NULL;
}

/*
* Each record in this area begins with a pre-defined header as specified in the
* section 16 in the Platform Management FRU Information Storage Definition.
* This header contains a ��Type�� field that identifies what information is
* contained in the record.  * There are some FMC specific headers, defined
* in section 5.5.1 of the FMC specification "IPMI Support". These FMC specific
* sections have a 1 byte sub-type, and a 3 byte Unique Organization Identifier
*/
struct MULTIRECORD_INFO * parse_multiboard_area(unsigned char *data)
{
	int i = 0, tmp, type;
	unsigned char *p;
	struct MULTIRECORD_INFO *multi;

	multi = (MULTIRECORD_INFO*)x_calloc(1, sizeof(struct MULTIRECORD_INFO));

	p = data;

	do {
		if (i != 0)
			p += 5 + p[2];
		if (p[0] >= 0x06 && p[0] <= 0xBF) {
			PSU_DEBUG_PRINT(MSG_ERROR, "MultiRecord Area %i: Invalid Record Header", i);
			return NULL;
		}
		if (calc_zero_checksum(p, 4)) {
			PSU_DEBUG_PRINT(MSG_ERROR, "MultiRecord Area %i (Record Type 0x%x): "
				"Header Checksum failed", i, p[0]);
			return NULL;
		}

		if (!p[2] || ((calc_zero_checksum(p + 5, p[2] - 1) + p[3]) & 0xFF)) {
			PSU_DEBUG_PRINT(MSG_ERROR, "MultiRecord Area %i (Record Type 0x%x): "
				"Record Checksum failed", i, p[0]);
			return NULL;
		}

		/*
		* Record Type ID
		*/
		switch (p[0]) {

		case MULTIRECORD_POWER_SUPPLY_INFO:

			multi->power_supply_info = (unsigned char*)x_calloc(1, p[2] + 6);// Record Length + 6
			memcpy(multi->power_supply_info, p, p[2] + 6);
			multi->power_supply_info[1] = multi->power_supply_info[1] & 0x7F;

			break;

		case MULTIRECORD_DC_OUTPUT:
		case MULTIRECORD_DC_INPUT:
			tmp = p[5] & 0xF;
			if ((tmp) >= NUM_SUPPLIES)
				PSU_DEBUG_PRINT(MSG_ERROR, "Too many Supplies defined in Multirecords");

			multi->supplies[tmp] = (unsigned char*)x_calloc(1, p[2] + 6);// Record Length + 6
			memcpy(multi->supplies[tmp], p, p[2] + 6);
			multi->supplies[tmp][1] = multi->supplies[tmp][1] & 0x7F;
			break;
		case MULTIRECORD_FMC:
			/*
			* Use VITA's OUI: 0x0012a2 is specified in the FMC spec - Rule 5.77
			*/
			if ((p[5] | p[6] << 8 | p[7] << 16) != VITA_OUI) {
				PSU_DEBUG_PRINT(MSG_ERROR, "OUI Doesn't match : is 0x%06X, "
					"should be 0x%06x", p[5] | p[6] << 8 | p[7] << 16, VITA_OUI);
			}
			/* type field is located: Header + Manufacturer ID = 5 + 3 */
			type = p[8] >> 4;

			switch (type) {
			case MULTIRECORD_CONNECTOR:
				/* see table 7 in FMC spec */
				multi->connector = (unsigned char*)x_calloc(1, p[2] + 6);
				memcpy(multi->connector, p, p[2] + 6);
				/* This isn't the end 'til we re-assemble things */
				multi->connector[1] = multi->connector[1] & 0x7F;
				break;
			case MULTIRECORD_I2C:
				if (p[2] <= 5) {
					PSU_DEBUG_PRINT(MSG_DEBUG, "I2C MultiRecord is too short (len:%i)"
						"	(at least 4 is needed for OUI and subtype)",
						p[2]);
				}
				else {
					/* see table 9 in FMC spec */
					unsigned char *foo2;
					foo2 = six2ascii(&p[9], p[2] - 4);

					multi->i2c_devices = (unsigned char*)x_calloc(1, strlen((char *)foo2) + 1);
					strcpy((char *)multi->i2c_devices, (char *)foo2);
					free(foo2);
					/* This isn't the end 'til we re-assemble things */
					multi->i2c_devices[1] = multi->i2c_devices[1] & 0x7F;
				}
				break;
			default:
				PSU_DEBUG_PRINT(MSG_ERROR, "Unknown multirecord type : %i", type);
				break;
			}

			if (type == 1) {

			}
			break;
		default:
			PSU_DEBUG_PRINT(MSG_ERROR, "Unknown MultiRecord Area");
		}

		i++;
	} while (!(p[1] & 0x80));

	return multi;
}

/*
* Common Header Format
* Section 8 in the Platform Management FRU Information Storage Definition
*/
struct FRU_DATA * parse_FRU(unsigned char *data)
{
	struct FRU_DATA *fru;

	fru = (FRU_DATA *)x_calloc(1, sizeof(struct FRU_DATA));

	/* Check FRU version */
	if (data[0] != 0x01) {
		PSU_DEBUG_PRINT(MSG_ERROR, "FRU Version number mismatch 0x%02x should be 0x01", data[0]);
		goto err;
	}

	/* Check Padding */
	if (data[6] != 0x00) {
		PSU_DEBUG_PRINT(MSG_ERROR, "FRU byte 6 should be PAD, and be zero -- but it's not");
		goto err;
	}

	/* Check header checksum */
	if (calc_zero_checksum(data, 7)) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Common Header Checksum failed");
		goto err;
	}

	/* Parse Internal Use Area */
	if (data[1]) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Internal Use Area not yet implemented - sorry");
		goto err;
	}

	/* Parse Chassis Info Area */
	if (data[2]) {
		PSU_DEBUG_PRINT(MSG_ERROR, "Chassis Info Area not yet implmented - sorry");
		goto err;
	}

	/* Parse Board Area */
	if (data[3]) {
		fru->Board_Area = parse_board_area(&data[data[3] * 8]);
		if (!fru->Board_Area)
			goto err;
	}

	/* Parse Product Info Area */
	if (data[4]) {
		fru->Product_Area = parse_product_area(&data[data[4] * 8]);
		if (!fru->Product_Area)
			goto err;
	}

	/* Parse MultiRecord Area */
	if (data[5])
		fru->MultiRecord_Area = parse_multiboard_area(&data[data[5] * 8]);

	return fru;

err:
	free(fru);
	return NULL;

}

void free_FRU(struct FRU_DATA *fru)
{
	int j;

	// Release Board Area
	if (fru->Board_Area){
		FRU_FREE(fru->Board_Area->manufacturer);
		FRU_FREE(fru->Board_Area->product_name);
		FRU_FREE(fru->Board_Area->serial_number);
		FRU_FREE(fru->Board_Area->part_number);
		FRU_FREE(fru->Board_Area->FRU_file_ID);
		for (j = 0; j < CUSTOM_FIELDS; j++)
			FRU_FREE(fru->Board_Area->custom[j]);
		FRU_FREE(fru->Board_Area);
	}

	// Release Product Area
	if (fru->Product_Area){
		FRU_FREE(fru->Product_Area->manufacturer_name);
		FRU_FREE(fru->Product_Area->product_name);
		FRU_FREE(fru->Product_Area->model_number);
		FRU_FREE(fru->Product_Area->version);
		FRU_FREE(fru->Product_Area->serial_number);
		FRU_FREE(fru->Product_Area->asset_tag);
		FRU_FREE(fru->Product_Area->FRU_file_ID);
		for (j = 0; j < CUSTOM_FIELDS; j++)
			FRU_FREE(fru->Product_Area->custom[j]);
		FRU_FREE(fru->Product_Area);
	}

	// Release MultiRecord Area
	if (fru->MultiRecord_Area){
		for (j = 0; j < NUM_SUPPLIES; j++)
			FRU_FREE(fru->MultiRecord_Area->supplies[j]);

		FRU_FREE(fru->MultiRecord_Area->i2c_devices);

		FRU_FREE(fru->MultiRecord_Area->connector);
		FRU_FREE(fru->MultiRecord_Area);
	}

	FRU_FREE(fru);

}

/*
* take string, and put in into the buffer
* return the number of bytes copied
*/
static unsigned int insert_str(unsigned char *buf, const unsigned char * str, bool force)
{
	int tmp;

	if (TYPE_CODE(str) == FRU_STRING_ASCII)
		tmp = strlen((const char *)&str[1]);
	else
		tmp = FIELD_LEN(str);

	/* Turn ASCII into 6 bit if possible */
	if ((TYPE_CODE(str) != FRU_STRING_ASCII) || (tmp <= 0x3F && !force)) {
		/* It fits, so just leave it as ASCII/binary/whatever format it's in */
		buf[0] = tmp | (TYPE_CODE(str) << 6);
		memcpy(&buf[1], &str[1], tmp);
	}
	else {
		/* turn it into 6-bit ASCII */
		unsigned char *six = NULL;

		/* printf("six in : 0x%x : len: %2d : %s\n", (str[0] >> 6) && 0x3, str[0] & 0x3F , &str[1]); */
		/* dump_str((unsigned char*)&str[1], tmp + 1 , 8); */
		tmp = ascii2six(&six, (unsigned char *)&str[1], tmp);
		if (tmp < 0) {
			/* Counldn't encode things */
			printf_warn("couldn't encode '%s' string\n", &str[1]);
			tmp = strlen((const char *)&str[1]);
			if (tmp > 0x3F) {
				printf_warn("fail : %d\n", tmp);
				printf_err("String too long to fit\n");
			}
			buf[0] = tmp | (FRU_STRING_ASCII << 6);
			memcpy(&buf[1], &str[1], tmp);
			return tmp + 1;
		}
		dump_str(six, tmp, 6);
		if (tmp > 0x3F) {
			printf_warn("fail : %d\n", tmp);
			printf_err("String too long to fit\n");
		}

		buf[0] = tmp | (FRU_STRING_SIXBIT << 6);
		memcpy(&buf[1], six, tmp);
		free(six);
	}


	return tmp + 1;
}

/*
* Takes the FRU structure, and builds the binary blob
*/
unsigned char * build_FRU_blob(struct FRU_DATA *fru, size_t *length, bool packed)
{
	unsigned char *p, *buf;
	unsigned int st, len, tmp, last = 0, i = 0, j;

	buf = (unsigned char*)x_calloc(1, 1024);
	len = 256;

	buf[0] = 0x01;
	i = 8;
	if (fru->Internal_Area)
		PSU_DEBUG_PRINT(MSG_ERROR, "Internal Use Area not yet implemented");

	if (fru->Chassis_Info)
		PSU_DEBUG_PRINT(MSG_ERROR, "Chassis Info not yet implemented");

	if (fru->Board_Area) {
		len = st = i;
		buf[3] = i / 8;
		buf[i] = 0x1;   /* Magic number */
		/* buf[i+1] = length, which needs to be determined later */
		buf[i + 2] = 25;  /* English */
		buf[i + 3] = (fru->Board_Area->mfg_date) & 0xFF;
		buf[i + 4] = (fru->Board_Area->mfg_date >> 8) & 0xFF;
		buf[i + 5] = (fru->Board_Area->mfg_date >> 16) & 0xFF;

		i += 6;
		i += insert_str(&buf[i], fru->Board_Area->manufacturer, packed);
		i += insert_str(&buf[i], fru->Board_Area->product_name, packed);
		i += insert_str(&buf[i], fru->Board_Area->serial_number, packed);
		i += insert_str(&buf[i], fru->Board_Area->part_number, packed);
		i += insert_str(&buf[i], fru->Board_Area->FRU_file_ID, packed);
		for (j = 0; j < CUSTOM_FIELDS; j++) {
			// Don't Write Board Area Custom
#if 0
			if (fru->Board_Area->custom[j]) {
				i += insert_str(&buf[i], fru->Board_Area->custom[j], packed);
			}
#endif
		}
		buf[i] = 0xC1;
		i++;
		i = (((i >> 3) + 1) << 3) - 1;
		len = i - st;
		buf[st + 1] = len / 8 + 1;
		buf[i] = 256 - calc_zero_checksum(&buf[st], len);
		i++;
	}
	if (fru->Product_Area) {
		st = i;
		buf[4] = st / 8;
		buf[i] = 0x1;   /* Magic number */
		/* buf[i+1] = length, which needs to be determined later */
		buf[i + 2] = 25;  /* English */

		i += 3;
		i += insert_str(&buf[i], fru->Product_Area->manufacturer_name, packed);
		i += insert_str(&buf[i], fru->Product_Area->product_name, packed);
		i += insert_str(&buf[i], fru->Product_Area->model_number, packed);
		i += insert_str(&buf[i], fru->Product_Area->version, packed);
		i += insert_str(&buf[i], fru->Product_Area->serial_number, packed);
		i += insert_str(&buf[i], fru->Product_Area->asset_tag, packed);
		i += insert_str(&buf[i], fru->Product_Area->FRU_file_ID, packed);
		for (j = 0; j < CUSTOM_FIELDS; j++) {
			// Don't Write Product Area Custom
#if 0
			if (fru->Board_Area->custom[j]) {
				i += insert_str(&buf[i], fru->Product_Area->custom[j], packed);
			}
#endif
		}
		buf[i] = 0xC1;
		i++;
		i = (((i >> 3) + 1) << 3) - 1;
		len = i - st;
		buf[st + 1] = len / 8 + 1;
		buf[i] = 256 - calc_zero_checksum(&buf[st], len);
		i++;
	}
	if (fru->MultiRecord_Area) {
		st = i;
		buf[5] = st / 8;

		p = fru->MultiRecord_Area->power_supply_info;
		// If Power Supply Information Exist
		if (p){
			memcpy(&buf[i], p, p[2] + 5);
			/* Record Checksum */
			buf[i + 3] = 0x100 - calc_zero_checksum(&buf[i + 5], buf[i + 2] - 1);
			/* Header Checksum */
			buf[i + 4] = 0;
			buf[i + 4] = 0x100 - calc_zero_checksum(&buf[i], 4);
			last = i + 1;
			i += p[2] + 5;
		}

		for (tmp = 0; tmp < NUM_SUPPLIES; tmp++) {
			p = fru->MultiRecord_Area->supplies[tmp];
			if (!p)
				continue;
			memcpy(&buf[i], p, p[2] + 5);
			/* Record Checksum */
			buf[i + 3] = 0x100 - calc_zero_checksum(&buf[i + 5], buf[i + 2] - 1);
			/* Header Checksum */
			buf[i + 4] = 0;
			buf[i + 4] = 0x100 - calc_zero_checksum(&buf[i], 4);
			last = i + 1;
			i += p[2] + 5;
		}
		p = fru->MultiRecord_Area->connector;
		if (p) {
			memcpy(&buf[i], p, p[2] + 5);
			/* Record Checksum */
			buf[i + 3] = 0x100 - calc_zero_checksum(&buf[i + 5], buf[i + 2] - 1);
			/* Header Checksum */
			buf[i + 4] = 0;
			buf[i + 4] = 0x100 - calc_zero_checksum(&buf[i], 4);
			last = i + 1;
			i += p[2] + 5;
		}
		p = fru->MultiRecord_Area->i2c_devices;
		if (p) {
			unsigned int len, oui = VITA_OUI;
			unsigned char *six = NULL;
			len = ascii2six(&six, p, strlen((char *)p));

			/* Type ID, Record Format version, Length, checksum, checksum */
			sprintf((char *)&buf[i], "%c%c%c%c%c", MULTIRECORD_FMC, 0x02, len + 4, 0, 0);
			/* Store OUI */
#ifndef __MINGW32__
# if __BYTE_ORDER == __BIG_ENDIAN
			oui = _byteswap_ulong(oui);//__bswap_32(oui);
#endif
#endif
			memcpy(&buf[i + 5], &oui, 3);
			/* Subtype & version  - see Table 9 in FMC spec*/
			sprintf((char *)&buf[i + 8], "%c", (0x1 << 4) | (0));
			/* finally copy over the string */
			memcpy(&buf[i + 9], six, len);
			/* Record Checksum */
			buf[i + 3] = 0x100 - calc_zero_checksum(&buf[i + 5], len + 3);
			/* Header Checksum */
			buf[i + 4] = 0x100 - calc_zero_checksum(&buf[i], 4);

			last = i + 1;
			i += len + 9;

			free(six);
		}
		if (last) {
			buf[last] = buf[last] | 0x80;
			/* redo the header checksum, since we just changed the header :( */
			buf[last + 3] = 0;
			buf[last + 3] = 0x100 - calc_zero_checksum(&buf[last - 1], 4);
		}
	}
	buf[7] = 256 - calc_zero_checksum(buf, 6);

	*length = i;
	return buf;
}