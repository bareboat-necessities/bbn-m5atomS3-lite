#include <M5AtomS3.h>
#include <Arduino.h>
#include <M5UnitENV.h>
#include <Wire.h>
#include "NmeaXDR.h"

DHT12 dht;
BMP280 bmp;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(4800);

  if (!dht.begin(&Wire, DHT12_I2C_ADDR, G2, G1, 100000U)) {
    gen_nmea0183_msg("$BBTXT,01,01,01,Sensor not found type=%s", "DHT12");
  }
  if (!bmp.begin(&Wire, BMP280_I2C_ADDR, G2, G1, 100000U)) {
    gen_nmea0183_msg("$BBTXT,01,01,01,Sensor not found type=%s", "BMP280");
  }

  /* Default settings from datasheet. */
  bmp.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
                  BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  BMP280::FILTER_X16,      /* Filtering. */
                  BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  if (dht.update()) {
    gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_DHT12", dht.humidity);   // %
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_DHT12", dht.cTemp);      // C
  }
  if (bmp.update()) {
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_BMP280", bmp.cTemp);        // C
    gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES_BMP280", bmp.pressure);     // Pa
  }
  delay(1000);
}
