# BBN Voltmeter on m5stack AtomS3 with ADS1115 M5Stack Voltmeter unit to NMEA 0183


M5Stack Voltmeter unit connected to M5Stack AtomS3-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,U,12.634,V,VOLT*50
$BBXDR,U,12.634,V,VOLT*50
$BBXDR,U,12.634,V,VOLT*50
$BBXDR,U,12.633,V,VOLT*57
$BBXDR,U,12.633,V,VOLT*57
$BBXDR,U,12.633,V,VOLT*57
$BBXDR,U,12.633,V,VOLT*57
````

The code is set up to measure 12 V circuits. You can easily modify it for other voltage ranges.
