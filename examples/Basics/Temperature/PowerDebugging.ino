#include <LeafonySTM32.h>

static LeafonySTM32 leafony;

void setup() {  
  leafony.begin();
  leafony.sensors.init();
}

void loop() {
  Serial.println("Awake");
  leafony.sensors.awakeHTS221();
  Serial.println(leafony.sensors.getTemp());
  leafony.sensors.debugEstimatedCurrent(&Serial);
  delay(1000);

  Serial.println("Sleep");
  leafony.sensors.sleepHTS221();
  leafony.sensors.debugEstimatedCurrent(&Serial);
  delay(1000);
}