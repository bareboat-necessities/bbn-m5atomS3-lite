# M5Stack with AtomS3-Lite and PIR Motion Sensor (AS312) to NMEA-0183

PIR Motion Sensor (AS312) connected to M5Stack AtomS3-Lite via GPIO digital pin (see .ino code code pin number)

Yellow 'OUT' goes to the digital GPIO pin of m5Atom.

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,S,1,,PIR_MOTION*26
````

M5Stack PIR Motion Sensor (AS312)

https://shop.m5stack.com/products/pir-module

