#include <stdbool.h>
#include "types.h"
#include "circular_buffer.h"

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define KbdINSERT     0
#define KbdHOME       0
#define KbdEND        0
#define KbdPAGEUP     25
#define KbdPAGEDOWN   26
#define KbdUPARROW    11
#define KbdLEFTARROW  8
#define KbdDOWNARROW  10
#define KbdRIGHTARROW 21
#define KbdF1         0
#define KbdF2         0
#define KbdF3         0
#define KbdF4         0
#define KbdF5         0
#define KbdF6         0
#define KbdF7         0
#define KbdF8         0
#define KbdF9         0
#define KbdF10        0
#define KbdF11        0
#define KbdF12        0
#define KbdSCROLL     0

#define KbdBreak    _BV(1)
#define KbdExtended _BV(2)
#define KbdL_Shift  _BV(3)
#define KbdL_CTRL   _BV(4)
#define KbdL_Alt    _BV(5)
#define KbdR_Shift  _BV(6)

typedef struct
{
  pin                      clock_pin;
  pin                      data_pin;
  volatile CircularBuffer *byte_buffer;
} Keyboard;

typedef struct
{
  byte key;
  byte modifiers;
} KbdKey;


Keyboard* kbd_init(Keyboard *kbd, byte buffer_size, pin clock_pin, pin data_pin);
void kbd_store_byte(Keyboard *kbd, byte code);
bool kbd_available(Keyboard *kbd);
bool kbd_get_key(Keyboard *kbd, KbdKey *key);

#endif /* _KEYBOARD_H_ */
