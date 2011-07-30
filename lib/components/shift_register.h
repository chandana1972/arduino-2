#include <inttypes.h>
#include "types.h"

#ifndef _SHIFT_REGISTER_H_
#define _SHIFT_REGISTER_H_

typedef struct
{
  pin data;
  pin shift_clock;
  pin latch_clock;
} ShiftRegister;

void shift_register_init(ShiftRegister *reg);
void shift_register_push(ShiftRegister *reg, byte value);
void shift_register_latch(ShiftRegister *reg);
void shift_register_set(ShiftRegister *reg, byte value);

#endif /* _SHIFT_REGISTER_H_ */
