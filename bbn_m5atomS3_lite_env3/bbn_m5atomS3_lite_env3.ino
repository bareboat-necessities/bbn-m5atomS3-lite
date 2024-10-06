#include <M5AtomS3.h>
#include <M5Unified.h>
#include <Arduino.h>
#include <M5UnitENV.h>
#include <Wire.h>
#include "NmeaXDR.h"

SHT3X sht3x;
QMP6988 qmp;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(4800);

  if (!qmp.begin(&Wire, QMP6988_SLAVE_ADDRESS_L, G2, G1, 100000U)) {
    Serial.println("Couldn't find QMP6988");
    while (1) delay(1);
  }

  if (!sht3x.begin(&Wire, SHT3X_I2C_ADDR, G2, G1, 100000U)) {
    Serial.println("Couldn't find SHT3X");
    while (1) delay(1);
  }
}

void loop() {
  if (sht3x.update()) {
    gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI", sht3x.humidity);   // %
    //gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP", sht3x.cTemp);    // C
  }

  if (qmp.update()) {
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP", qmp.cTemp);        // C
    gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES", qmp.pressure);     // Pa
  }
  delay(1000);
}
