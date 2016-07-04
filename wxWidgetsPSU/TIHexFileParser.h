/**
 * @file TIHexParser.h
 */

#ifndef _TIHEXPARSER_H_
#define _TIHEXPARSER_H_

#include <iostream>
#include <map>
#include <list>

using namespace std;

class TIHexFileParser {
	/**********************************************************************/
	/*! \brief Output stream overload operator.
	*
	* Operator overloaded to encode any data held in memory into the Intel
	* HEX format for storage on disk
	*
	* \sa operator>>()
	*
	* \param dataOut    - Output stream for to store the decoded file
	*                     information
	* \param ihLocal    - Points to this class so that friend function has
	*                     access to private class members
	*
	* \retval           - pointer to output stream
	***********************************************************************/
	friend ostream& operator<<(ostream& dataOut,
		TIHexFileParser& ihLocal);

	/**********************************************************************/
	/*! \brief Input stream overload operator.
	*
	* Operator overloaded to decode data streamed in from a file in the
	* Intel HEX format into memory
	*
	* \sa operator<<()
	*
	* \param dataIn     - Input stream for the encoded file information
	* \param ihLocal    - Points to this class so that friend function has
	*                     access to private class members
	*
	* \retval           - pointer to input stream
	***********************************************************************/
	friend istream& operator>>(istream& dataIn,
		TIHexFileParser& ihLocal);

private:
	/**********************************************************************/
	/*! \brief Container for decoded Intel HEX content.
	*
	* STL map holding the addresses found in the Intel HEX file and the
	* associated data byte stored at that address
	***********************************************************************/
	map<unsigned long, unsigned short> ihContent;

	/**********************************************************************/
	/*! \brief Iterator for the container holding the decoded Intel HEX
	*        content.
	*
	* This iterator is used by the class to point to the location in memory
	* currently being used to read or write data. If no file has been
	* loaded into memory, it points to the start of ihContent.
	***********************************************************************/
	map<unsigned long, unsigned short>::iterator ihIterator;

	/**********************************************************************/
	/*! \brief Pair for the container holding the decoded Intel HEX content.
	*
	* This is used to acquire the result of an attempt to insert new data
	* into ihContent. Since the ihContent is a map STL, it can't allow
	* data to be assigned to the same address more than once. In this way we
	* can ensure that no address in a file is falsely assigned data more
	* than once.
	***********************************************************************/
	pair<map<unsigned long, unsigned short>::iterator, bool> ihReturn;

	/**********************************************************************/
	/*! \brief Stores segment base address of Intel HEX file.
	*
	* The segment base address is a 32-bit address to which the current
	* load offset (as found in a Data Record line of the Intel HEX file) is
	* added to calculate the actual address of the data. The Data Records
	* can only point to a 64kByte address, so the segment base address
	* expands the addressing to 4GB. This variable always holds the last
	* address accessed. This variable is only used during file decoding
	* and encoding in the operator<< and operator>> class member friend
	* functions.
	***********************************************************************/
	unsigned long segmentBaseAddress;

	/**********************************************************************/
	/*! \brief Stores the content of the CS/IP Registers, if used.
	*
	* Used to store the content of the CS and IS Register for HEX files
	* created for x286 or earlier Intel processors. This information is
	* retrieved from the Start Segment Address Record or can be defined
	* by the user using the setStartSegmentAddress() function.
	* The found element defines if these registers hold valid data or not.
	*
	* \param    csRegister  - content of the CS register
	* \param    ipRegister  - content of the IP register
	* \param    exists      - defines if values for the above registers have
	*                         been written (true) or not (false)
	*
	* \sa getStartSegmentAddress(), setStartSegmentAddress()
	***********************************************************************/
	struct {
		unsigned short  csRegister;
		unsigned short  ipRegister;
		bool            exists;
	} startSegmentAddress;

	/**********************************************************************/
	/*! \brief Stores the content of the EIP Register, if used.
	*
	* Used to store the content of the EIP Register for HEX files created
	* for x386 Intel processors. This information is retrieved from the
	* the Start Linear Address Record or can be defined by using the
	* setStartLinearAddress() function.
	* The found element defines if this register holds valid data or not.
	*
	* \param    eipRegister - content of the EIP register
	* \param    exists      - defines if a value for the above register has
	*                         been written (true) or not (false)
	*
	* \sa getStartLinearAddress(), setStartLinearAddress()
	***********************************************************************/
	struct {
		unsigned long   eipRegister;
		bool            exists;
	} startLinearAddress;


