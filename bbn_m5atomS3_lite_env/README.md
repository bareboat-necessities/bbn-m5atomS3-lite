# M5Stack AtomS3-Lite with Env  sensors to NMEA 0183

M5Stack ENV Unit with Temperature Humidity Air Pressure Sensor (DHT12 + BMP280)

Connected to M5Stack AtomS3-Lite via i2c

- Air Pressure
- Air Temperature
- Humidity

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,C,23.20,C,TEMP_DHT12*6B
$BBXDR,C,24.58,C,TEMP_BMP280*5D
$BBXDR,P,101731.00,P,PRES_BMP280*4B
$BBXDR,H,30.30,P,HUMI_DHT12*65
$BBXDR,C,23.00,C,TEMP_DHT12*69
$BBXDR,C,24.58,C,TEMP_BMP280*5D
$BBXDR,P,101731.00,P,PRES_BMP280*4B
````

M5Stack ENV Unit with Temperature Humidity Air Pressure Sensor (DHT12 + BMP280):

https://docs.m5stack.com/en/unit/env

