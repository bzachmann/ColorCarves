/*
 * SpeedSensor.cpp
 *
 *  Created on: Mar 20, 2017
 *      Author: Boston
 */

#include "SpeedSensor.h"
#include <Arduino.h>

#define CLOCK_TICK_TIME_PS 62500

volatile uint16_t count_upper16 = 0;
volatile uint32_t countOld = 0;
volatile uint32_t countNew = 0;

volatile uint32_t elapsedCount = 0;
volatile uint32_t tickTimePS = 0;
volatile double elapsedTime_us = 0;
volatile double speed_conversion_factor = 0;
volatile double speed_MperS = 0;
volatile uint8_t interruptCount = 0;

SpeedSensor::SpeedSensor()
{
	speed = 0;
}

void SpeedSensor::update()
{
	int speedInt = (int)(speed_MperS * 100);
    speed = (uint16_t)map(speedInt, 0, 900, 0, 765);
}

double SpeedSensor::getSpeed()
{
	return speed;
}

void SpeedSensor::updateStripBrightness(StripColorSettings &stripSettings)
{
	if(stripSettings.getSpeedBrightnessEnable())
	{
		uint8_t brightness = map(speed, 0, 765, 0, 255);
		stripSettings.setBrightness(brightness);
	}
}

void SpeedSensor::updateStripStates(StripColorSettings &stripSettings)
{
	//TODO - implement this function
	if(stripSettings.getPatternEnable())
	{

	}
}

void setupInterrupts()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1B |= (1 << 7) | (1 << 6) | (2 << 0);  //rising edge detection and clock 8 time prescaler
	TIMSK1 |= (1 << 5) | (1 << 0); //enable input capture interrupt and overflow interrupt
	SREG |= (1 << 7); //global interrupt enable
}

void setTimerConversionFactor()
{
	uint8_t regValue = TCCR1B & 0b00000111;

	switch(regValue)
	{
	case 0b00000001:
		tickTimePS = CLOCK_TICK_TIME_PS * 1;
		break;
	case 0b00000010:
		tickTimePS = CLOCK_TICK_TIME_PS * 8;
		break;
	case 0b00000011:
		tickTimePS = CLOCK_TICK_TIME_PS * 64;
		break;
	case 0b00000100:
		tickTimePS = CLOCK_TICK_TIME_PS * 256;
		break;
	case 0b00000101:
		tickTimePS = CLOCK_TICK_TIME_PS * 1024;
		break;
	default:
		tickTimePS = 0;
		break;
	}
}

void setWheelConversionFactor()
{
	uint8_t wheel_diam_mm = 70;
	speed_conversion_factor = 1000.0 * wheel_diam_mm * 3.14159;
}

ISR(TIMER1_CAPT_vect)
{
	interruptCount++;
	if(interruptCount == 4)
	{
		countOld = countNew;
		countNew = (((uint32_t)count_upper16) << 16) | ICR1;

		elapsedCount = countNew - countOld;
		elapsedTime_us = ((((double)elapsedCount) * tickTimePS)/1000000.0);
		speed_MperS = speed_conversion_factor / elapsedTime_us;
		Serial.println(speed_MperS);
		interruptCount = 0;
	}
}

ISR(TIMER1_OVF_vect)
{
	count_upper16++;
}
