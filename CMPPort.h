/*
 * CMPPort.h
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#ifndef CMPPORT_H_
#define CMPPORT_H_

#include "MessageQueue.h"
#include "CMPMessage.h"

#define ESCAPE						0xE0
#define HEADERBYTE					0xE1
#define ENDBYTE						0xE2

#define REGISTERED_RECORDS_MAX		15
#define BUFFER_MAX					10

class CMPPort {

	typedef struct{
		uint16_t id;
		CMPMessage::msg_callback callback_func;
	}msg_record;

public:
	CMPPort();

	void in(uint8_t inByte);
	void registerMessage(CMPMessage msg);
	void handleNextCallback();
	void handleAllCallbacks();


private:
	void parseAndQueue();
	void resetBuffer();

	MessageQueue msgQueue;
	uint8_t buffer[BUFFER_MAX];
	uint8_t buffer_index;

	#warning todo - implement dynamic changing list of msg_records
	msg_record msg_records[REGISTERED_RECORDS_MAX];
	uint8_t record_index;

	bool header_rcvd;
	bool accept_next_byte;


};

#endif /* CMPPORT_H_ */
