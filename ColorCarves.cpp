#include <Arduino.h>
#include <Adafruit_BNO055.h>

#include "NeoPixelStrip.h"
#include "TiltSensor.h"
#include "CMP.h"
#include "StripColorSettings.h"


TiltSensor sensor = TiltSensor();
uint16_t tenTimer = 0;
uint64_t hundredTimer = 0;
NeoPixelStrip strip = NeoPixelStrip(NUM_LEDS, 6);

bool tiltEnable = 1;

void setup(void)
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("ColorCarves");
  Serial.println("");

  strip.begin();
  strip.setBrightness(5);
  strip.show();

  if(!sensor.begin())
  {
    Serial.print("no BNO055 detected");
    while(1);
  }

  tenTimer = millis();
  hundredTimer = millis();
  cmp_initialize();
}

void loop(void)
{

	if(millis() - tenTimer > 10)
	{
		sensor.update();
		tenTimer = millis();
	}

	if(millis() - hundredTimer > 50)
	{

		if(tiltEnable)
		{
			sensor.updateColors(stripSettings);
		}

		strip.setStrip(stripSettings);
		strip.show();

	    hundredTimer = millis();
	    cmp_update();
	}
}



