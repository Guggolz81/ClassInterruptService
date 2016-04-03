// 
// 
// 

#include "./HCSR04.h"

/* *************************************************************************************
Constructor
************************************************************************************* */
HCSR04::HCSR04(uint32_t triggerPin, uint32_t echoPin)
{
	_triggerPin = triggerPin;
	_echoPin = echoPin;

	time_rising = 0;
	time_falling = 0;
	time_startMeasurement = 0;

	temperatur = Temperatur_Default;
	lastDistance = -1.0;
	time_EarliestNextMeasuement = 0;
}

HCSR04::~HCSR04()
{
	if (IsrChangePtr != nullptr)
		delete IsrChangePtr;
}


/* *************************************************************************************
public Functions
************************************************************************************* */
void HCSR04::PinChange(uint32_t microSecounds)
{
	if (time_rising == 0)
		time_rising = microSecounds;
	else
		time_falling = microSecounds;
}

void HCSR04::Init()
{
	pinMode(_triggerPin, OUTPUT);
	pinMode(_echoPin, INPUT);	

	IsrChangePtr = new HCSR04Interrupt(this, _echoPin);
}

float HCSR04::CalcDistance()
{
	if (time_falling == 0 && time_rising == 0 && time_startMeasurement == 0)
	{
		// no measurement started return last value
		return lastDistance;
	}

	if ( (time_falling == 0 && time_rising == 0 && time_startMeasurement != 0) ||
		(time_falling == 0 && time_rising != 0 && time_startMeasurement != 0) )
	{
		// measurement started but no answer yet. There are 2 different cases:
		// a) There is no objet within the measure distance -> Measure finished
		// b) There is an object within the measure distance -> Measure isn't complete yet

		// check wich case we have
		unsigned char measuretime = (unsigned char)(millis() - time_startMeasurement);

		if (measuretime >= MaxMeasureTimeMs)
		{
			// we have case a), so finish the measurement
			time_falling = 0;
			time_rising = 0;
			time_startMeasurement = 0;
			lastDistance = MaxDistance;
			return lastDistance;
		}

		// measuement isn't finished yet -> return 0
		return 0.0;
	}

	if (time_falling != 0 && time_rising != 0 && time_startMeasurement != 0)
	{
		// measurement finished => calc distance

		// distance = High-time * c0 / 2
		// c0 without temperaturcompensation: 340
		// C0 with temperturcompensation: 331,5 + 0,6 * Temp[°C]

		float c0 = 331.5 + 0.6 * temperatur;

		uint32_t time_difference;

		if (time_falling < time_rising)
		{
			// micros have got an roll-over between the two edges
			time_difference = 0xffffffff - time_rising;
			time_difference += time_falling;
		}
		else
			time_difference = time_falling - time_rising;

		lastDistance = (float)time_difference * c0 / 2000;

		if (lastDistance > MaxDistance)
			lastDistance = MaxDistance;
		else
			if (lastDistance <= MinDistance)
				lastDistance = 0;
				
		
		time_falling = 0;
		time_rising = 0;
		time_startMeasurement = 0;

		return lastDistance;
	}

	// if coming here somthing went wrong -> stop measurement
	time_falling = 0;
	time_rising = 0;
	time_startMeasurement = 0;
	return lastDistance;
}

void HCSR04::StartMeasurement()
{
	if (time_EarliestNextMeasuement < millis())
	{
		// there is a recommended min time between 2 Measurements, so start a new Measurement only if this time is over
		ForceMeasurement();
	}	
}

void HCSR04::ForceMeasurement()
{
	time_rising = 0;
	time_falling = 0;
	
	time_startMeasurement = millis();
	time_EarliestNextMeasuement = time_startMeasurement + DelayBetween2Measurements;

	digitalWrite(_triggerPin, HIGH);
	delayMicroseconds(TriggerPulsHighTime);
	digitalWrite(_triggerPin, LOW);
}

void HCSR04::UpdateTemperatur(float temp)
{
	temperatur = temp;
}

/* *************************************************************************************
protected Functions
************************************************************************************* */


/* *************************************************************************************
private Functions
************************************************************************************* */




