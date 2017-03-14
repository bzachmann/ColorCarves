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
	CMPMessage testMsg2 = CMPMessage();
	testMsg2.setID(0x1235);
	testMsg2.setByte(0, 0x10);
	testMsg2.setByte(1, 0x20);
	testMsg2.setByte(2, 0x30);
	testMsg2.setByte(3, 0x40);
	testMsg2.setByte(4, 0x50);
	testMsg2.setByte(5, 0x60);
	testMsg2.setByte(6, 0x70);
	testMsg2.setByte(7, 0x80);
	msgPort.send(testMsg2);
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

