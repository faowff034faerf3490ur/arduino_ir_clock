// piezoelectric passive buzzer

#include <avr/io.h>

#define PWM_PIN 6

static uint8_t tune = 50;
static boolean EdgeTriggerSwitch = OFF;

void confirmation_sound( void ) {
  if ( !SignalFlag ) return;
  static unsigned long pms;
  if ( EdgeTriggerSwitch ) {
    pms = millis();
    analogWrite( PWM_PIN,tune ); 
    EdgeTriggerSwitch = OFF;
  }
  if ( millis() - pms > 80 ) analogWrite( PWM_PIN,255 );
}

unsigned int frequency = 10000;
float duty = 0.1;

void piezo_setup( void ) {
  TCCR0A = 0b00100001;
  TCCR0B = 0b00010010;
  OCR0A = ( uint16_t )( 1000000 / frequency );
  OCR0B = ( uint16_t )( 1000000 / frequency * duty );
}
