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
#include "components/button.h"

struct counter_data
{
  ShiftRegister reg;
  int num;
};


void
toggled(Button *button, struct counter_data *data)
{
  data->num++;
  if(data->num >= 8) {
    data->num = 0;
  }

  shift_register_set(&data->reg, (byte)(_BV(data->num)));
}

void
hold(Button *button, struct counter_data *data)
{
  if(button->time_closed % 250 == 0) {
    toggled(button, data);
  }
}

int
main()
{
  Button button;

  struct counter_data data = {
    (ShiftRegister){12, 10, 11},
    0
  };

  shift_register_init(&data.reg);
  shift_register_set(&data.reg, 1);
  button_init(&button);

  button.pin = 7;
  button.closed_on = LOW;
  button.debounce_delay = 10;
  button.hold_delay = 250;
  button.toggle_callback = &toggled;
  button.hold_callback = &hold;
  button.data = &data;

  pin_set_mode(7, INPUT);
  pin_set_value(7, PULLUP); // enable the internal pull-up resistor

  while(true) {
    button_check(&button);
    delay_ms(1); // TODO do not depend on delaying
  }

  return 0;
}

