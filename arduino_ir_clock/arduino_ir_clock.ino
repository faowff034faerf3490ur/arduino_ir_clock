//    Arduino Table Clock ( IR adjust & piezoelectric passive buzzer )
//
//    2010 Jan 28 Mon
//    MT 21:51:37 19˚C
//
//    https://youtu.be/RtYUacUfc_U

void setup()
{
  rtc_setup();    // DS3231 Real Time Clock
  irr_setup();    // VS1838 Infrared Receiver
  lcd_setup();    // LCD1602 Liquid Crystal Display
  piezo_setup();  // piezoelectric buzzer
  EEPROM_setup(); // time signal 
}

void loop()
{
  infrared_checker();
  event_dispatcher();
  confirmation_sound();
  display_clock();
}
