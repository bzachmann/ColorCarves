#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "NeoPixelStrip.h"
#include "TiltSensor.h"
#include "SpeedSensor.h"
#include "CMP.h"
#include "StripColorSettings.h"

TiltSensor sensor = TiltSensor();
NeoPixelStrip strip = NeoPixelStrip(NUM_LEDS, 6);
SpeedSensor speedSensor = SpeedSensor();
StripColorSettings stripSettings = StripColorSettings();
SoftwareSerial debugSerial(3,4); //rx, tx

uint16_t tenTimer = 0;
uint64_t hundredTimer = 0;
uint64_t testTimer = 0;

void setup(void)
{
  debugSerial.begin(9600);
  Serial.begin(9600);
  strip.begin();

  if(!sensor.begin())
  {
    debugSerial.print(F("no BNO055 detected\n"));
    stripSettings.setError(StripColorSettings::BNO055, StripColorSettings::NOT_CONNECTED);
    strip.setStrip(stripSettings);
    strip.show();
    while(1);
  }

  tenTimer = millis();
  hundredTimer = millis();
  testTimer = millis();
  cmp_initialize();

  setupInterrupts();
  setTimerConversionFactor();
  setWheelConversionFactor();
  stripSettings.restoreSettings();
}

void loop(void)
{
	cmp_update();

	uint16_t elapsed = millis() - tenTimer;
	if(elapsed > 10)
	{
		sensor.update();
		speedSensor.update();
		stripSettings.run(elapsed);

		tenTimer = millis();
	}

	elapsed = millis() - hundredTimer;
	if(elapsed > 50)
	{
		sensor.updateColors(stripSettings);

		speedSensor.updateStripBrightness(stripSettings);
		speedSensor.updateStripStates(stripSettings);

		strip.setStrip(stripSettings);
		strip.show();

	    hundredTimer = millis();
	}

	elapsed = millis() - testTimer;
	if(elapsed > 5000)
	{

		testTimer = millis();
	}
}





