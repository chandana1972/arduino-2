#include <avr/pgmspace.h>
#include <stdlib.h>
#include <inttypes.h>
#include "types.h"

#ifndef _TIMER_H_
#define _TIMER_H_

#define PIN_TO_TIMER(PIN) (Timer*)pgm_read_word(&pin_to_timer_map[PIN])

typedef struct
{
  volatile uint16_t *output;
  volatile byte     *register_a;
  volatile byte     *register_b;
} Timer;

extern Timer *pin_to_timer_map[];

#endif /* _TIMER_H_ */