	/**********************************************************************/
	/*! \brief Structure to hold warning messages.
	*
	* Holds warning messages generated during encoding/decoding process and
	* number of messages currently present in system
	*
	* \param    ihWarnings      - list of warning messages as strings
	* \param    noOfWarnings    - no of warning messages still present in
	*                             the list
	***********************************************************************/
	struct {
		list<string> ihWarnings;
		unsigned long noOfWarnings;
	} msgWarning;

	/**********************************************************************/
	/*! \brief Structure to hold error messages.
	*
	* Holds error messages generated during encoding/decoding process and
	* number of messages currently present in system
	*
	* \param    ihErrors        - list of error messages as strings
	* \param    noOferrors      - no of error messages still present in the
	*                             list
	***********************************************************************/
	struct {
		list<string> ihErrors;
		unsigned long noOfErrors;
	} msgError;

	/**********************************************************************/
	/*! \brief Note that EOF record is found.
	*
	* Used to note that the EOF record was found in order to ensure that it
	* doesn't appear twice during encoding.
	***********************************************************************/
	bool foundEof;

	/**********************************************************************/
	/*! \brief Select verbose mode.
	*
	* Used during development to display messages as the incoming data
	* stream is decoded
	***********************************************************************/
	bool verbose;

	/**********************************************************************/
	/*! \brief Select segment address mode.
	*
	* If true, use the segment addressing mode when encoding files.
	* otherwise the default linear address mode will be used. Please refer
	* to Intel's Hexadecimal Object File Format Specifiation for further
	* information.
	***********************************************************************/
	bool segmentAddressMode;

	/***********************************************************************
	* \brief Converts a 2 char string to its HEX value.
	*
	* Converts a two byte string to its equivalent value in hexadecimal
	*
	* \param        value   - a two character, valid ASCII representation of
	*                         a hexadecimal value
	*
	* \retval       'value' valid   - 8-bit value
	* \retval       'value' invalid - 0x00 and calls addWarning()
	*
	* \note
	* This function will post a warning message using the warning handling
	* system addWarning() if:
	*   -# The string contains anything other that exactly two characters
	*   -# The string contains anything other than the characters 0-9, a-f
	*      and A-F
	*
	* \sa ulToHexString(), ucToHexString(), ulToString()
	***********************************************************************/
	unsigned char stringToHex(string value);

	/***********************************************************************
	* \brief Converts a 4 char string to its HEX value.
	*
	* Converts a four byte string to its equivalent value in hexadecimal
	*
	* \param        value   - a four character, valid ASCII representation of
	*                         a hexadecimal value
	*
	* \retval       'value' valid   - 16-bit value
	* \retval       'value' invalid - 0x0000 and calls addWarning()
	*
	* \note
	* This function will post a warning message using the warning handling
	* system addWarning() if:
	*   -# The string contains anything other that exactly two characters
	*   -# The string contains anything other than the characters 0-9, a-f
	*      and A-F
	*
	* \sa ulToHexString(), ucToHexString(), ulToString()
	*/
	unsigned short stringToHex4CHAR(string value);

	/***********************************************************************
	* \brief Converts an unsigned long to a string in HEX format.
	*
	* Takes the received paramter and converts it into its equivalent value
	* represented in ASCII and formatted in hexadecimal. Return value is an
	* 8 character long string, prefaced with '0's where necessary.
	*
	* \param        value   - a value between 0x0000000 and 0xFFFFFFFF
	*
	* \retval               - 8-character long string
	*
	* \note
	* Alpha characters are capitalised.
	*
	* \sa
	* stringToHex(), ucToHexString(), ulToString()
	***********************************************************************/
	string ulToHexString(unsigned long value);

