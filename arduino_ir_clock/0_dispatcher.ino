// event transition dispatcher

void ( *event[] )() = { _00,_01,_02,_03,_04,_05,_06,_07,_08,_09,_10 };

#define   _BOOT    0    // _00() init
#define   _IDLE    1    // _01() idle
#define   _YEAR    2    // _02() adjust year
#define   _MONTH   3    // _03() adjust month
#define   _DATE    4    // _04() adjust date
#define   _SIGNAL  5    // _05()
#define   _AMPMMT  6    // _06() change 12/24
#define   _HOUR    7    // _07() adjust hour
#define   _MINUTE  8    // _08() adjust minute
#define   _SECOND  9    // _09() adjust second
#define   _DUMMY  10    // _10() prevent long press

static uint8_t EventID;

void event_dispatcher ( void ) { ( *event[ EventID ] )(); }

static uint8_t TemporaryEventID;
void event_switcher( uint8_t e ) {
  TemporaryEventID = e;
  EventID = _DUMMY;
}

#define ON  true
#define OFF false