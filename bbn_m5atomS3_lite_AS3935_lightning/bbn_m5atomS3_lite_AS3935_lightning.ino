#include <M5AtomS3.h>
#include <SparkFun_AS3935.h>
#include "NmeaXDR.h"

// 0x03 is default i2c address, but the address can also be 0x02, 0x01.
// Adjust the address jumpers on the underside of the product.
#define AS3935_ADDR 0x03
#define LIGHTNING_INT 0x08
#define DISTURBER_INT 0x04
#define NOISE_INT 0x01

SparkFun_AS3935 lightning(AS3935_ADDR);

// Interrupt pin for lightning detection
const int lightningInt = G7;

byte noiseFloor = 2;
byte watchDogVal = 2;
byte spike = 2;
byte lightningThresh = 1;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);

  pinMode(lightningInt, INPUT); // When lightning is detected the interrupt pin goes HIGH.

  Wire.begin(); // Begin Wire before lightning sensor.

  if ( !lightning.begin(Wire) ) { // Initialize the sensor.
    Serial.println("Lightning Detector did not start up, freezing!");
    while (1);
  }

  lightning.maskDisturber(true);
  lightning.setNoiseLevel(noiseFloor);
  lightning.watchdogThreshold(watchDogVal);
  lightning.spikeRejection(spike);
  lightning.lightningThreshold(lightningThresh);
  lightning.setIndoorOutdoor(INDOOR);
  //lightning.setIndoorOutdoor(OUTDOOR);
}

void loop() {
  if (digitalRead(lightningInt) == HIGH) {
    // Hardware has alerted us to an event, now we read the interrupt register
    // to see exactly what it is.
    uint8_t intVal = lightning.readInterruptReg();
    if (intVal == NOISE_INT) {
      // Noise
      // Too much noise? Uncomment the code below, a higher number means better noise rejection.
      //lightning.setNoiseLevel(setNoiseLevel);
    }
    else if (intVal == DISTURBER_INT) {
      // Disturber
      // Too many disturbers? Uncomment the code below, a higher number means better disturber rejection.
      //lightning.watchdogThreshold(threshVal);
    }
    else if (intVal == LIGHTNING_INT) {
      Serial.println("Lightning Strike Detected!");
      // Lightning! Now how far away is it? Distance estimation takes into
      // account any previously seen events in the last 15 seconds.
      byte distance = lightning.distanceToStorm();
      Serial.print("Approximately: ");
      Serial.print(distance);
      Serial.println("km away!");

      long lightning_energy = lightning.lightningEnergy();
      Serial.print("Lightning Energy: ");
      Serial.println(lightning_energy);
    }
  }
  delay(100);
}
