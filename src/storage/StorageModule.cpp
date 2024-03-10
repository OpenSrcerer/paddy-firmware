#include "StorageModule.hpp"
#include <FlashStorage_SAMD.h> // Not in the .hpp because this library is quirky

// Note: the area of flash memory reserved for the variable is
// lost every time the sketch is uploaded on the board.
namespace paddy
{

// Checks if the first 4 chars saved in
// Emulated EEPROM are digits. If not,
// no JWT was saved
bool StorageModule::hasJwt()
{
	// Read the stored length of the JWT.
	String jwtLength;
	read(jwtLength, 0, 4);

	const char* length = jwtLength.c_str();
	for (int i = 0; i < jwtLength.length(); ++i)
	{
		if(!isdigit(length[i]))
		{
			return false;
		}
	}

	return true;
}

const char* StorageModule::readJwt()
{
	// If in-memory JWT is already stored
	if (memoryJwt.length() != 0) {
		return memoryJwt.c_str();
	}

	// First read the length of the jwt (read the first 4 chars in EEPROM)
	String jwtLength;
	read(jwtLength, 0, 4);

	// Then read the actual jwt using the length
	String jwt;
	read(jwt, 4, 4 + jwtLength.toInt());

	memoryJwt = String(jwt);
	return memoryJwt.c_str();
}

void StorageModule::writeJwt(const char *jwt)
{
	// write the size in the first 4 chars of the EEPROM
	String jwtSize = String(strlen(jwt));
	padUntilLength(jwtSize, 4);
	write(jwtSize.c_str(), 4, 0);

	// Then write the actual JWT
	write(jwt, strlen(jwt), 4);

	memoryJwt = String(jwt);

	Serial.println("[StorageModule] Done writing JWT.");
}

void StorageModule::padUntilLength(String &string, int length)
{
	int paddingLength = length - string.length();
	for (int i = 0; i < paddingLength; i++)
	{
		string = String('0') + string;
	}
}

void StorageModule::read(String &outStr, uint16_t startAddress, uint16_t endAddress)
{
	// Read the content of emulated-EEPROM
	int i = startAddress;
	do
	{
		outStr = outStr + String((char)EEPROM.read(i));
		i++;
	} while (i < endAddress);

	Serial.print("[StorageModule] Read (");
	Serial.print(outStr.length());
	Serial.print(" chars) ... <");
	Serial.print(outStr);
	Serial.println(">");
}

void StorageModule::write(const char *value, size_t length, uint16_t startAddress)
{
	Serial.print("[StorageModule] Writing (");
	Serial.print(length);
	Serial.print(" chars) ... <");
	for (int i = 0; i < length; ++i)
	{
		Serial.print(value[i]);
		EEPROM.put(startAddress + i, value[i]);
	}
	Serial.println(">");

	if (!EEPROM.getCommitASAP())
	{
		Serial.println("CommitASAP not set. Need commit()");
		EEPROM.commit();
	}
}

StorageModule &StorageModule::getInstance()
{
	static StorageModule singleton;
	return singleton;
}

}