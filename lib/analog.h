#include "types.h"

#ifndef _ANALOG_H_
#define _ANALOG_H_

#define ADC_REF_AREF     0
#define ADC_REF_AVCC     _BV(REFS0)
#define ADC_REF_INTERNAL _BV(REFS0) | _BV(REFS1)

void adc_set_prescale_factor(byte factor);
void adc_set_reference(byte ref);
void adc_enable();
void adc_disable();
void adc_start();
void adc_stop();
void adc_enable_interrupt();
void adc_disable_interrupt();
void adc_enable_free_running_mode();
void adc_disable_free_running_mode();
void adc_set_pin(pin pin);
unsigned int adc_read_value(pin pin);
void adc_init();

#endif /* _ANALOG_H_ */
