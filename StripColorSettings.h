/*
 * StripColorSettings.h
 *
 *  Created on: Mar 14, 2017
 *      Author: bzachmann
 */

#ifndef STRIPCOLORSETTINGS_H_
#define STRIPCOLORSETTINGS_H_

#include <stdint.h>

#define NUM_LEDS	8

class StripColorSettings {
	typedef struct ledSetting{
		bool state;
		uint16_t value;
		uint16_t offset;
	}ledSetting;

public:
	StripColorSettings();
	bool setState(uint8_t index, bool state);
	bool getState(uint8_t index);
	bool setValue(uint8_t index, uint16_t value);
	uint16_t getValue(uint8_t index);
	bool setOffset(uint8_t index, uint16_t value);
	uint16_t getOffset(uint8_t index);

	void clearStates();
	void clearValues();
	void clearOffsets();
	bool restoreOffsets();
	bool restoreOffset(uint8_t index);
	bool saveOffsets();
	bool saveOffset(uint8_t index);

private:
	ledSetting leds[NUM_LEDS];
};

#endif /* STRIPCOLORSETTINGS_H_ */
