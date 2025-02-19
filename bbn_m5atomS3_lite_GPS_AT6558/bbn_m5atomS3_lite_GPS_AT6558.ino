#include <M5Unified.h>

/*
   https://docs.m5stack.com/en/unit/gps

   and

   https://shop.m5stack.com/products/atomic-portabc-extension-bases

   NMEA Extensions:

   https://www.eevblog.com/forum/metrology/fake-gnss-modules-and-timekeeping/?action=dlattach;attach=944088

   GnssToolkit3
   https://cbgps.com/p7/app/gnsstoolkit/index_en.htm
   https://github.com/zxcwhale/GnssToolKit3-binaries/
   
*/

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, G6, G5);  // UART pins when GPS is plugged into port C of ATOMIC PortABC Extension Base 
  //Serial2.begin(9600, SERIAL_8N1, G1, G2);  // UART pins when GPS is plugged directly into grove port of M5 AtomS3-lite 
  Serial2.print("$PCAS01,1*1D\r\n");        // Set baud mode to 9600
  Serial2.print("$PCAS11,4*19\r\n");        // Set "sea" mode
}

void loop() {
  while (Serial.available() > 0) {
    char ch = Serial.read();
    Serial2.write(ch);
  }
  while (Serial2.available() > 0) {
    char ch = Serial2.read(); 
    Serial.write(ch);
  }
  delay(10);
}

