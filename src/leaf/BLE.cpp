/**
 * @file BLE.cpp
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2022
 * 
 */
#include "BLE.h"

/**
 * @brief Construct a new BLE::BLE object
 * 
 */
BLE::BLE() {
  this->Serialble = new HardwareSerial(BLE_TX, BLE_RX);
  this->ble112 = new BGLib((HardwareSerial *)this->Serialble, 0, 0);
}

/**
 * @brief 
 * 
 */
void BLE::init(void) {
  pinMode(BLE_WAKEUP, OUTPUT);    // BLE Wakeup/Sleep
  digitalWrite(BLE_WAKEUP, HIGH); // BLE Wakeup


  uint8_t tm = 0;
  this->Serialble->begin(9600);
  while (!this->Serialble && tm < 150)
  { // Serial起動待ち タイムアウト1.5s
    tm++;
    delay(10);
  }

  // TODO: wait to boot up here
  // while (!bSystemBootBle)
  // {
  //   this->ble112->checkActivity(100);
  // }

  this->ble112->ble_cmd_system_get_bt_address();
  while (this->ble112->checkActivity(1000));

  /* interval_min : 250ms( = 400 x 0.625ms ) */
  /* interval_max : 500ms( = 800 x 0.625ms ) */
  this->ble112->ble_cmd_le_gap_set_adv_parameters(400, 800, 7); /* [BGLIB] <interval_min> <interval_max> <channel_map> */
  while (this->ble112->checkActivity(1000));
}

/**
 * @brief 
 * 
 */
void BLE::sleep(void) {
  this->ble112->ble_cmd_le_gap_stop_advertising(0);
  while (this->ble112->checkActivity());

  this->ble112->ble_cmd_system_halt(1);
  while (this->ble112->checkActivity());

  digitalWrite(BLE_WAKEUP, LOW);
  delay(500);
}

/**
 * @brief 
 * 
 */
void BLE::wakeup(void) {
  digitalWrite(BLE_WAKEUP, HIGH);
  delay(500);

  this->ble112->ble_cmd_system_halt(0);
  while (this->ble112->checkActivity());

  this->ble112->ble_cmd_le_gap_set_adv_parameters(400, 800, 7);
  while (this->ble112->checkActivity(1000));
}

/**
 * @brief 
 * 
 * @param len 
 * @param adv_data 
 */
void BLE::setAdvData(uint8 len, uint8 *adv_data) {
  this->ble112->ble_cmd_le_gap_set_adv_data(SCAN_RSP_ADVERTISING_PACKETS, len, adv_data);
  while (this->ble112->checkActivity(1000));
}

/**
 * @brief 
 * 
 */
void BLE::startAdv(void) {
  this->ble112->ble_cmd_le_gap_start_advertising(0, LE_GAP_USER_DATA, LE_GAP_SCANNABLE_NON_CONNECTABLE);
  while (this->ble112->checkActivity(1000));
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::onBusy(void (* Handler)(void)) {
  this->ble112->onBusy = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::onIdle(void (* Handler)(void)) {
  this->ble112->onIdle = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::onTimeout(void (* Handler)(void)) {
  this->ble112->onTimeout = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::onBeforeTXCommand(void (* Handler)(void)) {
  this->ble112->onBeforeTXCommand = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::onTXCommandComplete(void (* Handler)(void)) {
  this->ble112->onTXCommandComplete = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::ble_evt_gatt_server_attribute_value(void (* Handler)(const struct ble_msg_gatt_server_attribute_value_evt_t *msg)) {
  this->ble112->ble_evt_gatt_server_attribute_value = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::ble_evt_le_connection_opend(void (* Handler)(const ble_msg_le_connection_opend_evt_t *msg)) {
  this->ble112->ble_evt_le_connection_opend = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::ble_evt_le_connection_closed(void (* Handler)(const struct ble_msg_le_connection_closed_evt_t *msg)) {
  this->ble112->ble_evt_le_connection_closed = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::ble_evt_system_boot(void (* Handler)(const ble_msg_system_boot_evt_t *msg)) {
  this->ble112->ble_evt_system_boot = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::ble_evt_system_awake(void (* Handler)(void)) {
  this->ble112->ble_evt_system_awake = Handler;
}

/**
 * @brief 
 * 
 * @param Handler 
 */
void BLE::ble_rsp_system_get_bt_address(void (* Handler)(const struct ble_msg_system_get_bt_address_rsp_t *msg)) {
  this->ble112->ble_rsp_system_get_bt_address = Handler;
}