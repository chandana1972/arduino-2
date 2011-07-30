#include "util.h"
#include "components/rgb_led.h"

int
main()
{
  RGBLED led       = {9,5,6,3};
  byte   i         = 0;
  bool   direction = 0;

  while(1) {
    direction == 0 ? i++ : i--;

    rgb_led_set_color(led, i % 64, i, i % 128);

    if(direction == 0 && i >= 255) {
      direction = 1;
    } else if(direction == 1 && i <= 0) {
      direction = 0;
    }

    delay_ms(10);
  }
}
