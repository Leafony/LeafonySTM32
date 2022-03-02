/**
 * @file Sensors.h
 * @brief 
 * @version 0.1
 * @date 2021-11-23
 * 
 * @copyright Copyright (c) Leafony Systems 2021
 * 
 */
#ifndef _LEAF_SENSORS_
#define _LEAF_SENSORS_

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_HTS221.h>
#include <ClosedCube_OPT3001.h>
#include <Adafruit_LIS3DH.h>

class Sensors {
  public:
    Sensors();
    int init(void);
    void awakeHTS221(void);
    void awakeOPT3001(void);
    void awakeLIS3DH(void);
    void sleepHTS221(void);
    void sleepOPT3001(void);
    void sleepLIS3DH(void);
    float getTemp(void);
    float getHumid(void);
    float getIllum(void);
    float getAccelX(void);
    float getAccelY(void);
    float getAccelZ(void);
    float debugEstimatedCurrent(HardwareSerial *serial);
  private:
    const uint8_t _OPT3001_ADDRESS = 0x45;
    const uint8_t _LIS3DH_ADDRESS  = 0x19;

    const float _HTS221_CUR_ACTIVE = 2.0;
    const float _HTS221_CUR_PDOWN = 0.5;
    const float _HTS221_HEATER_ON = 33 * 1000; // Heater ON current at 3.3V Vdd.
    const float _OPT3001_CUR_ACTIVE = 3.7;
    const float _OPT3001_CUR_PDOWN = 0.4;
    const float _LIS3DH_CUR_ACTIVE_50Hz = 11.0;
    const float _LIS3DH_CUR_ACTIVE_1Hz = 2.0;
    const float _LIS3DH_CUR_ACTIVE_LP50Hz = 6.0;
    const float _LIS3DH_CUR_PDOWN = 0.5;

    struct _HTS221_Status {
      bool active = false;
      bool heater = false; 
    } _hts221_status;

    struct _OPT3001_Status {
      bool active = false;
    } _opt3001_status;

    struct _LIS3DH_Status {
      bool active = false;
    } _lis3dh_status;

    Adafruit_HTS221 hts;
    Adafruit_Sensor *hts_humidity, *hts_temp;
    ClosedCube_OPT3001 illum;
    OPT3001_Config illumConfig;
    OPT3001_ErrorCode illumErrorConfig;
    float _dataIllum;

    Adafruit_LIS3DH accel = Adafruit_LIS3DH();
};

#endif