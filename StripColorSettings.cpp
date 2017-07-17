/*
 * StripColorSettings.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: bzachmann
 */

#include "StripColorSettings.h"
#include "globals.h"

StripColorSettings::StripColorSettings()
{
	clearStates();
	clearBaseValue();
	clearOffsets();

	numLeds = NUM_LEDS;
	brightness = 128;
	tiltEnable = 1;
	patternEnable = 0;
	speedBrightnessEnable = 1;
	saveFlag = false;
	saveTimer = 0;
	patternOnLed = 0;

	//restoreSettings();
}

bool StripColorSettings::setState(uint8_t index, bool state)
{
	bool retVal = false;
	if(index < NUM_LEDS)
	{
		leds[index].state = state;
		retVal = true;
	}
	return retVal;
}

bool StripColorSettings::getState(uint8_t index)
{
	bool retVal = false;
	if(index < NUM_LEDS)
	{
		retVal = leds[index].state;
	}
	return retVal;
}

bool StripColorSettings::setBaseValue(uint16_t value)
{
	baseValue = value;
	return true;
}

uint16_t StripColorSettings::getBaseValue()
{
	return baseValue;
}

bool StripColorSettings::setOffset(uint8_t index, uint16_t value)
{
	bool retVal = false;
	if(index < NUM_LEDS)
	{
		leds[index].offset = value;
		retVal = true;
	}
	return retVal;
}

uint16_t StripColorSettings::getOffset(uint8_t index)
{
	uint16_t retVal = 0xFFFF;
	if(index < NUM_LEDS)
	{
		retVal = leds[index].offset;
	}
	return retVal;
}

bool StripColorSettings::setBrightness(uint8_t value)
{
	brightness = value;
	return true;
}

uint8_t StripColorSettings::getBrightness()
{
	return brightness;
}

bool StripColorSettings::setPatternOnLed(uint8_t value)
{
	bool retVal = false;
	if(value < NUM_LEDS)
	{
		patternOnLed = value;
		retVal = true;
	}
	return retVal;
}

uint8_t StripColorSettings::getPatternOnLed()
{
	return patternOnLed;
}

bool StripColorSettings::setTiltEnable(bool val)
{
	tiltEnable = val;
	return true;
}

bool StripColorSettings::getTiltEnable()
{
	return tiltEnable;
}

bool StripColorSettings::setPatternEnable(bool val)
{
	patternEnable = val;
	return true;
}

bool StripColorSettings::getPatternEnable()
{
	return patternEnable;
}

bool StripColorSettings::setSpeedBrightnessEnable(bool val)
{
	speedBrightnessEnable = val;
	return true;
}

bool StripColorSettings::getSpeedBrightnessEnable()
{
	return speedBrightnessEnable;
}

bool StripColorSettings::setError(errorCause cause, errorType type)
{
	uint8_t ucause = ((uint8_t)cause) & 0x0F;
	uint8_t utype = ((uint8_t)type) & 0x0F;

	for(uint8_t i = 0; i < NUM_LEDS; i++)
	{
		leds[i].offset = 0;
		leds[i].state = 0;
	}
	baseValue = 0;
	brightness = 64;

	if(NUM_LEDS >= 8)
	{
		for(uint8_t i = 0; i < 4; i++)
			{
				leds[i].state = (ucause >> i) & 0x01;
				leds[i + 4].state = (utype >> i) & 0x01;
			}
	}
}


void StripColorSettings::clearStates()
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
		leds[i].state = true;
	}
	return;
}

void StripColorSettings::clearBaseValue()
{
	baseValue = 0;
	return;
}

void StripColorSettings::clearOffsets()
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
		leds[i].offset = 0;
	}
	return;
}

void StripColorSettings::flagForSave()
{
	saveFlag = true;
	saveTimer = 0;
}

bool StripColorSettings::restoreSettings()
{
	//TODO - eeStripSettings in both restor and save methods take up a lot of RAM
	eeStripSettings eeStrip;
	bool retVal = false;

	debugSerial.println(F("--Restoring EEPROM Routine--"));
	debugSerial.println(F("getting EEPROM"));
	EEPROM.get(0,eeStrip);

	//calculate current checksum
	debugSerial.println(F("calculating checksum"));
	uint8_t * eePtr = (uint8_t*)(&eeStrip);
	uint16_t eeBytes = sizeof(eeStrip);
	uint8_t eeChecksum = *eePtr;
	eePtr ++;

	for(uint16_t i = 1; i < eeBytes; i++)
	{
		eeChecksum = eeChecksum ^ *eePtr;
		eePtr++;
	}

	debugSerial.print(F("checksum is: "));
	debugSerial.print(eeChecksum, HEX);
	debugSerial.println(F(""));

	//if good, compare
	if(eeChecksum == CHECKSUM_GOOD)
	{
		debugSerial.println(F("Checksum good, Restoring"));
		tiltEnable = eeStrip.tiltEnable;
		speedBrightnessEnable = eeStrip.speedBrightnessEnable;
		patternEnable = eeStrip.speedPatternEnable;

		if(!speedBrightnessEnable)//update brightness only if not changed by speed sensor
		{
			brightness = eeStrip.brightness;
		}

		for(uint8_t i = 0; i < NUM_LEDS; i++)
		{
			 leds[i].offset = eeStrip.leds[i].offset;
			if(!patternEnable) //update states only if not changed by pattern
			{
				leds[i].state = eeStrip.leds[i].state;
			}
		}
	}
	else
	{
		debugSerial.println(F("Bad Checksum, not restoring"));
		retVal = false;
	}

	return retVal;
}

