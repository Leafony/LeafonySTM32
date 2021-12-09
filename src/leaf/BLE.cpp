/**
 * @file BLE.cpp
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2021
 * 
 */
#include "BLE.h"

BLE::BLE() {
  this->Serialble = new HardwareSerial(BLE_TX, BLE_RX);
  this->ble112 = new BGLib((HardwareSerial *)this->Serialble, 0, 0);
}

void BLE::init(void) {
  pinMode(BLE_WAKEUP, OUTPUT);    // BLE Wakeup/Sleep
  digitalWrite(BLE_WAKEUP, HIGH); // BLE Wakeup
}

void BLE::onBusy(void (* Handler)(void)) {
  this->ble112->onBusy = Handler;
}

void BLE::onIdle(void (* Handler)(void)) {
  this->ble112->onIdle = Handler;
}

void BLE::onTimeout(void (* Handler)(void)) {
  this->ble112->onTimeout = Handler;
}

void BLE::onBeforeTXCommand(void (* Handler)(void)) {
  this->ble112->onBeforeTXCommand = Handler;
}

void BLE::onTXCommandComplete(void (* Handler)(void)) {
  this->ble112->onTXCommandComplete = Handler;
}