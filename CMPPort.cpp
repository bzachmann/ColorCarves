/* * CMPPort.cpp
 *
 *  Created on: Nov 6, 2016
 *  Author: bzachmann
 */
#include <Arduino.h>

#include "CMPPort.h"

CMPPort::CMPPort() {
	msgQueue = MessageQueue();
	buffer_index = 0;
	record_index = 0;
	header_rcvd = 0;
	accept_next_byte = 0;
	for(uint8_t i = 0; i < 10; i++)
	{
		buffer[i] = 0xFF;
	}
}

void CMPPort::in(uint8_t inByte)
{
	switch(inByte)
	{
	case HEADERBYTE:
		if(!header_rcvd)
		{
			header_rcvd = true;
		}
		else if(accept_next_byte)
		{
			if(buffer_index == BUFFER_MAX)
			{
				resetBuffer();
			}
			else
			{
				buffer[buffer_index] = inByte;
				accept_next_byte = false;
				buffer_index++;
			}
		}
		else
		{
			resetBuffer();
		}
		break;

	case ENDBYTE:
		if(!header_rcvd)
		{
			resetBuffer();
		}
		else if(accept_next_byte)
		{
			if(buffer_index == BUFFER_MAX)
			{
				resetBuffer();
			}
			else
			{
				buffer[buffer_index] = inByte;
				accept_next_byte = false;
				buffer_index++;
			}
		}
		else
		{
			parseAndQueue();
		}
		break;

	case ESCAPE:
		if(!header_rcvd)
		{
			resetBuffer();
		}
		else if(accept_next_byte)
		{
			if(buffer_index == BUFFER_MAX)
			{
				resetBuffer();
			}
			else
			{
				buffer[buffer_index] = inByte;
				accept_next_byte = false;
				buffer_index++;
			}
		}
		else
		{
			accept_next_byte = true;
		}
		break;

	default:
		if(!header_rcvd)
		{
			resetBuffer();
		}
		else
		{
			if(buffer_index == BUFFER_MAX)
			{
				resetBuffer();
			}
			else
			{
				buffer[buffer_index] = inByte;
				accept_next_byte = false;
				buffer_index++;
			}
		}
		break;
	}
}

void CMPPort::registerMessage(CMPMessage msg)
{
	if(record_index != REGISTERED_RECORDS_MAX)
	{
		msg_record temprecord;
		temprecord.id = msg.getID();
		temprecord.callback_func = msg.callback();
		msg_records[record_index] = temprecord;
		record_index++;
	}
}

void CMPPort::handleNextCallback()
{
	if(!msgQueue.isEmpty())
	{
		bool ok = false;
		CMPMessage tempMsg = msgQueue.dequeue(ok);

		for(uint8_t i = 0; i < record_index; i++)
		{
			msg_record tempRecord = msg_records[i];
			if(tempRecord.id == tempMsg.getID())
			{
				CMPMessage::msg_callback callback = tempRecord.callback_func;
				callback(tempMsg);
				break;
			}
		}
	}
}

void CMPPort::handleAllCallbacks()
{
	while(!msgQueue.isEmpty())
	{
		handleNextCallback();
	}
}
void CMPPort::parseAndQueue()
{
	if(buffer_index == BUFFER_MAX)
	{
		CMPMessage tempMsg = CMPMessage();
		uint16_t buffer0 = buffer[0];
		uint16_t buffer1 = buffer[1];
		buffer0 = buffer0 << 8;
		buffer1 - buffer1 & 0xFF;
		uint16_t msgId = (buffer0 + buffer1);
		tempMsg.setID(msgId);

		tempMsg.data[0] = buffer[2];
		tempMsg.data[1] = buffer[3];
		tempMsg.data[2] = buffer[4];
		tempMsg.data[3] = buffer[5];
		tempMsg.data[4] = buffer[6];
		tempMsg.data[5] = buffer[7];
		tempMsg.data[6] = buffer[8];
		tempMsg.data[7] = buffer[9];

		msgQueue.enqueue(tempMsg);
	}
	resetBuffer();

}
void CMPPort::resetBuffer()
{
	for(uint8_t i = 0; i < 10; i++)
	{
		buffer[i] = 0xFF;
	}

	header_rcvd = false;
	accept_next_byte = false;
	buffer_index = 0;
}
