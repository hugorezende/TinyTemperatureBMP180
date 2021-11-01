/*
	TinyTemperatureBMP180
	Created by Hugo Rezende
	hugorezende.com.br/blog
*/

// SDA = A4
// SCL = A5

#include <TinyTemperatureBMP180.h>
TinyTemperature bmp;
void setup() {
  Serial.begin(57600);
  // put your setup code here, to run once:
  bmp.initSensor();
}

void loop() {
  Serial.println(bmp.getTemp());
  delay(100);
  // put your main code here, to run repeatedly:

}
