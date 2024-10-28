# M5Stack with AtomS3-Lite and M5Stack Encoder Unit to NMEA-0183

M5Stack M5Stack Encoder Unit connected to M5Stack AtomS3-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,S,332,,ENCODER_ADJ*6B
$BBXDR,S,331,,ENCODER_ADJ*68
$BBXDR,S,302,,ENCODER_ADJ*68
$BBXDR,S,278,,ENCODER_ADJ*64
$BBXDR,S,254,,ENCODER_ADJ*6A
$BBXDR,S,230,,ENCODER_ADJ*68
$BBXDR,S,208,,ENCODER_ADJ*63
$BBXDR,S,188,,ENCODER_ADJ*68
$BBXDR,S,188,,ENCODER_SET*65
$BBXDR,S,188,,ENCODER_SET*65

````

M5Stack Encoder Unit

https://shop.m5stack.com/products/encoder-unit
