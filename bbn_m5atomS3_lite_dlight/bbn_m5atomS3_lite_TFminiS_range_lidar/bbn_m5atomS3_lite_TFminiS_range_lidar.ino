#include <M5AtomS3.h>
#include "NmeaXDR.h"

/*
  Benewake TFmini-S UART LiDAR to NMEA-0183 XDR
*/

// UART pins when Lidar is plugged into port C of ATOMIC PortABC Extension Base
#define RXD2 G6     // Green on the Lidar
#define TXD2 G5     // White on the Lidar

// UART pins when Lidar is plugged directly into grove port of M5 AtomS3-lite
//#define RXD2 G1   // Green on the Lidar
//#define TXD2 G2   // White on the Lidar

// Other esp32 Lidar wiring pins
//#define RXD2 G16  // Green on the Lidar
//#define TXD2 G17  // White on the Lidar


int i;
unsigned char check;
int dist;                    // actual distance measurements of LiDAR
unsigned char uart[9];       // save data measured by LiDAR
const int HEADER = 0x59;     // frame header of data package
int rec_debug_state = 0x01;  // receive state for frame

const long report_interval = 500;  // interval at which to update (milliseconds)
unsigned long previousMillis = 0UL;

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(4800);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= report_interval) {
    previousMillis = currentMillis;
    Get_Lidar_data();
  }
}

void Get_Lidar_data() {
  if (Serial2.available()) {
    if (rec_debug_state == 0x01) {
      uart[0] = Serial2.read();
      if (uart[0] == 0x59) {
        check = uart[0];
        rec_debug_state = 0x02;
      }
    } else if (rec_debug_state == 0x02) {
      uart[1] = Serial2.read();
      if (uart[1] == 0x59) {
        check += uart[1];
        rec_debug_state = 0x03;
      } else {
        rec_debug_state = 0x01;
      }
    } else if (rec_debug_state == 0x03) {
      uart[2] = Serial2.read();
      check += uart[2];
      rec_debug_state = 0x04;
    } else if (rec_debug_state == 0x04) {
      uart[3] = Serial2.read();
      check += uart[3];
      rec_debug_state = 0x05;
    } else if (rec_debug_state == 0x05) {
      uart[4] = Serial2.read();
      check += uart[4];
      rec_debug_state = 0x06;
    } else if (rec_debug_state == 0x06) {
      uart[5] = Serial2.read();
      check += uart[5];
      rec_debug_state = 0x07;
    } else if (rec_debug_state == 0x07) {
      uart[6] = Serial2.read();
      check += uart[6];
      rec_debug_state = 0x08;
    } else if (rec_debug_state == 0x08) {
      uart[7] = Serial2.read();
      check += uart[7];
      rec_debug_state = 0x09;
    } else if (rec_debug_state == 0x09) {
      uart[8] = Serial2.read();
      if (uart[8] == check) {
        dist = uart[2] + uart[3] * 256;       // the distance in cm
        int percent = 0;

        if (dist <= 200) {                    // dist in cm, so 200 cm = 2 meters
          percent = (200 - dist) * 100 / 200; // calculate percentage
        }

        gen_nmea0183_xdr("$BBXDR,D,%.2f,M,RANGE_TFminiS", dist / 100.0);

        while (Serial2.available()) {
          Serial2.read();
        } // Clear serial buffer
        delay(100);
      }
      rec_debug_state = 0x01;
    }
  }
}
