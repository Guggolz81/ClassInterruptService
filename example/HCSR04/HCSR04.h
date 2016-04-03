// HCSR04.h

#ifndef _HCSR04_h
#define _HCSR04_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "./ClassInterruptService.h"

class HCSR04;

class HCSR04Interrupt : public ClassInterruptService
{
public:
	explicit HCSR04Interrupt(HCSR04* ownerptr, uint32_t pin);
	~HCSR04Interrupt();

	virtual void HandledISR(void);

private:
	HCSR04* InterruptOwnerPtr;
	uint32_t _pin;
};

class HCSR04
{
	friend class HCSR04Interrupt;

 protected:

 public:
	explicit HCSR04(uint32_t triggerPin, uint32_t echoPin);
	~HCSR04();

	void PinChange(uint32_t microSecounds);

	void Init();
	// returns the distance in mm
	float CalcDistance();
	void StartMeasurement();
	void ForceMeasurement();

	void UpdateTemperatur(float temp);
	
 private:
	 const float Temperatur_Default = 20.0; // 20°C
	 const unsigned char MaxMeasureTimeMs = 20; // 20ms
	 const float MinDistance = 20.0; // 2cm ^= 20mm;
	 const float MaxDistance = 3000.0; // 3m ^= 3000mm
	 const uint32_t DelayBetween2Measurements = 60; // 60ms
	 const uint32_t TriggerPulsHighTime = 15; // µs

	 HCSR04Interrupt *IsrChangePtr = nullptr;

	 uint32_t _triggerPin, _echoPin;

	 volatile  uint32_t time_falling, time_rising;
	 uint32_t time_startMeasurement, time_EarliestNextMeasuement;
	 float temperatur, lastDistance;
};


#endif

