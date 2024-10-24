# M5Stack with AtomS3-Lite and M5Stack DLight Illuminance sensor to NMEA-0183

M5Stack DLight illuminance sensor connected to M5Stack AtomS3-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,X,132.0,L,ILLU*68
$BBXDR,X,128.0,L,ILLU*63
$BBXDR,X,128.0,L,ILLU*63
$BBXDR,X,136.0,L,ILLU*6C
$BBXDR,X,128.0,L,ILLU*63
$BBXDR,X,132.0,L,ILLU*68
$BBXDR,X,132.0,L,ILLU*68
$BBXDR,X,128.0,L,ILLU*63
$BBXDR,X,128.0,L,ILLU*63
$BBXDR,X,132.0,L,ILLU*68

````
