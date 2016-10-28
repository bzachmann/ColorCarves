/*
 * ColorScale.h
 *
 *  Created on: Oct 27, 2016
 *      Author: bzachmann
 */

#ifndef COLORSCALE_H_
#define COLORSCALE_H_
#include <stdint.h>
#include <stdbool.h>


typedef struct rgbValTag{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}rgbVal;

enum colorOffset{
	red,
	green,
	blue
} ;

class ColorScale {
public:
	static rgbVal getRGB(uint16_t value, uint16_t offset);

};

#endif /* COLORSCALE_H_ */
