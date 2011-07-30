#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

typedef struct
{
  byte *buffer;
  byte start;
  byte end;
  byte size;
  byte items;
} CircularBuffer;

volatile CircularBuffer* circular_buffer_init(volatile CircularBuffer *buf, byte size);
void circular_buffer_push(volatile CircularBuffer *buf, byte value);
byte circular_buffer_pop(volatile CircularBuffer *buf);
bool circular_buffer_is_empty(volatile CircularBuffer *buf);

#endif /* _CIRCULAR_BUFFER_H_ */
