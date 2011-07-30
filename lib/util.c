#include <inttypes.h>
#include <util/delay.h>
#include "util.h"

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void
delay_ms(uint16_t ms)
{
  // TODO optimize this to use the maximum allowed for _delay_ms
  while ( ms )
  {
    _delay_ms(1);
    ms--;
  }
}
