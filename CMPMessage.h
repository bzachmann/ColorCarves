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

class CMPMessage {
public:
	CMPMessage();

	void setID(uint16_t _id);
	uint16_t getID();

	bool setByte(uint8_t index, uint8_t value);
	uint8_t getByte(uint8_t index);

private:
	uint16_t id;
	uint8_t data[8];
};

#endif /* CMPMESSAGE_H_ */
