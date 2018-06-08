/**
 * @file tihexclass.h
 */

#ifndef _TIHEXCLASS_H_
#define _TIHEXCLASS_H_

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <iomanip>
#include <typeinfo>

using namespace std;

/******************************************************************************/
/*! Possible record types for Intel HEX file.
*
* List of all possible record types that can be found in an Intel HEX file.
*******************************************************************************/
enum TIhexRecordType {
	DATA_RECORD,
	END_OF_FILE_RECORD,
	EXTENDED_SEGMENT_ADDRESS,
	START_SEGMENT_ADDRESS,
	EXTENDED_LINEAR_ADDRESS,
	START_LINEAR_ADDRESS,
	NO_OF_RECORD_TYPES
};

template<class T> class tihex;
template<class T> ostream& operator<<(ostream& dataOut, tihex<T>& ihLocal);
template<class T> istream& operator>>(istream& dataIn, tihex<T>& ihLocal);


template <class T=unsigned char>
class tihex {
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
	friend ostream& operator<<<>(ostream& dataOut,
		tihex<T>& ihLocal);

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
        friend istream& operator>><>(istream& dataIn,
		tihex<T>& ihLocal);

private:
	/**********************************************************************/
	/*! \brief Container for decoded Intel HEX content.
	*
	* STL map holding the addresses found in the Intel HEX file and the
	* associated data byte stored at that address
	***********************************************************************/
	map<unsigned long, T> ihContent;

	/**********************************************************************/
	/*! \brief Iterator for the container holding the decoded Intel HEX
	*        content.
	*
	* This iterator is used by the class to point to the location in memory
	* currently being used to read or write data. If no file has been
	* loaded into memory, it points to the start of ihContent.
	***********************************************************************/
	typename map<unsigned long, T>::iterator ihIterator;

	/**********************************************************************/
	/*! \brief Pair for the container holding the decoded Intel HEX content.
	*
	* This is used to acquire the result of an attempt to insert new data
	* into ihContent. Since the ihContent is a map STL, it can't allow
	* data to be assigned to the same address more than once. In this way we
	* can ensure that no address in a file is falsely assigned data more
	* than once.
	***********************************************************************/
	pair<typename map<unsigned long, T>::iterator, bool> ihReturn;

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
	tihex()
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
	~tihex()
	{
		/* Currently nothing */
	}

