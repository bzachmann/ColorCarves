/*
 * CMPMessage.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#include "CMPMessage.h"

typedef void (*msg_callback)(CMPMessage msg);

CMPMessage::CMPMessage() {
	msgId = 0xFFFF;
	for(uint8_t i = 0; i < 8; i++)
	{
		data[i] = 0;
	}
	callback_func = 0;
}

void CMPMessage::setID(uint16_t m_id)
{
	msgId = m_id;
}

uint16_t CMPMessage::getID()
{
	return msgId;
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

void CMPMessage::registerCallback(msg_callback func)
{
	callback_func = func;
}

msg_callback CMPMessage::callback()
{
	return callback_func;
}
