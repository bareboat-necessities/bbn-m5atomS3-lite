#include <M5AtomS3.h>
#include <M5Unified.h>
#include <Arduino.h>
#include <Wire.h>
#include <M5_DLight.h>
#include "NmeaXDR.h"

M5_DLight sensor;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(4800);
  sensor.begin();

  // CONTINUOUSLY_H_RESOLUTION_MODE
  // CONTINUOUSLY_H_RESOLUTION_MODE2
  // CONTINUOUSLY_L_RESOLUTION_MODE
  // ONE_TIME_H_RESOLUTION_MODE
  // ONE_TIME_H_RESOLUTION_MODE2
  // ONE_TIME_L_RESOLUTION_MODE
  sensor.setMode(CONTINUOUSLY_L_RESOLUTION_MODE);
}

void loop() {
  uint16_t lux = sensor.getLUX();
  gen_nmea0183_xdr("$BBXDR,X,%.1f,L,ILLU", (float)lux);
  delay(1000);
}
