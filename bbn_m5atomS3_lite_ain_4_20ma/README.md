# M5Stack with AtomS3-Lite and M5Stack 4-20mA current sensors to NMEA-0183

M5Stack Analog to I2C Unit (4-20mA Input) connected to M5Stack AtomS3-Lite via i2c

Can be used with many industrial 4-20 mAmps current sensors.

Ex: 
- Tank level

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,I,0.00480,A,AMPS*6B
$BBXDR,I,0.00481,A,AMPS*6A
$BBXDR,I,0.00481,A,AMPS*6A


````
