/*
 * ColorScale.cpp
 *
 *  Created on: Oct 27, 2016
 *      Author: bzachmann
 */

#include "ColorScale.h"

/************************Prototypes*******************************/
uint8_t baseFunc(uint16_t value);
uint8_t colorFunc(uint16_t value, colorOffset color, bool &ok);
/*****************************************************************/

static rgbVal ColorScale::getRGB(uint16_t value, uint16_t offset)
/*******************************************************************************************
 *
 * 	Returns an rgbVall structure containing the rgb Values at the given value and offset
 *
 *******************************************************************************************/
{
	rgbVal rgbValues;

	uint16_t scaleVal = value % 765; // get value in range 0 - 765
	uint16_t scaleOffset = offset % 765; // get offset in range 0 - 765
	scaleVal = (scaleVal + scaleOffset) % 765; //combine and get new value

	bool ok = 0;

	rgbValues.red = colorFunc(scaleVal, red, ok);
	rgbValues.green = colorFunc(scaleVal, green, ok);
	rgbValues.blue = colorFunc(scaleVal, blue, ok);
	return rgbValues;

}

uint8_t colorFunc(uint16_t value, colorOffset color, bool &ok)
/*******************************************************************************************
 *
 * 	Returns the value of the color specified based on the value (0 - 765) passed in.
 * 	"ok" will be set to false if a value outside of the range
 * 	 0 - 765 if specified or an invalid color is specified.
 *
 *******************************************************************************************/
{
	uint16_t funcValue = value;

	if(color > 765)
	{
		ok = false;
		return 255;
	}
	else
	{
		if(color == red)
		{
			//do nothing to color
		}
		else if(color == green)
		{
			//shift the function right by 255
			funcValue = (value + 255) % 765;
		}
		else if(color == blue)
		{
			//shift the function right by 510
			funcValue = (value + 510) % 765;
		}
		else
		{
			ok = false;
			return 255;
		}

		return baseFunc(funcValue);

	}

}

uint8_t baseFunc(uint16_t value)
/*******************************************************************************************
 *
 * 	Piecewise function that is the basic function curve that a single red, green, or blue
 * 	value follows.  They are all identical except shifted by factors of 255.
 *
 *******************************************************************************************/
{
	uint8_t returnVal = 0;

	if(value <= 255)
	{
		returnVal = value;
	}
	else if(value > 255 && value <= 510)
	{
		returnVal = 510 - value;
	}
	else
	{
		returnVal = 0;
	}

	return returnVal;
}

