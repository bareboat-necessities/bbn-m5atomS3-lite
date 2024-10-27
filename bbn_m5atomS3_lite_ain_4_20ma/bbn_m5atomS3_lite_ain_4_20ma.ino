#include <M5AtomS3.h>
#include "MODULE_4_20MA.h"

MODULE_4_20MA meter;

void show_current_value(void) {
  Serial.printf("Current:%.2fmA\n", (float)(meter.getCurrentValue(0)) / 100.0);
}

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(4800);
  while (!(meter.begin(&Wire, MODULE_4_20MA_ADDR, G2, G1, 100000UL))) ;
}

void loop() {
  show_current_value();
  delay(1000);
}
