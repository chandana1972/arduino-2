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
#include "serial.h"

#include "components/shift_register.h"

#define DATA 13
#define SER_CLOCK 12
#define LATCH_CLOCK 11

PROGMEM byte digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                          0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void
main()
{
  ShiftRegister reg = {DATA, SER_CLOCK, LATCH_CLOCK};
  shift_register_init(&reg);

  while(1) {
    for(byte i = 0; i < 16; i++) {
      shift_register_set(&reg, pgm_read_byte(&digits[i]));
      delay_ms(500);
    }
  }
}
