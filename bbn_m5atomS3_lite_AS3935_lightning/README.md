# M5Stack with AtomS3-Lite and AS3935 Lightning Detector sensor to NMEA-0183

AS3935 Lightning Detector connected to M5Stack AtomS3-Lite via i2c and one additional digital GPIO pin (interrupt)

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,D,4500,M,LIGHTNING_RANGE*xx
$BBXDR,X,100,,LIGHTNING_LEVEL*xx
````

DFRobot AS3935 Lightning Detector:

https://www.dfrobot.com/product-1828.html
