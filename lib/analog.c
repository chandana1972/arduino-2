#include <avr/io.h>
#include "io.h"
#include "types.h"
#include "analog.h"

void
adc_set_prescale_factor(byte factor)
{
  ADCSRA |= factor;
}

void
adc_set_reference(byte ref)
{
  ADMUX &= ~(_BV(REFS1) | _BV(REFS0));
  ADMUX |= ref;
}

void
adc_enable()
{
  ADCSRA |= _BV(ADEN);
}

void
adc_disable()
{
  ADCSRA &= ~(_BV(ADEN));
}

void
adc_start()
{
  ADCSRA |= _BV(ADSC);
}

void
adc_stop()
{
  ADCSRA &= ~(_BV(ADSC));
}

void
adc_enable_interrupt()
{
  ADCSRA |= (1 << ADIE);
}

void
adc_disable_interrupt()
{
  ADCSRA &= ~(1 << ADIE);
}

void
adc_enable_free_running_mode()
{
  ADCSRA |= _BV(ADATE);
}

void
adc_disable_free_running_mode()
{
  ADCSRA &= ~(_BV(ADATE));
}

void
adc_set_pin(pin pin)
{
  ADMUX &= (0b11 << 6);
  ADMUX |= pin;
}

// This reads a single value from the ADC. This function will not work
// if free-running mode has been enabled.
unsigned int
adc_read_value(pin pin)
{
  adc_enable();
  adc_set_pin(pin);
  adc_start();
  loop_until_bit_is_clear(ADCSRA, ADSC);

  return (ADCL << 8) | ADCH;
}

void adc_init()
{
  adc_set_prescale_factor(128);
  adc_set_reference(ADC_REF_AVCC);
}
