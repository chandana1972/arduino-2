#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

#ifndef _ANALOG_SENSOR_H_
#define _ANALOG_SENSOR_H_

typedef struct _analog_sensor
{
  pin          pin;
  unsigned int min;
  unsigned int max;
  bool         calibrate;
} AnalogSensor;

int analog_sensor_read_value(AnalogSensor *sensor);
void analog_sensor_calibrate(AnalogSensor *sensor);
int analog_sensor_map(AnalogSensor *sensor, unsigned int value, int range_start, int range_end);


#endif /* _ANALOG_SENSOR_H_ */
