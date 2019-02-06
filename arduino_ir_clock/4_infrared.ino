// Infrared Receiver

static boolean DirectSwitch;
static unsigned long CurrentValue;
static unsigned long RepeatCounter;

void infrared_checker ( void )
{
  DirectSwitch = EdgeTriggerSwitch = OFF;
  if ( irrecv.decode( &results ) )
  {
    if ( results.decode_type == NEC )
    {
      DirectSwitch = ON;
      if ( results.bits  ) EdgeTriggerSwitch = ON;
      if ( results.bits  ) CurrentValue = results.value;
      else RepeatCounter++;
    } else RepeatCounter = 0;
    irrecv.resume();
  }
  else CurrentValue = 0;
  long_push_checker();
  release_checker();
}

// long push and release counter

static unsigned long ReleaseCounter;
static boolean DisplayStop = OFF;
static unsigned long ReleaseMax;
static uint8_t LastEventID = _YEAR;

#define RMS 600  // Release time Maximum second.
#define RMO 300  // Release time Maximum others.

void release_checker ( void )
{
  if ( DisplayStop == ON ) ReleaseMax = RMS; else ReleaseMax = RMO;
  if ( DirectSwitch ) ReleaseCounter = ReleaseMax;
  static unsigned long pms, cms; cms = millis();
  if ( cms - pms < 100  ) return; else pms = cms;
  if ( ReleaseCounter  > 0   ) ReleaseCounter--;
  if ( ReleaseCounter == 200 ) EventID = _BOOT;
  if ( ReleaseCounter != 1   ) return;
  LastEventID = _YEAR; //  forget last event ID
  EventID = _BOOT;
}

void long_push_checker ( void ) // wait about 3 sec and changes 12/24
{
  if ( RepeatCounter < 10 ) return;
  RepeatCounter = 0;
  LastEventID = _YEAR; //  forget last event ID
  EventID = _BOOT;
}
