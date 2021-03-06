// Liquid crystal display

// abbreviations
#define months_of_the_year "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
#define days_of_the_week   "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
#define days_of_the_month  00, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 // ordinary year
//                         00, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 // leap year

// days, weeks and months of the year
const char    *moy[] = { months_of_the_year };
const char    *dow[] = { days_of_the_week   };
static uint8_t dom[] = { days_of_the_month  };

void display_clock ( void )
{
  static unsigned long pms, cms; cms = millis();
  if ( cms - pms < 10 ) return; else pms = cms;  // response speed
  static DateTime t;
  static DateTime p;
  t = rtc.now();
  if ( t.second() != p.second() ) print_sec();
  if ( t.minute() != p.minute() ) print_min();
  if ( t.hour()   != p.hour()   ) { print_hour(); print_apm_str(); }
  if ( t.day()    != p.day()    ) { print_date(); print_dow_str(); }
  if ( t.month()  != p.month()  ) print_mon_str();
  if ( t.year()   != p.year()   ) print_year();
  print_temperature();
  p = t;
  static uint8_t PrevSignal;
  if ( !SignalFlag ) return;
  if ( t.hour() == PrevSignal ) return;
  else EdgeTriggerSwitch = ON;
  PrevSignal = t.hour();
  confirmation_sound();
}

bool Century = false;
bool h12;
bool PM;

void print_year( void )
{
  lcd.setCursor( 0, 0 );
  lcd.print( 2000 + clock.getYear(), DEC );
}

void print_mon_str( void ) {
  lcd.setCursor( 5, 0 );
  lcd.print( moy[clock.getMonth(Century) - 1 ] );
}

void print_date( void ) {
  lcd.setCursor( 9, 0 );
  add_zero( clock.getDate() );
}

void add_zero( uint8_t val ) {
  if ( val < 10 ) lcd.print( "0" );
  lcd.print( val );
}

void print_dow_str( void ) {
  lcd.setCursor( 12, 0 );
  set_dow();
  lcd.print( dow[ clock.getDoW( ) - 1 ] );
}

static boolean Military = OFF;

void print_apm_str( void ) {
  lcd.setCursor( 0, 1 );
  if ( Military == OFF ) {
    if ( clock.getHour(h12, PM) > 11 ) lcd.print( "PM ");
    else lcd.print( "AM " );
  } else lcd.print( "MT ");
}

void print_hour( void ) {
  uint8_t val = clock.getHour(h12, PM);
  if ( Military == OFF ) {
    if ( clock.getHour(h12, PM) > 12 ) val -= 12;
    if ( clock.getHour(h12, PM) == 0 ) val  = 12;
  }
  lcd.setCursor( 3, 1 );
  add_zero( val );
  lcd.print( ":" );
}

void print_min( void ) {
  lcd.setCursor( 6, 1 );
  add_zero( clock.getMinute() );
  lcd.print( ":" );
}

void print_sec( void ) {
  if ( DisplayStop == ON  ) return;
  lcd.setCursor( 9, 1 );
  add_zero( clock.getSecond() );
}

void print_time_signal_flag( void )
{
  lcd.setCursor( 15, 0 );
  if ( SignalFlag ) lcd.print( "'" );
  else  lcd.print( " " );
}

void print_temperature( void )
{
  static int8_t prevTemp = 100;
  static int8_t currTemp;
  currTemp = ( int8_t )clock.getTemperature();
  if ( prevTemp == currTemp ) return;
  prevTemp = currTemp;
  lcd.setCursor( 11, 1 );
  if ( currTemp < 0 )  lcd.print("-");
  else lcd.print(" ");
  add_zero( abs(currTemp ) );
  lcd.setCursor( 14, 1 );
  lcd.print( char(223) );
  lcd.print( "C" );
}

void clock_refresh( void )
{
  print_sec();
  print_min();
  print_hour();
  print_apm_str();
  print_dow_str();
  print_date();
  print_mon_str();
  print_year();
  print_temperature();
  print_time_signal_flag();
}

void set_dow( void )
{
  int dow;
  byte mArray[] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  DateTime t = rtc.now();
  dow = ( t.year() % 100);
  dow = dow * 1.25;
  dow += t.day();
  dow += mArray[ t.month() - 1];
  if ((( t.year() % 4 ) == 0 ) && ( t.month() < 3 ) ) dow -= 1;
  while (dow > 7) dow -= 7;
  clock.setDoW( dow );
}
