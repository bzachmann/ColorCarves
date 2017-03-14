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

#define CMPMESSAGE_DATALENGTH 8

class CMPMessage {
public:
	typedef void (*msg_callback)(CMPMessage msg);

	CMPMessage();

	void setID(uint16_t m_id);
	uint16_t getID();

	bool setByte(uint8_t index, uint8_t value);
	uint8_t getByte(uint8_t index);

	void registerCallback(msg_callback func);
	msg_callback callback();

	uint8_t data[8];

private:
	uint16_t msgId;
	msg_callback callback_func;
};

#endif /* CMPMESSAGE_H_ */
