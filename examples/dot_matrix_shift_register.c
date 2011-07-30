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

void
shift_in(bool value)
{
  pin_set_value(DATA, value);
  pin_set_value(SER_CLOCK, HIGH);
  pin_set_value(SER_CLOCK, LOW);
}

void
latch()
{
  pin_set_value(LATCH_CLOCK, HIGH);
}

void
main()
{
  ShiftRegister reg = {13, 12, 11};
  shift_register_init(&reg);

  while(1) {
    for(byte i = 0; i < 5; i++) {
      shift_register_set(&reg, 0b11111111 ^ 1 << i);
      shift_register_set(&reg, 0b11111111);
      delay_ms(5);
    }
  }
}
