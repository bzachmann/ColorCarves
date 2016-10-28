#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <Adafruit_NeoPixel.h>

#include "ColorScale.h"

Adafruit_BNO055 bno = Adafruit_BNO055(55);

double minX = 0;
double maxX = 0;
double minY = 0;
double maxY = 0;
double minZ = 0;
double maxZ = 0;
sensors_event_t event;

uint16_t value = 0;
rgbVal rgbValues;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 8);

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  strip.begin();
  strip.setBrightness(50);
  strip.show();

  /* Initialise the sensor */
//  if(!bno.begin())
//  {
//    /* There was a problem detecting the BNO055 ... check your connections */
//    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//    while(1);
//  }
//
//  delay(1000);
//
//  bno.setExtCrystalUse(true);
//
//  delay(5000);
//  bno.getEvent(&event);
//  minX = maxX = event.orientation.x;
//  minY = maxY = event.orientation.y;
//  minZ = maxZ = event.orientation.z;
//  Serial.println("***************ORIGINAL VALUES**********************");
//  Serial.print("minX: ");
//  Serial.print(minX, 4);
//  Serial.print("\tmaxX: ");
//  Serial.print(maxX, 4);
//  Serial.print("\tminY: ");
//  Serial.print(minY, 4);
//  Serial.print("\tmaxY: ");
//  Serial.print(maxY, 4);
//  Serial.print("\tminZ: ");
//  Serial.print(minZ, 4);
//  Serial.print("\tmaxZ: ");
//  Serial.print(maxZ, 4);
//  Serial.println("****************************************************");
//  Serial.println("");
//  Serial.println("");
}

void loop(void)
{
	rgbValues = ColorScale::getRGB(value, 0);
	Serial.print("Red: ");
	Serial.print(rgbValues.red);
	Serial.print("\tGreen: ");
	Serial.print(rgbValues.green);
	Serial.print("\tBlue: ");
	Serial.print(rgbValues.blue);
	Serial.println("");
	strip.setPixelColor(0, rgbValues.red, rgbValues.green, rgbValues.blue);
	strip.show();
	value++;
	if(value == 766)
	{
		value = 0;
	}
	delay(100);




  /* Get a new sensor event */

//  bno.getEvent(&event);
//  if(event.orientation.x < minX)
//	  minX = event.orientation.x;
//  if(event.orientation.x > maxX)
//	  maxX = event.orientation.x;
//  if(event.orientation.y < minY)
//  	  minY = event.orientation.y;
//  if(event.orientation.y > maxY)
//  	  maxY = event.orientation.y;
//  if(event.orientation.z < minZ)
//  	  minZ = event.orientation.z;
//  if(event.orientation.z > maxZ)
//  	  maxZ = event.orientation.z;
//
//  /* Display the floating point data */
//  Serial.print("minX: ");
//  Serial.print(minX, 4);
//  Serial.print("\tmaxX: ");
//  Serial.print(maxX, 4);
//  Serial.print("\tminY: ");
//  Serial.print(minY, 4);
//  Serial.print("\tmaxY: ");
//  Serial.print(maxY, 4);
//  Serial.print("\tminZ: ");
//  Serial.print(minZ, 4);
//  Serial.print("\tmaxZ: ");
//  Serial.print(maxZ, 4);
//  Serial.println("");
//
//  delay(100);


}


