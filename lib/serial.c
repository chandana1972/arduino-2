#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include "serial.h"

void
serial_init()
{
  /* Set the baud rate */
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
  /* set the framing to 8N1 */
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
  /* Engage! */
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
}

void
serial_write(char *s)
{
  while(*s) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = *s++;
  }
}

void
serial_write_int(int num)
{
  char buf[5];
  itoa(num, buf, 10);

  serial_write(buf);
}
