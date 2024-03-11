#include "StorageModule.hpp"
#include <FlashStorage_SAMD.h> // Not in the .hpp because this library is quirky

// Note: the area of flash memory reserved for the variable is
// lost every time the sketch is uploaded on the board.
namespace paddy
{

bool StorageModule::hasInsecure()
{
	return (memoryJwt.length() && memorySsid.length()) ||
		   (hasAt(JWT_ADDRESS) && hasAt(SSID_ADDRESS));
}

bool StorageModule::hasPersonal()
{
	bool insecure = hasInsecure();
	return (insecure && memoryPass.length()) ||
		   (insecure && hasAt(PASS_ADDRESS));
}

bool StorageModule::hasEnterprise()
{
	bool insecure = hasInsecure();
	return (insecure && memoryEUsername.length() && memoryEPassword.length()) ||
		   (insecure && hasAt(E_USERNAME_ADDRESS) && hasAt(E_PASSWORD_ADDRESS));
}

// Checks if the first 4 chars saved in
// emulated EEPROM are digits. If not,
// no item was saved at that address
bool StorageModule::hasAt(int at)
{
	String storedLength; // Read the stored length of the variable.
	read(storedLength, at, at + 4);

	return isAddress(storedLength.c_str());
}

bool StorageModule::isAddress(const char* addr)
{
	for (int i = 0; i < strlen(addr); ++i)
	{
		if(!isdigit(addr[i]))
		{
			return false;
		}
	}

	return true;
}

const char* StorageModule::readAt(int at)
{
	// Optimization, if in-memory var is already stored
	// Take directly from memory
	String& memoryVar = getMemoryItemByAddress(at);
	if (memoryVar.length() != 0) {
		return memoryVar.c_str();
	}

	// First read the length of the jwt (read the first 4 chars in EEPROM)
	String storedLength;
	read(storedLength, at, at + 4);

	// Nothing is stored!
	if (!isAddress(storedLength.c_str()))
	{
		// memoryVar = String(); // Cannot use this because of length check above
		return memoryVar.c_str();
	}

	// Then read the actual jwt using the length
	String stored;
	read(stored, at + 4, at + 4 + storedLength.toInt());

	memoryVar = String(stored);
	return memoryVar.c_str();
}

void StorageModule::writeAt(const char* toWrite, int at)
{
	// Ignore empty strings
	if (strlen(toWrite) < 1)
	{
		Serial.println("[StorageModule] Skipping empty write.");
		return;
	}

	// write the size as 4 chars in the EEPROM
	String varSize = String(strlen(toWrite));
	padUntilLength(varSize, 4);
	write(varSize.c_str(), 4, at);

	// Then write the actual var
	write(toWrite, strlen(toWrite), at + 4);

	// Update memory variable
	String& memoryVar = getMemoryItemByAddress(at);
	memoryVar = String(toWrite);

	Serial.println("[StorageModule] Done writing.");
}

void StorageModule::clearAll()
{
	deleteAt(JWT_ADDRESS);
	deleteAt(SSID_ADDRESS);
	deleteAt(PASS_ADDRESS);
	deleteAt(E_USERNAME_ADDRESS);
	deleteAt(E_PASSWORD_ADDRESS);
}

// Just deletes the addresses.
void StorageModule::deleteAt(int at)
{
	String& memoryVar = getMemoryItemByAddress(at);
	memoryVar = String(); // Delete memory copy
	write("xxxx", 4, at); // Delete stored copy
}

String& StorageModule::getMemoryItemByAddress(size_t addr)
{
	switch (addr) {
		case JWT_ADDRESS:
			return memoryJwt;
		case SSID_ADDRESS:
			return memorySsid;
		case PASS_ADDRESS:
			return memoryPass;
		case E_USERNAME_ADDRESS:
			return memoryEUsername;
		case E_PASSWORD_ADDRESS:
			return memoryEPassword;
	}
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
	Serial.print("[StorageModule] Read at address ");
	Serial.print(startAddress);

	// Read the content of emulated-EEPROM
	int i = startAddress;
	do
	{
		outStr = outStr + String((char) EEPROM.read(i));
		i++;
	} while (i < endAddress);

	Serial.print(" (");
	Serial.print(outStr.length());
	Serial.print(" chars) ... <");
	Serial.print(outStr);
	Serial.println(">");
}

void StorageModule::write(const char *value, size_t length, uint16_t startAddress)
{
	Serial.print("[StorageModule] Writing at address ");
	Serial.print(startAddress);
	Serial.print(" (");
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