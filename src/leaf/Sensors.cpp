/**
 * @file Sensors.cpp
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2021
 * 
 */
#include "Sensors.h"

Sensors::Sensors()
{
}

int Sensors::init(void)
{
  Wire.begin();

  /********************
   * HTS221
   ********************/
  // Try to initialize!
  if (!hts.begin_I2C()) {
//  if (!hts.begin_SPI(HTS_CS)) {
//  if (!hts.begin_SPI(HTS_CS, HTS_SCK, HTS_MISO, HTS_MOSI)) {
    Serial.println("Failed to find HTS221 chip");
    while (1) { delay(10); }
  }
  Serial.println("HTS221 Found!");

//  hts.setDataRate(HTS221_RATE_1_HZ);
  Serial.print("Data rate set to: ");
  switch (hts.getDataRate()) {
   case HTS221_RATE_ONE_SHOT: Serial.println("One Shot"); break;
   case HTS221_RATE_1_HZ: Serial.println("1 Hz"); break;
   case HTS221_RATE_7_HZ: Serial.println("7 Hz"); break;
   case HTS221_RATE_12_5_HZ: Serial.println("12.5 Hz"); break;
  }

  hts_temp = hts.getTemperatureSensor();
  hts_temp->printSensorDetails();

  hts_humidity = hts.getHumiditySensor();
  hts_humidity->printSensorDetails();

  _hts221_status.active = true;

  /********************
   * OPT3001
   ********************/
  illum.begin(_OPT3001_ADDRESS);
  illumConfig.RangeNumber = B1100;               // automatic full scale
  illumConfig.ConvertionTime = B1;               // conversion time = 800ms
  illumConfig.ModeOfConversionOperation = B11;   // continuous conversion
  illumConfig.Latch = B0;                        // hysteresis-style
  illumErrorConfig = illum.writeConfig(illumConfig);
  if(illumErrorConfig != NO_ERROR){
    illumErrorConfig = illum.writeConfig(illumConfig);   //retry
  }

  /********************
   * LIS3DH
   ********************/
  accel.begin(_LIS3DH_ADDRESS);
  accel.setClick(0, 0);                      // Disable Interrupt
  accel.setRange(LIS3DH_RANGE_2_G);          // Full scale +/- 2G
  accel.setDataRate(LIS3DH_DATARATE_10_HZ);  // Data rate = 10Hz

  delay(10);
  return 0;
}

void Sensors::awakeHTS221(void)
{
  hts.setActive(true);
  _hts221_status.active = true;
}

void Sensors::sleepHTS221(void)
{
  hts.setActive(false);
  _hts221_status.active = false;
}

float Sensors::getTemp(void)
{
  sensors_event_t temp;
  hts_temp->getEvent(&temp);
  return temp.temperature;
}

float Sensors::getHumid(void)
{
  sensors_event_t humidity;
  hts_humidity->getEvent(&humidity);
  return humidity.relative_humidity;
}

float Sensors::getIllum(void)
{
  OPT3001 result = illum.readResult();

  if(result.error == NO_ERROR){
    _dataIllum = result.lux;
  }

  return _dataIllum;
}

float Sensors::getAccelX(void) {
  return accel.x_g;
}

float Sensors::getAccelY(void) {
  return accel.y_g;
}

float Sensors::getAccelZ(void) {
  return accel.z_g;
}

float Sensors::debugEstimatedCurrent(HardwareSerial *serial) {
  /* TODO: read internal registers in all sensors, and calculate total power consumption. */
  float cur_hts221 = 0.0;
  float cur_opt3001 = 0.0;
  float cur_lis3dh = 0.0;
  float cur_total = 0.0;

  /********************
   * HTS221
   ********************/
  // AV_CONF
  if (_hts221_status.active) {
    cur_hts221 += _HTS221_CUR_ACTIVE;
  } else {
    cur_hts221 += _HTS221_CUR_PDOWN;
  }
  // Heater

  /********************
   * OPT3001
   ********************/

  /********************
   * LIS3DH
   ********************/

  /********************
   * Monitor
   ********************/
  cur_total = cur_hts221 + cur_opt3001 + cur_lis3dh;

  serial->println("===== 4-Sensors =====");
  serial->print("HTS221: ");
  serial->print(cur_hts221);
  serial->println("uA");
  serial->print("OPT3001: ");
  serial->print(cur_opt3001);
  serial->println("uA");
  serial->print("LIS3DH: ");
  serial->print(cur_lis3dh);
  serial->println("uA");
  serial->print("4-Sensors Total: ");
  serial->print(cur_total);
  serial->println("uA");
  serial->println("=====================");
  // return total power consumption
  return cur_total;
}