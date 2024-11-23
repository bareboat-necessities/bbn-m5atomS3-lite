#include <M5AtomS3.h>
#include <NewPing.h>

#define TRIGGER_PIN  G7  // Pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     G8  // Pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 75  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

float temp = 28.0; // Temperature in Celsius (this value would probably come from a temperature sensor).
float factor = sqrt(1 + temp / 273.15) / 60.368; // Speed of sound calculation based on temperature.

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800); 
}

void loop() {
  delay(1000); // Wait 1 second between distance readings.
  Serial.print("Ping: ");
  Serial.print((float)sonar.ping_median(5) * factor); // Send 5 pings, get median distance, convert to cm and print result
  Serial.println("cm");
}
