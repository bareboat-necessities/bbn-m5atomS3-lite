# M5Stack AtomS3-Lite with MAX6675 thermocouple sensor to NMEA 0183

MAX6675 thermocouple sensor

Connected to M5Stack AtomS3-Lite via GPIO pins:

SO = 5

CS = 6

CLK = 7

Generates NMEA-0183 XDR sentences (USB Serial with baud rate 4800) like this:

````
$BBXDR,C,26.75,C,THERMOCOUPLE*6F
````

https://www.amazon.com/HiLetgo-MAX6675-Thermocouple-Temperature-Arduino/dp/B01HT871SO

## Use cases

Exhaust gas temperature 

