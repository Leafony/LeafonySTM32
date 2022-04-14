/**
 * @file Battery.cpp
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2022
 * 
 */
#include "Battery.h"

/**
 * @brief Construct a new Battery:: Battery object
 * 
 */
Battery::Battery() {
}

/**
 * @brief 
 * 
 */
void Battery::init(void) {
  Wire.begin();
  delay(10);
}

/**
 * @brief 
 * 
 * @return float 
 */
float Battery::getVoltage(void) {
  // read ADC registers:
  Wire.beginTransmission(_BATT_ADC_ADDR);
  Wire.write(0x00);
  Wire.endTransmission(false);
  Wire.requestFrom(_BATT_ADC_ADDR,2);
  uint8_t adcVal1 = Wire.read();
  uint8_t adcVal2 = Wire.read();

  // when ADC is not connected, read values are 0xFF:
  if (adcVal1 == 0xff && adcVal2 == 0xff) {
    adcVal1 = adcVal2 = 0;
  }

  // voltage mV = adcVal * Vref(3.3V) / resolution(8bit) * Vdiv(2)
  double tempMillivolt = ((double)((adcVal1 << 4) | (adcVal2 >> 4)) * 3300 * 2) / 256;
  float dataBatt = (float)(tempMillivolt / 1000);
  return dataBatt;
}