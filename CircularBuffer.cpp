/*
 * CircularBuffer.cpp
 *
 *  Created on: Oct 31, 2016
 *      Author: bzachmann
 */

#include "CircularBuffer.h"
#include <string.h>
#include <Arduino.h>

CircularBuffer::CircularBuffer() {
	index = 0;
	for(uint16_t i = 0; i < sizeof(BUFFERSIZE); i++)
	{
		buffer[i] = 0;
	}
}

CircularBuffer::~CircularBuffer() {

}

void CircularBuffer::add(int32_t value)
{
	index++;
	if(index == BUFFERSIZE)
	{
		index = 0;
	}
	buffer[index] = value;
}

int32_t CircularBuffer::average()
{
	int64_t sum = 0;
	int32_t average = 0;

	for(uint16_t i = 0; i < BUFFERSIZE; i++)
	{
		sum = sum + buffer[i];
	}

	//if(BUFFERSIZE == 256)
	//{
		//special (efficient) divide if buffer is  256 length
		//average = sum >> 8;
	//}
	//else
	//{
	average = sum / BUFFERSIZE;

	//}

	return average;
}
