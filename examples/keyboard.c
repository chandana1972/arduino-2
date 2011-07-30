#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "avr.h"
#include "util.h"
#include "io.h"
#include "types.h"
#include "digital.h"
#include "serial.h"

#include "circular_buffer.h"
#include "components/keyboard.h"

#define KBD_CLOCK_PIN 2
#define KBD_DATA_PIN 3

Keyboard kbd;

void
main()
{
  KbdKey key;

  sei();
  serial_init();
  pin_set_mode(KBD_CLOCK_PIN, INPUT);
  pin_set_mode(KBD_DATA_PIN, INPUT);
  kbd_init(&kbd, 8, KBD_CLOCK_PIN, KBD_DATA_PIN);
  // TODO check if malloc failed

  // INT0 on falling edge
  EICRA |= 1 << ISC01;
  EICRA &= ~(1 << ISC00);
  EIMSK |= 1 << INT0;

  while(1) {
    if(kbd_get_key(&kbd, &key) && !(key.modifiers & KbdBreak)) {
      if(key.key == '\n') {
        serial_write("\r\n");
      } else {
        char buf[2] = {key.key, 0};
        serial_write(buf);
      }
    }
  }
}


ISR(INT0_vect)
{
  static byte current_bit = 0;
  static byte code = 0;

  byte value;

  // TODO if the first bit is not a zero, we're out of sync
  value = pin_get_value(kbd.data_pin);
  if(current_bit > 0 && current_bit < 9) {
    // TODO save parity, too
    code |= value << (current_bit - 1);
  }

  current_bit++;

  if(current_bit == 11) {
    // TODO pull clock low to prevent keyboard from sending more data
    // ^ really, though? we're probably fast enough
    // TODO check parity
    kbd_store_byte(&kbd, code);

    current_bit = 0;
    code        = 0;
  }
}
