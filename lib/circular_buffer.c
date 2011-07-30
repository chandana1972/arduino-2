#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "types.h"
#include "circular_buffer.h"

volatile CircularBuffer*
circular_buffer_init(volatile CircularBuffer *buf, byte size)
{
  buf->buffer = malloc(size);
  if(buf->buffer == NULL) {
    return NULL;
  }

  buf->size  = size;
  buf->start = 0;
  buf->end   = 0;

  return buf;
}

void
circular_buffer_push(volatile CircularBuffer *buf, byte value)
{
  byte oldSREG = SREG;
  cli();

  buf->items++;
  if(buf->items > buf->size) {
    buf->items = buf->size;
  }

  buf->buffer[buf->end++] = value;
  if(buf->end == buf->size) {
    buf->end = 0;
  }
  SREG = oldSREG;
}

byte
circular_buffer_pop(volatile CircularBuffer *buf)
{
  byte val;
  byte oldSREG = SREG;
  cli();

  buf->items--;
  val = buf->buffer[buf->start++];
  if(buf->start == buf->size) {
    buf->start = 0;
  }

  SREG = oldSREG;
  return val;
}

bool
circular_buffer_is_empty(volatile CircularBuffer *buf)
{
  return buf->items == 0;
}
