#include <M5AtomS3.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SGP30.h>

Adafruit_SGP30 sgp;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  Wire.begin();
  Wire.setClock(100000);
  Serial.printf("SGP30 before init\n");
  delay(10);
  if (!sgp.begin(&Wire)) {  // Init the sensor.
    while (1) ;
  }
  Serial.printf("SGP30 init\n");
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

int counter = 0;
void loop() {
  // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
  //float temperature = 22.1; // [°C]
  //float humidity = 45.2; // [%RH]
  //sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

  if (!sgp.IAQmeasure()) {  
    // Commands the sensor to take a single eCO2/VOC measurement.
    //Serial.println("Measurement failed");
    return;
  }
  Serial.printf("TVOC:%d ppb\n", sgp.TVOC);
  Serial.printf("eCO2:%d ppm\n", sgp.eCO2);

  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return;
  }
  Serial.printf("rawH2:%d\n", sgp.rawH2);
  Serial.printf("rawEthanol2:%d\n", sgp.rawEthanol);

  delay(1000);

  counter++;
  if (counter == 30) {
    counter = 0;

    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get baseline readings");
      return;
    }
    Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
    Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
  }
}
