#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>

#include "util.h"
#include "analog.h"
#include "pwm.h"
#include "io.h"
#include "types.h"
#include "digital.h"
#include "serial.h"

#include "components/rgb_led.h"
#include "components/shift_register.h"
#include "components/button.h"
#include "components/analog_sensor.h"

int main()
{
  init();
  set_pin_mode(11, OUTPUT);
  set_pin_value(11, LOW);

  int value;
  while(1){
    value = adc_read_value(0);
    itoa(value, buf, 10);
    value = map(value, 0, 1023, 544, 2400);
    itoa(value, buf, 10);
    set_pin_value(11, HIGH);
    _delay_us(value);
    set_pin_value(11, LOW);
    delay_ms(20);


    /* for(int i = 0; i < 40; i++) { */
    /*   set_pin_value(11, HIGH); */
    /*   int high = i * 100; */
    /*   _delay_us(high); */
    /*   set_pin_value(11, LOW); */
    /*   _delay_ms(high * 1000 - 15); */
    /*   delay_ms(50); */
    /* } */
  }


  // use timer of pin 9/10 for interrupts
  /* {&OCR1A, &, &}, */
  /* TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM */
  /* TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM) */

  //*timer->capture = 4999;
  // ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).

  // set_pwm(11, 1);

  /* int i = 0; */
  /* int direction = 0; */
  /* while(1) { */
  /*   direction == 0 ? i++ : i--; */

  /*   set_pwm(11, 256-i); */
  /*   delay_ms(500); */


  /*   if(direction == 0 && i >= 128) { */
  /*     direction = 1; */
  /*   } else if(direction == 1 && i <= 0) { */
  /*     direction = 0; */
  /*   } */
  /* } */

  return 0;
}
