#include <avr/io.h>
#include "timer.h"
#include "pwm.h"

// TODO proper name, proper params
void
pwm_set_value(pin pin, byte value)
{
  Timer *timer = PIN_TO_TIMER(pin);

  // not a pin that supports PWM
  if(timer == NULL) {
    return;
  }

  *timer->register_a = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  *timer->register_b =  _BV(CS22);

  *timer->output = value;
}
