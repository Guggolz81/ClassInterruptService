/* ClassInterruptService.h
* ---------------------------------------------------------------------------
*
* AUTHOR/LICENSE:
* Created by Daniel Guggolz - daniel.guggolz@mail.de
* Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
*
* DISCLAIMER:
* This software is furnished "as is", without technical support, and with no 
* warranty, express or implied, as to its usefulness for any purpose.
* 
* Project Homepage
* https://github.com/Guggolz81/ClassInterruptService
*
* BACKGROUND:
* When I first want to use the attachInterrupt Functionality of arduino I was not very happy with it.
* I have to attach and detatch a global or static function and could not attach a class function. Also
* The use of it not really sizeable. For example if you want to add 5 ISR of the same Sensor you have to 
* create 5 functions manually. It was not possible to simply use 5 instances of a object and let the ISR handling
* automatically done. This also means a lot of wasting efficiency and scaleability. So I sarched for a solution and found it 
* at http://www.embedded.com/design/prototyping-and-development/4023817/Interrupts-in-C- and 
* http://www.embedded.com/design/prototyping-and-development/4023817/2/Interrupts-in-C-.
* Based on the described methodes I created this class so that I could easily handle the interrupts. For my project I actually did not know
* How much sensors I must use 5...10, but I want realise it by Interrupt and with Object instances. So that I only have to change the number 
* of used Sensors and inizialise them - regarding PIN - correctly and every Sensor Instance uses Interrupts for its measurement
*
* DESCRIPTION
* If more or less ISR shall be used the following has to be changed:
* > MAX_INTERRUPTS
* > create / delete interrupt_x functions
* > update functionpointer array at register functionality
*
* USAGE 
* This class is only the main Servive class for the Class Interrupt Service Routine Handling. To use it is recommended to create an 
* individual Interrupt class witch public inherited this class and finally defines the virtual HandledISR() function. The created Interrupt 
* class must then a friend class to the proper class you create.
* 
* When there is a lesser or higher need of class interrupts than 20 you must do the following steps:
* > change MAX_INTERRUPTS to the required value
* > add or remove the function declarations static void Interrupt_xx(void); with xx represents the number
* > update f_array within the Register function
*
* HISTORY:
* 03/04/2016 v1.0 - Initial release tested with Arduino Due
* ---------------------------------------------------------------------------
*/
#ifndef _ClassInterruptService_h
#define _ClassInterruptService_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ClassInterruptService
{
public:
	ClassInterruptService(void);

	// returns either the used ISR number or -1 if the registration fails
	static int Register(uint32_t pin, ClassInterruptService* intThisPtr, uint32_t isrMode);
	
	// Derigiters the first ISR of the given Pointer
	static void Deregister(ClassInterruptService* intThisPtr);
	
	// Deregisters the specified ISR number if the Pointers match. These function should be used if an Instance use different ISR
	static void Deregister(int noISR, ClassInterruptService* intThisPtr);

	// returns the number of available Interrupts which could be handled
	static int AvailableInterrupts();

	// wrapper functions to HandledISR() -> number of functions must match with the MAX_INTERRUPTS
	static void Interrupt_0(void);
	static void Interrupt_1(void);
	static void Interrupt_2(void);
	static void Interrupt_3(void);
	static void Interrupt_4(void);

	static void Interrupt_5(void);
	static void Interrupt_6(void);
	static void Interrupt_7(void);
	static void Interrupt_8(void);
	static void Interrupt_9(void);

	static void Interrupt_10(void);
	static void Interrupt_11(void);
	static void Interrupt_12(void);
	static void Interrupt_13(void);
	static void Interrupt_14(void);

	static void Interrupt_15(void);
	static void Interrupt_16(void);
	static void Interrupt_17(void);
	static void Interrupt_18(void);
	static void Interrupt_19(void);

	virtual void HandledISR(void) = 0;

private:
	// Defines how much Interrupts could be handled
	static const int MAX_INTERRUPTS = 20;

	static ClassInterruptService* ISRVectorTable[MAX_INTERRUPTS];
	static int ISRPin[MAX_INTERRUPTS];

	static int nextISR, availableISR;
	static bool iniDone;

	static int SearchISR(ClassInterruptService * Ptr);
};
	

#endif

