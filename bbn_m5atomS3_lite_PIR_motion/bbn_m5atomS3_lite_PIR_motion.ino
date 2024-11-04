#include <M5AtomS3.h>
#include "NmeaXDR.h"

#define PIR_MOTION_PIN G7

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  pinMode(PIR_MOTION_PIN, INPUT);
}

void loop() {
  bool sensed = digitalRead(PIR_MOTION_PIN) > 0;
  if (sensed) {
    gen_nmea0183_xdr("$BBXDR,S,1,,PIR_MOTION", 0);
  }
  delay(500);
}
