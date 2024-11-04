#include <M5AtomS3.h>
#include "NmeaXDR.h"

/*
 * https://shop.m5stack.com/products/pir-module
 * 
 * PIR Motion Sensor (AS312) to NMEA 0183 XDR
 */
#define PIR_MOTION_PIN G7

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  pinMode(PIR_MOTION_PIN, INPUT);
  digitalRead(PIR_MOTION_PIN);
}

void loop() {
  bool sensed = digitalRead(PIR_MOTION_PIN) == 1;
  if (sensed) {
    gen_nmea0183_xdr("$BBXDR,S,1,,PIR_MOTION", 1);
  }
  delay(500);
}
