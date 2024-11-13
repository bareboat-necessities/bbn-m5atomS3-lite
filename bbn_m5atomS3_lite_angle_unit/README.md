# M5Stack with AtomS3-Lite and M5Stack Angle Unit to NMEA-0183

M5Stack Angle Unit connected to M5Stack AtomS3-Lite via gpio analog pin.

This sensor can be used for user input of angular offsets such as offset for wind direction sensor, offset for IMU mount angle, etc

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,A,180.0,D,ANGLE*2D
$BBXDR,A,80.0,D,ANGLE*1C
$BBXDR,A,39.0,D,ANGLE*1E
$BBXDR,A,16.0,D,ANGLE*13
$BBXDR,A,-42.0,D,ANGLE*3F
$BBXDR,A,-53.0,D,ANGLE*3F
$BBXDR,A,-53.0,D,ANGLE*3F
````

M5Stack Mini Angle Unit Rotary Switch with Potentiometer :

https://docs.m5stack.com/en/unit/angle

