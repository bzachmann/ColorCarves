/*
 * SpeedSensor.h
 *
 *  Created on: Mar 20, 2017
 *      Author: Boston
 */

#ifndef SPEEDSENSOR_H_
#define SPEEDSENSOR_H_

#include "globals.h"
#include "StripColorSettings.h"
#include <stdint.h>

extern void setupInterrupts();
extern void setTimerConversionFactor();
extern void setWheelConversionFactor();


class SpeedSensor {
public:
	SpeedSensor();

	void update();
	double getSpeed();
	void updateStripBrightness(StripColorSettings &stripSettings);
	void updateStripStates(StripColorSettings &stripSettings);

private:
	double speed;
	uint16_t patternTimer;

};

#endif /* SPEEDSENSOR_H_ */
