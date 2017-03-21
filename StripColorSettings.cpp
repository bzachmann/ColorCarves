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
	clearValues();
	clearOffsets();

	uint8_t numLeds = NUM_LEDS;
	uint8_t brightness = 0;
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

bool StripColorSettings::setValue(uint8_t index, uint16_t value)
{
	bool retVal = false;
	if(index < NUM_LEDS)
	{
		leds[index].value = value;
		retVal = true;
	}
	return retVal;
}

uint16_t StripColorSettings::getValue(uint8_t index)
{
	uint16_t retVal = 0xFFFF;
	if(index < NUM_LEDS)
	{
		retVal = leds[index].value;
	}
	return retVal;
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

void StripColorSettings::clearStates()
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
		leds[i].state == false;
	}
	return;
}

void StripColorSettings::clearValues()
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
		leds[i].value == 0;
	}
	return;
}

void StripColorSettings::clearOffsets()
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
		leds[i].offset == 0;
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
