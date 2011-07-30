#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "avr.h"
#include "util.h"
#include "io.h"
#include "types.h"
#include "digital.h"
#include "pwm.h"

void
main()
{
  byte i;
  
  pin_set_mode(6, OUTPUT);

  while(true) {
    pwm_set_value(6, i++);
    delay_ms(5);
  }
}
