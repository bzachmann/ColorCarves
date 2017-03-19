/*
 * MesssageQueue.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#include "MessageQueue.h"

MessageQueue::MessageQueue()
/*******************************************************************************************
 *
 * 	Constructor sets the queue in a state that flags it as empty (iBack = -1)
 *
 *******************************************************************************************/
{
	iFront = 0;
	iBack = -1;
}

bool MessageQueue::enqueue(CMPMessage message)
/*******************************************************************************************
 *
 * 	adds the message to the queue. Returns false if the queue was full and could not be added
 *
 *******************************************************************************************/
{
	bool success;
	if(iBack != iFront)
	{
		//special case for very first entry
		if(iBack == -1)
		{
			buffer[0] = message;
			iBack = 1;
			success = true;
		}
		else
		{
			buffer[iBack] = message;
			iBack++;
			if(iBack == QUEUELENGTH)
			{
				iBack = 0;
			}
		}
	}
	else//queue full
	{
		success = false;
	}
	return success;
}
CMPMessage MessageQueue::dequeue(bool &ok)
/*******************************************************************************************
 *
 * 	removes the top message from the queue. Sets the bool flag to false if the queue was empty
 * 	and could not remove anymore messages
 *
 *******************************************************************************************/
{
	ok = false;
	CMPMessage returnMessage;
	if(!isEmpty())
	{
		returnMessage = buffer[iFront];
		iFront++;
		if(iFront == QUEUELENGTH)
		{
			iFront = 0;
		}
		if(iFront == iBack)//queue empty. reset
		{
			iBack = -1;
			iFront = 0;
		}
		ok = true;

	}
	else
	{
		ok = false;
	}
	return returnMessage;
}

bool MessageQueue::isEmpty()
/*******************************************************************************************
 *
 * 	Returns whether or not the queue is empty
 *
 *******************************************************************************************/
{
	return (iBack == -1);
}
