#ifndef NmeaXDR_h
#define NmeaXDR_h

/*
  XDR - Transducer Measurement
  https://gpsd.gitlab.io/gpsd/NMEA.html#_xdr_transducer_measurement
  https://www.eye4software.com/hydromagic/documentation/articles-and-howtos/handling-nmea0183-xdr/

  Format: $--XDR,a,x.x,a,c--c, ..... *hh<CR><LF>
  Example:

  $HCXDR,A,171,D,PITCH,A,-37,D,ROLL,G,367,,MAGX,G,2420,,MAGY,G,-8984,,MAGZ*41
  $SDXDR,C,23.15,C,WTHI*70

  Transducer Types:
     A - Angular displacement
     C - Temperature
     D - Depth
     F - Frequency
     H - Humidity
     N - Force
     P - Pressure
     R - Flow
     B - Absolute humidity
     G - Generic
     I - Current
     L - Salinity
     S - Switch, valve
     T - Tachometer
     U - Voltage
     V - Volume
     could be more

  Unit of measurement                                     
     "" - could be empty!                                 
     A - Amperes                                          
     B - Bars | Binary                                    
     C - Celsius                                          
     D - Degrees                                          
     H - Hertz                                            
     I - liters/second                                    
     K - Kelvin | Density, kg/m3 kilogram per cubic metre 
     M - Meters | Cubic Meters (m3)                       
     N - Newton                                           
     P - Percent of full range | Pascal                   
     R - RPM                                              
     S - Parts per thousand                               
     V - Volts                                            
     could be more
*/

/*
  Bareboat Necessities Sensors NMEA-0183 XDR Sentences:

  NMEA-0183 Sender 
    BB

  Temperature, pressure, humidity

  $BBXDR,C,24.57,C,TEMP_BMP280*52
  $BBXDR,P,101733.00,P,PRES_BMP280*49
  $BBXDR,H,30.60,P,HUMI_DHT12*60
  $BBXDR,C,23.40,C,TEMP_DHT12*6D
  $BBXDR,C,24.58,C,TEMP_BMP280*5D
  $BBXDR,P,101734.00,P,PRES_BMP280*4E
  $BBXDR,H,30.30,P,HUMI_DHT12*65
  $BBXDR,C,23.00,C,TEMP_DHT12*69
  $BBXDR,C,24.58,C,TEMP_BMP280*5D


*/

#include "NmeaChecksum.h"

void gen_nmea0183_xdr(const char *nmea_fmt, float value) {
  char nmea_part[82];
  snprintf(nmea_part, 76, nmea_fmt, value);
  int checksum = nmea0183_checksum(nmea_part);
  Serial.printf("%s*%02X\r\n", nmea_part, checksum);
}

#endif
