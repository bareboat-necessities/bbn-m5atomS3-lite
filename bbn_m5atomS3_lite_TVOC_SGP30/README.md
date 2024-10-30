M5Stack with AtomS3-Lite and SGP30 Air Quality and TVOC sensor to NMEA-0183

SGP30 Air Quality and TVOC sensor connected to M5Stack AtomS3-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,X,5,,TVOC*2D
$BBXDR,X,415,,eCO2*7D
$BBXDR,X,13507,,rawH2*38
$BBXDR,X,18875,,rawEthanol*14
$BBXDR,X,7,,TVOC*2F
$BBXDR,X,416,,eCO2*7E
$BBXDR,X,13501,,rawH2*3E
$BBXDR,X,18864,,rawEthanol*14
````

SGP30 Air Quality and TVOC sensor :

[M5Stack SGP30 Air Quality and TVOC sensor](https://shop.m5stack.com/products/tvoc-eco2-gas-unit-sgp30)
