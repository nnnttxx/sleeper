#include "Sleeper.h"

Sleeper g_sleeper;

// Initialisation code
void setup(void) {
	Serial.begin(9600);
	Serial.println("Setup done.");
}

// Main loop
void loop(void) {
	Serial.print("Total milliseconds awake: ");
    Serial.println(millis());
    delay(100);

	// Power down for 10 seconds.
	g_sleeper.SleepMillis(10000);
}
