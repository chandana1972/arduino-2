#include <inttypes.h>
#include <avr/pgmspace.h>
#include "types.h"

#ifndef _DIGITAL_H_
#define _DIGITAL_H_

#define PINS_PER_PORT 8

#define PIN_TO_SHIFT(PIN)    PIN % PINS_PER_PORT
#define PIN_TO_INDEX(PIN)    PIN / PINS_PER_PORT
#define PIN_TO_PORT(PIN)     (byte*)pgm_read_word(&digital_pin_to_port_map[PIN_TO_INDEX(PIN)])
#define PIN_TO_REGISTER(PIN) (byte*)pgm_read_word(&digital_pin_to_register_map[PIN_TO_INDEX(PIN)])
#define PIN_TO_INPUT(PIN)    (byte*)pgm_read_word(&digital_pin_to_input_map[PIN_TO_INDEX(PIN)])

byte pin_set_mode(pin pin, byte type);
byte pin_set_value(pin pin, byte value);
byte pin_get_value(pin pin);

extern volatile PROGMEM byte *digital_pin_to_port_map[];
extern volatile PROGMEM byte *digital_pin_to_register_map[];
extern volatile PROGMEM byte *digital_pin_to_input_map[];

#endif /* _DIGITAL_H_ */
