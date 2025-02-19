#include <M5Unified.h>
#include <Arduino.h>
#include "Unit_Encoder.h"
#include "NmeaXDR.h"
#include "NmeaChecksum.h"

Unit_Encoder sensor;
signed short int last_encoder_value = 0;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Wire.begin();
  Serial.begin(4800);
  sensor.begin(&Wire, ENCODER_ADDR, G2, G1, 100000U);
}

void loop() {
  signed short int encoder_value = sensor.getEncoderValue();
  bool btn_status                = sensor.getButtonStatus();
  if (last_encoder_value != encoder_value) {
    gen_nmea0183_xdr("$BBXDR,S,%.0f,,ENCODER_ADJ", (float)encoder_value);
    if (last_encoder_value < encoder_value) {
      sensor.setLEDColor(1, 0x00FF00);
    } else {
      sensor.setLEDColor(2, 0xFF0000);
    }
    last_encoder_value = encoder_value;
  } else {
    sensor.setLEDColor(0, 0x0000FF);
  }
  if (!btn_status) {
    gen_nmea0183_xdr("$BBXDR,S,%.0f,,ENCODER_SET", (float)encoder_value);
    sensor.setLEDColor(0, 0xFFFF00);
  }
  delay(200);
}
