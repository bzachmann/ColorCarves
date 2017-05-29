/*
 * TiltSensor.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: bzachmann
 */

#include "TiltSensor.h"

#warning - todo add calibration functionality

TiltSensor::TiltSensor()
{
	 bno = Adafruit_BNO055(SENSOR_ID);
	 buffer = CircularBuffer();
	 //bno.setExtCrystalUse(true);
}

bool TiltSensor::begin()
{
	return bno.begin(Adafruit_BNO055::OPERATION_MODE_NDOF);
	bno.setExtCrystalUse(true); //the adafruit dev board has external crystal
	delay(10);
}

void TiltSensor::update()
{
	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	int32_t sensorAngle = 0;
	switch(AXIS)
	{
	case AXISX:
		sensorAngle = (int32_t)(euler.x() * 10);
		break;
	case AXISY:
		sensorAngle = (int32_t)(euler.y() * 10);
		break;
	case AXISZ:
		sensorAngle = (int32_t)(euler.z() * 10);
		break;
	default:
		break;

	}
	buffer.add(sensorAngle);
}

int32_t TiltSensor::getAngle()
{
	return buffer.average();
}

void TiltSensor::updateColors(StripColorSettings &stripSettings)
{
	if(stripSettings.getTiltEnable())
	{
		int32_t angle = getAngle();
		if(angle > 500)
		{
			angle = 500;
		}
		else if(angle < -500)
		{
			angle = -500;
		}
		uint16_t mappedVal = (uint16_t)(map(angle, -500, 500, 0, 765));
		stripSettings.setBaseValue(mappedVal);
	}
	else
	{
		stripSettings.setBaseValue(DEFAULT_TILT);
	}
}
