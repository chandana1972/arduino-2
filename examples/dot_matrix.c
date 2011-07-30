#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "avr.h"
#include "util.h"
#include "io.h"
#include "types.h"
#include "digital.h"
#include "serial.h"

#define ROW_PIN 2
#define COL_PIN 9

void
timer_enable()
{
  TIMSK2 |= _BV(OCIE2A);
}

void
timer_disable()
{
  TIMSK2 &= ~_BV(OCIE2A);
}

void
timer_set_period(unsigned long period)
{
  uint8_t pre, top;

  if (period == 0) {
    period = 1;
  }

  period *= CYCLES_PER_MS;

  period /= 2;            // we work with half-cycles before the toggle
  if (period <= 256) { // 2^8
	pre = 1;
	top = period - 1;
  } else if (period <= 256L * 8) { // 2^11
	pre = 2;
	top = period / 8-1;
  } else if (period <= 256L * 32) { // 2^13
	pre = 3;
	top = period / 32-1;
  } else if (period <= 256L * 64) { // 2^14
	pre = 4;
	top = period / 64-1;
  } else if (period <= 256L * 128) { // 2^15
	pre = 5;
	top = period / 128-1;
  } else if (period <= 256L * 256) { // 2^16
	pre = 6;
	top = period / 256-1;
  } else if (period <= 256L * 1024) {// 2^18
	pre = 7;
	top = period / 1024-1;
  } else {
	pre = 7;
	top = 255;
  }

  TCCR2B = 0;
  TCCR2A = 0;
  TCNT2 = 0;
  ASSR &= ~_BV(AS2);    // use clock, not T2 pin
  OCR2A = top;
  TCCR2A = _BV(WGM21);
  TCCR2B = pre;
}



typedef struct
{
  pin    first_row_pin;
  pin    first_col_pin;
  byte   rows;
  byte   cols;
  bool **status;
  byte   current_col;
} DotMatrix;

bool
dot_matrix_init(DotMatrix *matrix)
{
  byte i, j;
  bool *columns;

  matrix->status = malloc(sizeof(bool *) * matrix->rows);
  if(matrix->status == NULL) {
    return false;
  }

  columns = malloc(sizeof(bool) * matrix->rows * matrix->cols);
  if(columns == NULL) {
    free(matrix->status);
    return false;
  }

  for(i = 0; i < matrix->rows; i++) {
    matrix->status[i] = &columns[i * matrix->cols];
    for(j = 0; j < matrix->cols; j++) {
      matrix->status[i][j] = 0;
    }
  }

  for(i = 0; i < matrix->rows; i++) {
    pin_set_mode(matrix->first_row_pin + i, OUTPUT);
    pin_set_value(matrix->first_row_pin + i, LOW);
  }

  for(i = 0; i < matrix->cols; i++) {
    pin_set_mode(matrix->first_col_pin + i, OUTPUT);
    pin_set_value(matrix->first_col_pin + i, HIGH);
  }

  return true;
}

void
dot_matrix_set(DotMatrix *matrix, byte row, byte column, byte value)
{
  matrix->status[row][column] = value;
}

void
dot_matrix_display(DotMatrix *matrix)
{
  /* This function expects to be called every time a new column should
   * be displayed, possibly from a loop or timer interrupt.
   */

  /* Column has to sink current, so setting the pin to LOW will enable
   * the column.
   *
   * Row has to provide current, so setting the pin to HIGH will
   * enable the row.
   */

  pin_set_value(matrix->first_col_pin + matrix->current_col, HIGH);
  matrix->current_col++;
  if(matrix->current_col >= matrix->cols) {
    matrix->current_col = 0;
  }

  for(byte row = 0; row < matrix->rows; row++) {
    pin_set_value(matrix->first_row_pin + row, matrix->status[row][matrix->current_col]);
  }
  pin_set_value(matrix->first_col_pin + matrix->current_col, LOW);
}

DotMatrix matrix = {2, 9, 7, 5};

void
main()
{
  byte letters[3][7] = {
    {
      0b00000,
      0b00001,
      0b00100,
      0b10100,
      0b00100,
      0b00001,
      0b00000
    },
    {
      0b00000,
      0b11111,
      0b00100,
      0b00100,
      0b00100,
      0b11111,
      0b00000
    },
    {
      0b00000,
      0b00000,
      0b00001,
      0b00001,
      0b11111,
      0b00000,
      0b00000,
    }
  };

  // FIXME check if dot_matrix_init failed
  dot_matrix_init(&matrix);

  timer_set_period(9000);
  timer_enable();
  sei();


  /* pin_set_mode(KB_CLOCK_PIN, INPUT); */
  /* pin_set_mode(KB_DATA_PIN, INPUT); */


  /* serial_init(); */

  /* byte dat; */
  /* char buf[10]; */
  /* while(1) { */
  /*   dat = pin_get_value(KB_CLOCK_PIN); */
  /*   sprintf(buf, "%x\r\n", dat); */
  /*   serial_write(buf); */
  /* } */
}


ISR(TIMER2_COMPA_vect)
{
  dot_matrix_display(&matrix);
}


/* int0/int1 : portd [2/3] (pins D0 to D7)
 */
