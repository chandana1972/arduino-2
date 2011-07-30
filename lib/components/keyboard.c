/* To use this library for reading from a keyboard, a signal handler
 * has to be installed that implements the PS/2 bit protocol.
 *
 * Example:
 */

/* ISR(INT0_vect) */
/* { */
/*   static byte current_bit = 0; */
/*   static byte code = 0; */

/*   byte value; */

/*   value = pin_get_value(kbd.data_pin); */
/*   if(current_bit > 0 && current_bit < 9) { */
/*     code |= value << (current_bit - 1); */
/*   } */

/*   current_bit++; */

/*   if(current_bit == 11) { */
/*     kbd_store_byte(&kbd, code); */

/*     current_bit = 0; */
/*     code        = 0; */
/*   } */
/* } */


#include <avr/pgmspace.h>
#include <stdbool.h>

#include "components/keyboard.h"
#include "types.h"

static PROGMEM unsigned char scan2ascii[] = {
  0, KbdF9, 0, KbdF5, KbdF3, KbdF1, KbdF2, KbdF12,
  0, KbdF10, KbdF8, KbdF6, KbdF4, '\t', '`', 0,
  0, 0 /*Lalt*/, 0 /*Lshift*/, 0, 0 /*Lctrl*/, 'q', '1', 0,
  0, 0, 'z', 's', 'a', 'w', '2', 0,
  0, 'c', 'x', 'd', 'e', '4', '3', 0,
  0, ' ', 'v', 'f', 't', 'r', '5', 0,
  0, 'n', 'b', 'h', 'g', 'y', '6', 0,
  0, 0, 'm', 'j', 'u', '7', '8', 0,
  0, ',', 'k', 'i', 'o', '0', '9', 0,
  0, '.', '/', 'l', ';', 'p', '-', 0,
  0, 0, '\'', 0, '[', '=', 0, 0,
  0 /*CapsLock*/, 0, '\n', ']', 0, '\\', 0, 0,
  0, 0, 0, 0, 0, 0, '\b', 0,
  0, '1', 0, '4', '7', 0, 0, 0,
  '0', '.', '2', '5', '6', '8', '\e', 0 /*NumLock*/,
  KbdF11, '+', '3', '-', '*', '9', KbdSCROLL, 0,
  0, 0, 0, KbdF7 };

Keyboard*
kbd_init(Keyboard *kbd, byte buffer_size, pin clock_pin, pin data_pin)
{
  kbd->clock_pin   = clock_pin;
  kbd->data_pin    = data_pin;
  kbd->byte_buffer = malloc(sizeof(CircularBuffer));

  if(kbd->byte_buffer == NULL) {
    return NULL;
  }

  if(circular_buffer_init(kbd->byte_buffer, buffer_size) == NULL) {
    free(kbd->byte_buffer);
    return NULL;
  }

  return kbd;
}

void
kbd_store_byte(Keyboard *kbd, byte code)
{
  circular_buffer_push(kbd->byte_buffer, code);
}

bool
kbd_available(Keyboard *kbd)
{
  return !circular_buffer_is_empty(kbd->byte_buffer);
}


bool
kbd_get_key(Keyboard *kbd, KbdKey *key)
{
  byte code;
  byte pos       = 0;
  bool done      = false;
  key->key       = 0;
  key->modifiers = 0;

  while(!done) {
    if(circular_buffer_is_empty(kbd->byte_buffer)) {
      // If no bytes are available and we haven't yet read one, no key
      // has been pressed. If no bytes are available but we already
      // read one we're just waiting for the remaining bytes of the
      // keypress.
      if(pos > 0) {
        // FIXME if we don't receive a byte in x milliseconds,
        // something went wrong and we should not lock up
        while(circular_buffer_is_empty(kbd->byte_buffer)) {}
      } else {
        return false;
      }
    }

    code = circular_buffer_pop(kbd->byte_buffer);

    if(pos == 0) {
      switch(code) {
      case 0xF0:
        key->modifiers |= KbdBreak;
        break;
      case 0xE0:
        key->modifiers |= KbdExtended;
        break;
      case 0x12:
        key->modifiers |= KbdL_Shift;
        break;
      case 0x14:
        key->modifiers |= KbdL_CTRL;
        break;
      case 0x11:
        key->modifiers |= KbdL_Alt;
        break;
      case 0x59:
        key->modifiers |= KbdR_Shift;
        break;
      default:
        key->key = pgm_read_byte(&scan2ascii[code]);
        done = true;
        break;
      }
    } else {
      if(key->modifiers & KbdExtended) {
        // TODO deal with extended keys
      } else {
        key->key = pgm_read_byte(&scan2ascii[code]);
        done = true;
      }
    }
    pos++;
  }

  return true;
}
