/*
 * CMP.cpp
 *
 *  Created on: Nov 9, 2016
 *      Author: bzachmann
 */

#include "CMP.h"
#include "CMPMessage.h"

CMPPort msgPort;

void msg_callback_TESTMSG(CMPMessage msg)
{
	digitalWrite(13, !digitalRead(13));
	for(uint8_t i = 0; i < 8; i++)
	{
		Serial.write(msg.data[i]);
	}
}

void msg_init_TESTMSG()
{
	CMPMessage testMsg = CMPMessage();
	//testMsg.setID(ID_TESTMSG);
	testMsg.setID(0x1234);
	testMsg.registerCallback(&msg_callback_TESTMSG);
	msgPort.registerMessage(testMsg);
}

void cmp_update()
{
	while(Serial.available())
	{
		msgPort.in((uint8_t)(Serial.read()));
	}
	msgPort.handleAllCallbacks();
}

void cmp_initialize()
{
	msgPort = CMPPort();
	msg_init_TESTMSG();
}

