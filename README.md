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

## Integration with SignalK

Integration with SignalK is done via NMEA XDR Parser SignalK plugin. 

More: https://github.com/GaryWSmith/xdr-parser-plugin

## More BBN devices

- [M5Stack Tough (ESP-32) Sailing Instruments Color Touch Waterproof Display and Autopilot Control](https://github.com/bareboat-necessities/bbn-m5stack-tough)
- [BBN OS on M5Stack CoreMP135 with NMEA 2000/0183, SignalK and more](https://github.com/bareboat-necessities/lysmarine_gen/tree/coremp135_bookworm)
- [BBN Boat Heave Sensor using IMU on M5Stack AtomS3](https://github.com/bareboat-necessities/bbn-wave-period-esp32)
- [DIY NMEA 2000 to USB gateway in Actisense format on M5Atom-Lite](https://github.com/bareboat-necessities/bbn-nmea200-m5atom/tree/main/bbn-nmea2000-usb-gw-m5atom)
- [NMEA 2000 environmental sensors on M5Atom-Lite](https://github.com/bareboat-necessities/bbn-nmea200-m5atom/tree/main/bbn-nmea2000-env-m5atom)
- [Sending WhatsApp alerts from AtomS3-lite with AtomPoE Base](https://github.com/bareboat-necessities/bbn-m5atomS3-lite/tree/main/bbn_m5atomS3_lite_whatsapp)

## TODO:

- Lightning detector sensor
- UV Light intencity
- Range (Time of Flight)
- Engine RPM Meter
- Compass
- Boat Pitch and Roll
- Oil Pressure
- Bilge Sensors
- Fuel Level
- Anchor Chain Counter


## Project Home

https://bareboat-necessities.github.io/
