/*
 * CircularBuffer.h
 *
 *  Created on: Oct 31, 2016
 *      Author: bzachmann
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#define BUFFERSIZE 64

#include <stdint.h>

class CircularBuffer {
public:
	CircularBuffer();
	virtual ~CircularBuffer();
	void add(int32_t value);
	int32_t average();

private:
	int32_t buffer[BUFFERSIZE];
	int16_t index;
};

#endif /* CIRCULARBUFFER_H_ */
