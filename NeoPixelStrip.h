/*
 * NeoPixelStrip.h
 *
 *  Created on: Mar 14, 2017
 *      Author: bzachmann
 */

#ifndef NEOPIXELSTRIP_H_
#define NEOPIXELSTRIP_H_

#include <Adafruit_NeoPixel.h>
#include "StripColorSettings.h"

class NeoPixelStrip: public Adafruit_NeoPixel {
public:

	NeoPixelStrip(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800);
	void setStrip(StripColorSettings &stripSettings);
};

#endif /* NEOPIXELSTRIP_H_ */
