#include "sensor.hpp"

struct _sensor
{
  uint32_t ID;
  float value;
  bool updated;
};

Sensor *initSensor(const uint32_t id)
{
  Sensor *p = new Sensor;
  p->ID = id;
  p->updated = false;
  p->value = 0.0;
  return p;
}

float getSensorValue(Sensor *sensor)
{
  return sensor->value;
}

void updateSensorValue(Sensor *sensor, float newValue)
{
  sensor->updated = false;

  if ((int)sensor->value != (int)newValue)
  {
    sensor->value = newValue;
    sensor->updated = true;
  }
}

String sensorToCSV(Sensor *sensor)
{
  String csv;
  csv += String(sensor->ID);
  csv += ",";
  csv += String(sensor->value);
  return csv;
}

String updatedSensorsToCSV(Sensor *sensors[], uint16_t size)
{
  String csv;

  uint16_t updatedCounter = 0;
  for (uint16_t i = 0; i < size; i++)
  {
    if (sensors[i]->updated)
    {
      updatedCounter++;
    }
  }

  if (updatedCounter == 0)
    return csv;

  for (uint16_t i = 0; i < size; i++)
  {
    if (sensors[i]->updated)
    {
      csv += sensorToCSV(sensors[i]);
      if (updatedCounter > 1)
      {
        csv += ",";
        updatedCounter--;
      }
    }
  }
  return csv;
}