	/**********************************************************************/
	/*! \brief Converts an unsigned short to a string in HEX format.
	*
	* Takes the received paramter and converts it into its equivalent value
	* represented in ASCII and formatted in hexadecimal. Return value is a
	* 4 character long string, prefaced with '0' where necessary.
	*
	* \param        value   - a value between 0x0000 and 0xFFFF
	*
	* \retval               - 4-character long string
	*
	* \note
	* Alpha characters are capitalised.
	*
	* \sa
	* stringToHex(), ulToHexString(), ulToString()
	***********************************************************************/
	string usToHexString(unsigned short value);

	/**********************************************************************/
	/*! \brief Converts an unsigned char to a string in HEX format.
	*
	* Takes the received paramter and converts it into its equivalent value
	* represented in ASCII and formatted in hexadecimal. Return value is a
	* 2 character long string, prefaced with '0' where necessary.
	*
	* \param        value   - a value between 0x00 and 0xFF
	*
	* \retval               - 2-character long string
	*
	* \note
	* Alpha characters are capitalised.
	*
	* \sa
	* stringToHex(), ulToHexString(), ulToString()
	***********************************************************************/
	string ucToHexString(unsigned char value);

	/**********************************************************************/
	/*! \brief Converts an unsigned long to a string in DEC format.
	*
	* Takes the received paramter and converts it into its equivalent value
	* represented in ASCII and formatted in decimal. Return value will never
	* be longer than a 48 character long string.
	*
	* \param        value   - value to be converted
	*
	* \retval               - ASCII string representation of value
	*
	* \sa
	* stringToHex(), ulToHexString(), ucToHexString()
	***********************************************************************/
	string ulToString(unsigned long value);

	/**********************************************************************/
	/*! \brief Decodes the data content of a data record.
	*
	* Takes the data element of a data record in string format, converts
	* each 2 char element into a single byte and then inserts that byte of
	* data into the ihContent STL map.
	*
	* \sa encodeDataRecord()
	*
	* \param recordLength   - Number of bytes in this record as extracted
	*                         from this line in the Intel HEX file
	* \param loadOffset     - The offset from the segment base address for
	*                         the first byte in this record
	* \param data           - The data content of the record in a string
	***********************************************************************/
	void decodeDataRecord(unsigned char recordLength,
		unsigned long loadOffset,
		string::const_iterator data);

	/**********************************************************************/
	/*! \brief Add a warning message to the warning message list.
	*
	*
	* \param    warningMessage - the text to be added for this warning
	***********************************************************************/
	void addWarning(string warningMessage);

	/**********************************************************************/
	/*! \brief Add an error message to the error message list.
	*
	* \param    errorMessage - the text to be added for this error
	***********************************************************************/
	void addError(string errorMessage);

public:
	/**********************************************************************/
	/*! \brief intelhex Class Constructor.
	*
	* Important initialisation steps performed here:
	* - clear segment base address to zero
	* - clear all x86 start address registers to zero
	* - note that there are, as yet, no errors or warnings
	* - note that the EOF record has not yet been found
	* - set verbode mode to 'false' (default)
	* - initialise class ihIterator
	***********************************************************************/
	TIHexFileParser()
	{
		/* Initialise the segment base address to zero                    */
		segmentBaseAddress = 0;
		/* Clear content of register variables used with the 'Start Segment'
		*  and 'Start Linear' address records                             */
		startSegmentAddress.ipRegister = 0;
		startSegmentAddress.csRegister = 0;
		startSegmentAddress.exists = false;
		startLinearAddress.eipRegister = 0;
		startLinearAddress.exists = false;
		/* Set up error and warning handling variables                    */
		msgWarning.noOfWarnings = 0;
		msgError.noOfErrors = 0;
		/* Note that the EOF record has not been found yet                */
		foundEof = false;
		/* Set verbose mode to off                                        */
		verbose = false;
		/* Set segment address mode to false (default)                    */
		segmentAddressMode = false;
		/* Ensure ihContent is cleared and point ihIterator at it         */
		ihContent.clear();
		ihContent.begin();
		ihIterator = ihContent.begin();
	}

	/**********************************************************************/
	/*! \brief intelhex Class Deconstructor.
	*
	* Currently the deconstructor is intentially empty.
	***********************************************************************/
	~TIHexFileParser()
	{
		/* Currently nothing */
	}

