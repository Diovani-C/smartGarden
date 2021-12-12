#include "utilities.hpp"

void blinkActionLed(uint8_t actionLed)
{
  if (digitalRead(actionLed) == LOW)
  {
    digitalWrite(actionLed, HIGH);
    delay(500);
    // End with LED OFF
    digitalWrite(actionLed, LOW);
    delay(500);
  }
}

float ADCRead(uint8_t ADC_Pin)
{
  uint8_t samples = 10;
  float average = 0.0;

  for (uint8_t i = 0; i < samples; i++)
  {
    average += analogRead(ADC_Pin);
  }

  return (average /= (float)samples);
}
