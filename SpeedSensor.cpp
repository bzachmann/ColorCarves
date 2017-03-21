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

void SpeedSensor::update()
{
  int voltage = analogRead(A0);
  speed = (uint16_t)map(voltage, 0, 1023, 0, 765);
}

uint16_t SpeedSensor::getSpeed()
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
