/*
 * CMPMessage.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#include "CMPMessage.h"

CMPMessage::CMPMessage() {
	id = 0xFFFF;
	for(uint8_t i = 0; i < 8; i++)
	{
		data[i] = 0;
	}
}

void CMPMessage::setID(uint16_t _id)
{
	id = _id;
}

uint16_t CMPMessage::getID()
{
	return id;
}

bool CMPMessage::setByte(uint8_t index, uint8_t value)
{
	if(index > 7)
	{
		return false;
	}
	else
	{
		data[index] = value;
		return true;
	}
}

uint8_t CMPMessage::getByte(uint8_t index)
{
	if(index > 7)
	{
		return 0xFF;
	}
	else
	{
		return data[index];
	}
}
