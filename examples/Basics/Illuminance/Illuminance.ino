#include <LeafonySTM32.h>

static LeafonySTM32 leafony;

void setup() {  
  leafony.begin();
  leafony.sensors.init();
}

void loop() {
  Serial.println(leafony.sensors.getIllum());
  delay(1000);
}