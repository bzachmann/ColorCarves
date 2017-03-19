/* * CMPPort.cpp
 *
 *  Created on: Nov 6, 2016
 *  Author: bzachmann
 */
#include <Arduino.h>

#include "CMPPort.h"

CMPPort::CMPPort()
/*******************************************************************************************
 *
 * 	Constructor creates a new Message Queue sets default variable values
 *
 *******************************************************************************************/
{
	msgQueue = MessageQueue();
	buffer_index = 0;
	record_index = 0;
	header_rcvd = false;
}

void CMPPort::in(uint8_t inByte)
/*******************************************************************************************
 *
 * 	This method takes in one byte of data and adds the byte to the data stream. The bytes
 * 	that enter the stream must correctly follow the CMP protocol. If the byte is an invalid
 * 	byte based on the previous sequence, the byte along with the message that was being
 * 	constructed are discarded.  If the byte is the last byte in a valid message and the
 * 	entire message is valid, the message is added to the Message
 * 	Queue where their corresponding callback functions are handled later.
 *
 *******************************************************************************************/
{
	if ((inByte == HEADERBYTE) && (!header_rcvd))
	{
		header_rcvd = true;
	}
	else
	{
		if(!header_rcvd)
		{
			resetBuffer();
		}
		else
		{
			buffer[buffer_index] = inByte;
			buffer_index++;
			if(buffer_index == BUFFER_MAX)
			{
				parseAndQueue();
			}
		}
	}
}

void CMPPort::registerMessage(CMPMessage msg)
/*******************************************************************************************
 *
 * 	Adds a record (id and corresponding callback function) to message records array.
 * 	This array is searched for callback functions when a callback needs to be handled.
 *
 *******************************************************************************************/
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
/*******************************************************************************************
 *
 * 	Dequeues the top message in the queue, searches the msg_records array for a callback
 * 	function that corresponds to the id of the message that was just dequeued, and calls that
 * 	function.
 *
 *******************************************************************************************/
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
/*******************************************************************************************
 *
 * 	calls handleNextCallback until the message queue is empty
 *
 *******************************************************************************************/
{
	while(!msgQueue.isEmpty())
	{
		handleNextCallback();
	}
}

void CMPPort::send(CMPMessage msg)
/*******************************************************************************************
 *
 * 	Sends the given CMP Message following the CMP Protocol
 *
 *******************************************************************************************/
{
	Serial.write((uint8_t)HEADERBYTE);

	uint16_t id = msg.getID();
	Serial.write((uint8_t)((id >> 8) & 0xFF));
	Serial.write((uint8_t)(id & 0xFF));
	for(int i = 0; i < CMPMESSAGE_DATALENGTH; i++)
	{
		Serial.write(msg.getByte(i));
	}
}

void CMPPort::parseAndQueue()
/*******************************************************************************************
 *
 * 	Constructs a CMP message based on what is currently in the receive buffer and adds
 * 	message to the message queue
 *
 *******************************************************************************************/
{
	if(buffer_index == BUFFER_MAX)
	{
		CMPMessage tempMsg = CMPMessage();
		uint16_t buffer0 = buffer[0];
		uint16_t buffer1 = buffer[1];
		buffer0 = buffer0 << 8;
		buffer1 = buffer1 & 0xFF;
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
/*******************************************************************************************
 *
 * 	Resets the buffer state so that it is ready to receive next message.
 * 	(Protocol sequence starts over)
 *
 *******************************************************************************************/
{
	header_rcvd = false;
	buffer_index = 0;
}
