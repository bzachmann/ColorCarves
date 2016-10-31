/*
 * TiltSensor.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: bzachmann
 */

#include "TiltSensor.h"

//sensors_event_t event;

TiltSensor::TiltSensor() {
	bno = Adafruit_BNO055(SENSOR_ID);

}

TiltSensor::~TiltSensor() {
	// TODO Auto-generated destructor stub
}

bool TiltSensor::begin()
{

}

