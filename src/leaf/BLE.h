/**
 * @file BLE.h
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2022
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
    void setAdvData(uint8 len, uint8 *adv_data);
    void startAdv(void);

    void onBusy(void (* Handler)(void));               // special function to run when entering a "busy" state (e.g. mid-packet)
    void onIdle(void (* Handler)(void));               // special function to run when returning to idle mode
    void onTimeout(void (* Handler)(void));            // special function to run when the parser times out waiting for expected data
    void onBeforeTXCommand(void (* Handler)(void));    // special function to run immediately before sending a command
    void onTXCommandComplete(void (* Handler)(void));  // special function to run immediately after command transmission is complete

    void ble_evt_gatt_server_attribute_value(void (* Handler)(const struct ble_msg_gatt_server_attribute_value_evt_t *msg));
    void ble_evt_le_connection_opend(void (* Handler)(const ble_msg_le_connection_opend_evt_t *msg));
    void ble_evt_le_connection_closed(void (* Handler)(const struct ble_msg_le_connection_closed_evt_t *msg));
    void ble_evt_system_boot(void (* Handler)(const ble_msg_system_boot_evt_t *msg));
    void ble_evt_system_awake(void (* Handler)(void));
    void ble_rsp_system_get_bt_address(void (* Handler)(const struct ble_msg_system_get_bt_address_rsp_t *msg));

    float debugEstimatedCurrent(HardwareSerial *serial);

    HardwareSerial *Serialble;
    BGLib *ble112;

  private:
    const float _BLE_CUR_ACTIVE = 3.8 * 1000;
    const float _BLE_CUR_SLEEP = 2.8;

    struct _BLE_Status {
      bool active = false;
    } _ble_status;
};

#endif