	/**********************************************************************/
	/*! \brief intelhex Class Copy Constructor.
	*
	* Copy constructor copies all essential elements for the class.
	***********************************************************************/
	TIHexFileParser(const TIHexFileParser &ihSource)
	{
		/* Initialise the segment base address                            */
		segmentBaseAddress = ihSource.segmentBaseAddress;
		/* Initialise content of register variables used with the 'Start Segment'
		*  and 'Start Linear' address records                             */
		startSegmentAddress.ipRegister = ihSource.startSegmentAddress.ipRegister;
		startSegmentAddress.csRegister = ihSource.startSegmentAddress.csRegister;
		startSegmentAddress.exists = ihSource.startSegmentAddress.exists;
		startLinearAddress.eipRegister = ihSource.startLinearAddress.eipRegister;
		startLinearAddress.exists = ihSource.startLinearAddress.exists;
		/* Set up error and warning handling variables                    */
		msgWarning.noOfWarnings = ihSource.msgWarning.noOfWarnings;
		msgWarning.ihWarnings = ihSource.msgWarning.ihWarnings;
		msgError.noOfErrors = ihSource.msgError.noOfErrors;
		msgError.ihErrors = ihSource.msgError.ihErrors;
		/* Note that the EOF record has not been found yet                */
		foundEof = ihSource.foundEof;
		/* Set verbose mode to off                                        */
		verbose = ihSource.verbose;
		/* Set segment address mode to false (default)                    */
		segmentAddressMode = ihSource.segmentAddressMode;
		/* Copy HEX file content variables                                */
		ihContent = ihSource.ihContent;
		ihIterator = ihSource.ihIterator;
	}

	/**********************************************************************/
	/*! \brief intelhex Class Assignment Operator.
	*
	* Implements the assignment operator so that the content of the Intel
	* HEX file in memory can be copied to another 'intelhex' variable.
	* You may want to keep a copy of the original data in memory and
	* only manipulate a copy.
	*
	* \param    ihSource    - intelhex variable to be assigned to new
	*                         variable
	*
	* \retval   pointer to variable to which value is to be assigned
	***********************************************************************/
	TIHexFileParser& operator= (const TIHexFileParser &ihSource)
	{
		/* Check that we are not trying to assign ourself to ourself      */
		/* i.e. are the source/destination addresses the same like        */
		/* myData = myData;                                               */
		if (this == &ihSource)
			return *this;

		/* Initialise the segment base address                            */
		segmentBaseAddress = ihSource.segmentBaseAddress;
		/* Initialise content of register variables used with the 'Start Segment'
		*  and 'Start Linear' address records                             */
		startSegmentAddress.ipRegister = ihSource.startSegmentAddress.ipRegister;
		startSegmentAddress.csRegister = ihSource.startSegmentAddress.csRegister;
		startSegmentAddress.exists = ihSource.startSegmentAddress.exists;
		startLinearAddress.eipRegister = ihSource.startLinearAddress.eipRegister;
		startLinearAddress.exists = ihSource.startLinearAddress.exists;
		/* Set up error and warning handling variables                    */
		msgWarning.noOfWarnings = ihSource.msgWarning.noOfWarnings;
		msgWarning.ihWarnings = ihSource.msgWarning.ihWarnings;
		msgError.noOfErrors = ihSource.msgError.noOfErrors;
		msgError.ihErrors = ihSource.msgError.ihErrors;
		/* Note that the EOF record has not been found yet                */
		foundEof = ihSource.foundEof;
		/* Set verbose mode to off                                        */
		verbose = ihSource.verbose;
		/* Set segment address mode to false (default)                    */
		segmentAddressMode = ihSource.segmentAddressMode;
		/* Copy HEX file content variables                                */
		ihContent = ihSource.ihContent;
		ihIterator = ihSource.ihIterator;

		return *this;
	}

	/**********************************************************************/
	/*! \brief Overloaded prefix increment operator
	*
	* Overloads the prefix increment operator to move interal iterator to
	* next entry in the ihContent map
	*
	***********************************************************************/
	TIHexFileParser& operator++()
	{
		++ihIterator;

		return(*this);
	}

	/**********************************************************************/
	/*! \brief Overloaded postfix increment operator
	*
	* Overloads the postfix increment operator to move interal iterator to
	* next entry in the ihContent map
	*
	***********************************************************************/
	const TIHexFileParser operator++(int)
	{
		TIHexFileParser tmp(*this);
		++(*this);
		return(tmp);
	}

