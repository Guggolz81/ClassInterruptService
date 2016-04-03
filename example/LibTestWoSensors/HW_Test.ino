/*
Name:		HW_Test.ino
Created:	2/4/2016 12:10:52 PM
Author:		Daniel Guggolz
*/

#include "ClassInterruptService.h"

// this example combines the bride class (from the other example with the ultrasonic sensor) and the sensor class
// For this example I have made a shortcut from PIN 33 to PIN 45, PIN 35 to 47 and PIN 37 to PIN 49.
// With this setup it is possible to force the Interrupt at the PINs given to the testISR class instances by 
// change of State of PINs 33, 35 and 37 by SW
class testISR :ClassInterruptService
{
public:
	testISR(uint32_t _pin) { done = false; pin = _pin; };
	void Init() { pinMode(pin, INPUT); Register(pin, this, CHANGE); };
	volatile bool done;

	virtual void HandledISR(void) { done = true; };
	int NoInterrupts() { return NoFreeInterrupts(); };
	uint32_t pin;
};


// Test instances could also defined as an array
testISR test1(45);
testISR test2(47);
testISR test3(49);



void setup() {
	Serial.begin(9600);

	// Inizialise PINMode and Interrupt
	test1.Init();
	test2.Init();
	test3.Init();
	
	// Inizialise the connected Test Pins to force the Interrupt
	pinMode(35, OUTPUT);
	pinMode(37, OUTPUT);
	pinMode(33, OUTPUT);

	digitalWrite(35, LOW);
	digitalWrite(37, LOW);
	digitalWrite(33, LOW);
	
}

// The delays are only used to reduce the speed at the serial monitor
void loop() {

	delay(1000);

	// force the first Interrpt
	digitalWrite(33, HIGH);

	delay(1000);

	// evaluation if the Interrupt fired and catched
	if (test1.done)
		Serial.println("1 OK");
	else
		Serial.println("1 NOK");

	delay(1000);

	// force the second Interrpt
	digitalWrite(35, HIGH);

	delay(1000);

	// evaluation if the Interrupt fired and catched
	if (test2.done)
		Serial.println("2 OK");
	else
		Serial.println("2 NOK");

	delay(1000);

	// force the third Interrpt
	digitalWrite(37, HIGH);

	delay(1000);

	// evaluation if the Interrupt fired and catched
	if (test3.done)
		Serial.println("3 OK");
	else
		Serial.println("3 NOK");


	while (true) { Serial.println("Ende"); delay(1000); }
}
