#include <M5AtomS3.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include "NmeaXDR.h"
#include "NmeaChecksum.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme(&Wire); // I2C

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Wire.setClock(100000);
  delay(10);
  Serial.begin(4800);
  while (!bme.begin()) {}
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() {
  if (!bme.performReading()) {
    delay(4);
    return;
  }
  gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_BME680", bme.temperature);             // C
  gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES_BME680", bme.pressure);                // Pa
  gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_BME680", bme.humidity);                // %
  gen_nmea0183_xdr("$BBXDR,H,%.2f,,GASR_BME680", bme.gas_resistance / 1000.0);  // KOhms
  delay(5000);
}
