/*
 * MesssageQueue.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#include "MessageQueue.h"

MessageQueue::MessageQueue() {
	iFront = 0;
	iBack = -1;
}

bool MessageQueue::enqueue(CMPMessage message)
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
{
	return (iBack == -1);
}
