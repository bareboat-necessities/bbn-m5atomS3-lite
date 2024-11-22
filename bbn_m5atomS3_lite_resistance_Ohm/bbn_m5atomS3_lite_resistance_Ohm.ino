#include <M5AtomS3.h>
#include "NmeaXDR.h"

// readVoltage is used to improve the linearity of the ESP32 ADC
// see: https://github.com/G6EJD/ESP32-ADC-Accuracy-Improvement-function
double readVoltage(byte pin) {
  double reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if (reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  return (-0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089) * 1000;
} // Added an improved polynomial, use either, comment out as required

double readVoltageAvg(byte pin, int samples) {
  double sum = 0.0;
  for (int i = 0; i < samples; i++) {
    sum += readVoltage(pin);
  }
  return sum / samples;
}

enum ResistanceConfiguration {
  UPSTREAM,
  DOWNSTREAM,
};

unsigned long timeout = 0;
int adc_voltage_pin = G8;

ResistanceConfiguration voltage_divider_type = DOWNSTREAM;
double reference_voltage = 3.3;     // in volts
double reference_resistance = 100;  // in Ohms

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  pinMode(adc_voltage_pin, INPUT);
  analogSetPinAttenuation(adc_voltage_pin, ADC_11db); // for range 0-2.6v
  Serial.begin(4800);
}

void loop() {
  if (timeout < millis()) {
    double volt = readVoltageAvg(adc_voltage_pin, 16) * reference_voltage / 4095;
    double measured_resistance = 0.0;
    switch (voltage_divider_type) {
      case UPSTREAM:
        if (volt == 0.0f) {
          measured_resistance = NAN;
        } else {
          measured_resistance = (reference_voltage - volt) / volt;
        }
        break;
      case DOWNSTREAM:
        if (volt == reference_voltage) {
          measured_resistance = NAN;
        } else {
          measured_resistance = volt / (reference_voltage - volt);
        }
        break;
    }
    measured_resistance *= reference_resistance;
    gen_nmea0183_xdr("$BBXDR,G,%.1f,O,Ohms_esp32", measured_resistance);
    timeout = millis() + 1000;
  }
}
