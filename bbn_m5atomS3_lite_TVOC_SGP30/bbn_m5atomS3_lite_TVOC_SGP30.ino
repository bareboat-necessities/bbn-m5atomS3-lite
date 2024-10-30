#include <M5AtomS3.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SGP30.h>
#include "NmeaXDR.h"
#include "NmeaChecksum.h"

Adafruit_SGP30 sgp;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  Wire.begin();
  Wire.setClock(100000);
  delay(10);
  if (!sgp.begin(&Wire, true)) {  // Init the sensor.
    while (1) ;
  }
  //Serial.print("Found SGP30 serial #");
  //Serial.print(sgp.serialnumber[0], HEX);
  //Serial.print(sgp.serialnumber[1], HEX);
  //Serial.println(sgp.serialnumber[2], HEX);
}

int counter = 0;
void loop() {
  // If you have a temperature / humidity sensor, you can set the absolute humidity 
  // to enable the humditiy compensation for the air quality signals

  //float temperature = 22.1; // [°C]
  //float humidity = 45.2; // [%RH]
  //sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

  // Commands the sensor to take a single eCO2/VOC measurement.
  if (!sgp.IAQmeasure()) { 
    // Measurement failed
    delay(4);
    return;
  }
  gen_nmea0183_xdr("$BBXDR,X,%.0f,,TVOC", sgp.TVOC);        // ppb
  gen_nmea0183_xdr("$BBXDR,X,%.0f,,eCO2", sgp.eCO2);        // ppm

  if (! sgp.IAQmeasureRaw()) {
    // Raw Measurement failed
    delay(4);
    return;
  }
  gen_nmea0183_xdr("$BBXDR,X,%.0f,,rawH2", sgp.rawH2);       
  gen_nmea0183_xdr("$BBXDR,X,%.0f,,rawEthanol", sgp.rawEthanol);       

  delay(1000);

  counter++;
  if (counter == 30) {
    counter = 0;
    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      return;
    }
  }
}
