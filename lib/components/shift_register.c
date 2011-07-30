#include <inttypes.h>
#include "components/shift_register.h"
#include "digital.h"
#include "io.h"
#include "types.h"

void
shift_register_init(ShiftRegister *reg)
{
  pin_set_mode(reg->data,        OUTPUT);
  pin_set_mode(reg->shift_clock, OUTPUT);
  pin_set_mode(reg->latch_clock, OUTPUT);
}

void
shift_register_push(ShiftRegister *reg, byte value)
{
  pin_set_value(reg->data, value);

  pin_set_value(reg->shift_clock, LOW);
  pin_set_value(reg->shift_clock, HIGH);
  pin_set_value(reg->shift_clock, LOW);
}

void
shift_register_latch(ShiftRegister *reg)
{
  pin_set_value(reg->latch_clock, LOW);
  pin_set_value(reg->latch_clock, HIGH);
  pin_set_value(reg->latch_clock, LOW);
}

void
shift_register_set(ShiftRegister *reg, byte value)
{
  byte i;

  pin_set_value(reg->shift_clock, LOW);
  pin_set_value(reg->latch_clock, LOW);

  for(i = 0; i < 8; i++) {
    shift_register_push(reg, !!(value & (1 << (7-i))));
  }
  shift_register_latch(reg);
}
