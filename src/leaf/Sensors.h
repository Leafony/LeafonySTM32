/**
 * @file Sensors.h
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2021
 * 
 */
#ifndef _LEAF_SENSORS_
#define _LEAF_SENSORS_

#include <Arduino.h>
#include <Wire.h>
#include <HTS221.h>
#include <ClosedCube_OPT3001.h>
#include <Adafruit_LIS3DH.h>

class Sensors {
  public:
    Sensors();
    int init(void);
    float getTemp(void);
    float getHumid(void);
    float getIllum(void);
    float getAccelX(void);
    float getAccelY(void);
    float getAccelZ(void);
  private:
    const uint8_t _OPT3001_ADDRESS=0x45;
    const uint8_t _LIS3DH_ADDRESS=0x19;

    ClosedCube_OPT3001 illum;
    OPT3001_Config illumConfig;
    OPT3001_ErrorCode illumErrorConfig;
    float _dataIllum;

    Adafruit_LIS3DH accel = Adafruit_LIS3DH();
};

#endif