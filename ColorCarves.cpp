#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_BNO055.h>

#include "ColorScale.h"
#include "TiltSensor.h"
#include "CMP.h"
#include "StripColorSettings.h";

//Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8);

TiltSensor sensor = TiltSensor();
uint16_t tenTimer = 0;
uint64_t hundredTimer = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, 6);




void setup(void)
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test");
  Serial.println("");

  strip.begin();
  strip.setBrightness(5);
  strip.show();


  /* Initialise the sensor */
  if(!sensor.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
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
		//Serial.println("10 ms");
	}
	if(millis() - hundredTimer > 50)
	{
		//TODO create function in tiltSensor that does updateLEDs(&stripColors)
		//call that function here instead;
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
		for(int i = 0; i < NUM_LEDS; i++)
		{
			stripSettings.setValue(i, mappedVal);
		}


		//TODO create new class that inherits neopixel library class that also does void setStrip(StripColorSettings mycolors);
		//call that funciton here instead;
		for(int i = 0; i < NUM_LEDS; i++)
		{
			rgbVal rgbValues = ColorScale::getRGB(stripSettings.getValue(i), stripSettings.getOffset(i));
			strip.setPixelColor(i, rgbValues.red, rgbValues.green, rgbValues.blue);
		}
		strip.show();

	    hundredTimer = millis();
	    cmp_update();
	    //Serial.println("50 ms  -   ");
	}
}



