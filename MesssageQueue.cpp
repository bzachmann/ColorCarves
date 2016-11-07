/*
 * MesssageQueue.cpp
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#include "MesssageQueue.h"

MesssageQueue::MesssageQueue() {
	iFront = 0;
	iBack = -1;
}

bool MesssageQueue::enqueue(CMPMessage message)
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
CMPMessage MesssageQueue::dequeue(bool &ok)
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

bool MesssageQueue::isEmpty()
{
	return (iBack == -1);
}
