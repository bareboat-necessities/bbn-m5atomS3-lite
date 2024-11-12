#include <M5AtomS3.h>
#include <Adafruit_VL53L0X.h>
#include "NmeaXDR.h"
#include "Nmea0183Msg.h"

Adafruit_VL53L0X VL53L0X = Adafruit_VL53L0X();

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Wire.begin();
  Serial.begin(4800);

  if (!VL53L0X.begin(VL53L0X_I2C_ADDR, false, &Wire)) {
    gen_nmea0183_msg("$BBTXT,01,01,01,RANGE sensors not found=%s", "VL53L0X");
  }
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  VL53L0X.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  if (measure.RangeStatus != 4) {       // phase failures have incorrect data
    gen_nmea0183_xdr("$BBXDR,D,%.4f,M,RANGE_VL53L0X", measure.RangeMilliMeter / 1000.0);
  } else {
    // out of range
  }
  delay(100);
}
