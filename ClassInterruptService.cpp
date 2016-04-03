// ---------------------------------------------------------------------------
// Created by Daniel Guggolz
// Copyright 2015 License: GNU GPL v3 http://www.gnu.org/licenses/gpl.html
//
// See "ClassInterruptService.h" for purpose, syntax, version history, links, and more.
// --------------------------------------------------------------------------

#include "./ClassInterruptService.h"

/* *************************************************************************************
Create static Variables
************************************************************************************* */
int ClassInterruptService::nextISR = 0;
bool ClassInterruptService::iniDone = false;
int ClassInterruptService::availableISR = 0;

int ClassInterruptService::ISRPin[ClassInterruptService::MAX_INTERRUPTS];
ClassInterruptService* ClassInterruptService::ISRVectorTable[ClassInterruptService::MAX_INTERRUPTS];

/* *************************************************************************************
Constructor
************************************************************************************* */
ClassInterruptService::ClassInterruptService()
{
	if (!iniDone)
	{
		nextISR = 0;
		availableISR = MAX_INTERRUPTS;
		iniDone = true;

		for (int i = 0; i < MAX_INTERRUPTS; i++)
		{
			ISRVectorTable[i] = nullptr;
			ISRPin[i] = -1;
		}
	}
}

/* *************************************************************************************
public Functions
************************************************************************************* */
int ClassInterruptService::Register(uint32_t pin, ClassInterruptService * intThisPtr, uint32_t isrMode)
{
	int usedISR = nextISR;

	void(*f_array[])(void) = { Interrupt_0, Interrupt_1, Interrupt_2, Interrupt_3, Interrupt_4, Interrupt_5, Interrupt_6, Interrupt_7, Interrupt_8,
		Interrupt_9, Interrupt_10, Interrupt_11, Interrupt_12, Interrupt_13, Interrupt_14, Interrupt_15, Interrupt_16, Interrupt_17, Interrupt_18,
		Interrupt_19 };

	if (nextISR >= 0)
	{
		// free ISR available 
		if (isrMode == LOW || isrMode == CHANGE || isrMode == RISING || isrMode == FALLING 
#if defined(ARDUINO_AVR_YUN) || defined(ARDUINO_SAM_DUE) || defined(ARDUINO_AVR_MRK1000)
			|| isrMode == HIGH
#endif
			)
		{
			// correct Mode is given
			ISRVectorTable[nextISR] = intThisPtr;
			ISRPin[nextISR] = pin;
			attachInterrupt(digitalPinToInterrupt(pin), f_array[nextISR], isrMode);

			// update internals after the registration
			nextISR = SearchISR(nullptr);
			availableISR--;
			return usedISR;
		}
	}

	// ISR could not be registered
	return -1;	
}

void ClassInterruptService::Deregister(ClassInterruptService * intThisPtr)
{
	// execute deregistering
	Deregister(SearchISR(intThisPtr), intThisPtr);
}

void ClassInterruptService::Deregister(int noISR, ClassInterruptService * intThisPtr)
{
	if (noISR >= 0 && noISR < MAX_INTERRUPTS)
	{
		detachInterrupt(digitalPinToInterrupt(ISRPin[noISR]));
		ISRVectorTable[noISR] = nullptr;

		// update internals after deregistration
		nextISR = SearchISR(nullptr);
		availableISR++;
	}	
}

int ClassInterruptService::AvailableInterrupts()
{
	return availableISR;
}

void ClassInterruptService::Interrupt_0(void)
{
	ISRVectorTable[0]->HandledISR();
}

void ClassInterruptService::Interrupt_1(void)
{
	ISRVectorTable[1]->HandledISR();
}

void ClassInterruptService::Interrupt_2(void)
{
	ISRVectorTable[2]->HandledISR();
}

void ClassInterruptService::Interrupt_3(void)
{
	ISRVectorTable[3]->HandledISR();
}

void ClassInterruptService::Interrupt_4(void)
{
	ISRVectorTable[4]->HandledISR();
}

void ClassInterruptService::Interrupt_5(void)
{
	ISRVectorTable[5]->HandledISR();
}

void ClassInterruptService::Interrupt_6(void)
{
	ISRVectorTable[6]->HandledISR();
}

void ClassInterruptService::Interrupt_7(void)
{
	ISRVectorTable[7]->HandledISR();
}

void ClassInterruptService::Interrupt_8(void)
{
	ISRVectorTable[8]->HandledISR();
}

void ClassInterruptService::Interrupt_9(void)
{
	ISRVectorTable[9]->HandledISR();
}

void ClassInterruptService::Interrupt_10(void)
{
	ISRVectorTable[10]->HandledISR();
}

void ClassInterruptService::Interrupt_11(void)
{
	ISRVectorTable[11]->HandledISR();
}

void ClassInterruptService::Interrupt_12(void)
{
	ISRVectorTable[12]->HandledISR();
}

void ClassInterruptService::Interrupt_13(void)
{
	ISRVectorTable[13]->HandledISR();
}

void ClassInterruptService::Interrupt_14(void)
{
	ISRVectorTable[14]->HandledISR();
}

void ClassInterruptService::Interrupt_15(void)
{
	ISRVectorTable[15]->HandledISR();
}

void ClassInterruptService::Interrupt_16(void)
{
	ISRVectorTable[16]->HandledISR();
}

void ClassInterruptService::Interrupt_17(void)
{
	ISRVectorTable[17]->HandledISR();
}

void ClassInterruptService::Interrupt_18(void)
{
	ISRVectorTable[18]->HandledISR();
}

void ClassInterruptService::Interrupt_19(void)
{
	ISRVectorTable[19]->HandledISR();
}

/* *************************************************************************************
private Functions
************************************************************************************* */
int ClassInterruptService::SearchISR(ClassInterruptService * Ptr)
{
	bool goon = true;
	int i = 0;
	int res = -1;

	while (i< MAX_INTERRUPTS && goon)
	{
		if (ISRVectorTable[i] == Ptr)
		{
			res = i;
			goon = false;
		}
		i++;
	}

	return res;
}


