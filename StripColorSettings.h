/*
 * StripColorSettings.h
 *
 *  Created on: Mar 14, 2017
 *      Author: bzachmann
 */

#ifndef STRIPCOLORSETTINGS_H_
#define STRIPCOLORSETTINGS_H_

#include <stdint.h>
#include <eeprom.h>

#define NUM_LEDS		33
#define CHECKSUM_GOOD	0xEE
#define TIMEOUT_SAVE_MS	500
#define CHECK_SAVE_MS	100

class StripColorSettings {
	typedef struct ledSetting{
		bool state;
		uint16_t offset;
	}ledSetting;

	typedef struct _eeStripSettings{
		bool tiltEnable;
		bool speedBrightnessEnable;
		bool speedPatternEnable;
		uint8_t brightness;
		ledSetting leds[NUM_LEDS];
		uint8_t checksumReserve;
	} eeStripSettings;

public:
	enum errorCause {
		BNO055 = 1,
		NUM_ERRORCAUSES,
	};

	enum errorType {
		NOT_CONNECTED = 1,
		NUM_ERRORTYPES,
	};

public:
	StripColorSettings();
	bool setState(uint8_t index, bool state);
	bool getState(uint8_t index);
	bool setBaseValue(uint16_t value);
	uint16_t getBaseValue();
	bool setOffset(uint8_t index, uint16_t value);
	uint16_t getOffset(uint8_t index);
	bool setBrightness(uint8_t value);
	uint8_t getBrightness();
	bool setPatternOnLed(uint8_t value);
	uint8_t getPatternOnLed();
	bool setTiltEnable(bool val);
	bool getTiltEnable();
	bool setPatternEnable(bool val);
	bool getPatternEnable();
	bool setSpeedBrightnessEnable(bool val);
	bool getSpeedBrightnessEnable();

	bool setError(errorCause cause, errorType type);

	void clearStates();
	void clearBaseValue();
	void clearOffsets();

	void flagForSave();

	bool restoreSettings();
	bool saveSettings();
	void run(uint16_t elapsedMs);


private:
	ledSetting leds[NUM_LEDS];
	uint8_t patternOnLed;

	uint16_t baseValue;
	uint8_t numLeds;
	uint8_t brightness;

	uint16_t saveTimer;
	bool saveFlag;

	bool tiltEnable;
	bool speedBrightnessEnable;
	bool patternEnable;

private:
	void updateTimer(uint16_t elapsedMs);
};

#endif /* STRIPCOLORSETTINGS_H_ */
