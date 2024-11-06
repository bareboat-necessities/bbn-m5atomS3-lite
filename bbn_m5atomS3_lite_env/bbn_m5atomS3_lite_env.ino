#include <M5AtomS3.h>
#include <Arduino.h>
#include <M5UnitENV.h>
#include <Wire.h>
#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

DHT12 dht12;
BMP280 bmp280;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(4800);

  int i = 0;
  while (!dht12.begin(&Wire, DHT12_I2C_ADDR, G2, G1, 100000U) && i < 3) {
    gen_nmea0183_msg("$BBTXT,01,01,01,Sensor not found type=%s", "DHT12");
    delay(4);
    i++;
  }
  i = 0;
  while (!bmp280.begin(&Wire, BMP280_I2C_ADDR, G2, G1, 100000U) && i < 3) {
    gen_nmea0183_msg("$BBTXT,01,01,01,Sensor not found type=%s", "BMP280");
    delay(4);
    i++;
  }

  /* Default settings from datasheet. */
  bmp280.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
                     BMP280::SAMPLING_X2,     /* Temp. oversampling */
                     BMP280::SAMPLING_X16,    /* Pressure oversampling */
                     BMP280::FILTER_X16,      /* Filtering. */
                     BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  if (dht12.update()) {
    gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_DHT12", dht12.humidity);   // %
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_DHT12", dht12.cTemp);      // C
  }
  if (bmp280.update()) {
    gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_BMP280", bmp280.cTemp);        // C
    gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES_BMP280", bmp280.pressure);     // Pa
  }
  delay(1000);
}
