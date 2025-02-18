#include <M5Unified.h>
#include <Arduino.h>
#include <M5_ADS1115.h>
#include <Wire.h>
#include "NmeaXDR.h"

/*
 * @Hardwares: M5AtomS3 Lite + Unit Vmeter ADS1115
 * @Dependent Library:
 * M5_ADS1115: https://github.com/m5stack/M5-ADS1115
 */
   
#define M5_UNIT_VMETER_I2C_ADDR             0x49
#define M5_UNIT_VMETER_EEPROM_I2C_ADDR      0x53
#define M5_UNIT_VMETER_PRESSURE_COEFFICIENT 0.015918958F

ADS1115 Vmeter;

float resolution         = 0.0;
float calibration_factor = 0.0;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Wire.begin();
  Serial.begin(4800);
  while (!Vmeter.begin(&Wire, M5_UNIT_VMETER_I2C_ADDR, G2, G1, 100000U)) {
    Serial.println("Unit Vmeter Init Fail");
    delay(1000);
  }
  Vmeter.setEEPROMAddr(M5_UNIT_VMETER_EEPROM_I2C_ADDR);
  Vmeter.setMode(ADS1115_MODE_SINGLESHOT);
  Vmeter.setRate(ADS1115_RATE_8);
  Vmeter.setGain(ADS1115_PGA_512);
  // | PGA      | Max Input Voltage(V) |
  // | PGA_6144 |        128           |
  // | PGA_4096 |        64            |
  // | PGA_2048 |        32            |
  // | PGA_512  |        16            |
  // | PGA_256  |        8             |

  resolution = Vmeter.getCoefficient() / M5_UNIT_VMETER_PRESSURE_COEFFICIENT;
  calibration_factor = Vmeter.getFactoryCalibration();
}

void loop() {
  int16_t adc_raw = Vmeter.getSingleConversion();
  float voltage   = adc_raw * resolution * calibration_factor;
  //Serial.printf("Cal ADC:%.0f\n", adc_raw * calibration_factor);
  //Serial.printf("Cal Voltage:%.2f mV\n", voltage);
  //Serial.printf("Raw ADC:%d\n\n", adc_raw);
  gen_nmea0183_xdr("$BBXDR,U,%.3f,V,VOLT", voltage / 1000);   // Volt
  delay(1000);
}

