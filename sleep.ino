#include "Sleeper.h"

#define ADC_InCH0   0
#define ADC_InCH7   7
#define ADC_InTemp  8
#define ADC_InVBG  14
#define ADC_InGND  15


Sleeper g_sleeper;
/* usage
  // Power down for 10 seconds.
  g_sleeper.SleepMillis(10000);
*/

volatile unsigned int i;

// Initialisation code
void setup(void) {
  Serial.begin(9600);
  Serial.println("Setup done.");

  Serial.print("Total milliseconds awake: ");
  Serial.println(millis());
  Serial.print("i: "); Serial.println(i);
  delay(1000);

  ADCSRA &= ~_BV(ADEN);   // disable ADC for max. power saving
}

// Main loop
void loop(void)
{
  unsigned long ulVCC;

  ulVCC = ulMeasureVCC();
  
  // Power down for 10 seconds.
  g_sleeper.SleepMillis(10000);

  while (1)
  {
    Serial.print("Total milliseconds awake: ");
    Serial.println(millis());
    Serial.print("i: "); Serial.println(i);
    delay(1000);
  }
}

unsigned long ulMeasureVCC(void)
{
  uint16_t adc_low, adc_high;
  uint32_t adc_result;

  ADMUX |= _BV(REFS0);  // Aui32VCC with external capacitor at AREF pin
  ADMUX |= ADC_InVBG;   // Input Channel Selection: 1.1V (VBG)
  delay(10);
  ADCSRA |= _BV(ADEN);    // enable ADC

  ADCSRA |= _BV(ADSC);  //Messung starten

  while (bitRead(ADCSRA, ADSC));  //warten bis Messung beendet ist
  //Ergebnisse des ADC zwischenspeichern. Wichtig: zuerst ADCL auslesen, dann ADCH
  adc_low = ADCL;
  adc_high = ADCH;

  ADCSRA &= ~_BV(ADEN);   // disable ADC
  adc_result = (adc_high << 8) | adc_low; //Gesamtergebniss der ADC-Messung

  // voltage reference rises with falling temperature
  return (1125300L / adc_result);  //Versorgungsspannung in mV berechnen (1100mV * 1023 = 1125300)
}
