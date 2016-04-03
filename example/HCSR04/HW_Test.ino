/*
Name:		HW_Test.ino
Created:	2/4/2016 12:10:52 PM
Author:		Daniel Guggolz
*/

#include "HCSR04.h"

// The classinstances could bedefined individually (like shown) or with array.
HCSR04 test1(35, 34);
HCSR04 test2(37, 36);
HCSR04 test3(39, 38);


void setup() {
	Serial.begin(9600);

	// Inizialise the ultrasonic sensor means Pin Mode, and Register Interrupt automatically
	// This depends on the HCSR04Interrupt class which handles the Interrupt service Routine and generates the bridge between the 
	// sensor class HCSR04 and the ClassInterruptService Library. 
	
	// The advantage of using the library is, that you could concentrate on functional use of the sensor and easily add / remove Sensors to your project
	// without seperate ISR handling to add or remove
	test1.Init();
	test2.Init();
	test3.Init();
}


void loop() {

	// Start the measurement of the three sensors, note the Sensors must show in different directions or must have some space in between
	test1.StartMeasurement();
	test2.StartMeasurement();
	test3.StartMeasurement();

	delay(1000);

	// Somewhere in the delay time the Interrupts were created and we have to get the results of the measurements. So the main loop 
	// could also do some stuff in replacement to the delay functionality
	Serial.print("Distance: "); Serial.println(test1.CalcDistance());
	Serial.print("Distance: "); Serial.println(test2.CalcDistance());
	Serial.print("Distance: "); Serial.println(test3.CalcDistance());

	delay(1000);

	while (true) { Serial.println("Ende"); delay(1000); }
}
