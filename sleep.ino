#include "Sleeper.h"

Sleeper g_sleeper;

volatile unsigned int i;

// Initialisation code
void setup(void) {
  Serial.begin(9600);
  Serial.println("Setup done.");

  Serial.print("Total milliseconds awake: ");
  Serial.println(millis());
  Serial.print("i: "); Serial.println(i);
  delay(1000);
}

// Main loop
void loop(void)
{
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
