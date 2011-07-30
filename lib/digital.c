#include <avr/io.h>
#include <avr/pgmspace.h>
#include "digital.h"
#include "io.h"
#include "types.h"

volatile PROGMEM byte *digital_pin_to_port_map[] = {
  &PORTD, // pins D0 to D7
  &PORTB, // pins D8 to D13
  &PORTC // pins A0 to A5
};

volatile PROGMEM byte *digital_pin_to_register_map[] = {
  &DDRD, // pins D0 to D7
  &DDRB, // pins D8 to D13
  &DDRC // PINS A0 to A5
};

volatile PROGMEM byte *digital_pin_to_input_map[] = {
  &PIND,
  &PINB,
  &PINC
};

byte
pin_set_mode (pin pin, byte type) {
  volatile byte *reg = PIN_TO_REGISTER(pin);

  if(type == INPUT) {
    return *reg &= ~(_BV(PIN_TO_SHIFT(pin)));
  } else {
    return *reg |= _BV(PIN_TO_SHIFT(pin));
  }
}

byte
pin_set_value (pin pin, byte value)
{
  volatile byte *port = PIN_TO_PORT(pin);

  if(value == HIGH) {
    return *port |= _BV(PIN_TO_SHIFT(pin));
  } else {
    return *port &= ~(_BV(PIN_TO_SHIFT(pin)));
  }
}

byte
pin_get_value(pin pin)
{
  volatile byte *input = PIN_TO_INPUT(pin);
  byte           shift = PIN_TO_SHIFT(pin);

  return !!(*input & (_BV(shift)));
}
