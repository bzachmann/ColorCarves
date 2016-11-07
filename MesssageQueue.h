/*
 * MesssageQueue.h
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#ifndef MESSSAGEQUEUE_H_
#define MESSSAGEQUEUE_H_

#include "CMPMessage.h"

#define QUEUELENGTH 10

class MesssageQueue {
public:
	MesssageQueue();

	bool enqueue(CMPMessage message);
	CMPMessage dequeue(bool &ok);

	bool isEmpty();

private:
	CMPMessage buffer[QUEUELENGTH];
	int8_t iFront;
	int8_t iBack;




};

#endif /* MESSSAGEQUEUE_H_ */
