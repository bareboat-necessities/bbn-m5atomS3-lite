#include <M5AtomS3.h>
#include <M5Unified.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS G8          // Pin to which 1wire bus is connected to esp32
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

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void loop() {
  int count = sensors.getDeviceCount();
  if (count > 0) {
    sensors.requestTemperatures();
    for (int i = 0; i < count; i++) {
      DeviceAddress addr;
      if (!sensors.getAddress(addr, i)) {
        Serial.println("Unable to find address for Device");
      } else {
        printAddress(addr);
      }
      Serial.printf(" Temp %.2f\n", sensors.getTempCByIndex(i));
    }
  }
  delay(1000);
}
