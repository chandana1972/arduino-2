#include "analog.h"
#include "util.h"
#include "components/analog_sensor.h"

int
analog_sensor_read_value(AnalogSensor *sensor)
{
  unsigned int value = adc_read_value(sensor->pin);

  if(sensor->calibrate) {
    if(value > sensor->max) {
      sensor->max = value;
    } else if(value < sensor->min) {
      sensor->min = value;
    }
  }

  return value;
}

void
analog_sensor_calibrate(AnalogSensor *sensor)
{
  sensor->min       = 1023;
  sensor->max       = 0;
  sensor->calibrate = true;
}

int
analog_sensor_map(AnalogSensor *sensor, unsigned int value, int range_start, int range_end)
{
  return map(value, sensor->min, sensor->max, range_start, range_end);
}
