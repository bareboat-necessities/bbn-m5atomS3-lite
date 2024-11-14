#include <M5AtomS3.h>
#include <SparkFun_AS3935.h>
#include "NmeaXDR.h"

// 0x03 is default i2c address, but the address can also be 0x02, 0x01.
// Adjust the address jumpers on the underside of the product.
// C - SCL i2c clock
// D - SDL i2c data
#define AS3935_ADDR 0x03
#define LIGHTNING_INT 0x08
#define DISTURBER_INT 0x04
#define NOISE_INT 0x01

SparkFun_AS3935 lightning(AS3935_ADDR);

// Interrupt pin for lightning detection
const int lightningInt = G8;

byte noiseFloor = 4;
byte watchDogVal = 3;
byte spike = 2;
byte lightningThresh = 0;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);

  Wire.begin(G2 /* SDL */, G1 /* SCL */, 100000UL);

  pinMode(lightningInt, INPUT); // When lightning is detected the interrupt pin goes HIGH.

  if (!lightning.begin(Wire)) {
    //Serial.println("Lightning Detector did not start!");
    while (1);
  }

  lightning.maskDisturber(true);
  lightning.setNoiseLevel(noiseFloor);
  //lightning.watchdogThreshold(watchDogVal);
  //lightning.spikeRejection(spike);
  //lightning.lightningThreshold(lightningThresh);
  lightning.setIndoorOutdoor(INDOOR);
  //lightning.setIndoorOutdoor(OUTDOOR);

  //Serial.println("Lightning Detector did start!");
}

void loop() {
  if (digitalRead(lightningInt) == HIGH) {
    // Hardware has alerted us to an event, now we read the interrupt register
    // to see exactly what it is.
    uint8_t intVal = lightning.readInterruptReg();
    if (intVal == NOISE_INT) {
      // Noise
      //Serial.println("Noise Detected!");
    }
    else if (intVal == DISTURBER_INT) {
      // Disturber
      //Serial.println("Disturber Detected!");
    }
    else if (intVal == LIGHTNING_INT) {
      //Serial.println("Lightning Strike Detected!");
      // Lightning! Now how far away is it? Distance estimation takes into
      // account any previously seen events in the last 15 seconds.
      gen_nmea0183_xdr("$BBXDR,D,%.0f,M,LIGHTNING_RANGE", (float)lightning.distanceToStorm() * 1000.0);
      gen_nmea0183_xdr("$BBXDR,X,%.0f,,LIGHTNING_LEVEL", (float)lightning.lightningEnergy());
    }
  }
  delay(100);
}
