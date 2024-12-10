# NMEA-0183 XDR Sensors on ESP32 m5atomS3-lite

NMEA-0183 XDR Sensors on m5atomS3-lite for Arduino IDE.

The sensors stream NMEA-0183 XDR sentences via USB

## Sensors:

- [Dallas Temperature DS18B20  1-wire](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_DS18B20)
- [Thermocouple MAX6675](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_thermo_MAX6675)
- [Air Quality SGP30](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_TVOC_SGP30)
- [Humidity i2c SHT30](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_env3) or [with BME680](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_WOX_BME680) or [with DHT12](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_env)
- [Air Pressure i2c QMP6988](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_env3) or [with BME680](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_WOX_BME680) or [with BMP280](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_env)
- [Air Temperature i2c QMP6988](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_env3) or [with BME680](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_WOX_BME680) or [with BMP280](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_env)
- [Voltage to i2c with ADS1115](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_voltmeter)
- [Illuminance i2c BH1750FVI-TR](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_dlight)
- [4-20mA current with STM32G030F6 (Ex: Tank Liquid Level) to i2c](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_ain_4_20ma)
- [Water Quality Meter Ocean TDS (Total Dissolved Solids) CQRSENTDS01](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_TDS_CQRSENTDS01)
- [Encoder with STM32F030](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_encoder_unit)
- [M5Stack Limit Switch](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_limit_switch)
- [M5Stack PIR Motion Sensor (AS312)](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_PIR_motion)
- [M5Stack GPS with AT6558](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_GPS_AT6558)
- [Time-of-Flight Distance Ranging Sensor Unit (VL53L0X)](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_VL53L0X_range)
- [Benewake TFmini-S UART LiDAR sensor](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_TFminiS_range_lidar)
- [M5Stack Angle input sensor](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_angle_unit)
- [Lightning Strike Detector Sensor AS3935](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_AS3935_lightning)
- [Resistance 0-240 Ohm Sensor with esp32 ADC and voltage divider](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/blob/main/bbn_m5atomS3_lite_resistance_Ohm)
- [Bilge Level with JSN-SR04T Waterproof Ultrasonic Sensor](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_JSN-SR04T)
- [Fuel Level](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_fuel_level)
- [Engine Oil Pressure](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_oil_pressure)

## Integration with SignalK

Integration with SignalK is done via NMEA XDR Parser SignalK plugin. 

More: https://github.com/GaryWSmith/xdr-parser-plugin

## Required Libraries

For required libraries and their versions see .github/workflows/build.yaml

## More BBN devices

- [M5Stack Tough (ESP-32) Sailing Instruments Color Touch Waterproof Display and Autopilot Control](https://github.com/bareboat-necessities/bbn-m5stack-tough)
- [BBN OS on M5Stack CoreMP135 with NMEA 2000/0183, SignalK and more](https://github.com/bareboat-necessities/lysmarine_gen/tree/coremp135_bookworm)
- [BBN Boat Heave Sensor using IMU on M5Stack AtomS3](https://github.com/bareboat-necessities/bbn-wave-period-esp32)
- [DIY NMEA 2000 to USB gateway in Actisense format on M5Atom-Lite](https://github.com/bareboat-necessities/bbn-nmea200-m5atom/tree/main/bbn-nmea2000-usb-gw-m5atom)
- [NMEA 2000 environmental sensors on M5Atom-Lite](https://github.com/bareboat-necessities/bbn-nmea200-m5atom/tree/main/bbn-nmea2000-env-m5atom)
- [Sending WhatsApp alerts from AtomS3-lite with AtomPoE Base](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_whatsapp)
- [Detecting Devices on i2c bus](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_i2c_detect)


## Mounting m5stack products

m5stack SandwichC Brick:

https://shop.m5stack.com/products/sandwichc-brick


m5stack ClipB Brick:

https://shop.m5stack.com/products/m5stack-clip-b-brick-kit

m5stack ClipA Brick:

https://shop.m5stack.com/products/m5stack-clip-a-brick-kit

m5stack Screw Kit:

https://shop.m5stack.com/products/16-pcs-m3-12-18-25-32-screw-with-allen-key

m5stack ATOMIC PortABC Extension Base:

https://shop.m5stack.com/products/atomic-portabc-extension-base

m5stack grove connectors:

YH2.0-4P

Jst PH2.0 4 pin

Grove to QWIIC adapter:

https://www.sparkfun.com/products/15109

Ideas for enclosures:   https://www.polycase.com/

LTC4311 I2C Extender / Active Terminator

https://www.adafruit.com/product/4756

## Customized Enclosures

https://www.polycase.com/customized-enclosures

## TODO:

- UV Light intencity
- Engine RPM Meter
- Compass
- Boat Pitch and Roll
- Bilge Sensors
- Anchor Chain Counter
- Dingy Locator with GPS and LoRa



## Project Home

https://bareboat-necessities.github.io/
