# M5Stack AtomS3-Lite with Bosch BME680 to NMEA 0183

Bosch BME680 Sensor to NMEA 0183 via i2c

Connected to M5Stack AtomS3-Lite via i2c

- Air Pressure
- Air Temperature
- Humidity
- Gas Electrical Resistance

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,C,25.97,C,TEMP_BME680*4E
$BBXDR,P,102061.00,P,PRES_BME680*5B
$BBXDR,H,48.09,P,HUMI_BME680*4F
$BBXDR,H,32.17,,GASR_BME680*03
````

Bosch BME680 with Temperature Humidity Air Pressure Sensor:

[BME680](https://www.adafruit.com/product/3660)

