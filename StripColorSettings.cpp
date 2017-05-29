/*
 * StripColorSettings.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: bzachmann
 */

#include "StripColorSettings.h"

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

bool StripColorSettings::restoreOffsets()
{
	//TODO - implement save and restore from eeprom
	return false;
}

bool StripColorSettings::restoreOffset(uint8_t index)
{
	//TODO - implement save and restore from eeprom
	return false;
}

bool StripColorSettings::saveOffsets()
{
	bool dif = false;
	eeStripSettings eeStrip;
	EEPROM.get(0, eeStrip);

	//calculate current checksum
	uint8_t * eePtr = (uint8_t*)(&eeStrip);
	uint16_t eeBytes = sizeof(eeStrip);
	uint8_t eeChecksum = *eePtr;
	eePtr ++;

	for(uint16_t i = 1; i < eeBytes; i++)
	{
		eeChecksum = eeChecksum ^ *eePtr;
		eePtr++;
	}

	//if good, compare
	if(eeChecksum == CHECKSUM_GOOD)
	{
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
		dif = true;
	}


	if(dif)//repalce if different
	{
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
		eePtr = (uint8_t*)(&eeStrip);
		uint8_t xorTemp = *eePtr;
		eePtr ++;

		for(uint16_t i = 1; i < eeBytes - 1; i++)  //do not xor checksumReserve;
		{
			xorTemp = xorTemp ^ *eePtr;
			eePtr++;
		}

		eeStrip.checksumReserve = xorTemp ^ CHECKSUM_GOOD;

		//write to eeprom
		EEPROM.put(0, eeStrip);
	}

}

bool StripColorSettings::saveOffset(uint8_t index)
{
	//TODO - implement save and restore from eeprom
	return false;
}
