# JSN-SR04T Waterproof Ultrasonic Sensor to NMEA 0183 XDR

https://www.makerguides.com/interfacing-esp32-and-jsn-sr04t-waterproof-ultrasonic-sensor/

https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home

## Connecting to m5stack atomS3-Lite

Pins:

- G8 to TX
- G7 to RX
- VCC 3.3 to VCC
- GND to GND

## NMEA 0183 XDR

Produces NMEA 0183 XDR via USB serial with baud rate 4800

````
$BBXDR,D,0.52,M,Range_JSN_S04T*55
$BBXDR,D,0.70,M,Range_JSN_S04T*55
$BBXDR,D,0.71,M,Range_JSN_S04T*54
````
