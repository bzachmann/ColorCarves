#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_BNO055.h>

#include "ColorScale.h"


rgbVal rgbValues;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8);
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  bno.setExtCrystalUse(true);

  delay(1000);
}

void loop(void)
{
	sensors_event_t event;
	bno.getEvent(&event);
	float value = event.orientation.z;
	if(value > 50)
	{
		value = 50;
	}
	else if(value < -50)
	{
		value = -50;
	}
	uint16_t mappedVal = (uint16_t)(map(value, -50, 50, 0, 765));

	rgbValues = ColorScale::getRGB(mappedVal, 0);
	strip.setPixelColor(0, rgbValues.red, rgbValues.green, rgbValues.blue);
	strip.show();
	value++;

	delay(100);


}


