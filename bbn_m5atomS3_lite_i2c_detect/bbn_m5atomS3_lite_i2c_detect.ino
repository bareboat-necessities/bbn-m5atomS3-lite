/*
  Copyright 2024, Mikhail Grushinskiy

  Adapted from: https://github.com/bareboat-necessities/rust-modules/tree/main/rust-i2c-scan

  TODO: Also check whoami registers.
  See: https://github.com/technoblogy/i2c-detective/blob/main/I2CDetectiveClue.ino
  
*/

#include <M5AtomS3.h>
#include <M5Unified.h>
#include <Wire.h>

typedef struct {
  const char *name;
  const char *description;
  const uint8_t *addresses;
  const uint8_t whoami_reg;
  const uint8_t whoami_id;
} I2cDeviceInfo;

static I2cDeviceInfo I2C_SCANNER_KNOWN_DEVICES[] = {
  {"47L04/47C04/47L16/47C16", "4K/16K I2C Serial EERAM - Control register", (uint8_t[]){0x1c, 0x18, 0x1a, 0x1e, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"47L04/47C04/47L16/47C16", "4K/16K I2C Serial EERAM - SRAM Memory with EEPROM backup", (uint8_t[]){0x54, 0x50, 0x56, 0x52, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AD5243", "Dual, 256-Position, I2 C-Compatible Digital Potentiometer", (uint8_t[]){0x2f, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AD5248", "Dual, 256-Position, I2 C-Compatible Digital Potentiometer", (uint8_t[]){0x2c, 0x2e, 0x2f, 0x2d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AD5251", "Dual 64-Position I2 C Nonvolatile Memory Digital Potentiometers", (uint8_t[]){0x2c, 0x2e, 0x2f, 0x2d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AD5252", "Dual 256-Position I2C Nonvolatile Memory Digital Potentiometers", (uint8_t[]){0x2c, 0x2e, 0x2f, 0x2d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ADS1015", "4-channel 12-bit ADC", (uint8_t[]){0x49, 0x48, 0x4b, 0x4a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ADS1115", "4-channel 16-bit ADC", (uint8_t[]){0x49, 0x48, 0x4b, 0x4a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ADS7828", "12-Bit, 8-Channel Sampling ANALOG-TO-DIGITAL CONVERTER", (uint8_t[]){0x49, 0x48, 0x4b, 0x4a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ADXL345", "3-axis accelerometer", (uint8_t[]){0x53, 0x1d, 0x0}, (uint8_t)0x0, (uint8_t)0xE5},
  {"AHT10", "ASAIR Humidity and Temperature sensor", (uint8_t[]){0x38, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AHT20", "Humidity and Temperature Sensor", (uint8_t[]){0x38, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AK8975", "3-axis magnetometer", (uint8_t[]){0xe, 0xd, 0xc, 0xf, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AM2315", "Humidity/Temp sensor", (uint8_t[]){0x5c, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AMG8833", "IR Thermal Camera Breakout", (uint8_t[]){0x68, 0x69, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"APDS-9250", "Digital RGB, IR and Ambient Light Sensor", (uint8_t[]){0x52, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"APDS-9960", "IR/Color/Proximity Sensor", (uint8_t[]){0x39, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AS7262", "6-channel visible spectral_ID device with electronic shutter and smart interface", (uint8_t[]){0x49, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AT24C02N", "Two-wire Serial EEPROM 2K (256 x 8)", (uint8_t[]){0x57, 0x54, 0x50, 0x56, 0x53, 0x55, 0x52, 0x51, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"AT24C64", "2-Wire Serial EEPROM 64K (8192 x 8)", (uint8_t[]){0x57, 0x54, 0x50, 0x56, 0x53, 0x55, 0x52, 0x51, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ATECC508A", "Crypto Element", (uint8_t[]){0x60, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ATECC608A", "Microchip CryptoAuthentication™ Device", (uint8_t[]){0x60, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"BH1750FVI", "Digital 16bit Serial Output Type Ambient Light Sensor IC", (uint8_t[]){0x5c, 0x23, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"BMA150", "Digital triaxial acceleration sensor", (uint8_t[]){0x38, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"BMA180", "Accelerometer", (uint8_t[]){0x77, 0x0}, (uint8_t)0x0, (uint8_t)0x03},
  {"BME280", "Temp/Barometric/Humidity", (uint8_t[]){0x77, 0x76, 0x0}, (uint8_t)0xD0, (uint8_t)0x60},
  {"BME680", "Low power gas, pressure, temperature & humidity sensor", (uint8_t[]){0x77, 0x76, 0x0}, (uint8_t)0xD0, (uint8_t)0x61},
  {"BME688", "Digital low power gas, pressure, temperature and humidity sensor with AI", (uint8_t[]){0x77, 0x76, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"BMP085", "Temp/Barometric", (uint8_t[]){0x77, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"BMP180", "Temp/Barometric", (uint8_t[]){0x77, 0x0}, (uint8_t)0xD0, (uint8_t)0x55},
  {"BMP280", "Temp/Barometric", (uint8_t[]){0x77, 0x76, 0x0}, (uint8_t)0xD0, (uint8_t)0x58},
  {"BNO055", "Absolute Orientation Sensor", (uint8_t[]){0x28, 0x29, 0x0}, (uint8_t)0x0, (uint8_t)0xA0},
  {"BQ32000", "Real-Time Clock (RTC)", (uint8_t[]){0x68, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"BU9796", "Low Duty LCD Segment Drivers", (uint8_t[]){0x3e, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"CAP1188", "8-channel Capacitive Touch", (uint8_t[]){0x2c, 0x2a, 0x2b, 0x2d, 0x28, 0x29, 0x0}, (uint8_t)0xFD, (uint8_t)0x50},
  {"CAT24C512", "EEPROM - 512Kbit - 64KB", (uint8_t[]){0x57, 0x54, 0x50, 0x56, 0x53, 0x55, 0x52, 0x51, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"CAT5171", "256‐position I2C Compatible Digital Potentiometer", (uint8_t[]){0x2c, 0x2d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"CCS811", "Volatile organics (VOC) and equivalent CO2 (eCO2) sensor", (uint8_t[]){0x5b, 0x5a, 0x0}, (uint8_t)0x20, (uint8_t)0x81},
  {"CCS811", "Ultra-Low Power Digital Gas Sensor for Monitoring Indoor Air Quality TVOC eCO2", (uint8_t[]){0x5b, 0x5a, 0x0}, (uint8_t)0x20, (uint8_t)0x81},
  {"Chirp!", "Water sensor", (uint8_t[]){0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"COM-15093", "SparkFun Qwiic Single Relay", (uint8_t[]){0x18, 0x19, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"CS43L22", "Low Power Stereo DAC w/ Headphone & Speaker Amps", (uint8_t[]){0x4a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"D7S", "D7S Vibration Sensor", (uint8_t[]){0x55, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"DHT12", "Humidity Temperature Sensor", (uint8_t[]){0x5c, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"DPS310", "Pressure Sensor", (uint8_t[]){0x76, 0x77, 0x0}, (uint8_t)0xd, (uint8_t)0x10},
  {"DRV2605", "Haptic Motor Driver", (uint8_t[]){0x5a, 0x0}, (uint8_t)0x0, (uint8_t)0x60},
  {"DS1307", "64 x 8 Serial Real-Time Clock", (uint8_t[]){0x68, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"DS1371", "I2C, 32-Bit Binary Counter Watchdog Clock", (uint8_t[]){0x68, 0x0}, (uint8_t)0x3, (uint8_t)0x3},
  {"DS1841", "Temperature-Controlled, NV, I2C, Logarithmic Resistor", (uint8_t[]){0x2a, 0x2b, 0x28, 0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"DS1881", "Dual NV Audio Taper Digital Potentiometer", (uint8_t[]){0x2c, 0x2a, 0x2e, 0x2f, 0x2b, 0x2d, 0x28, 0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"DS3231", "Extremely Accurate RTC/TCXO/Crystal", (uint8_t[]){0x68, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"DS3502", "High-Voltage, NV, I2C POT", (uint8_t[]){0x2a, 0x2b, 0x28, 0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x40},
  {"EMC2101", "SMBus Fan Control with 1°C Accurate Temperature Monitoring", (uint8_t[]){0x4c, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"FS1015", "Air Velocity Sensor Module -- 0-5, 0-15m/sec", (uint8_t[]){0x50, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"FS3000", "Air Velocity Sensor Module - 3.3V - 0-7, 0-15m/sec", (uint8_t[]){0x28, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"FT6x06", "Capacitive Touch Driver", (uint8_t[]){0x38, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"FXAS21002", "3-axis gyroscope", (uint8_t[]){0x21, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"FXOS8700", "6-axis sensor with integrated linear accelerometer and magnetometer", (uint8_t[]){0x1c, 0x1d, 0x1f, 0x1e, 0x0}, (uint8_t)0xd, (uint8_t)0xc7},
  {"HDC1008", "Low Power, High Accuracy Digital Humidity Sensor with Temperature Sensor", (uint8_t[]){0x43, 0x42, 0x0}, (uint8_t)0x2, (uint8_t)0x10},
  {"HDC1080", "Low Power, High Accuracy Digital Humidity Sensor with Temperature Sensor", (uint8_t[]){0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"HIH6130", "HumidIcon", (uint8_t[]){0x27, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"HMC5883", "3-Axis Digital Compass/Magnetometer IC", (uint8_t[]){0x1e, 0x0}, (uint8_t)0xa, (uint8_t)0x48},
  {"HT16K33", "LED Matrix Driver", (uint8_t[]){0x71, 0x72, 0x77, 0x73, 0x70, 0x76, 0x75, 0x74, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"HTS221", "Capacitive digital sensor for relative humidity and temperature", (uint8_t[]){0x5f, 0x0}, (uint8_t)0xf, (uint8_t)0xbc},
  {"HTU21D-F", "Humidity/Temp Sensor", (uint8_t[]){0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"HTU31D", "Digital Relative Humidity & Temperature Sensor", (uint8_t[]){0x41, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"HW-061", "I2C Serial Interface LCD1602 Adapter", (uint8_t[]){0x23, 0x24, 0x26, 0x22, 0x27, 0x21, 0x25, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ICM-20948", "9-Axis Motion Tracking device", (uint8_t[]){0x68, 0x69, 0x0}, (uint8_t)0x0, (uint8_t)0xe1},
  {"INA219", "26V Bi-Directional High-Side Current/Power/Voltage Monitor", (uint8_t[]){0x46, 0x49, 0x47, 0x48, 0x4c, 0x4d, 0x43, 0x4b, 0x44, 0x41, 0x4a, 0x45, 0x42, 0x4f, 0x4e, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x39},
  {"INA260", "Precision Digital Current and Power Monitor With Low-Drift, Precision Integrated Shunt", (uint8_t[]){0x46, 0x49, 0x47, 0x48, 0x4c, 0x4d, 0x43, 0x4b, 0x44, 0x41, 0x4a, 0x45, 0x42, 0x4f, 0x4e, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x61},
  {"IS31FL3731", "144-LED Audio Modulated Matrix LED Driver (CharliePlex)", (uint8_t[]){0x77, 0x66, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ISL29125", "Digital Red, Green and Blue Color Light Sensor with IR Blocking Filter", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x7d},
  {"IST-8310", "Three-axis Magnetometer", (uint8_t[]){0xe, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ITG3200", "Gyro", (uint8_t[]){0x68, 0x69, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"L3GD20H", "gyroscope", (uint8_t[]){0x6b, 0x6a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"LC709203F", "Smart LiB Gauge Battery Fuel Gauge LSI For 1‐Cell Lithium‐ion/ Polymer (Li+)", (uint8_t[]){0x11, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"LIS3DH", "3-axis accelerometer", (uint8_t[]){0x18, 0x19, 0x0}, (uint8_t)0xf, (uint8_t)0x33},
  {"LM25066", "PMBus power management IC", (uint8_t[]){0x46, 0x57, 0x11, 0x54, 0x47, 0x16, 0x50, 0x10, 0x13, 0x43, 0x56, 0x5a, 0x53, 0x14, 0x44, 0x59, 0x17, 0x55, 0x41, 0x45, 0x52, 0x42, 0x58, 0x12, 0x51, 0x15, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"LM75b", "Digital temperature sensor and thermal watchdog", (uint8_t[]){0x49, 0x48, 0x4c, 0x4d, 0x4b, 0x4a, 0x4f, 0x4e, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"LPS22HB", "MEMS nano pressure sensor", (uint8_t[]){0x2e, 0x0}, (uint8_t)0xf, (uint8_t)0xb1},
  {"LSM303", "Triple-axis Accelerometer+Magnetometer (Compass)", (uint8_t[]){0x19, 0x1e, 0x0}, (uint8_t)0xf, (uint8_t)0x33},
  {"LSM303", "Triple-axis Accelerometer+Magnetometer (Compass)", (uint8_t[]){0x18, 0x1e, 0x0}, (uint8_t)0x4f, (uint8_t)0x40},
  {"LTC4151", "High voltage (7-80V) current and voltage monitor", (uint8_t[]){0x6c, 0x6e, 0x6b, 0x6a, 0x68, 0x6f, 0x6d, 0x66, 0x69, 0x67, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MA12070P", "Merus Multi level Class D Interated amplifier", (uint8_t[]){0x23, 0x22, 0x21, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MAG3110", "3-Axis Magnetometer", (uint8_t[]){0xe, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MAX17048", "3μA 1-Cell/2-Cell Fuel Gauge with ModelGauge", (uint8_t[]){0x36, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MAX17048", "3μA 1-Cell/2-Cell Fuel Gauge with ModelGauge", (uint8_t[]){0x36, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MAX30101", "High-Sensitivity Pulse Oximeter and Heart-Rate Sensor for Wearable Health", (uint8_t[]){0x55, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MAX3010x", "Pulse & Oximetry sensor", (uint8_t[]){0x57, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MAX31341", "Low-Current, Real-Time Clock with I2C Interface and Power Management", (uint8_t[]){0x69, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MAX44009", "Ambient Light Sensor with ADC", (uint8_t[]){0x4b, 0x4a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MB85RC", "Ferroelectric RAM", (uint8_t[]){0x57, 0x54, 0x50, 0x56, 0x53, 0x55, 0x52, 0x51, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP23008", "8-Bit I/O Expander with Serial Interface I2C GPIO expander", (uint8_t[]){0x23, 0x24, 0x26, 0x22, 0x27, 0x21, 0x25, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP23017", "I2C GPIO expander", (uint8_t[]){0x23, 0x24, 0x26, 0x22, 0x27, 0x21, 0x25, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP3422", "18-Bit, Multi-Channel ΔΣ Analog-to-Digital Converter with I2CTM Interface and On-Board Reference", (uint8_t[]){0x68, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP4532", "7/8-Bit Single/Dual I2C Digital POT with Volatile Memory", (uint8_t[]){0x2c, 0x2a, 0x2e, 0x2f, 0x2b, 0x2d, 0x28, 0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP4725A0", "12-bit DAC", (uint8_t[]){0x60, 0x61, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP4725A1", "12-Bit Digital-to-Analog Converter with EEPROM Memory", (uint8_t[]){0x64, 0x60, 0x61, 0x65, 0x63, 0x66, 0x62, 0x67, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP4725A2", "12-Bit Digital-to-Analog Converter with EEPROM Memory", (uint8_t[]){0x64, 0x65, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP4725A3", "12-Bit Digital-to-Analog Converter with EEPROM Memory", (uint8_t[]){0x66, 0x67, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP4728", "12-Bit 4-Channel Digital-to-Analog Converter (DAC) with EEPROM", (uint8_t[]){0x64, 0x60, 0x61, 0x65, 0x63, 0x66, 0x62, 0x67, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP7940N", "Battery-Backed I2C Real-Time Clock/Calendar with SRAM", (uint8_t[]){0x6f, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MCP9808", "±0.5°C Maximum Accuracy Digital Temperature Sensor", (uint8_t[]){0x1c, 0x1d, 0x18, 0x1b, 0x1f, 0x1a, 0x19, 0x1e, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MLX90614", "IR temperature sensor", (uint8_t[]){0x5a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MLX90632", "FIR temperature sensor", (uint8_t[]){0x3a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MLX90640", "Far infrared thermal sensor array (32x24 RES)", (uint8_t[]){0x33, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MMA845x", "3-axis, 14-bit/8-bit digital accelerometer", (uint8_t[]){0x1c, 0x1d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MPL115A2", "Miniature I2C digital barometer, 50 to 115 kPa", (uint8_t[]){0x60, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MPL3115A2", "Barometric Pressure", (uint8_t[]){0x60, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MPR121", "12-point capacitive touch sensor", (uint8_t[]){0x5c, 0x5b, 0x5a, 0x5d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MPU6050", "6-Axis (Gyro + Accelerometer) MEMS MotionTracking™ Devices", (uint8_t[]){0x68, 0x69, 0x0}, (uint8_t)0x75, (uint8_t)0x68},
  {"MPU6886", "6-Axis (Gyro + Accelerometer) MEMS MotionTracking™ Devices", (uint8_t[]){0x68, 0x69, 0x0}, (uint8_t)0x75, (uint8_t)0x19},
  {"MPU9250", "9-DoF IMU Gyroscope, Accelerometer and Magnetometer", (uint8_t[]){0x68, 0x69, 0x0}, (uint8_t)0x75, (uint8_t)0x71},
  {"MPU9250", "3-Axis Gyroscope and Accelerometer", (uint8_t[]){0x68, 0x0}, (uint8_t)0x75, (uint8_t)0x48},
  {"MS5607", "Barometric Pressure", (uint8_t[]){0x77, 0x76, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"MS5611", "Barometric Pressure", (uint8_t[]){0x77, 0x76, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"NE5751", "Audio processor for IV communication", (uint8_t[]){0x41, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"Nunchuck controller", "Nintendo", (uint8_t[]){0x52, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCA1070", "Multistandard programmable analog CMOS speech transmission IC", (uint8_t[]){0x22, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCA6408A", "Low-voltage, 8-bit I2C-bus and SMBus I/O expander", (uint8_t[]){0x21, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCA9536", "4-bit 2.3- to 5.5-V I2C/SMBus I/O expander with config registers", (uint8_t[]){0x41, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCA9539", "16-bit I/O expander with interrupt and reset", (uint8_t[]){0x77, 0x76, 0x75, 0x74, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCA9541", "2-1 I2C bus arbiter", (uint8_t[]){0x71, 0x72, 0x77, 0x73, 0x70, 0x76, 0x75, 0x74, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCA9685", "16-channel PWM driver default address", (uint8_t[]){0x5e, 0x64, 0x6c, 0x60, 0x6e, 0x46, 0x6b, 0x57, 0x49, 0x6a, 0x5c, 0x5b, 0x54, 0x47, 0x48, 0x4c, 0x50, 0x4d, 0x68, 0x43, 0x61, 0x56, 0x4b, 0x5a, 0x53, 0x65, 0x44, 0x7f, 0x71, 0x72, 0x78, 0x7a, 0x77, 0x59, 0x55, 0x41, 0x4a, 0x73, 0x63, 0x6f, 0x6d, 0x66, 0x5d, 0x45, 0x5f, 0x7b, 0x70, 0x69, 0x76, 0x52, 0x42, 0x4f, 0x58, 0x7e, 0x75, 0x74, 0x4e, 0x79, 0x62, 0x51, 0x67, 0x7d, 0x7c, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCD3311C", "DTMF/modem/musical tone generator", (uint8_t[]){0x24, 0x25, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCD3312C", "DTMF/modem/musical-tone generator", (uint8_t[]){0x24, 0x25, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8523", "RTC", (uint8_t[]){0x68, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8563", "Real-time clock/calendar", (uint8_t[]){0x51, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8569", "LCD column driver for dot matrix displays", (uint8_t[]){0x3c, 0x3b, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8573", "Clock/calendar with Power Fail Detector", (uint8_t[]){0x6b, 0x6a, 0x68, 0x69, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8574", "Remote 8-Bit I/O Expander", (uint8_t[]){0x46, 0x49, 0x47, 0x48, 0x4c, 0x4d, 0x43, 0x4b, 0x44, 0x41, 0x4a, 0x45, 0x42, 0x4f, 0x4e, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8574", "Remote 8-Bit I/O Expander for I2C Bus", (uint8_t[]){0x23, 0x24, 0x26, 0x22, 0x27, 0x21, 0x25, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8574AP", "I²C-bus to parallel port expander", (uint8_t[]){0x38, 0x3c, 0x3b, 0x3e, 0x3f, 0x39, 0x3a, 0x3d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8575", "Remote16-BIT I2C AND SMBus I/O Expander withInterrupt Output", (uint8_t[]){0x23, 0x24, 0x26, 0x22, 0x27, 0x21, 0x25, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8577C", "32/64-segment LCD display driver", (uint8_t[]){0x3a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PCF8578", "Row/column LCD dot matrix driver/display", (uint8_t[]){0x3c, 0x3d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PM2008", "Laser particle sensor", (uint8_t[]){0x28, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PMSA003I", "Digital universal partical concentration sensor", (uint8_t[]){0x12, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"PN532", "NFC/RFID reader", (uint8_t[]){0x48, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA1064", "4-digit LED driver", (uint8_t[]){0x38, 0x3b, 0x39, 0x3a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA2502", "MPEG audio source decoder", (uint8_t[]){0x30, 0x31, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA4700", "VPS Dataline Processor", (uint8_t[]){0x23, 0x21, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA5243P/E", "Computer controlled teletext circuit", (uint8_t[]){0x11, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA5243P/H", "Computer controlled teletext circuit", (uint8_t[]){0x11, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA5243P/K", "Computer controlled teletext circuit", (uint8_t[]){0x11, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA5243P/L", "Computer controlled teletext circuit", (uint8_t[]){0x11, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA5246", "Integrated VIP and teletext", (uint8_t[]){0x11, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAA7706H", "Car radio Digital Signal Processor (DSP)", (uint8_t[]){0x1c, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAB3035", "Digital tuning circuit for computer-controlled TV", (uint8_t[]){0x60, 0x61, 0x63, 0x62, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SAB3037", "Digital tuning circuit for computer-controlled TV", (uint8_t[]){0x60, 0x61, 0x63, 0x62, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SCD30", "CO2, humidity, and temperature sensor", (uint8_t[]){0x61, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SCD40", "CO2 sensor - 2000ppm", (uint8_t[]){0x62, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SCD40-D-R2", "Miniaturized CO2 Sensor", (uint8_t[]){0x62, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SCD41", "CO2 sensor", (uint8_t[]){0x62, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SEN-15892", "Zio Qwiic Loudness Sensor", (uint8_t[]){0x38, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SEN-17374", "Sparkfun EKMC4607112K PIR", (uint8_t[]){0x13, 0x12, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SFA30", "Formaldehyde Sensor Module for HVAC and Indoor Air Quality Applications", (uint8_t[]){0x5d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SGP30", "Gas Sensor", (uint8_t[]){0x58, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SGP40", "Indoor Air Quality Sensor for VOC Measurements", (uint8_t[]){0x59, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SH1106", "132 X 64 Dot Matrix OLED/PLED  Preliminary Segment/Common Driver with Controller", (uint8_t[]){0x3c, 0x3d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SHT31", "Humidity/Temp sensor", (uint8_t[]){0x44, 0x45, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SHTC3", "Humidity & Temperature Sensor", (uint8_t[]){0x70, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SI1132", "UV Index and Ambient Light Sensor", (uint8_t[]){0x60, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SI1133", "UV Index and Ambient Light Sensor", (uint8_t[]){0x55, 0x52, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"Si1145", "Proximity/UV/Ambient Light Sensor IC With I2C Interface", (uint8_t[]){0x60, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"Si4713", "FM Radio Transmitter with Receive Power Scan", (uint8_t[]){0x11, 0x63, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"Si5351A", "Clock Generator", (uint8_t[]){0x60, 0x61, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"Si7021", "Humidity/Temp sensor", (uint8_t[]){0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SPL06-007", "Digital Temperature/Pressure Sensor", (uint8_t[]){0x77, 0x76, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SPS30", "Particulate Matter Sensor for Air Quality Monitoring and Control", (uint8_t[]){0x69, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SSD1305", "132 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller", (uint8_t[]){0x3c, 0x3d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"SSD1306", "128 x 64 Dot Matrix Monochrome OLED/PLED Segment/Common Driver with Controller", (uint8_t[]){0x3c, 0x3d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"ST25DV16K", "Dynamic NFC/RFID tag IC with 4-, 16-, or 64-Kbit EEPROM, and fast transfer mode capability", (uint8_t[]){0x57, 0x53, 0x2d, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"STDS75", "STDS75 temperature sensor", (uint8_t[]){0x49, 0x48, 0x4c, 0x4d, 0x4b, 0x4a, 0x4f, 0x4e, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"STMPE610", "Resistive Touch controller", (uint8_t[]){0x44, 0x41, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"STMPE811", "Resistive touchscreen controller", (uint8_t[]){0x44, 0x41, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TCA9548", "1-to-8 I2C Multiplexer", (uint8_t[]){0x71, 0x72, 0x77, 0x73, 0x70, 0x76, 0x75, 0x74, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TCA9548A", "Low-Voltage8-Channel I2CSwitchwithReset", (uint8_t[]){0x71, 0x72, 0x77, 0x73, 0x70, 0x76, 0x75, 0x74, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TCA9554", "4 Low Voltage 8-Bit I 2C and SMBus Low-Power I/O Expander With Interrupt Output and Configuration Registers", (uint8_t[]){0x23, 0x24, 0x26, 0x22, 0x27, 0x21, 0x25, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TCS34725", "Color sensor", (uint8_t[]){0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA4670", "Picture signal improvement circuit", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA4671", "Picture signal improvement circuit", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA4672", "Picture signal improvement (PSI) circuit", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA4680", "Video processor", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA4687", "Video processor", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA4688", "Video processor", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA4780", "Video control with gamma control", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA7433", "Basic function audio processor", (uint8_t[]){0x45, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8370", "High/medium perf. sync. processor", (uint8_t[]){0x46, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8376", "One-chip multistandard video", (uint8_t[]){0x45, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8415", "TVNCR stereo/dual sound processor", (uint8_t[]){0x42, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8417", "TVNCR stereo/dual sound processor", (uint8_t[]){0x42, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8421", "Audio processor with loudspeaker and headphone channel", (uint8_t[]){0x41, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8424", "Audio processor with loudspeaker channel", (uint8_t[]){0x41, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8425", "Audio processor with loudspeaker channel", (uint8_t[]){0x41, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8426", "Hi-fi stereo audio processor", (uint8_t[]){0x41, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA8442", "Interface for colour decoder", (uint8_t[]){0x44, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA9150", "Deflection processor", (uint8_t[]){0x46, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TDA9860", "Hi-fi audio processor", (uint8_t[]){0x41, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TEA5767", "Radio receiver", (uint8_t[]){0x60, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TEA6100", "FM/IF for computer-controlled radio", (uint8_t[]){0x61, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TEA6300", "Sound fader control and preamplifier/source selector", (uint8_t[]){0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TEA6320", "4-input tone/volume controller with fader control", (uint8_t[]){0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TEA6330", "Sound fader control circuit for car radios", (uint8_t[]){0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TMP006", "Infrared Thermopile Sensor in Chip-Scale Package", (uint8_t[]){0x46, 0x47, 0x43, 0x44, 0x41, 0x45, 0x42, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TMP007", "IR Temperature sensor", (uint8_t[]){0x46, 0x47, 0x43, 0x44, 0x41, 0x45, 0x42, 0x40, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TMP102", "Temperature sensor", (uint8_t[]){0x49, 0x48, 0x4b, 0x4a, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TPA2016", "2.8-W/Ch Stereo Class-D Audio Amplifier With Dynamic Range Compression and Automatic Gain Control", (uint8_t[]){0x58, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TSA5511", "1.3 GHz PLL frequency synthesizer for TV", (uint8_t[]){0x60, 0x61, 0x63, 0x62, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TSL2561", "Light sensor", (uint8_t[]){0x49, 0x39, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"TSL2591", "Light sensor", (uint8_t[]){0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"UMA1014T", "Low-power frequency synthesizer for mobile radio communications", (uint8_t[]){0x63, 0x62, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VCNL40x0", "Proximity sensor", (uint8_t[]){0x13, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VCNL4200", "High Sensitivity Long Distance Proximity and Ambient Light Sensor With I2C Interface", (uint8_t[]){0x51, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VEML6070", "UVA Light Sensor with I2C Interface", (uint8_t[]){0x38, 0x39, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VEML6075", "UVA and UVB Light Sensor", (uint8_t[]){0x10, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VEML7700", "High Accuracy Ambient Light Sensor", (uint8_t[]){0x10, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VL53L0x", "Time Of Flight distance sensor", (uint8_t[]){0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VL6180X", "Time Of Flight distance sensor", (uint8_t[]){0x29, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"VML6075", "UVA and UVB Light Sensor with I2C Interface", (uint8_t[]){0x10, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"WITTY PI 3", "WITTY PI 3 (Mini) - REALTIME CLOCK (DS3231SN) AND POWER MANAGEMENT FOR RASPBERRY PI", (uint8_t[]){0x68, 0x69, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"XD8574", "I²C 8-Bit I/O Expander", (uint8_t[]){0x71, 0x72, 0x77, 0x73, 0x70, 0x76, 0x75, 0x74, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
  {"XD8574A", "I²C 8-Bit I/O Expander", (uint8_t[]){0x23, 0x24, 0x26, 0x22, 0x27, 0x21, 0x25, 0x20, 0x0}, (uint8_t)0x0, (uint8_t)0x0},
};

void lookup(uint8_t addr) {
  for (size_t i = 0; i < sizeof(I2C_SCANNER_KNOWN_DEVICES) / sizeof(I2C_SCANNER_KNOWN_DEVICES[0]); i++) {
    const uint8_t *addresses = I2C_SCANNER_KNOWN_DEVICES[i].addresses;
    for (size_t j = 0; addresses[j] != 0x0; j++) {
      if (addr == addresses[j]) {
        Serial.printf("  %s:  %s\n", I2C_SCANNER_KNOWN_DEVICES[i].name, I2C_SCANNER_KNOWN_DEVICES[i].description);
      }
    }
  }
}

void setup() {
  auto cfg = M5.config();
  AtomS3.begin(cfg);
  Serial.begin(9600);
  Wire.begin();
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      lookup(address);
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }
}

void loop() {
  delay(3);
}
