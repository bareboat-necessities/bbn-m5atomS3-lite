# M5Stack with AtomS3-Lite and Time-of-Flight Distance Ranging Sensor Unit (VL53L0X) to NMEA-0183

Time-of-Flight Distance Ranging Sensor Unit (VL53L0X) sensor connected to M5Stack AtomS3-Lite via i2c

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,D,0.2410,M,RANGE_VL53L0X*66
$BBXDR,D,0.2430,M,RANGE_VL53L0X*64
$BBXDR,D,0.2650,M,RANGE_VL53L0X*60
$BBXDR,D,0.2650,M,RANGE_VL53L0X*60
$BBXDR,D,0.6140,M,RANGE_VL53L0X*62
$BBXDR,D,0.7280,M,RANGE_VL53L0X*6C
$BBXDR,D,1.2650,M,RANGE_VL53L0X*61
$BBXDR,D,0.9040,M,RANGE_VL53L0X*6C
$BBXDR,D,0.7200,M,RANGE_VL53L0X*64

````

Time-of-Flight Distance Ranging Sensor Unit (VL53L0X) sensor :

https://shop.m5stack.com/products/tof-sensor-unit
