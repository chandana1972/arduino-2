#include "io.h"
#include "types.h"

#ifndef _BUTTON_H_
#define _BUTTON_H_

#define BUTTON_CLOSED 1
#define BUTTON_OPENED 0

typedef struct
{
  pin   pin;
  byte  closed_on;
  int   debounce_delay;
  int   hold_delay;
  int   time_open;
  int   time_closed;
  byte  state;
  void (*close_callback)();
  void (*open_callback)();
  void (*hold_callback)();
  void (*unhold_callback)();
  void (*toggle_callback)();
  void *data;
} Button;

void button_init(Button *button);
void button_check(Button *button);

#endif /* _BUTTON_H_ */
