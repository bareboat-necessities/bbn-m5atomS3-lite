#include <M5Unified.h>
#include <Wire.h>

#include "NmeaXDR.h"
#include "NmeaChecksum.h"
#include "MODULE_4_20MA.h"

MODULE_4_20MA meter;

void show_current_value(void) {
  gen_nmea0183_xdr("$BBXDR,I,%.5f,A,AMPS", (float)(meter.getCurrentValue(0)) / 100.0 / 1000.0);        // Amp
}

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Wire.begin();
  Serial.begin(4800);
  while (!(meter.begin(&Wire, MODULE_4_20MA_ADDR, G2, G1, 100000UL))) ;
}

void loop() {
  show_current_value();
  delay(1000);
}
