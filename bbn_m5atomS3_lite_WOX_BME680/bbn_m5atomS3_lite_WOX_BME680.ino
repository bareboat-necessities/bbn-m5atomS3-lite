#include <M5AtomS3.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme680(&Wire); // I2C

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Wire.setClock(100000);
  delay(10);
  Serial.begin(4800);
  int i = 0;
  while (!bme680.begin() && i < 3) {
    gen_nmea0183_msg("$BBTXT,01,01,01,Sensor not found type=%s", "BME680");
    delay(4);
    i++;
  }
  // Set up oversampling and filter initialization
  bme680.setTemperatureOversampling(BME680_OS_8X);
  bme680.setHumidityOversampling(BME680_OS_2X);
  bme680.setPressureOversampling(BME680_OS_4X);
  bme680.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme680.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() {
  if (!bme680.performReading()) {
    delay(4);
    return;
  }
  gen_nmea0183_xdr("$BBXDR,C,%.2f,C,TEMP_BME680", bme680.temperature);             // C
  gen_nmea0183_xdr("$BBXDR,P,%.2f,P,PRES_BME680", bme680.pressure);                // Pa
  gen_nmea0183_xdr("$BBXDR,H,%.2f,P,HUMI_BME680", bme680.humidity);                // %
  gen_nmea0183_xdr("$BBXDR,H,%.2f,,GASR_BME680", bme680.gas_resistance / 1000.0);  // KOhms
  delay(5000);
}
