#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_BNO055.h>

#include "ColorScale.h"
#include "TiltSensor.h"
#include "CMP.h"


rgbVal rgbValues;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8);
TiltSensor sensor = TiltSensor();
uint16_t tenTimer = 0;
uint64_t hundredTimer = 0;

void setup(void)
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test");
  Serial.println("");

  strip.begin();
  strip.setBrightness(50);
  strip.setPixelColor(0, 255, 0, 0);
  strip.show();

  /* Initialise the sensor */
  if(!sensor.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000);
  tenTimer = millis();
  hundredTimer = millis();
  cmp_initialize();
}

void loop(void)
{
//	strip.setPixelColor(0, 255, 0, 0);
//	strip.show();
//	delay(500);
//	strip.setPixelColor(0, 0, 255, 0);
//	strip.show();
//	delay(500);
//	strip.setPixelColor(0,0,0,255);
//	strip.show();
//	delay(500);

	if(millis() - tenTimer > 10)
	{
		sensor.update();
		tenTimer = millis();
		//Serial.println("10 ms");
	}
	if(millis() - hundredTimer > 50)
	{
		int32_t angle = sensor.getAngle();
		if(angle > 500)
		{
			angle = 500;
		}
		else if(angle < -500)
		{
			angle = -500;
		}
		uint16_t mappedVal = (uint16_t)(map(angle, -500, 500, 0, 765));
		rgbValues = ColorScale::getRGB(mappedVal, 0);
	    strip.setPixelColor(0, rgbValues.red, rgbValues.green, rgbValues.blue);
	    strip.show();
	    hundredTimer = millis();
	    cmp_update();
	    //Serial.println("50 ms  -   ");
	}
}



