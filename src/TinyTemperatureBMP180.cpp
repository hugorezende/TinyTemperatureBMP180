#include <Arduino.h>
#include "TinyTemperatureBMP180.h"

// SofftI2C configs
#define I2C_TIMEOUT 1000
#define I2C_PULLUP 1
#define SDA_PORT PORTC
#define SDA_PIN 4 // = A4
#define SCL_PORT PORTC
#define SCL_PIN 5 // = A5

#define ADDRESS_SENSOR 0x77 // BMP180 address
#define ADDRLEN 1           // Address length

#include <SoftI2CMaster.h>

int16_t ac1, ac2, ac3, b1, b2, mb, mc, md; // Store sensor PROM values from BMP180
uint16_t ac4, ac5, ac6;                    // Store sensor PROM values from BMP180

// Ultra Low Power       OSS = 0, OSD =  5ms
// Standard              OSS = 1, OSD =  8ms
// High                  OSS = 2, OSD = 14ms
// Ultra High Resolution OSS = 3, OSD = 26ms

const uint8_t oss = 3;  // Set oversampling setting
const uint8_t osd = 26; // with corresponding oversampling delay

TinyTemperature::TinyTemperature()
{
}

void TinyTemperature::initSensor()
{
  ac1 = read_2_bytes(0xAA);
  ac2 = read_2_bytes(0xAC);
  ac3 = read_2_bytes(0xAE);
  ac4 = read_2_bytes(0xB0);
  ac5 = read_2_bytes(0xB2);
  ac6 = read_2_bytes(0xB4);
  b1 = read_2_bytes(0xB6);
  b2 = read_2_bytes(0xB8);
  mb = read_2_bytes(0xBA);
  mc = read_2_bytes(0xBC);
  md = read_2_bytes(0xBE);

  //  Serial.println("");
  //  Serial.print(F("AC1 = "));
  //  Serial.println(ac1);
  //  Serial.print(F("AC2 = "));
  //  Serial.println(ac2);
  //  Serial.print(F("AC3 = "));
  //  Serial.println(ac3);
  //  Serial.print(F("AC4 = "));
  //  Serial.println(ac4);
  //  Serial.print(F("AC5 = "));
  //  Serial.println(ac5);
  //  Serial.print(F("AC6 = "));
  //  Serial.println(ac6);
  //  Serial.print(F("B1 = "));
  //  Serial.println(b1);
  //  Serial.print(F("B2 = "));
  //  Serial.println(b2);
  //  Serial.print(F("MB = "));
  //  Serial.println(mb);
  //  Serial.print(F("MC = "));
  //  Serial.println(mc);
  //  Serial.print(F("MD = "));
  //  Serial.println(md);
  //  Serial.println("");
}

uint16_t TinyTemperature::read_2_bytes(uint8_t code)
{
  uint16_t value;

  i2c_start_wait((ADDRESS_SENSOR << 1) | I2C_WRITE);
  if (!i2c_write(code))
    return;
  i2c_stop();
  delay(6);
  i2c_start_wait((ADDRESS_SENSOR << 1) | I2C_READ);
  value = (i2c_read(false) << 8) | i2c_read(true);
  i2c_stop();
  return value;
}

float TinyTemperature::getTemp()
{
  float T;
  uint16_t UT;
  int32_t x1, x2, b5;

  i2c_start_wait((ADDRESS_SENSOR << 1) | I2C_WRITE);
  if (!i2c_write(0xf4)) {
    Serial.println("Error I2C");
    return;
  }
  if (!i2c_write(0x2e)) {
    Serial.println("Error I2C");
    return;
  }
  i2c_stop();
  delay(6);

  UT = read_2_bytes(0xf6);
  x1 = (UT - (int32_t)ac6) * (int32_t)ac5 >> 15;
  x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
  b5 = x1 + x2;
  T = (b5 + 8) >> 4;
  return (T / 10.0); // Return Temperature
}
