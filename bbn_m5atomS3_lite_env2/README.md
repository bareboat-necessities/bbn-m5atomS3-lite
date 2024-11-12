 M5Stack AtomS3-Lite with Env II sensors to NMEA 0183

M5Stack ENV II Unit with Temperature Humidity Air Pressure Sensor (SHT30 + BMP280)

Connected to M5Stack AtomS3-Lite via i2c

- Air Pressure
- Air Temperature
- Humidity

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,H,47.35,P,HUMI_SHT3X*1F
$BBXDR,C,24.79,C,TEMP_SHT3X*1F
$BBXDR,C,24.58,C,TEMP_BMP280*5D
$BBXDR,P,101731.00,P,PRES_BMP280*4B
````

M5Stack ENV II Unit with Temperature Humidity Air Pressure Sensor (SHT30 + BMP280):

https://shop.m5stack.com/products/env-ii-unit
