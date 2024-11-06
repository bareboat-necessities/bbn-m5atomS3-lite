#include <M5AtomS3.h>
#include <Arduino.h>
#include <M5UnitENV.h>
#include <Wire.h>
#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

SHT3X sht3x;
QMP6988 qmp6988;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(4800);
  
  if (!qmp6988.begin(&Wire, QMP6988_SLAVE_ADDRESS_L, G2, G1, 100000U)) {
    gen_nmea0183_msg("$BBTXT,01,01,01,Sensor not found type=%s", "QMP6988");
  }
  if (!sht3x.begin(&Wire, SHT3X_I2C_ADDR, G2, G1, 100000U)) {
    gen_nmea0183_msg("$BBTXT,01,01,01,Sensor not found type=%s", "SHT3X");
  }
}

void loop() {
  if (sht3x.update()) {
    gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_SHT3X", sht3x.humidity);   // %
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_SHT3X", sht3x.cTemp);    // C
  }
  if (qmp6988.update()) {
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_QMP6988", qmp6988.cTemp);        // C
    gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES_QMP6988", qmp6988.pressure);     // Pa
  }
  delay(1000);
}
