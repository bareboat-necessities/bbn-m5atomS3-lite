#include <M5AtomS3.h>

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
  AtomS3.begin(cfg);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, G5, G6);  // Port C pins
  Serial2.print("$PCAS01,1*1D\r\n");        // Set baud mode to 9600
}

void loop() {
  if (Serial.available()) {
    int ch = Serial.read();
    Serial2.write(ch);
  }
  if (Serial2.available()) {
    int ch = Serial2.read(); 
    Serial.write(ch);
  }
}