	/**********************************************************************/
	/*! \brief intelhex Class Copy Constructor.
	*
	* Copy constructor copies all essential elements for the class.
	***********************************************************************/
	tihex(const tihex &ihSource)
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
	tihex& operator= (const tihex &ihSource)
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
	tihex& operator++()
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
	const tihex operator++(int)
	{
		tihex tmp(*this);
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
	tihex& operator--()
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
	const tihex operator--(int)
	{
		tihex tmp(*this);
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
			typename map<unsigned long, T>::iterator it \
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
			typename map<unsigned long, T>::iterator it;
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
			typename map<unsigned long, T>::iterator it;

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
			typename map<unsigned long, T>::reverse_iterator rit;

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
	bool getData(T * data)
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
	bool getData(T * data, unsigned long address)
	{
		bool found = false;
		typename map<unsigned long, T>::iterator localIterator;

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
	void fillBlankAddr(T value = 0xffff);
};

/*******************************************************************************
* Converts a 2 char string to its HEX value
*******************************************************************************/
template <class T>
unsigned char tihex<T>::stringToHex(string value)
{
	unsigned char returnValue = 0;
	string::iterator valueIterator;

	if (value.length() == 2)
	{
		valueIterator = value.begin();

		for (int x = 0; x < 2; x++)
		{
			/* Shift result variable 4 bits to the left                       */
			returnValue <<= 4;

			if (*valueIterator >= '0' && *valueIterator <= '9')
			{
				returnValue +=
					static_cast<unsigned char>(*valueIterator - '0');
			}
			else if (*valueIterator >= 'A' && *valueIterator <= 'F')
			{
				returnValue +=
					static_cast<unsigned char>(*valueIterator - 'A' + 10);
			}
			else if (*valueIterator >= 'a' && *valueIterator <= 'f')
			{
				returnValue +=
					static_cast<unsigned char>(*valueIterator - 'a' + 10);
			}
			else
			{
				/* Error occured - non-HEX value found                        */
				string message;

				message = "Can't convert byte 0x" + value + " @ 0x" +
					ulToHexString(segmentBaseAddress) + " to hex.";

				addError(message);

				returnValue = 0;
			}

			/* Iterate to next char in the string                             */
			++valueIterator;
		}
	}
	else
	{
		/* Error occured - more or less than two nibbles in the string        */
		string message;

		message = value + " @ 0x" + ulToHexString(segmentBaseAddress) +
			" isn't an 8-bit value.";

		addError(message);
	}

	return returnValue;
}
/*******************************************************************************
* Converts a 2 char string to its HEX value
*******************************************************************************/
template <class T>
unsigned short tihex<T>::stringToHex4CHAR(string value){
	unsigned short returnValue = 0;
	string::iterator valueIterator;

	if (value.length() == 4)
	{
		valueIterator = value.begin();

		for (int x = 0; x < 4; x++)
		{
			/* Shift result variable 4 bits to the left                       */
			returnValue <<= 4;

			if (*valueIterator >= '0' && *valueIterator <= '9')
			{
				returnValue +=
					static_cast<unsigned char>(*valueIterator - '0');
			}
			else if (*valueIterator >= 'A' && *valueIterator <= 'F')
			{
				returnValue +=
					static_cast<unsigned char>(*valueIterator - 'A' + 10);
			}
			else if (*valueIterator >= 'a' && *valueIterator <= 'f')
			{
				returnValue +=
					static_cast<unsigned char>(*valueIterator - 'a' + 10);
			}
			else
			{
				/* Error occured - non-HEX value found                        */
				string message;

				message = "Can't convert byte 0x" + value + " @ 0x" +
					ulToHexString(segmentBaseAddress) + " to hex.";

				addError(message);

				returnValue = 0;
			}

			/* Iterate to next char in the string                             */
			++valueIterator;
		}
	}
	else
	{
		/* Error occured - more or less than two nibbles in the string        */
		string message;

		message = value + " @ 0x" + ulToHexString(segmentBaseAddress) +
			" isn't an 16-bit value.";

		addError(message);
	}

	//cout << "returnValue = 0x" << hex << setw(4) << returnValue << endl;
	//cout << dec;

	return returnValue;
}
/*******************************************************************************
* Converts an unsigned long to a string in HEX format
*******************************************************************************/
template <class T>
string tihex<T>::ulToHexString(unsigned long value)
{
	string returnString;
	char localString[50];

	returnString.erase();

#ifdef _MSC_FULL_VER
	sprintf_s(localString, 49, "%08lX", value);
#else
	snprintf(localString, 49, "%08lX", value);
#endif

	returnString.insert(0, localString);

	return returnString;
}

/*******************************************************************************
* Converts an unsigned long to a string in DEC format
*******************************************************************************/
template <class T>
string tihex<T>::ulToString(unsigned long value)
{
	string returnString;
	char localString[50];

	returnString.erase();

#ifdef _MSC_FULL_VER
	sprintf_s(localString, 49, "%lu", value);
#else
	snprintf(localString, 49, "%lu", value);
#endif
	returnString.insert(0, localString);

	return returnString;
}

/*******************************************************************************
* Converts an unsigned short to a string in HEX format
*******************************************************************************/
template <class T>
string tihex<T>::usToHexString(unsigned short value)
{
	string returnString;
	char localString[50];

	returnString.erase();

#ifdef _MSC_FULL_VER
	sprintf_s(localString, 49, "%04X", value);
#else
	snprintf(localString, 49, "%04X", value);
#endif

	returnString.insert(0, localString);

	return returnString;

}

/*******************************************************************************
* Converts an unsigned char to a string in HEX format
*******************************************************************************/
template <class T>
string tihex<T>::ucToHexString(unsigned char value)
{
	string returnString;
	char localString[50];

	returnString.erase();

#ifdef _MSC_FULL_VER
	sprintf_s(localString, 49, "%02X", value);
#else
	snprintf(localString, 49, "%02X", value);
#endif

	returnString.insert(0, localString);

	return returnString;
}

/*******************************************************************************
* Adds a warning to the list of warning messages
*******************************************************************************/
template <class T>
void tihex<T>::addWarning(string warningMessage)
{
	string localMessage;

	/* Build the message and push the warning message onto the list           */
	localMessage += ulToString(msgWarning.noOfWarnings + 1) + " Warning: "
		+ warningMessage;

	msgWarning.ihWarnings.push_back(localMessage);

	/* Update the number of warning messages                                  */
	msgWarning.noOfWarnings = msgWarning.ihWarnings.size();
}

/*******************************************************************************
* Adds an error to the list of error messages
*******************************************************************************/
template <class T>
void tihex<T>::addError(string errorMessage)
{
	string localMessage;

	/* Build the message and push the error message onto the list             */
	localMessage += ulToString(msgError.noOfErrors + 1) + " Error: "
		+ errorMessage;

	msgError.ihErrors.push_back(localMessage);

	/* Update the number of error messages                                    */
	msgError.noOfErrors = msgError.ihErrors.size();
}

/*******************************************************************************
* Decodes a data record read in from a file
*******************************************************************************/
template <class T>
void tihex<T>::decodeDataRecord(unsigned char recordLength,//(Byte Count)
	unsigned long loadOffset,//(Address)
	string::const_iterator data)
{
	/* Variable to store a byte of the record as a two char string            */
	string sByteRead;

	/* Variable to store the byte of the record as an u.char                  */
	T byteRead;

	/* Calculate new SBA by clearing the low four bytes and then adding the   */
	/* current loadOffset for this line of Intel HEX data                     */
	segmentBaseAddress &= ~(0xFFFFUL);
	segmentBaseAddress += loadOffset;

	//cout << "=== segmentBaseAddress = 0x" << hex << setw(8) << setfill('0') << segmentBaseAddress << " ===" << endl;
	//cout << "=== recordLength = 0x" << hex << setw(4) << setfill('0') << (unsigned int)recordLength << " ===" << endl;
	//cout << dec;

	for (unsigned char x = 0; x < recordLength; x += sizeof(T))// Parse Data Field
	{
		sByteRead.erase();

		sByteRead = *data;
		data++;
		sByteRead += *data;
		data++;
                if(typeid(T) == typeid(unsigned short)){// If 2 bytes length data
		    sByteRead += *data;
		    data++;
		    sByteRead += *data;
		    data++;
                }

                if(typeid(T) == typeid(unsigned char)){
		    byteRead = stringToHex(sByteRead);
		}
                else if(typeid(T) == typeid(unsigned short)){
		    byteRead = stringToHex4CHAR(sByteRead);
                }

		ihReturn = ihContent.insert(
			pair<int, T>(segmentBaseAddress, byteRead));

		if (ihReturn.second == false)
		{
			/* If this address already contains the byte we are trying to     */
			/* write, this is only a warning                                  */
			if (ihReturn.first->second == byteRead)
			{
				string message;

				message = "Location 0x" + ulToHexString(segmentBaseAddress) +
					" already contains data 0x" + sByteRead;

				addWarning(message);
			}
			/* Otherwise this is an error                                     */
			else
			{
				string message;


				if(typeid(T) == typeid(unsigned char)){
					message = "Couldn't add 0x" + sByteRead + " @ 0x" +
						ulToHexString(segmentBaseAddress) +
						"; already contains 0x" +
						ucToHexString(ihReturn.first->second);

				}else if(typeid(T) == typeid(unsigned short)){
					message = "Couldn't add 0x" + sByteRead + " @ 0x" +
						ulToHexString(segmentBaseAddress) +
						"; already contains 0x" +
						usToHexString(ihReturn.first->second);

				}
				addError(message);
			}
		}

		/* Increment the segment base address                                 */
		++segmentBaseAddress;
	}
}

#define TI_HEX_FORMAT_SEGMENT_BASE_START_ADDRESS  0x3f0000
/*******************************************************************************
* Input Stream for Intel HEX File Decoding (friend function)
*******************************************************************************/
template <class T>
istream& operator>>(istream& dataIn, tihex<T>& ihLocal)
{
	// Create a string to store lines of Intel Hex info
	string ihLine;
	/* Create a string to store a single byte of Intel HEX info               */
	string ihByte;
	// Create an iterator for this variable
	string::iterator ihLineIterator;
	// Create a line counter
	unsigned long lineCounter = 0;
        // Byte Read
        T byteRead;

#if 0
        if(typeid(T) == typeid(unsigned char)){
	    // Variable to hold a single byte (two chars) of data
	    unsigned char byteRead;
	}else if(typeid(T) == typeid(unsigned short)){
	    // Variable to hold a 2 byte (two chars) of data
	    unsigned short byteRead;
        }
#endif

	// Variable to calculate the checksum for each line
	unsigned char intelHexChecksum;
	// Variable to hold the record length
	unsigned char recordLength;
	// Variable to hold the load offset
	unsigned long loadOffset;
	// Variables to hold the record type
	TIhexRecordType recordType;
	// Variables to check TI HEX format segment base address
	bool bHasTIHEXFormatSegmentBaseAddress = false;

	do
	{
		/* Clear the string before this next round                            */
		ihLine.erase();

		/* Clear the checksum before processing this line                     */
		intelHexChecksum = 0;

		/* Get a line of data                                                 */
		dataIn >> ihLine;

		/* If the line contained some data, process it                        */
		if (ihLine.length() > 0)
		{
			/* Increment line counter                                         */
			lineCounter++;

			/* Set string iterator to start of string                         */
			ihLineIterator = ihLine.begin();

			/* Check that we have a ':' record mark at the beginning          */
			if (*ihLineIterator != ':')
			{
				/* Add some warning code here                                 */
				string message;

				message = "Line without record mark ':' found @ line " +
					ihLocal.ulToString(lineCounter);

				ihLocal.addWarning(message);

				/* If this is the first line, let's simply give up. Chances   */
				/* are this is not an Intel HEX file at all                   */
				if (lineCounter == 1)
				{
					message = "Intel HEX File decode aborted; ':' missing in " \
						"first line.";
					ihLocal.addError(message);

					/* Erase ihLine content and break out of do...while loop  */
					ihLine.erase();
					break;
				}
			}
			else
			{
				/* Remove the record mark from the string as we don't need it */
				/* anymore                                                    */
				ihLine.erase(ihLineIterator);
			}

			/* Run through the whole line to check the checksum               */
			for (ihLineIterator = ihLine.begin();
				ihLineIterator != ihLine.end();
				/* Nothing - really! */)
			{
				/* Convert the line in pair of chars (making a single byte)   */
				/* into single bytes, and then add to the checksum variable.  */
				/* By adding all the bytes in a line together *including* the */
				/* checksum byte, we should get a result of '0' at the end.   */
				/* If not, there is a checksum error                          */
				ihByte.erase();

				ihByte = *ihLineIterator;
				++ihLineIterator;
				/* Just in case there are an odd number of chars in the       */
				/* just check we didn't reach the end of the string early     */
				if (ihLineIterator != ihLine.end())
				{
					ihByte += *ihLineIterator;
					++ihLineIterator;

					byteRead = ihLocal.stringToHex(ihByte);

					intelHexChecksum += byteRead;
				}
				else
				{
					string message;

					message = "Odd number of characters in line " +
						ihLocal.ulToString(lineCounter);

					ihLocal.addError(message);
				}
			}

			/* Make sure the checksum was ok                                  */
			if (intelHexChecksum == 0)
			{
				/* Reset iterator back to beginning of the line so we can now */
				/* decode it                                                  */
				ihLineIterator = ihLine.begin();

				/* Clear all the variables associated with decoding a line of */
				/* Intel HEX code.                                            */
				recordLength = 0;
				loadOffset = 0;

				/* Get the record length                                      */
				ihByte.erase();
				ihByte = *ihLineIterator;
				++ihLineIterator;
				ihByte += *ihLineIterator;
				++ihLineIterator;
				recordLength = ihLocal.stringToHex(ihByte);

				/* Get the load offset (2 bytes)(Address)                      */
				ihByte.erase();
				ihByte = *ihLineIterator;
				++ihLineIterator;
				ihByte += *ihLineIterator;
				++ihLineIterator;
				loadOffset =
					static_cast<unsigned long>(ihLocal.stringToHex(ihByte));
				loadOffset <<= 8;
				ihByte.erase();
				ihByte = *ihLineIterator;
				++ihLineIterator;
				ihByte += *ihLineIterator;
				++ihLineIterator;
				loadOffset +=
					static_cast<unsigned long>(ihLocal.stringToHex(ihByte));

				/* Get the record type                                        */
				ihByte.erase();
				ihByte = *ihLineIterator;
				++ihLineIterator;
				ihByte += *ihLineIterator;
				++ihLineIterator;
				recordType =
					static_cast<TIhexRecordType>(ihLocal.stringToHex(ihByte));

				/* Decode the INFO or DATA portion of the record              */
				switch (recordType)
				{
				case DATA_RECORD:

					ihLocal.decodeDataRecord(recordLength, loadOffset,
						ihLineIterator);
					if (ihLocal.verbose == true)
					{
						cout << "Data Record begining @ 0x" <<
							ihLocal.ulToHexString(loadOffset) << endl;
					}
					break;

				case END_OF_FILE_RECORD:
					/* Check that the EOF record wasn't already found. If */
					/* it was, generate appropriate error                 */
					if (ihLocal.foundEof == false)
					{
						ihLocal.foundEof = true;
					}
					else
					{
						string message;

						message = "Additional End Of File record @ line " +
							ihLocal.ulToString(lineCounter) +
							" found.";

						ihLocal.addError(message);
					}
					/* Generate error if there were                       */
					if (ihLocal.verbose == true)
					{
						cout << "End of File" << endl;
					}
					break;

				case EXTENDED_SEGMENT_ADDRESS:
					/* Make sure we have 2 bytes of data                  */
					if (recordLength == 2)
					{
						/* Extract the two bytes of the ESA               */
						unsigned long extSegAddress = 0;

						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						extSegAddress = static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
						extSegAddress <<= 8;
						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						extSegAddress += static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));

						/* ESA is bits 4-19 of the segment base address   */
						/* (SBA), so shift left 4 bits                    */
						extSegAddress <<= 4;

						/* Update the SBA                                 */
						ihLocal.segmentBaseAddress = extSegAddress;
					}
					else
					{
						/* Note the error                                 */
						string message;

						message = "Extended Segment Address @ line " +
							ihLocal.ulToString(lineCounter) +
							" not 2 bytes as required.";

						ihLocal.addError(message);
					}
					if (ihLocal.verbose == true)
					{
						cout << "Ext. Seg. Address found: 0x" <<
							ihLocal.ulToHexString(ihLocal.segmentBaseAddress)
							<< endl;
					}

					break;

				case START_SEGMENT_ADDRESS:
					/* Make sure we have 4 bytes of data, and that no     */
					/* Start Segment Address has been found to date       */
					if (recordLength == 4 &&
						ihLocal.startSegmentAddress.exists == false)
					{
						/* Note that the Start Segment Address has been   */
						/* found.                                         */
						ihLocal.startSegmentAddress.exists = true;
						/* Clear the two registers, just in case          */
						ihLocal.startSegmentAddress.csRegister = 0;
						ihLocal.startSegmentAddress.ipRegister = 0;

						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startSegmentAddress.csRegister =
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
						ihLocal.startSegmentAddress.csRegister <<= 8;
						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startSegmentAddress.csRegister +=
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));

						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startSegmentAddress.ipRegister =
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
						ihLocal.startSegmentAddress.ipRegister <<= 8;
						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startSegmentAddress.ipRegister +=
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
					}
					/* Note an error if the start seg. address already    */
					/* exists                                             */
					else if (ihLocal.startSegmentAddress.exists == true)
					{
						string message;

						message = "Start Segment Address record appears again @ line " +
							ihLocal.ulToString(lineCounter) +
							"; repeated record ignored.";

						ihLocal.addError(message);
					}
					/* Note an error if the start lin. address already    */
					/* exists as they should be mutually exclusive        */
					if (ihLocal.startLinearAddress.exists == true)
					{
						string message;

						message = "Start Segment Address record found @ line " +
							ihLocal.ulToString(lineCounter) +
							" but Start Linear Address already exists.";

						ihLocal.addError(message);
					}
					/* Note an error if the record lenght is not 4 as     */
					/* expected                                           */
					if (recordLength != 4)
					{
						string message;

						message = "Start Segment Address @ line " +
							ihLocal.ulToString(lineCounter) +
							" not 4 bytes as required.";

						ihLocal.addError(message);
					}
					if (ihLocal.verbose == true)
					{
						cout << "Start Seg. Address - CS 0x" <<
							ihLocal.ulToHexString(ihLocal.startSegmentAddress.csRegister) <<
							" IP 0x" <<
							ihLocal.ulToHexString(ihLocal.startSegmentAddress.ipRegister)
							<< endl;
					}
					break;

				case EXTENDED_LINEAR_ADDRESS:
					/* Make sure we have 2 bytes of data                  */
					if (recordLength == 2)
					{
						/* Extract the two bytes of the ELA               */
						unsigned long extLinAddress = 0;

						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						extLinAddress = static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
						extLinAddress <<= 8;
						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						extLinAddress += static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));

						/* ELA is bits 16-31 of the segment base address  */
						/* (SBA), so shift left 16 bits                   */
						extLinAddress <<= 16;

						/* Update the SBA                                 */
						ihLocal.segmentBaseAddress = extLinAddress;

						if (ihLocal.segmentBaseAddress == TI_HEX_FORMAT_SEGMENT_BASE_START_ADDRESS){
							bHasTIHEXFormatSegmentBaseAddress = true;
						}

					}
					else
					{
						/* Note the error                                 */
						//cout << "Error in Ext. Lin. Address" << endl;

						string message;

						message = "Extended Linear Address @ line " +
							ihLocal.ulToString(lineCounter) +
							" not 2 bytes as required.";

						ihLocal.addError(message);
					}
					if (ihLocal.verbose == true)
					{
						cout << "Ext. Lin. Address 0x" <<
							ihLocal.ulToHexString(ihLocal.segmentBaseAddress)
							<< endl;
					}

					break;

				case START_LINEAR_ADDRESS:
					/* Make sure we have 4 bytes of data                  */
					if (recordLength == 4 &&
						ihLocal.startLinearAddress.exists == false)
					{
						/* Extract the four bytes of the SLA              */
						ihLocal.startLinearAddress.eipRegister = 0;

						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startLinearAddress.eipRegister =
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
						ihLocal.startLinearAddress.eipRegister <<= 8;
						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startLinearAddress.eipRegister +=
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
						ihLocal.startLinearAddress.eipRegister <<= 8;
						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startLinearAddress.eipRegister +=
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
						ihLocal.startLinearAddress.eipRegister <<= 8;
						ihByte.erase();
						ihByte = *ihLineIterator;
						++ihLineIterator;
						ihByte += *ihLineIterator;
						++ihLineIterator;
						ihLocal.startLinearAddress.eipRegister +=
							static_cast<unsigned long>
							(ihLocal.stringToHex(ihByte));
					}
					/* Note an error if the start seg. address already    */
					/* exists                                             */
					else if (ihLocal.startLinearAddress.exists == true)
					{
						string message;

						message = "Start Linear Address record appears again @ line " +
							ihLocal.ulToString(lineCounter) +
							"; repeated record ignored.";

						ihLocal.addError(message);
					}
					/* Note an error if the start seg. address already    */
					/* exists as they should be mutually exclusive        */
					if (ihLocal.startSegmentAddress.exists == true)
					{
						string message;

						message = "Start Linear Address record found @ line " +
							ihLocal.ulToString(lineCounter) +
							" but Start Segment Address already exists.";

						ihLocal.addError(message);
					}
					/* Note an error if the record lenght is not 4 as     */
					/* expected                                           */
					if (recordLength != 4)
					{
						string message;

						message = "Start Linear Address @ line " +
							ihLocal.ulToString(lineCounter) +
							" not 4 bytes as required.";

						ihLocal.addError(message);
					}
					if (ihLocal.verbose == true)
					{
						cout << "Start Lin. Address - EIP 0x" <<
							ihLocal.ulToHexString(ihLocal.startLinearAddress.eipRegister)
							<< endl;
					}
					break;

				default:
					/* Handle the error here                              */
					if (ihLocal.verbose == true)
					{
						cout << "Unknown Record @ line " <<
							ihLocal.ulToString(lineCounter) << endl;
					}


					string message;

					message = "Unknown Intel HEX record @ line " +
						ihLocal.ulToString(lineCounter);

					ihLocal.addError(message);

					break;
				}
			}
			else
			{
				/* Note that the checksum contained an error                  */
				string message;

				message = "Checksum error @ line " +
					ihLocal.ulToString(lineCounter) +
					"; calculated 0x" +
					ihLocal.ucToHexString(intelHexChecksum - byteRead) +
					" expected 0x" +
					ihLocal.ucToHexString((unsigned char)byteRead);

				ihLocal.addError(message);
			}
		}
	} while (ihLine.length() > 0);


	if (bHasTIHEXFormatSegmentBaseAddress == false){
		string message;

		message = "No Segment Base Address Start From " + ihLocal.ulToHexString(TI_HEX_FORMAT_SEGMENT_BASE_START_ADDRESS);
		//ihLocal.addError(message);
	}

	if (ihLocal.verbose == true)
	{
		cout << "Decoded " << lineCounter << " lines from file." << endl;
	}

	return(dataIn);
}

