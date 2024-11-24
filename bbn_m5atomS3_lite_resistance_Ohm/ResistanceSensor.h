#ifndef ResistanceSensor_h
#define ResistanceSensor_h

// readVoltage is used to improve the linearity of the ESP32 ADC
// see: https://github.com/G6EJD/ESP32-ADC-Accuracy-Improvement-function
double readVoltage_util(byte pin) {
  double reading = analogRead(pin); // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if (reading < 1 || reading > 4095) return 0;
  // return -0.000000000009824 * pow(reading,3) + 0.000000016557283 * pow(reading,2) + 0.000854596860691 * reading + 0.065440348345433;
  return (-0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089) * 1000;
} // Added an improved polynomial, use either, comment out as required

double readVoltageAvg(byte pin, int samples) {
  double sum = 0.0;
  for (int i = 0; i < samples; i++) {
    sum += readVoltage_util(pin);
  }
  return sum / samples;
}

enum ResistanceConfiguration {
  UPSTREAM,
  DOWNSTREAM,
};

struct ResistanceSensor {
  int adc_voltage_pin = G8;
  ResistanceConfiguration voltage_divider_type = DOWNSTREAM;
  double reference_voltage = 3.3;     // in volts
  double reference_resistance = 100;  // in Ohms
  double measured_resistance;         // in Ohms
};

void ResistanceSensor_init(ResistanceSensor* rs, int pin, ResistanceConfiguration conf, 
    float reference_voltage, float reference_resistance) {
  rs->adc_voltage_pin = pin;
  rs->voltage_divider_type = conf;
  rs->reference_voltage = reference_voltage;
  rs->reference_resistance = reference_resistance;
  pinMode(rs->adc_voltage_pin, INPUT);
  analogSetPinAttenuation(rs->adc_voltage_pin, ADC_11db); // for range 0-2.6v
}

void ResistanceSensor_read(ResistanceSensor* rs) {
  double rs->volt = readVoltageAvg(rs->adc_voltage_pin, 16) * rs->reference_voltage / 4095;
  double rs->measured_resistance = 0.0;
  switch (rs->voltage_divider_type) {
    case UPSTREAM:
      if (rs->volt == 0.0f) {
        rs->measured_resistance = NAN;
      } else {
        rs->measured_resistance = (rs->reference_voltage - rs->volt) / rs->volt;
      }
      break;
    case DOWNSTREAM:
      if (rs->volt == rs->reference_voltage) {
        rs->measured_resistance = NAN;
      } else {
        rs->measured_resistance = rs->volt / (rs->reference_voltage - rs->volt);
      }
      break;
  }
  rs->measured_resistance *= rs->reference_resistance;
}

#endif
