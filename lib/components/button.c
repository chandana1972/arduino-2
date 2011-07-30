#include <avr/io.h>
#include <stdlib.h>

#include "types.h"
#include "io.h"
#include "digital.h"

#include "components/button.h"

void
button_init(Button *button)
{
  button->pin             = 0;
  button->closed_on       = LOW;
  button->debounce_delay  = 10;
  button->hold_delay      = 250;
  button->time_open       = 0;
  button->time_closed     = 0;
  button->state           = BUTTON_OPENED;
  button->close_callback  = NULL;
  button->open_callback   = NULL;
  button->hold_callback   = NULL;
  button->unhold_callback = NULL;
  button->toggle_callback = NULL;
}

void
button_check(Button *button)
{
  byte value;

  pin_set_mode(button->pin, INPUT);
  value = pin_get_value(button->pin);

  if(value == button->closed_on) {
    button->time_closed++;

    if(button->time_closed > button->debounce_delay && button->state == BUTTON_OPENED) {
      button->time_open = 0;
      button->state = BUTTON_CLOSED;

      if(button->close_callback) {
        button->close_callback(button, button->data);
      }
    }

    if(button->time_closed >= button->hold_delay && button->hold_callback) {
      button->hold_callback(button, button->data);
    }
  } else {
    button->time_open++;

    if(button->time_open > button->debounce_delay && button->state == BUTTON_CLOSED) {
      button->state = BUTTON_OPENED;

      if(button->time_closed < button->hold_delay && button->toggle_callback){
        button->toggle_callback(button, button->data);
      } else if(button->time_closed >= button->hold_delay && button->unhold_callback) {
        button->unhold_callback(button, button->data);
      }

      button->time_closed = 0;

      if(button->open_callback) {
        button->open_callback(button, button->data);
      }
    }
  }
}
