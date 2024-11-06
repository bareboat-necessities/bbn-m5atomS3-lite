# M5Stack AtomS3-Lite with Env III sensors to NMEA 0183

M5Stack ENV III Unit with Temperature Humidity Air Pressure Sensor (SHT30 + QMP6988)

Connected to M5Stack AtomS3-Lite via i2c

- Air Pressure
- Air Temperature
- Humidity

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,H,47.35,P,HUMI_SHT3X*1F
$BBXDR,C,24.79,C,TEMP_SHT3X*1F
$BBXDR,C,25.16,C,TEMP_QMP6988*70
$BBXDR,P,101649.56,P,PRES_QMP6988*60
````

M5Stack ENV III Unit with Temperature Humidity Air Pressure Sensor (SHT30 + QMP6988):

https://shop.m5stack.com/products/env-iii-unit-with-temperature-humidity-air-pressure-sensor-sht30-qmp6988

