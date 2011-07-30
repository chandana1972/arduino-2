#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>

#include "util.h"
#include "io.h"
#include "types.h"
#include "digital.h"

#include "components/shift_register.h"

void main() __attribute__ ((noreturn));

void
main()
{
  unsigned char i;
  ShiftRegister reg = {12, 10, 11};

  shift_register_init(&reg);


  while(true) {
    for(i = 0; i < 8; i++) {
      shift_register_set(&reg, _BV(i));
      delay_ms(100);
    }

    for(i = 7; i >= 0; i--) {
      shift_register_set(&reg, _BV(i));
      delay_ms(100);
    }
  }
}

