#include <M5AtomS3.h>
#include <Adafruit_INA219.h>

#include "NmeaXDR.h"

#define INA219_I2C_ADDRESS_0 (0x40)

Adafruit_INA219 ina219(INA219_I2C_ADDRESS_0);
unsigned long timeout = 0;

void setup()   {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  Wire.begin(G2, G1, 100000UL);
  if (!ina219.begin()) {
    //Serial.println("Failed to find INA219 chip");
    while (1) {
      delay(10);
    }
  }
  /*
    By default the INA219 will be calibrated with a range of 32V, 2A.
    However uncomment one of the below to change the range.  A smaller
    range can't measure as large of values but will measure with slightly
    better precision.
  */
  //ina219.setCalibration_32V_1A();
  //ina219.setCalibration_16V_400mA();
}

void loop() {
  if (timeout < millis()) {
    // Read voltage and current from INA219.
    float shuntvoltage = ina219.getShuntVoltage_mV();
    float busvoltage = ina219.getBusVoltage_V();
    float current_mA = ina219.getCurrent_mA();

    // Compute load voltage, power, and milliamp-hours.
    float loadvoltage = busvoltage + (shuntvoltage / 1000);
    float power_mW = loadvoltage * current_mA;

    gen_nmea0183_xdr("$BBXDR,U,%.3f,V,VOLT_INA219", loadvoltage);
    gen_nmea0183_xdr("$BBXDR,I,%.3f,A,AMPS_INA219", current_mA / 1000);
    gen_nmea0183_xdr("$BBXDR,W,%.3f,W,WATT_INA219", power_mW / 1000);
    timeout = millis() + 1000;
  }
}
