/*
 * CMP.cpp
 *
 *  Created on: Nov 9, 2016
 *      Author: bzachmann
 */

#include "CMP.h"
#include "CMPMessage.h"

CMPPort msgPort;
StripColorSettings stripSettings = StripColorSettings();

void msg_callback_LEDSET(CMPMessage msg)
/*******************************************************************************************
 *
 * 	callback message that is called if the LEDSET message is received
 *
 *******************************************************************************************/

{
	uint8_t index = msg.getByte(0);
	uint16_t value = ((uint16_t)(msg.getByte(1) << 8)) | ((uint16_t)(msg.getByte(2)));
	stripSettings.setOffset(index, value);
	msgPort.send(msg);
}

void msg_init_LEDSET()
/*******************************************************************************************
 *
 * 	Registers the LEDSET message so that the CMP Port will act on it if received
 *
 *******************************************************************************************/
{
	CMPMessage ledsetMsg = CMPMessage();
	ledsetMsg.setID(ID_LEDSET);
	ledsetMsg.registerCallback(&msg_callback_LEDSET);
	msgPort.registerMessage(ledsetMsg);
}

void msg_callback_TESTMSG(CMPMessage msg)
/*******************************************************************************************
 *
 * 	callback message that is called if the TEST message is received
 *
 *******************************************************************************************/
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
/*******************************************************************************************
 *
 * 	Registers the TEST message so that the CMP Port will act on it if received
 *
 *******************************************************************************************/
{
	CMPMessage testMsg = CMPMessage();
	testMsg.setID(ID_TESTMSG);
	testMsg.registerCallback(&msg_callback_TESTMSG);
	msgPort.registerMessage(testMsg);
}

void cmp_update()
/*******************************************************************************************
 *
 * 	This function will take any data that is available on the Serial Port and pass it to
 * 	msgPort using the .in() function.  After all data has been processed, the msgPort
 * 	will call any of the callback functions that are needed to be called
 * 	based on the previous data input and any registered ID's that are present
 *
 *******************************************************************************************/
{
	//TODO - add a msgPort.available boolean that is false if the messageque is full if false then skip the .in & handle callbacks
	while(Serial.available())
	{
		msgPort.in((uint8_t)(Serial.read()));
	}
	msgPort.handleAllCallbacks();
}


//TODO - pass in a software serial to listen on for the .in() source
void cmp_initialize()
/*******************************************************************************************
 *
 * 	Calling this function sets creates a new CMP Port and initializes any messages that
 * 	need to be initialized
 *
 *******************************************************************************************/
{
	msgPort = CMPPort();
	msg_init_LEDSET();
	msg_init_TESTMSG();
}