/*******************************************************************************
* Output Stream for Intel HEX File Encoding (friend function)
*******************************************************************************/
template <class T>
ostream& operator<<(ostream& dataOut, tihex<T>& ihLocal)
{
	/* Stores the address offset needed by the linear/segment address records */
	unsigned long addressOffset;
	/* Iterator into the ihContent - where the addresses & data are stored    */
	typename map<unsigned long, T>::iterator ihIterator;
	/* Holds string that represents next record to be written                 */
	string thisRecord;
	/* Checksum calculation variable                                          */
	unsigned char checksum;

	thisRecord.clear();

	/* Check that there is some content to encode */
	if (ihLocal.ihContent.size() > 0)
	{
		/* Calculate the Linear/Segment address                               */
		ihIterator = ihLocal.ihContent.begin();
		addressOffset = (*ihIterator).first;
		checksum = 0;

		/* Construct the first record to define the segment base address      */
		if (ihLocal.segmentAddressMode == false)
		{
			unsigned char dataByte;

			addressOffset >>= 16;// 003F4000 >> 16

			thisRecord = ":02000004";
			checksum = 0x02 + 0x04;

			// cout << "addressOffset=" << hex << setw(8) << setfill('0') << addressOffset << endl;
			// 003F

			if(typeid(T) == typeid(unsigned char)){
			    dataByte = static_cast<unsigned char>(addressOffset & 0xFF);
			    checksum += dataByte;
			    thisRecord += ihLocal.ucToHexString(dataByte);

			    dataByte = static_cast<unsigned char>((addressOffset >> 8) & 0xFF);
			    checksum += dataByte;
			    thisRecord += ihLocal.ucToHexString(dataByte);
			}else if(typeid(T) == typeid(unsigned short)){
			    dataByte = static_cast<unsigned char>((addressOffset >> 8) & 0xFF);// 00
			    checksum += dataByte;
			    thisRecord += ihLocal.ucToHexString(dataByte);

			    dataByte = static_cast<unsigned char>(addressOffset & 0xFF);// 3F
			    checksum += dataByte;
			    thisRecord += ihLocal.ucToHexString(dataByte);
			}


			thisRecord += ihLocal.ucToHexString(0x00 - (checksum & 0xFF));
		}
		else
		{
			unsigned char dataByte;

			addressOffset >>= 4;

			thisRecord = ":02000002";
			checksum = 0x02 + 0x02;

			dataByte = static_cast<unsigned char>(addressOffset & 0xFF);
			checksum += dataByte;
			thisRecord += ihLocal.ucToHexString(dataByte);

			dataByte = static_cast<unsigned char>((addressOffset >> 8) & 0xFF);
			checksum += dataByte;
			thisRecord += ihLocal.ucToHexString(dataByte);

			thisRecord += ihLocal.ucToHexString(0x00 - (checksum & 0xFF));
		}

		/* Output the record                                                  */
		dataOut << thisRecord << endl;

		/* Now loop through all the available data and insert into file       */
		/* with maximum 16 bytes per line, and making sure to keep the        */
		/* segment base address up to date                                    */
		vector<T> recordData;
		unsigned long previousAddress;
		unsigned long currentAddress;
		unsigned long loadOffset;

		while (ihIterator != ihLocal.ihContent.end())
		{
			/* Check to see if we need to start a new linear/segment section  */
			loadOffset = (*ihIterator).first;

			/* If we are using the linear mode...                             */
			if (ihLocal.segmentAddressMode == false)
			{
				if ((loadOffset >> 16) != addressOffset)
				{
					unsigned char dataByte;

					thisRecord.clear();
					checksum = 0;

					addressOffset = loadOffset;
					addressOffset >>= 16;

					thisRecord = ":02000004";
					checksum = 0x02 + 0x04;

					dataByte = static_cast<unsigned char>(addressOffset & 0xFF);
					checksum += dataByte;
					thisRecord += ihLocal.ucToHexString(dataByte);

					dataByte = static_cast<unsigned char>((addressOffset >> 8) & 0xFF);
					checksum += dataByte;
					thisRecord += ihLocal.ucToHexString(dataByte);

					thisRecord += ihLocal.ucToHexString(0x00 - (checksum & 0xFF));

					/* Output the record                                      */
					dataOut << thisRecord << endl;
				}
			}
			/* ...otherwise assume segment mode                               */
			else
			{
				if ((loadOffset >> 4) != addressOffset)
				{
					unsigned char dataByte;

					thisRecord.clear();
					checksum = 0;

					addressOffset = loadOffset;
					addressOffset >>= 4;

					thisRecord = ":02000002";
					checksum = 0x02 + 0x02;

					dataByte = static_cast<unsigned char>(addressOffset & 0xFF);
					checksum += dataByte;
					thisRecord += ihLocal.ucToHexString(dataByte);

					dataByte = static_cast<unsigned char>((addressOffset >> 8) & 0xFF);
					checksum += dataByte;
					thisRecord += ihLocal.ucToHexString(dataByte);

					thisRecord += ihLocal.ucToHexString(0x00 - (checksum & 0xFF));

					/* Output the record                                      */
					dataOut << thisRecord << endl;
				}
			}

			/* Prepare for encoding next data record                          */
			thisRecord.clear();
			checksum = 0;
			recordData.clear();

			/* We need to check where the data actually starts, but only the  */
			/* bottom 16-bits; the other bits are in the segment/linear       */
			/* address record                                                 */
			loadOffset = (*ihIterator).first & 0xFFFF;

			/* Loop through and collect up to 16 bytes of data                */
			for (int x = 0; x < 16; x++)
			{
				currentAddress = (*ihIterator).first & 0xFFFF;

				recordData.push_back((*ihIterator).second);

				ihIterator++;

				/* Check that we haven't run out of data                      */
				if (ihIterator == ihLocal.ihContent.end())
				{
					break;
				}

				/* Check that the next address is consecutive                 */
				previousAddress = currentAddress;
				currentAddress = (*ihIterator).first & 0xFFFF;
				if (currentAddress != (previousAddress + 1))
				{
					break;
				}

				/* If we got here we have a consecutive address and can keep  */
				/* building up the data portion of the data record            */
			}

			/* Now we should have some data to encode; check first            */
			if (recordData.size() > 0)
			{
				typename vector<T>::iterator itData;
				T dataByte;

				/* Start building data record                                 */
				thisRecord = ":";

				/* Start with the RECLEN record length                        */
                                if(typeid(T) == typeid(unsigned char)){
			            dataByte = static_cast<unsigned char>(recordData.size());
				}
				else if(typeid(T) == typeid(unsigned short)){
				    dataByte = static_cast<unsigned char>(recordData.size() * 2);
				}
				thisRecord += ihLocal.ucToHexString((unsigned char)dataByte);
				checksum += dataByte;

				/* Then the LOAD OFFSET                                       */
				dataByte = static_cast<unsigned char>((loadOffset >> 8) & 0xFF);
				thisRecord += ihLocal.ucToHexString((unsigned char)dataByte);
				checksum += dataByte;
				dataByte = static_cast<unsigned char>(loadOffset & 0xFF);
				thisRecord += ihLocal.ucToHexString((unsigned char)dataByte);
				checksum += dataByte;

				/* Then the RECTYP record type (no need to add to checksum -  */
				/* value is zero '00'                                         */
				thisRecord += "00";

				/* Now we add the data                                        */
				for (itData = recordData.begin(); itData != recordData.end(); itData++)
				{
					dataByte = (*itData);
					checksum += dataByte;
                                        if(typeid(T) == typeid(unsigned char)){
					    thisRecord += ihLocal.ucToHexString(dataByte);
					}else if(typeid(T) == typeid(unsigned short)){
					    checksum += (dataByte >> 8);
					    thisRecord += ihLocal.usToHexString(dataByte);
					}
				}

				/* Last bit - add the checksum                                */
				thisRecord += ihLocal.ucToHexString(0x00 - (checksum & 0xFF));

				/* Now write the record                                       */
				dataOut << thisRecord << endl;
			}
		}
	}

	/* If there is a segment start address, output the data                   */
	if (ihLocal.startSegmentAddress.exists == true)
	{
		unsigned char dataByte;

		thisRecord.clear();
		checksum = 0;

		thisRecord = ":04000003";
		checksum = 0x04 + 0x03;

		dataByte = static_cast<unsigned char>((ihLocal.startSegmentAddress.csRegister >> 8) & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);

		dataByte = static_cast<unsigned char>(ihLocal.startSegmentAddress.csRegister & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);

		dataByte = static_cast<unsigned char>((ihLocal.startSegmentAddress.ipRegister >> 8) & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);

		dataByte = static_cast<unsigned char>(ihLocal.startSegmentAddress.ipRegister & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);


		/* Last bit - add the checksum                                        */
		thisRecord += ihLocal.ucToHexString(0x00 - (checksum & 0xFF));

		/* Now write the record                                               */
		dataOut << thisRecord << endl;
	}

	/* If there is a linear start address, output the data                    */
	if (ihLocal.startLinearAddress.exists == true)
	{
		unsigned char dataByte;

		thisRecord.clear();
		checksum = 0;

		thisRecord = ":04000005";
		checksum = 0x04 + 0x05;

		dataByte = static_cast<unsigned char>((ihLocal.startLinearAddress.eipRegister >> 24) & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);

		dataByte = static_cast<unsigned char>((ihLocal.startLinearAddress.eipRegister >> 16) & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);

		dataByte = static_cast<unsigned char>((ihLocal.startLinearAddress.eipRegister >> 8) & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);

		dataByte = static_cast<unsigned char>(ihLocal.startLinearAddress.eipRegister & 0xFF);
		checksum += dataByte;
		thisRecord += ihLocal.ucToHexString(dataByte);


		/* Last bit - add the checksum                                        */
		thisRecord += ihLocal.ucToHexString(0x00 - (checksum & 0xFF));

		/* Now write the record                                               */
		dataOut << thisRecord << endl;
	}

	/* Whatever happened, we can always output the EOF record                 */
	dataOut << ":00000001FF" << endl;

	return (dataOut);
}

