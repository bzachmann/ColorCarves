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
	setBrightness(stripSettings.getBrightness());

	for(int i = 0; i < NUM_LEDS; i++)
	{
		if(stripSettings.getState(i))
		{
			rgbVal rgbValues = ColorScale::getRGB(stripSettings.getBaseValue(), stripSettings.getOffset(i));
			setPixelColor(i, rgbValues.red, rgbValues.green, rgbValues.blue);
		}
		else
		{
			setPixelColor(i, 0, 0, 0);
		}
	}
}

