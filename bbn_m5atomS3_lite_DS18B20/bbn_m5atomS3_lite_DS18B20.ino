#include <M5AtomS3.h>
#include <M5Unified.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Nmea0183Msg.h"

#define ONE_WIRE_BUS G8          // Pin to which 1-wire bus is connected to esp32
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress addr0;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  sensors.begin();
  int count = sensors.getDeviceCount();
  gen_nmea0183_msg("$BBTXT,01,01,01,Temp sensors found=%s", String(count).c_str());
  if (count > 0) {
    if (!sensors.getAddress(addr0, 0)) {
      gen_nmea0183_msg("$BBTXT,01,01,02,Unable to find address for device=%s", String(0).c_str());
    }
  }
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
      DeviceAddress deviceAddress;
      if (sensors.getAddress(deviceAddress, i)) {
        if (memcmp(deviceAddress, addr0, sizeof(DeviceAddress)) == 0) {
          gen_nmea0183_msg("$BBXDR,C,%s,C,TEMP0", String(sensors.getTempCByIndex(i)).c_str());        // C
        }
      }
    }
  }
  delay(1000);
}