//#define FORCE_ADDRESS_START_FROM_003F4000
//#define FIXED_START_ADDRESS 0x003f4000
#define ADDR_ALIGN_XXXF
/*******************************************************************************
* Fill Blank Address with value
*******************************************************************************/
template <class T>
void tihex<T>::fillBlankAddr(T value){
	bool foundEmptyRegion = false;
	unsigned long emptyAddressCount = 0;
	unsigned long emptyRegionStart = 0;
	unsigned long emptyRegionEnd = 0;
	unsigned long previousAddress = 0;
	unsigned long lcurrentAddress = 0;

        // Check Template Type
	if( typeid(T) == typeid(unsigned char) ) {
		std::cout << "Template Type is 'unsigned char'" << std::endl;
                value = (unsigned char)0xff;
	}else if( typeid(T) == typeid(unsigned short) ){
		std::cout << "Template Type is 'unsigned short'" <<std::endl;
                value = (unsigned short)0xffff;
	}

#ifdef FORCE_ADDRESS_START_FROM_003F4000
	// Force Address Start form 0x003f4000
	unsigned long start_Address;
	startAddress(&start_Address);

	if (start_Address != 0x003f4000){
		ihReturn = ihContent.insert(pair<int, T>(FIXED_START_ADDRESS, value));
	}

#endif

#ifdef ADDR_ALIGN_XXXF
	// Fill Address To Align XXXF
	unsigned long end_Address;
	endAddress(&end_Address);
	if ((end_Address + 1) % 16 != 0) {
		for (unsigned int idx = 0; idx < 8; idx++){
			end_Address += 1;
			ihReturn = ihContent.insert(pair<int, T>(end_Address, value));
		}
	}
#endif

	// Set ihIterator To Begin
	if (ihContent.size() != 0)
	{
		ihIterator = ihContent.begin();
	}

	previousAddress = currentAddress();

	do
	{
		++ihIterator;

		lcurrentAddress = currentAddress();

		if (lcurrentAddress != (previousAddress + 1UL))
		{
			foundEmptyRegion = true;
			emptyRegionStart = previousAddress + 1UL;
			emptyRegionEnd = lcurrentAddress - 1UL;
			emptyAddressCount = (emptyRegionEnd - emptyRegionStart) + 1UL;

			cout << hex << setw(8) << "emptyRegionStart=" << emptyRegionStart << " , " << "emptyRegionEnd=" << emptyRegionEnd << endl;

			// Insert fill data
			for (unsigned long addr = emptyRegionStart; addr <= emptyRegionEnd; addr++){
				ihReturn = ihContent.insert(pair<int, T>(addr, value));
			}

		}

		previousAddress = lcurrentAddress;


	} while (!endOfData());


}
#endif
