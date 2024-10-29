#include <M5AtomS3.h>
#include <Arduino.h>
#include "Max6675.h"
#include "NmeaXDR.h"

int thermoSO = 5;
int thermoCS = 6;
int thermoCLK = 7;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoSO);

void setup() {
  Serial.begin(4800);
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout, just print the current temp
  gen_nmea0183_xdr("$BBXDR,C,%.2f,C,THERMOCOUPLE", thermocouple.readCelsius());        // C
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(1000);
}
