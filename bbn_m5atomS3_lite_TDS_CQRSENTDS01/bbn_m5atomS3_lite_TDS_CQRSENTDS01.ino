#include <M5AtomS3.h>
#include <Arduino.h>
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
  float tdsValue = tds.update(temp);

  if (timeout < millis()) {
    Serial.print("TDS value: ");
    Serial.print(tdsValue, 0);
    Serial.println(" ppm");
    timeout = millis() + 1000;
  }
}
