#include <avr/io.h>
#include "timer.h"

Timer PROGMEM *pin_to_timer_map[] = {
  NULL,
  NULL,
  NULL,
  &(Timer) {(uint16_t*) &OCR2B, &TCCR2A, &TCCR2B},
  NULL,
  &(Timer) {(uint16_t*) &OCR0B, &TCCR0A, &TCCR0B},
  &(Timer) {(uint16_t*) &OCR0A, &TCCR0A, &TCCR0B},
  NULL,
  NULL,
  &(Timer) {&OCR1A, &TCCR1A, &TCCR1B},
  &(Timer) {&OCR1B, &TCCR1A, &TCCR1B},
  &(Timer) {(uint16_t*) &OCR2A, &TCCR2A, &TCCR2B},
  NULL
};