	/**********************************************************************/
	/*! \brief Overloaded prefix decrement operator
	*
	* Overloads the prefix decrement operator to move interal iterator to
	* previous entry in the ihContent map
	*
	***********************************************************************/
	TIHexFileParser& operator--()
	{
		--ihIterator;

		return(*this);
	}

	/**********************************************************************/
	/*! \brief Overloaded postfix decrement operator
	*
	* Overloads the postfix decrement operator to move interal iterator to
	* previous entry in the ihContent map
	*
	***********************************************************************/
	const TIHexFileParser operator--(int)
	{
		TIHexFileParser tmp(*this);
		--(*this);
		return(tmp);
	}

	/**********************************************************************/
	/*! \brief Moves the address pointer to the first available address.
	*
	* The address pointer will be moved to the first available address in
	* memory of the decoded file or of the data the user has inserted into
	* memory for the purpose of encoding into the Intel HEX format.
	*
	* \sa end()
	*
	* \note This function has no effect if no file has been as yet decoded
	* and no data has been inserted into memory.
	***********************************************************************/
	void begin()
	{
		if (ihContent.size() != 0)
		{
			ihIterator = ihContent.begin();
		}
	}

	/**********************************************************************/
	/*! \brief Moves the address pointer to the last available address.
	*
	* The address pointer will be moved to the last available address in
	* memory of the decoded file or of the data the user has inserted into
	* memory for the purpose of encoding into the Intel HEX format.
	*
	* \sa begin()
	*
	* \note This function has no effect if no file has been as yet decoded
	* and no data has been inserted into memory.
	***********************************************************************/
	void end()
	{
		if (!ihContent.empty())
		{
			ihIterator = ihContent.end();
			--ihIterator;
		}
	}

	/**********************************************************************/
	/*! \brief Checks if we have reached end of available data
	*
	* The internal pointer is checked to see if we have reached the end of
	* the data held in memory
	*
	* \sa operator++(), operator++(int), operator--(), operator--(int),
	* empty()
	*
	* \retval true  - reached the end of the Intel HEX data in memory or no
	*                 data in memory yet.
	* \retval false - end of Intel HEX data in memory not yet reached.
	*
	* \note This function has no effect if no file has been as yet decoded
	* and no data has been inserted into memory.
	***********************************************************************/
	unsigned long size()
	{
		return static_cast<unsigned long>(ihContent.size());
	}

	/**********************************************************************/
	/*! \brief Checks if we have reached end of available data
	*
	* The internal pointer is checked to see if we have reached the end of
	* the data held in memory
	*
	* \sa operator++(), operator++(int), operator--(), operator--(int),
	* empty()
	*
	* \retval true  - reached the end of the Intel HEX data in memory or no
	*                 data in memory yet.
	* \retval false - end of Intel HEX data in memory not yet reached.
	*
	* \note This function has no effect if no file has been as yet decoded
	* and no data has been inserted into memory.
	***********************************************************************/
	bool endOfData()
	{
		/* Return true if there is no data anyway                         */
		bool result = true;

		if (!ihContent.empty())
		{
			map<unsigned long, unsigned short>::iterator it \
				= ihContent.end();

			--it;

			if (it != ihIterator)
			{
				result = false;
			}
		}
		return result;
	}

	bool empty()
	{
		return ihContent.empty();
	}

	/**********************************************************************/
	/*! \brief Moves the address pointer to the desired address.
	*
	* Address pointer will take on the requested address if the address
	* exists in the data stored in memory. If not, the address pointer does
	* not change.
	*
	* \sa currentAddress()
	*
	* \param address    - Desired new address for the address pointer
	*
	* \retval true      - Address exists; pointer moved successfully
	* \retval false     - Address did not exist; pointer not moved
	***********************************************************************/
	bool jumpTo(unsigned long address)
	{
		bool result = false;

		if (ihContent.size() != 0)
		{
			map<unsigned long, unsigned short>::iterator it;
			it = ihContent.find(address);
			if (it != ihContent.end())
			{
				result = true;
				ihIterator = it;
			}
		}
		return result;
	}

