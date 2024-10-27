# M5Stack with AtomS3-Lite and M5Stack 4-20mA current sensors to NMEA-0183

M5Stack Analog to I2C Unit (4-20mA Input) connected to M5Stack AtomS3-Lite via i2c

Can be used with many industrial 4-20 mAmps current sensors.

Ex: 
- Tank level

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,I,0.00480,A,AMPS*6B
$BBXDR,I,0.00481,A,AMPS*6A
$BBXDR,I,0.00481,A,AMPS*6A

````

Analog to I2C Unit 4-20mA Input (STM32G030)

https://shop.m5stack.com/products/ain4-20ma-unit

Would be useful for fluid level sensors like this one:

https://www.amazon.com/4-20mA-Liquid-Sensor-Throw-Sensors/dp/B07WDK2PRN
