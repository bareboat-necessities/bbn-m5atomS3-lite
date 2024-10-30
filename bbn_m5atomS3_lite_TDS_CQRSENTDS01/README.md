# M5Stack with AtomS3-Lite and Ocean TDS CQRobot (Total Dissolved Solids) Meter Sensor to NMEA-0183

https://www.cqrobot.com/index.php?route=product/product&product_id=1122

M5Stack with AtomS3-Lite and Ocean TDS CQRobot (Total Dissolved Solids) Meter Sensor CQRSENTDS01 to NMEA-0183.

Connected to GPIO pin G8 as analog input.

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

Total Dissolved Solids in ppt (Parts per Thousand):
  
````
$BBXDR,X,0.3955,S,TDS*12
$BBXDR,X,0.3958,S,TDS*1F
$BBXDR,X,0.3952,S,TDS*15
$BBXDR,X,0.3955,S,TDS*12
````

ppm = ppt * 1000

The ideal TDS level for drinking water is 300–500 ppm, while 500 ppm 
is the maximum recommended by the EPA. Water with a TDS level above 1,000 ppm 
is not considered safe to drink, and levels above 2,000 ppm may 
require a filtration system.