	/**********************************************************************/
	/*! \brief Increments to next piece of data.
	*
	* Address pointer will take on the address of the next location for
	* which there is data.
	*
	* \sa decrementAddress()
	*
	* \retval true  - pointer was incremented; a new data value was found
	* \retval false - end of available data reached; pointer is unchanged
	***********************************************************************/
	bool incrementAddress()
	{
		bool result = false;

		/* If we have data */
		if (ihContent.size() != 0)
		{
			/* If we're not already pointing to the end */
			if (ihIterator != ihContent.end())
			{
				/* Increment iterator */
				ihIterator++;

				/* If we still haven't reached the end... */
				if (ihIterator != ihContent.end())
				{
					/* Everything is ok! */
					result = true;
				}
			}
		}

		/* If incrementation of the iterator was successful, return true  */
		return result;
	}

	/**********************************************************************/
	/*! \brief Decrements to next piece of data.
	*
	* Address pointer will take on the address of the previous location for
	* which there is data.
	*
	* \sa incrementAddress()
	*
	* \retval true  - pointer was decremented; a new data value was found
	* \retval false - start of available data reached; pointer is unchanged
	***********************************************************************/
	bool decrementAddress()
	{
		bool result = false;

		/* If we have data */
		if (ihContent.size() != 0)
		{
			/* If we're not already pointing to the start */
			if (ihIterator != ihContent.begin())
			{
				/* Decrement iterator */
				ihIterator--;

				/* Everything is ok! */
				result = true;
			}
		}

		/* If incrementation of the iterator was successful, return true  */
		return result;
	}

	/**********************************************************************/
	/*! \brief Returns the current address being pointed to.
	*
	* Current address will be returned.
	*
	* \sa jumpTo()
	*
	* \retval   Current address being pointed to.
	***********************************************************************/
	unsigned long currentAddress()
	{
		return ihIterator->first;
	}

	/**********************************************************************/
	/*! \brief Returns the lowest address currently available.
	*
	* Returns the first address that appears in the memory if there is data
	* present. If not, no value will be returned.
	*
	* \sa endAddress()
	*
	* \param address    - variable to hold address requested
	*
	* \retval true      - address existed and returned value is valid
	* \retval false     - address did not exist and returned valid is not
	*                     valid
	***********************************************************************/
	bool startAddress(unsigned long * address)
	{
		if (ihContent.size() != 0)
		{
			map<unsigned long, unsigned short>::iterator it;

			it = ihContent.begin();
			*address = (*it).first;
			return true;
		}

		return false;
	}

	/**********************************************************************/
	/*! \brief Returns the highest address currently available.
	*
	* Returns the last address that appears in the memory if there is data
	* present. If not, no value will be returned.
	*
	* \param address    - variable to hold address requested
	*
	* \retval true      - address existed and returned value is valid
	* \retval false     - address did not exist and returned valid is not
	*                     valid
	*
	* \sa startAddress()
	***********************************************************************/
	bool endAddress(unsigned long * address)
	{
		if (ihContent.size() != 0)
		{
			map<unsigned long, unsigned short>::reverse_iterator rit;

			rit = ihContent.rbegin();
			*address = (*rit).first;
			return true;
		}

		return false;
	}

	/**********************************************************************/
	/*! \brief Returns the data to which the iterator is currently pointing.
	*
	* Returns the data to which the internal iterator (pointer) is currently
	* pointing. If no data is in memory, this function returns false.
	*
	* \param data       - variable to hold data requested
	*
	* \retval true      - data was available and returned value is valid
	* \retval false     - data was not available and returned valid is not
	*                     valid
	*
	* \sa putData()
	***********************************************************************/
	bool getData(unsigned short * data)
	{
		if (!ihContent.empty() && (ihIterator != ihContent.end()))
		{
			*data = ihIterator->second;
			return true;
		}
		return false;
	}

