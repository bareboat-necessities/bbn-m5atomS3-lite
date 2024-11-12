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

const int HEADER_TFminiS = 0x59;     // frame header of data package

struct TFminiS {
  unsigned char check;
  int dist;                    // actual distance measurements of LiDAR
  unsigned char uart[9];       // save data measured by LiDAR
  int rec_debug_state = 0x01;  // receive state for frame
};

TFminiS lidar;

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
    if (lidar.rec_debug_state == 0x01) {
      lidar.uart[0] = Serial2.read();
      if (lidar.uart[0] == HEADER_TFminiS) {
        lidar.check = lidar.uart[0];
        lidar.rec_debug_state = 0x02;
      }
    } else if (lidar.rec_debug_state == 0x02) {
      lidar.uart[1] = Serial2.read();
      if (lidar.uart[1] == 0x59) {
        lidar.check += lidar.uart[1];
        lidar.rec_debug_state = 0x03;
      } else {
        lidar.rec_debug_state = 0x01;
      }
    } else if (lidar.rec_debug_state == 0x03) {
      lidar.uart[2] = Serial2.read();
      lidar.check += lidar.uart[2];
      lidar.rec_debug_state = 0x04;
    } else if (lidar.rec_debug_state == 0x04) {
      lidar.uart[3] = Serial2.read();
      lidar.check += lidar.uart[3];
      lidar.rec_debug_state = 0x05;
    } else if (lidar.rec_debug_state == 0x05) {
      lidar.uart[4] = Serial2.read();
      lidar.check += lidar.uart[4];
      lidar.rec_debug_state = 0x06;
    } else if (lidar.rec_debug_state == 0x06) {
      lidar.uart[5] = Serial2.read();
      lidar.check += lidar.uart[5];
      lidar.rec_debug_state = 0x07;
    } else if (lidar.rec_debug_state == 0x07) {
      lidar.uart[6] = Serial2.read();
      lidar.check += lidar.uart[6];
      lidar.rec_debug_state = 0x08;
    } else if (lidar.rec_debug_state == 0x08) {
      lidar.uart[7] = Serial2.read();
      lidar.check += lidar.uart[7];
      lidar.rec_debug_state = 0x09;
    } else if (lidar.rec_debug_state == 0x09) {
      lidar.uart[8] = Serial2.read();
      if (lidar.uart[8] == lidar.check) {
        lidar.dist = lidar.uart[2] + lidar.uart[3] * 256;       // the distance in cm
        int percent = 0;
        if (lidar.dist <= 200) {                   // dist in cm, so 200 cm = 2 meters
          percent = (200 - lidar.dist) * 100 / 200;      // calculate percentage
        }

        gen_nmea0183_xdr("$BBXDR,D,%.2f,M,RANGE_TFminiS", lidar.dist / 100.0);

        while (Serial2.available()) {
          Serial2.read();
        } // Clear serial buffer
        delay(100);
      }
      lidar.rec_debug_state = 0x01;
    }
  }
}
