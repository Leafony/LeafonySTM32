// Copyright (c) Leafony. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "LeafonySTM32.h"

/**
 * @brief Construct a new Leafony S T M 3 2:: Leafony S T M 3 2 object
 * 
 */
LeafonySTM32::LeafonySTM32() : _isInited(0) {
}

/**
 * @brief 
 * 
 */
void LeafonySTM32::begin() {
  Serial.begin(115200);
}

/**
 * @brief 
 * 
 */
void LeafonySTM32::update() {

}

/**
 * @brief 
 * 
 */
void LeafonySTM32::powerOff() {

}