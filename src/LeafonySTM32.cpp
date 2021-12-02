// Copyright (c) Leafony. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "LeafonySTM32.h"

LeafonySTM32::LeafonySTM32() : _isInited(0) {
}

void LeafonySTM32::begin() {
  Serial.begin(115200);
}

void LeafonySTM32::update() {

}

void LeafonySTM32::powerOff() {

}