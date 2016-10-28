#include <Arduino.h>
#include <Adafruit_BNO055.h>

bool blinkState = 0;
void setup() {

	pinMode(13, OUTPUT);
	Serial.begin(9600);

}

void loop() {
	digitalWrite(13, blinkState);
	blinkState = !blinkState;
	Serial.println(blinkState);
	delay(200);
}