	/**********************************************************************/
	/*! \brief Returns the data for desired address.
	*
	* Returns the data for the desired address. If the address has no data
	* assigned to it, the function returns false, the pointer to data is not
	* written and the class's address pointer remains unchanged. If the
	* address has data assigned to it, the pointer to data will be written
	* with the data found and the class's address pointer will be moved to
	* this new location.
	*
	* \param data       - variable to hold data requested
	* \param address	- address to be queried for valid data
	*
	* \retval true      - data was available and returned value is valid
	* \retval false     - data was not available and returned valid is not
	*                     valid
	*
	* \sa putData()
	***********************************************************************/
	bool getData(unsigned short * data, unsigned long address)
	{
		bool found = false;
		map<unsigned long, unsigned short>::iterator localIterator;

		if (!ihContent.empty())
		{
			localIterator = ihContent.find(address);

			if (localIterator != ihContent.end())
			{
				found = true;
				ihIterator = localIterator;
				*data = ihIterator->second;
			}
		}

		return found;
	}

	/**********************************************************************/
	/*! \brief Inserts desired byte at the current address pointer.
	*
	* Inserts byte of data at the current address pointer
	*
	* \param    data - data byte to be inserted
	*
	* \sa startAddress()
	***********************************************************************/
	bool insertData(unsigned char data);
	bool insertData(unsigned char data, unsigned long address);

	void overwriteData(unsigned char data);
	void overwriteData(unsigned char data, unsigned long address);

	bool blankFill(unsigned char data);

	bool blankFill(unsigned char * const data, unsigned long sizeOfData);

	void blankFill(unsigned char * const data, unsigned long sizeOfData,
		unsigned long endAddress);

	bool blankFillRandom();

	void blankFillRandom(unsigned long endAddress);

	bool blankFillAddressLowByte();

	void blankFillAddressLowByte(unsigned long endAddress);

	void ClearALL(void) {
		/* Initialise the segment base address to zero                    */
		segmentBaseAddress = 0;
		/* Clear content of register variables used with the 'Start Segment'
		*  and 'Start Linear' address records                             */
		startSegmentAddress.ipRegister = 0;
		startSegmentAddress.csRegister = 0;
		startSegmentAddress.exists = false;
		startLinearAddress.eipRegister = 0;
		startLinearAddress.exists = false;
		/* Set up error and warning handling variables                    */
		msgWarning.noOfWarnings = 0;
		msgError.noOfErrors = 0;
		/* Note that the EOF record has not been found yet                */
		foundEof = false;
		/* Set verbose mode to off                                        */
		verbose = false;
		/* Set segment address mode to false (default)                    */
		segmentAddressMode = false;
		/* Ensure ihContent is cleared and point ihIterator at it         */
		ihContent.clear();
		ihContent.begin();
		ihIterator = ihContent.begin();
	}

	/**********************************************************************/
	/*! \brief Returns number of unread warning messages.
	*
	* Number of unread warning messages will be returned.
	*
	* \sa popNextWarning(), getNoErrors(), popNextError()
	***********************************************************************/
	unsigned long getNoWarnings()
	{
		return msgWarning.noOfWarnings;
	}

	/**********************************************************************/
	/*! \brief Returns number of unread error messages.
	*
	* Number of unread error messages will be returned.
	*
	* \sa popNextWarning(), getNoWarnings(), popNextError()
	***********************************************************************/
	unsigned long getNoErrors()
	{
		return msgError.noOfErrors;
	}

	/**********************************************************************/
	/*! \brief Pop next warning message from the list of warnings.
	*
	* Next warning message is returned from the list of warnings. If there
	* are no more warning in the list, the string will be unchanged.
	*
	* \param    warning - variable to store warning string to be returned
	*
	* \retval   true    - more warning messages are available
	* \retval   false   - no more warning messages are available
	*
	* \sa getNoWarnings(), getNoErrors(), popNextError()
	***********************************************************************/
	bool popNextWarning(string& warning)
	{
		if (msgWarning.noOfWarnings > 0)
		{
			warning = msgWarning.ihWarnings.front();

			msgWarning.ihWarnings.pop_front();

			msgWarning.noOfWarnings = msgWarning.ihWarnings.size();

			return true;
		}
		else
		{
			return false;
		}
	}

	/**********************************************************************/
	/*! \brief Pop next error message from the list of errors.
	*
	* Next error message is returned from the list of errors. If there are
	* no more errors in the list, no string will be returned unchanged.
	*
	* \param    error   - variable to store error string to be returned
	*
	* \retval   true    - more error messages are available
	* \retval   false   - no more error messages are available
	*
	* \sa getNoWarnings(), getNoErrors(), popNextError()
	***********************************************************************/
	bool popNextError(string& error)
	{
		if (msgError.noOfErrors > 0)
		{
			error = msgError.ihErrors.front();

			msgError.ihErrors.pop_front();

			msgError.noOfErrors = msgError.ihErrors.size();

			return true;
		}
		else
		{
			return false;
		}
	}

