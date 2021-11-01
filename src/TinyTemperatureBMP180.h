/*
  TinyTemperature - Get temperature with BMP180 with few memory as possible
  Created by Hugo Rezende - 2021.
  Released into the public domain.

  This library use Software I2C library
  https://playground.arduino.cc/Main/SoftwareI2CLibrary/
*/

#ifndef TINY_TEMPERATURE_H
#define TINY_TEMPERATURE_H

class TinyTemperature
{
  public:
    TinyTemperature();
    uint16_t read_2_bytes(uint8_t code);
    float getTemp();
    void initSensor();

  private:
    int16_t ac1, ac2, ac3, b1, b2, mb, mc, md; // Store sensor PROM values from BMP180
    uint16_t ac4, ac5, ac6;                    // Store sensor PROM values from BMP180
    float T, P;
    
};
#endif
