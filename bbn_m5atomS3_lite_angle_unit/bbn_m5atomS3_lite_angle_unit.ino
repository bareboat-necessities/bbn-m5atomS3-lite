#include <M5Unified.h>
#include "NmeaXDR.h"

struct AngleInput {
  int potentiometerPin = G8;  // set the pin for the potentiometer.
  int min_value = 110;
  int max_value = 4095;
  int avg_sensorValue;
  int angle;
};

void measure_angle(AngleInput* a) {
  const int iter = 100;
  a->avg_sensorValue = 0;
  for (int i = 0; i < iter; i++) {
    int cur_sensorValue = analogRead(a->potentiometerPin);  // read the value from the sensor.
    a->avg_sensorValue = a->avg_sensorValue + cur_sensorValue;
  }
  a->avg_sensorValue = a->avg_sensorValue / iter;
  a->angle = (180 - (360 * (a->avg_sensorValue - a->min_value) / (a->max_value - a->min_value)));
  if (a->angle > 180) a->angle = 180;
  if (a->angle < -180) a->angle = -180;
}

AngleInput angle_input;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Serial.begin(4800);
  pinMode(angle_input.potentiometerPin, INPUT);  // Sets the specified pin to input mode.
}

void loop() {
  measure_angle(&angle_input);
  //Serial.println(angle_input.avg_sensorValue);
  gen_nmea0183_xdr("$BBXDR,A,%.1f,D,ANGLE", (float)angle_input.angle);      // Angle degrees
  delay(500);
}
