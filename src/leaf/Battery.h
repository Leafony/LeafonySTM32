/**
 * @file Battery.h
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2021
 * 
 */
#ifndef _LEAF_BATTERY_
#define _LEAF_BATTERY_

#include <Arduino.h>
#include <Wire.h>

class Battery {
  public:
    Battery();
    void init(void);
    float getVoltage(void);
  private:
    const int _BATT_ADC_ADDR = 0x50;
};

#endif