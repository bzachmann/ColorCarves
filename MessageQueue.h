/*
 * MessageQueue.h
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_

#include "CMPMessage.h"

#define QUEUELENGTH 10

class MessageQueue {
public:
	MessageQueue();

	bool enqueue(CMPMessage message);
	CMPMessage dequeue(bool &ok);

	bool isEmpty();

private:
	CMPMessage buffer[QUEUELENGTH];
	int8_t iFront;
	int8_t iBack;




};

#endif /* MESSAGEQUEUE_H_ */
