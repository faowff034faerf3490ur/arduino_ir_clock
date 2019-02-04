// setup

// DS3231 Real Time Clock ( https://github.com/NorthernWidget/DS3231 )
#include <DS3231.h>
DS3231 clock; RTClib rtc;
void rtc_setup( void ) { Wire.begin(); set_dow(); }

// 1602A Liquid Crystal Display ( https://github.com/johnrickman/LiquidCrystal_I2C )
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd( 0x27,16,2 );
void lcd_setup( void ) { lcd.init(); lcd.backlight(); }

// VS1838 infrared radiation receiver ( )
#include <IRremote.h>
#define RECV_PIN 12 
IRrecv irrecv( RECV_PIN ); decode_results results;
void irr_setup( void ) { irrecv.enableIRIn(); }

// Arduino's EEPROM
#include <EEPROM.h>
static bool SignalFlag;
void EEPROM_setup( void ) { SignalFlag = EEPROM.read( 1 ); }