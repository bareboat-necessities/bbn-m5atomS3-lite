#include <M5AtomS3.h>
#include <M5Unified.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS G8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  sensors.begin();
  int count = sensors.getDeviceCount();
  Serial.printf("Sensors found %d\n", count);
}

void loop() {
  int count = sensors.getDeviceCount();
  if (count > 0) {
    sensors.requestTemperatures();
    for (int i = 0; i < count; i++) {
      Serial.printf("Temp %.2f\n", sensors.getTempCByIndex(i));
    }
  }
  delay(1000);
}
