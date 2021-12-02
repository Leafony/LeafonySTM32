/**
 * @file BLE.h
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2021
 * 
 */
#ifndef _LEAF_BLE_
#define _LEAF_BLE_

#include <Arduino.h>
#include "../lib/TBGLib.h"

//=====================================================================
// IO definition
//=====================================================================
// Bus-A
// #define BLE_WAKEUP PA8
// #define BLE_TX PA1
// #define BLE_RX PA0

// Bus-B
#define BLE_WAKEUP PB11
#define BLE_TX PC5
#define BLE_RX PC4

class BLE {
  public:
    BLE();
    void init(void);
    void startAdvertising(void);
    void sleep(void);
    void wakeup(void);
  private:
    HardwareSerial Serialble(BLE_TX, BLE_RX);
    BGLib ble112((HardwareSerial *)&Serialble, 0, 0);
};

#endif