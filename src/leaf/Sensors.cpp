/**
 * @file Sensors.cpp
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2021
 * 
 */
#include "Sensors.h"

Sensors::Sensors()
{
}

int Sensors::init(void)
{
  Wire.begin();

  smeHumidity.begin();
  illum.begin(_OPT3001_ADDRESS);
  illumConfig.RangeNumber = B1100;               // automatic full scale
  illumConfig.ConvertionTime = B1;               // conversion time = 800ms
  illumConfig.ModeOfConversionOperation = B11;   // continuous conversion
  illumConfig.Latch = B0;                        // hysteresis-style
  illumErrorConfig = illum.writeConfig(illumConfig);
  if(illumErrorConfig != NO_ERROR){
    illumErrorConfig = illum.writeConfig(illumConfig);   //retry
  }

  accel.begin(_LIS3DH_ADDRESS);
  accel.setClick(0, 0);                      // Disable Interrupt
  accel.setRange(LIS3DH_RANGE_2_G);          // Full scale +/- 2G
  accel.setDataRate(LIS3DH_DATARATE_10_HZ);  // Data rate = 10Hz

  delay(10);
  return 0;
}

float Sensors::getTemp(void)
{
  return (float)smeHumidity.readTemperature();;
}

float Sensors::getHumid(void)
{
  return (float)smeHumidity.readHumidity();
}

float Sensors::getIllum(void)
{
  OPT3001 result = illum.readResult();

  if(result.error == NO_ERROR){
    _dataIllum = result.lux;
  }

  return _dataIllum;
}

float Sensors::getAccelX(void) {
  return accel.x_g;
}

float Sensors::getAccelY(void) {
  return accel.y_g;
}

float Sensors::getAccelZ(void) {
  return accel.z_g;
}