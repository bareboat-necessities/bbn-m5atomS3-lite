#include <OneWire.h>
#include <M5Unified.h>
#include <DallasTemperature.h>
#include "Nmea0183Msg.h"

#define ONE_WIRE_BUS G8          // Pin to which 1-wire bus is connected to esp32
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  pinMode(ONE_WIRE_BUS, INPUT);
  Serial.begin(4800);
  sensors.begin();
  int count = sensors.getDeviceCount();
  gen_nmea0183_msg("$BBTXT,01,01,01,TEMPERATURE sensors found=%s", String(count).c_str());
  if (count > 0) {
    for (int i = 0; i < count; i++) {
      DeviceAddress deviceAddress;
      if (!sensors.getAddress(deviceAddress, i)) {
        gen_nmea0183_msg("$BBTXT,01,01,02,TEMPERATURE unable to find sensor address for device=%s", String(i).c_str());
      } else {
        char str[17];
        addressToStr(deviceAddress, str);
        gen_nmea0183_msg("$BBTXT,01,01,02,TEMPERATURE found sensor address=%s", str);
      }
    }
  }
}

void byte_to_hex_ascii(unsigned char byte, char hex_str[3]) {
  sprintf(hex_str, "%02X", byte);
}

void addressToStr(DeviceAddress deviceAddress, char str[17]) {
  for (uint8_t i = 0; i < 8; i++) {
    char a[3];
    byte_to_hex_ascii(deviceAddress[i], a);
    str[2 * i] = a[0];
    str[2 * i + 1] = a[1];
  }
  str[16] = (char)0;
}

void loop() {
  int count = sensors.getDeviceCount();
  if (count > 0) {
    sensors.requestTemperatures();
    for (int i = 0; i < count; i++) {
      DeviceAddress deviceAddress;
      if (sensors.getAddress(deviceAddress, i)) {
        char str[17];
        addressToStr(deviceAddress, str);
        gen_nmea0183_msg("$BBXDR,C,%s", (String(sensors.getTempCByIndex(i)) + ",C,TEMP_" + String(str)).c_str());        // C
      }
    }
  }
  delay(1000);
}