bool StripColorSettings::saveSettings()
{
	if(saveTimer < TIMEOUT_SAVE_MS)
	{
		return false;
	}
	saveFlag = false;
	saveTimer = 0;

	bool dif = false;
	eeStripSettings eeStrip;

	debugSerial.println(F("--Saving EEPROM Routine--"));
	debugSerial.println(F("getting EEPROM"));
	EEPROM.get(0, eeStrip);

	//calculate current checksum
	debugSerial.println(F("calculating checksum"));
	uint8_t * eePtr = (uint8_t*)(&eeStrip);
	uint16_t eeBytes = sizeof(eeStrip);
	uint8_t eeChecksum = *eePtr;
	eePtr ++;

	for(uint16_t i = 1; i < eeBytes; i++)
	{
		eeChecksum = eeChecksum ^ *eePtr;
		eePtr++;
	}

	debugSerial.print(F("checksum is: "));
	debugSerial.print(eeChecksum, HEX);
	debugSerial.println(F(""));

	//if good, compare
	if(eeChecksum == CHECKSUM_GOOD)
	{
		debugSerial.println(F("Checksum good!"));
		bool rootDif = (eeStrip.tiltEnable != tiltEnable) ||
				(eeStrip.speedBrightnessEnable != speedBrightnessEnable) ||
				(eeStrip.speedPatternEnable != patternEnable) ||
				((eeStrip.brightness != brightness)  && !speedBrightnessEnable);

		bool ledOffsetDif =  false;
		bool ledStateDif = false;
		for(uint8_t i = 0; i < NUM_LEDS; i++)
		{
			ledOffsetDif = eeStrip.leds[i].offset != leds[i].offset;
			ledStateDif = (eeStrip.leds[i].state != leds[i].state) && (!patternEnable);
			if(ledOffsetDif || ledStateDif)
			{
				break;
			}
		}

		dif = rootDif || ledOffsetDif || ledStateDif;

	}
	else //otherwise its whack and need to replace. mark as different
	{
		debugSerial.println(F("Bad Checksum, flagging EEPROM rewrite!"));
		dif = true;
	}


	if(dif)//replace if different
	{
		debugSerial.println(F("EEPROM different from current settings, saving values"));
		eeStrip.tiltEnable = tiltEnable;
		eeStrip.speedBrightnessEnable = speedBrightnessEnable;
		eeStrip.speedPatternEnable = patternEnable;

		if(!speedBrightnessEnable)//update brightness only if not changed by speed sensor
		{
			eeStrip.brightness = brightness;
		}

		for(uint8_t i = 0; i < NUM_LEDS; i++)
		{
			eeStrip.leds[i].offset = leds[i].offset;
			if(!patternEnable) //update states only if not changed by pattern
			{
				eeStrip.leds[i].state = leds[i].state;
			}
		}

		//calculate new checkSum reserve so that the checksum will equal CHECKSUM_GOOD
		debugSerial.println(F("Calculating checksum reserve"));
		eePtr = (uint8_t*)(&eeStrip);
		uint8_t xorTemp = *eePtr;
		eePtr ++;

		for(uint16_t i = 1; i < eeBytes - 1; i++)  //do not xor checksumReserve;
		{
			xorTemp = xorTemp ^ *eePtr;
			eePtr++;
		}

		eeStrip.checksumReserve = xorTemp ^ CHECKSUM_GOOD;
		debugSerial.print(F("Checksum reserve is: "));
		debugSerial.print(eeStrip.checksumReserve, HEX);
		debugSerial.println(F(""));

		//write to eeprom
		debugSerial.println(F("Writing to EEPROM now!"));
		EEPROM.put(0, eeStrip);
	}
	return true;
}

void StripColorSettings::run(uint16_t elapsedMs)
{
	if(saveFlag)
	{
		updateTimer(elapsedMs);
	}
	saveSettings();
}

void StripColorSettings::updateTimer(uint16_t elapsedMs)
{
	if((saveTimer + elapsedMs) > saveTimer)
	{
		saveTimer += elapsedMs;
	}
	else
	{
		saveTimer = 0xFFFF;
	}
}
