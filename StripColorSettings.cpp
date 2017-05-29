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
	//TODO - implement save and restore from eeprom
	return false;
}

bool StripColorSettings::saveOffset(uint8_t index)
{
	//TODO - implement save and restore from eeprom
	return false;
}
