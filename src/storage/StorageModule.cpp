/******************************************************************************************************************************************
  FlashStoreAndRetrieve.ino
  For SAMD21/SAMD51 using Flash emulated-EEPROM

  The FlashStorage_SAMD library aims to provide a convenient way to store and retrieve user's data using the non-volatile flash memory
  of SAMD21/SAMD51. It now supports writing and reading the whole object, not just byte-and-byte.

  Based on and modified from Cristian Maglie's FlashStorage (https://github.com/cmaglie/FlashStorage)

  Built by Khoi Hoang https://github.com/khoih-prog/FlashStorage_SAMD
  Licensed under LGPLv3 license

  Orginally written by A. Christian

  Copyright (c) 2015-2016 Arduino LLC.  All right reserved.
  Copyright (c) 2020 Khoi Hoang.

  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
  as published bythe Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public License along with this library.
  If not, see (https://www.gnu.org/licenses/)
 ******************************************************************************************************************************************/


// Note: the area of flash memory reserved for the variable is
// lost every time the sketch is uploaded on the board.
// Define your new string here:
const char myString[] = "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCIsImtpZCI6IjEifQ.eyJzdWIiOiIxMjM0NSIsImlzcyI6Imh0dHBzOi8vZGFuaWVsc3RlZmFuaS5vbmxpbmUiLCJpYXQiOjE3MDc4NTM5NzcsImV4cCI6MTczOTM5Mzk3NywiYXVkIjoiUGFkZHlNUVRUQnJva2VyQ2xpZW50cyJ9.hAqm8QbomTDMT05tZuaZAruaK91FIhkFhXQhpLG3KhWsCWXoDggyAICQngQYjox2nPETPEzsWOsUdXKOWvU0nyzMA_Bkno1y1WKOq1_IiaqUMzJthIBMQLG-ltgYsXQZ_r_U-o-j01qVGbUY5WZ-PZxoQg0WtvC8zJ-NeTZQv6amZD0Rt3dic0ijyxHOkbNnvNmZkDM5quNSHklp1YjrOKm6cyRQofekxUOQJ-2t_2LnMz0xRMGuETZlNaeqqZDYV_3ACkm0I8KXzH4WgrKjhurnBwBWJS6R5yXby94lZUC9aUmsFxC1ziprDGGK8kY4OF_6gjXzGChsTy4hTluft8gNrW6FVaOnWImEadXp19ux6IFPB8r4MNiDCvbYySefanuSVfnvw_HzG70LazuNSAaZuQ5KDcC501lQ_6YhzwSVuDokeQLAnRIqcljrd8yMNy-BspTQMQWvF9_AIX18NeSk6odykURKIGoARs7Q-3BB2X3u4ClXcf0Kk8m6-cQityfitTNZQCEC7rAKorgNYek7QHWz53uI2YQwiM_fVW6koXe8eq1Xd8J4c0GfpiX00ogy_Jp2pF8lSJr-HRx7pU0pImGtQLsY_zllcYNO1bEVoEvqDmiYW22bcCKJ3VW70t9ALdKXdDsERtLjYhkZGWpk9SGrO4jwefPuGesBSbg";
size_t stringLength = strlen(myString);

void setup()
{
	Serial.begin(115200);
	while (!Serial)
		;
	delay(200);

	Serial.print("EEPROM length: ");
	Serial.println(EEPROM.length());

	char storedString[stringLength];
	read(storedString);

	if (storedString[0] == 'e')
	{
		Serial.print("Stored string (");
		Serial.print(stringLength);
		Serial.print(" chars)... <");
		for (int i = 0; i < stringLength; i++)
		{
			Serial.print(storedString[i]);
		}
		Serial.println(">");

		while (1)
			;
	}

	write();
}

char *read(char *outStr)
{
	uint16_t address = 0;

	// Read the content of emulated-EEPROM
	for (int i = 0; i < stringLength; i++)
	{
		outStr[i] = EEPROM.read(address + i);
	}
	Serial.println();
}

void write()
{
	uint16_t address = 0;

	Serial.print("Writing (");
	Serial.print(stringLength);
	Serial.print(" chars) ... <");
	// Save into emulated-EEPROM
	for (int i = 0; i < stringLength; i++)
	{
		Serial.print(myString[i]);
		EEPROM.put(address + i, myString[i]);
	}
	Serial.println(">");

	if (!EEPROM.getCommitASAP())
	{
		Serial.println("CommitASAP not set. Need commit()");
		EEPROM.commit();
	}
	Serial.println("Done writing to EEEPROM.");
}

void loop()
{
	// Do nothing...
}
