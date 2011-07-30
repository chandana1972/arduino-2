#include <inttypes.h>
#include "components/rgb_led.h"
#include "io.h"
#include "types.h"
#include "digital.h"
#include "pwm.h"

void
rgb_led_set_color(RGBLED led, byte red, byte green, byte blue)
{
  pin_set_mode(led.pin_blue_1, OUTPUT);
  pin_set_mode(led.pin_blue_2, OUTPUT);
  pin_set_mode(led.pin_red,    OUTPUT);
  pin_set_mode(led.pin_green,  OUTPUT);

  pwm_set_value(led.pin_blue_1, blue);
  pwm_set_value(led.pin_blue_2, blue);
  pwm_set_value(led.pin_red,    red);
  pwm_set_value(led.pin_green,  green);
}
