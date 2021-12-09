// Copyright (c) Leafony. All rights reserved.

// Licensed under the MIT license. See LICENSE file in the project root for full license information.
/**
 * @par Copyright (C), 2017-2021, Leafony
 * @class LeafonySTM32
 * @brief Leafony STM32 Library
 * @file LeafonySTM32.h
 * @author Leafony
 * @version v0.0.1
 * @date 2021/11/23
 * @brief Header for LeafonySTM32.cpp module
 * 
 * @par Description
 * 
 * @par Method List:
 * 
 * @par History:
 *  System:
 *    LeafonySTM32.begin();
 *    LeafonySTM32.update();
 *    LeafonySTM32.powerOff(); 
 * 
 */

#ifndef _LEAFONYSTM32_H_
#define _LEAFONYSTM32_H_

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "STM32LowPower.h"

#include "leaf/Sensors.h"
#include "leaf/Battery.h"
#include "leaf/BLE.h"

class LeafonySTM32
{
  public:
    LeafonySTM32();
    void begin();
    void update();
    void powerOff();

    Sensors sensors;
    Battery battery;
    BLE ble;
  private:
    bool _isInited;
};

#endif
