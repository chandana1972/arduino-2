#include <inttypes.h>
#include "types.h"


#ifndef _RGB_LED_H_
#define _RGB_LED_H_

typedef struct
{
  pin pin_blue_1;
  pin pin_blue_2;
  pin pin_red;
  pin pin_green;
} RGBLED;

void rgb_led_set_color(RGBLED led, byte red, byte green, byte blue);

#endif /* _RGB_LED_H_ */
