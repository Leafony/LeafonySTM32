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

#define BLE_WAKEUP PB12 // D7   PB12
#define BLE_RX PA0      // [A2] PA1
#define BLE_TX PA1      // [A1] PA0
#define INT_0 PC7       // INT0
#define INT_1 PB3       // INT1

class BLE {
  public:
    BLE();
    void init(void);
    void setAdvertising();
    void startAdvertising(void);
    void sleep(void);
    void wakeup(void);

    void onBusy(void (* Handler)(void));               // special function to run when entering a "busy" state (e.g. mid-packet)
    void onIdle(void (* Handler)(void));               // special function to run when returning to idle mode
    void onTimeout(void (* Handler)(void));            // special function to run when the parser times out waiting for expected data
    void onBeforeTXCommand(void (* Handler)(void));    // special function to run immediately before sending a command
    void onTXCommandComplete(void (* Handler)(void));  // special function to run immediately after command transmission is complete

    HardwareSerial *Serialble;
    BGLib *ble112;
};

#endif