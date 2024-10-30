#include <M5AtomS3.h>
#include <Arduino.h>
#include "NmeaXDR.h"
#include "CQRobotTDS.h"

/*
  TDS sensor is connected to analog port G8
*/
int TDS_pin = G8;
CQRobotTDS tds(TDS_pin, 3.3, 4096.0 /* For ESP32 built-in 12bit ADC */);
unsigned long timeout = 0;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  pinMode(TDS_pin, INPUT);
  Serial.begin(4800);
}

void loop() {
  float temp = 25.0; // TODO: read temperature from a real sensor
  float tdsValuePPM = tds.update(temp);

  if (timeout < millis()) {
    gen_nmea0183_xdr("$BBXDR,X,%.4f,S,TDS", (float)(tdsValuePPM * 0.001));        // Parts per Thousand
    timeout = millis() + 1000;
  }
}
