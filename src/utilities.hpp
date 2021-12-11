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

/**
 * @brief Blink lights to notify error
 * 
 * @param errorCode FileSystem: 3; Webserver: 5; Other: 7; 
 * @param actionLed Action Led pin
 * @param onLed On Led pin
 */
void throwError(uint8_t errorCode, uint8_t actionLed, uint8_t onLed);