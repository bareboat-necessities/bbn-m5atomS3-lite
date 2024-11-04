# M5Stack with AtomS3-Lite and M5Stack Limit Switch to NMEA-0183

M5Stack Limit Switch connected to M5Stack AtomS3-Lite via GPIO digital pin

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,S,0,,LIMIT_CUR*63
$BBXDR,S,1,,LIMIT_NEW*7A
$BBXDR,S,0,,LIMIT_NEW*7B
$BBXDR,S,1,,LIMIT_NEW*7A
$BBXDR,S,0,,LIMIT_NEW*7B
$BBXDR,S,0,,LIMIT_CUR*63
$BBXDR,S,0,,LIMIT_CUR*63
````

M5Stack Limit Switch

https://shop.m5stack.com/products/limit-switch-unit
