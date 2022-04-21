#include <LeafonySTM32.h>

static LeafonySTM32 leafony;

void setup() {  
  leafony.begin();
  leafony.sensors.init();
}

void loop() {
  Serial.println("Awake");
  leafony.sensors.awakeLIS3DH();
  Serial.println(leafony.sensors.getAccelX());
  Serial.println(leafony.sensors.getAccelY());
  Serial.println(leafony.sensors.getAccelZ());
  leafony.sensors.debugEstimatedCurrent(&Serial);
  delay(1000);

  Serial.println("Sleep");
  leafony.sensors.sleepLIS3DH();
  leafony.sensors.debugEstimatedCurrent(&Serial);
  delay(1000);
}