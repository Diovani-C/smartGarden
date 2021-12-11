#include <Arduino.h>

/**
 * @brief Define a sensor to store and transfer data
 */
typedef struct _sensor Sensor;

/**
 * @brief Init the sensor
 * 
 * @param id 0 < ID
 * @return Sensor* Return a pointer to a sensor
 */
Sensor *initSensor(const uint32_t id);

float getSensorValue(Sensor *sensor);

/**
 * @brief Verify if there is difference between the previuos value and the new one and update the sensor values
 * 
 * @param sensor sensor object
 * @param newValue new sensor reading value
 * @return true if it was updated
 * @return false if it was not updated
 */
void updateSensorValue(Sensor *sensor, float newValue);

/**
 * @brief Return a csv version of the sensor "ID,Value"
 * 
 * @param sensor sensor object
 * @return String - "ID,Value"
 */
String sensorToCSV(Sensor *sensor);

/**
 * @brief verify which sensor changed the values from previous reading and add to csv line
 * 
 * @param sensors sensors array
 * @param size size of the sensors array
 * @return String "ID,Value" or empty "" if no sensor changed
 */
String updatedSensorsToCSV(Sensor *sensors[], uint16_t size);
