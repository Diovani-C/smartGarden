#include <Arduino.h>
#include "esp_adc_cal.h"

/**
 * @brief Read adc pin and average the result
 *
 * @param ADC_Pin
 * @return float
 */
float ADCRead(uint8_t ADC_Pin);

/**
 * @brief One second blink
 *
 * @param actionLed Action Led pin
 */
void blinkActionLed(uint8_t actionLed);
