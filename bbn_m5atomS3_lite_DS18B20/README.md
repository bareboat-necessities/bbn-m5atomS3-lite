# Dallas Temperature 1-Wire Sensor to NMEA 0183


DS18B20 with GikFun plugin terminal board (includes required pull-up resistor for 1-wire bus)

DS18B20 data is connected to pin G8 on m5stack AtomS3-lite

Can be used for 

- Engine temperature
- Exhaust temperature
- Fridge temperature
- Engine coolant temperature
- Batteries bank temperature
- etc

Supports multiple 1-wire Dallas Temperature sensors.

Generates NMEA 0183 XDR and TXT sentences on USB serial with 4800 baud rate

````
$BBTXT,01,01,01,TEMPERATURE sensors found=1*0A
$BBTXT,01,01,02,TEMPERATURE found sensor address=28478546D4523ABF*1A
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,23.94,C,TEMP_28478546D4523ABF*38
$BBXDR,C,24.00,C,TEMP_28478546D4523ABF*32
$BBXDR,C,24.00,C,TEMP_28478546D4523ABF*32
````

Waterproof Digital Temperature Sensor DS18B20 with GikFun plugin terminal board

https://www.amazon.com/Gikfun-DS18B20-Waterproof-Digital-Temperature/dp/B08V93CTM2
