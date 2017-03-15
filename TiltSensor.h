/*
 * TiltSensor.h
 *
 *  Created on: Oct 30, 2016
 *      Author: bzachmann
 */

#ifndef TILTSENSOR_H_
#define TILTSENSOR_H_

#include <Adafruit_BNO055.h>
#include "CircularBuffer.h"
#include "StripColorSettings.h"

typedef enum {
	AXISX,
	AXISY,
	AXISZ
}AxisType;

#define SENSOR_ID	21
#define AXIS		AXISZ //0 = X, 1 = Y, 2 = Z

class TiltSensor {
public:
	TiltSensor();

	bool begin();
	void update();
	int32_t getAngle();
	void updateColors(StripColorSettings &strip);


private:
	Adafruit_BNO055 bno;
	CircularBuffer buffer;
};

#endif /* TILTSENSOR_H_ */