	/**********************************************************************/
	/*! \brief Returns segment start address for the IP and ES registers.
	*
	* If these values exist, they will be returned. If not, the function
	* returns false.
	*
	* \param    ipRegister  - variable to store IP register's value
	* \param    csRegister  - variable to store CS register's value
	*
	* \retval   true    - IP and CS registers have defined values
	* \retval   false   - IP and CS registers do not contain values
	*
	* \sa getStartLinearAddress(), setStartSegmentAddress(),
	*     setStartLinearAddress()
	***********************************************************************/
	bool getStartSegmentAddress(unsigned short * ipRegister,
		unsigned short * csRegister)
	{
		if (startSegmentAddress.exists == true)
		{
			*ipRegister = startSegmentAddress.ipRegister;
			*csRegister = startSegmentAddress.csRegister;
		}

		return startSegmentAddress.exists;
	}

	/**********************************************************************/
	/*! \brief Returns segment linear address for the EIP register.
	*
	* If this value exists, they will be returned. If not, the function
	* returns false.
	*
	* \param    eipRegister - variable to store EIP register's value
	*
	* \retval   true    - EIP register has defined value
	* \retval   false   - EIP register do not contain value
	*
	* \sa getStartSegmentAddress(), setStartSegmentAddress(),
	*     setStartLinearAddress()
	***********************************************************************/
	bool getStartLinearAddress(unsigned long * eipRegister)
	{
		if (startLinearAddress.exists == true)
		{
			*eipRegister = startLinearAddress.eipRegister;
		}

		return startLinearAddress.exists;
	}

	/**********************************************************************/
	/*! \brief Sets the segment start address for the IP and CS registers.
	*
	* Allows user to define or redefine the contents of the IP and CS
	* registers
	*
	* \param    ipRegister  - desired IP register value
	* \param    csRegister  - desired CS register value
	*
	* \sa getStartLinearAddress(), getStartSegmentAddress(),
	*     setStartLinearAddress()
	***********************************************************************/
	void setStartSegmentAddress(unsigned short ipRegister,
		unsigned short csRegister)
	{
		startSegmentAddress.ipRegister = ipRegister;
		startSegmentAddress.csRegister = csRegister;
		startSegmentAddress.exists = true;
	}

	/**********************************************************************/
	/*! \brief Sets the segment start address for the EIP register.
	*
	* Allows user to define or redefine the contents of the EIP register
	*
	* \param    eipRegister - desired EIP register value
	*
	* \sa getStartSegmentAddress(), setStartSegmentAddress(),
	*     getStartLinearAddress()
	***********************************************************************/
	void setStartLinearAddress(unsigned long eipRegister)
	{
		startLinearAddress.eipRegister = eipRegister;
		startLinearAddress.exists = true;
	}

	/**********************************************************************/
	/*! \brief Turns on segment addressing mode during encoding.
	*
	* Uses the Segment Address Record during encoding.
	***********************************************************************/
	void segmentAddressingOn()
	{
		segmentAddressMode = true;
	}

	/**********************************************************************/
	/*! \brief Turns on linear addressing mode during encoding.
	*
	* Uses the Linear Address Record during encoding.
	***********************************************************************/
	void linearAddressingOn()
	{
		segmentAddressMode = false;
	}

	/**********************************************************************/
	/*! \brief Turns on textual output to cout during decoding.
	*
	* Per record single line output to cout during decoding of Intel HEX
	* files.
	***********************************************************************/
	void verboseOn()
	{
		verbose = true;
	}

	/**********************************************************************/
	/*! \brief Turns off textual output to cout during decoding.
	*
	* No output to cout during decoding of Intel HEX files.
	***********************************************************************/
	void verboseOff()
	{
		verbose = false;
	}

	/**********************************************************************/
	/*! \brief Fill Blank Address with value.
	*
	* By Default the fill value is 0xffff.
	***********************************************************************/
	void fillBlankAddr(unsigned short value = 0xffff);
};
#endif