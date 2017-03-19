/*
 * CMPMessage.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#include "CMPMessage.h"

typedef void (*msg_callback)(CMPMessage msg);

CMPMessage::CMPMessage()
/*******************************************************************************************
 *
 * 	constructor sets msgID to 0xFFFF,sets all data to 0, and sets function pointer to 0
 *
 *******************************************************************************************/
{
	msgId = 0xFFFF;
	for(uint8_t i = 0; i < 8; i++)
	{
		data[i] = 0;
	}
	callback_func = 0;
}

void CMPMessage::setID(uint16_t m_id)
/*******************************************************************************************
 *
 * 	sets the id of the message
 *
 *******************************************************************************************/
{
	msgId = m_id;
}

uint16_t CMPMessage::getID()
/*******************************************************************************************
 *
 * 	sets the id of the message
 *
 *******************************************************************************************/
{
	return msgId;
}

bool CMPMessage::setByte(uint8_t index, uint8_t value)
/*******************************************************************************************
 *
 * 	sets the byte at index index to value value
 *
 *******************************************************************************************/
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
/*******************************************************************************************
 *
 * 	gets the value at the given byte index
 *
 *******************************************************************************************/
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
/*******************************************************************************************
 *
 * 	sets the address of the callback function
 *
 *******************************************************************************************/
{
	callback_func = func;
}

msg_callback CMPMessage::callback()
/*******************************************************************************************
 *
 *  returns a function pointer to the register callback function
 *
 *******************************************************************************************/
{
	return callback_func;
}
