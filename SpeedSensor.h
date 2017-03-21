/*
 * SpeedSensor.h
 *
 *  Created on: Mar 20, 2017
 *      Author: Boston
 */

#ifndef SPEEDSENSOR_H_
#define SPEEDSENSOR_H_

#include "StripColorSettings.h"
#include <stdint.h>

class SpeedSensor {
public:
	SpeedSensor();

	void update();
	uint16_t getSpeed();
	void updateStripBrightness(StripColorSettings &stripSettings);
	void updateStripStates(StripColorSettings &stripSettings);

private:
	uint16_t speed;

};

#endif /* SPEEDSENSOR_H_ */
