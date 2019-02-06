// time adjust

static int8_t s;  // using multi-purpose value
/////////////////////////////////////////////////////////////////////////////////
//        BOOT          BOOT          BOOT          BOOT          BOOT
/////////////////////////////////////////////////////////////////////////////////
void _00 ( void )
{
  lcd.noCursor();
  lcd.noBlink();
  clock_refresh();
  DisplayStop = OFF;
  EventID++;
}
/////////////////////////////////////////////////////////////////////////////////
//        IDLE          IDLE          IDLE          IDLE          IDLE
/////////////////////////////////////////////////////////////////////////////////
void _01 ( void )
{
  if ( !EdgeTriggerSwitch ) return;
  EventID = LastEventID;
  lcd.cursor();
}
/////////////////////////////////////////////////////////////////////////////////
//        YEAR        YEAR        YEAR        YEAR        YEAR        YEAR
/////////////////////////////////////////////////////////////////////////////////
void _02 ( void )
{
  LastEventID = EventID;
  lcd.setCursor( 3, 0 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _CENTER ) { EventID++; ReleaseCounter = 0; return; }
  if ( CurrentValue == _LEFT   ) { EventID = _SECOND; ReleaseMax = RMS; s = clock.getSecond() + 1 ; return; }
  if ( CurrentValue == _RIGHT  ) { EventID++; return; }
  event_switcher( _YEAR );
  s = clock.getYear();
  if ( CurrentValue == _UP   ) s++;
  if ( CurrentValue == _DOWN ) s--;
  if ( s > 99 ) s = 0;
  if ( s < 0 ) s = 99;
  clock.setYear( s );
  DateTime y = rtc.now();
  if ( y.year() % 4 == 0 ) dom[2] = 29; else dom[2] = 28;
  if ( y.day() > dom[ y.month() ] ) clock.setDate( dom[ y.month() ] );
  print_dow_str();
  print_date();
  print_year();
}
/////////////////////////////////////////////////////////////////////////////////
//        MONTH        MONTH        MONTH        MONTH        MONTH
/////////////////////////////////////////////////////////////////////////////////
void _03 ( void )
{
  LastEventID = EventID;
  lcd.setCursor( 7, 0 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _CENTER ) { EventID++; return; }
  if ( CurrentValue == _LEFT   ) { EventID--; return; }
  if ( CurrentValue == _RIGHT  ) { EventID++; return; }
  event_switcher( _MONTH );
  DateTime m = rtc.now();
  s = m.month();
  if ( CurrentValue == _UP   ) s++;
  if ( CurrentValue == _DOWN ) s--;
  if ( s > 12 ) s = 1;
  if ( s < 1  ) s = 12;
  clock.setMonth( s );
  if ( m.year() % 4 == 0 ) dom[2] = 29; else dom[2] = 28;
  if ( m.day() > dom[ s ] )  clock.setDate( dom[ s ] );
  print_dow_str();
  print_mon_str();
  print_date();
}
/////////////////////////////////////////////////////////////////////////////////
//        DATE        DATE        DATE        DATE        DATE        DATE
/////////////////////////////////////////////////////////////////////////////////
void _04 ( void )
{
  LastEventID = EventID;
  lcd.setCursor( 10, 0 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _CENTER ) { EventID++; return; }
  if ( CurrentValue == _LEFT   ) { EventID--; return; }
  if ( CurrentValue == _RIGHT  ) { EventID++; return; }
  s = clock.getDate();
  if ( CurrentValue == _UP   ) s++;
  if ( CurrentValue == _DOWN ) s--;
  if ( clock.getYear() % 4 == 0 ) dom[2] = 29; else dom[2] = 28;
  if ( s > dom[clock.getMonth(Century) ] ) s = 1;
  if ( s < 1 ) s = dom[clock.getMonth(Century)];
  clock.setDate( s );
  print_dow_str();
  print_date();
  event_switcher( _DATE );
}
/////////////////////////////////////////////////////////////////////////////////
//        SIGNAL        SIGNAL        SIGNAL        SIGNAL        SIGNAL
/////////////////////////////////////////////////////////////////////////////////
void _05( void ) // _SIGNAL
{
  LastEventID = EventID;
  lcd.setCursor( 15, 0 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _CENTER ) { EventID++; return; }
  if ( CurrentValue == _LEFT   ) { EventID--; return; }
  if ( CurrentValue == _RIGHT  ) { EventID++; return; }
  SignalFlag = !SignalFlag;
  print_time_signal_flag();
  EEPROM.write( 1 , SignalFlag );
  event_switcher( _SIGNAL );
}
/////////////////////////////////////////////////////////////////////////////////
//        AMPMMT        AMPMMT        AMPMMT        AMPMMT        AMPMMT
/////////////////////////////////////////////////////////////////////////////////
void _06 ( void )
{
  LastEventID = EventID;
  lcd.setCursor( 1, 1 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _CENTER ) { EventID++; return; }
  if ( CurrentValue == _LEFT   ) { EventID--; return; }
  if ( CurrentValue == _RIGHT  ) { EventID++; return; }
  event_switcher ( _AMPMMT );
  Military = !Military;
  print_apm_str();
  print_hour();
}
/////////////////////////////////////////////////////////////////////////////////
//        HOUR        HOUR        HOUR        HOUR        HOUR        HOUR
/////////////////////////////////////////////////////////////////////////////////
void _07 ( void )
{
  LastEventID = EventID;
  lcd.setCursor( 4, 1 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _CENTER ) { EventID++; return; }
  if ( CurrentValue == _LEFT   ) { EventID--; return; }
  if ( CurrentValue == _RIGHT  ) { EventID++; return; }
  s = clock.getHour( h12, PM );
  if ( CurrentValue == _UP   ) s++;
  if ( CurrentValue == _DOWN ) s--;
  if ( s > 23 ) s = 0;
  if ( s < 0  ) s = 23;
  clock.setHour( s );
  print_apm_str();
  print_hour();
  event_switcher( _HOUR );
}
/////////////////////////////////////////////////////////////////////////////////
//        MINUTE        MINUTE        MINUTE        MINUTE        MINUTE
/////////////////////////////////////////////////////////////////////////////////
void _08 ( void )
{
  LastEventID = EventID;
  lcd.setCursor( 7, 1 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _CENTER ) { EventID++; return; }
  if ( CurrentValue == _LEFT   ) { EventID--; return; }
  if ( CurrentValue == _RIGHT  ) { EventID++; s = clock.getSecond(); return; }
  s = clock.getMinute();
  if ( CurrentValue == _UP   ) s++;
  if ( CurrentValue == _DOWN ) s--;
  if ( s > 59 ) s = 0;
  if ( s < 0  ) s = 59;
  clock.setMinute( s );
  print_min();
  event_switcher( _MINUTE );
}
/////////////////////////////////////////////////////////////////////////////////
//        SECOND        SECOND        SECOND        SECOND        SECOND
/////////////////////////////////////////////////////////////////////////////////
void _09 ( void )
{
  LastEventID = EventID;
  lcd.setCursor( 10, 1 );
  if ( !EdgeTriggerSwitch ) return; RepeatCounter = 0;
  if ( CurrentValue == _LEFT  ) { EventID--; ReleaseCounter = RMO; DisplayStop = OFF; return; }
  if ( CurrentValue == _RIGHT ) { EventID = _YEAR; ReleaseCounter = RMO; DisplayStop = OFF; return; }
  if ( CurrentValue == _UP    ) { s++; DisplayStop = ON; }
  if ( CurrentValue == _DOWN  ) { s--; DisplayStop = ON; }
  if ( s > 59 ) s = 0; if ( s < 0  ) s = 59;
  lcd.setCursor( 9,1 ); add_zero(s);
  if ( CurrentValue != _CENTER ) return;
  clock.setSecond( s );
  event_switcher( _BOOT );
  DisplayStop = OFF;
}
/////////////////////////////////////////////////////////////////////////////////
//        _DUMMY        _DUMMY        _DUMMY        _DUMMY        _DUMMY
/////////////////////////////////////////////////////////////////////////////////
void _10 ( void )
{
  if ( DirectSwitch ) return;
  EventID = TemporaryEventID;
  lcd.cursor();
}
