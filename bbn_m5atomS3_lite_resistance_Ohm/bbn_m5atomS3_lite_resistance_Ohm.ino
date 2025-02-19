#include <M5Unified.h>
#include "NmeaXDR.h"
#include "ResistanceSensor.h"

unsigned long timeout = 0;

ResistanceSensor resistanceSens;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  ResistanceSensor_init(&resistanceSens, G8, DOWNSTREAM, 3.3, 100.0);
  Serial.begin(4800);
}

void loop() {
  if (timeout < millis()) {
    ResistanceSensor_read(&resistanceSens);
    gen_nmea0183_xdr("$BBXDR,G,%.1f,O,Ohms_esp32", resistanceSens.measured_resistance);
    timeout = millis() + 1000;
  }
}
