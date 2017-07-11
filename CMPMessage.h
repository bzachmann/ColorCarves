/*
 * CMPMessage.h
 *
 *  Created on: Nov 6, 2016
 *      Author: bzachmann
 */

#ifndef CMPMESSAGE_H_
#define CMPMESSAGE_H_

#include <stdint.h>
#include <stdbool.h>

#define CMPMESSAGE_DATALENGTH 3

class CMPMessage {
public:
	typedef void (*msg_callback)(CMPMessage msg);

	CMPMessage();

	void setID(uint8_t m_id);
	uint8_t getID();

	bool setByte(uint8_t index, uint8_t value);
	uint8_t getByte(uint8_t index);

	void registerCallback(msg_callback func);
	msg_callback callback();

private:
	msg_callback callback_func;

	uint8_t msgId;
	uint8_t data[CMPMESSAGE_DATALENGTH];
};

#endif /* CMPMESSAGE_H_ */
