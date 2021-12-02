#include <LeafonySTM32.h>

static LeafonySTM32 leafony;

void setup() {  
  leafony.begin();
  leafony.battery.init();
}

void loop() {
  Serial.println(leafony.battery.getVoltage());
  delay(1000);
}