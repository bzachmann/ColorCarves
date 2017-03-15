/*
 * NeoPixelStrip.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: bzachmann
 */

#include "NeoPixelStrip.h"
#include "ColorScale.h"

NeoPixelStrip::NeoPixelStrip(uint16_t n, uint8_t p=6, neoPixelType t=NEO_GRB + NEO_KHZ800) : Adafruit_NeoPixel(n,p,t) {
	// TODO Auto-generated constructor stub

}

void NeoPixelStrip::setStrip(StripColorSettings &stripSettings)
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
		rgbVal rgbValues = ColorScale::getRGB(stripSettings.getValue(i), stripSettings.getOffset(i));
		setPixelColor(i, rgbValues.red, rgbValues.green, rgbValues.blue);
	}
}
