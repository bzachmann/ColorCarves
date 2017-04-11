/*
 * SpeedSensor.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: Boston
 */

#include "SpeedSensor.h"
#include <Arduino.h>

SpeedSensor::SpeedSensor()
{
	speed = 0;
}

void SpeedSensor::update(double speed_MperS)
{
	int speedInt = (int)(speed_MperS * 100);
    speed = (uint16_t)map(speedInt, 0, 900, 0, 765);
}

double SpeedSensor::getSpeed()
{
	return speed;
}

void SpeedSensor::updateStripBrightness(StripColorSettings &stripSettings)
{
	uint8_t brightness = map(speed, 0, 765, 0, 255);
	stripSettings.setBrightness(brightness);
}

void SpeedSensor::updateStripStates(StripColorSettings &stripSettings)
{
	//TODO - implement this function
}
