/*
 * TiltSensor.h
 *
 *  Created on: Oct 30, 2016
 *      Author: bzachmann
 */

#ifndef TILTSENSOR_H_
#define TILTSENSOR_H_

#include <Adafruit_BNO055.h>

#define SENSOR_ID	21


class TiltSensor {
public:
	TiltSensor();
	virtual ~TiltSensor();

	bool begin();

private:
	Adafruit_BNO055 bno;


};

#endif /* TILTSENSOR_H_ */
