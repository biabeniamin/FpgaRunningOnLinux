#include "Temperature.h"
#include "Memory.h"

PDWORD _temperatureXadcAddress = 0;

void initTemperatureXadc()
{
	_temperatureXadcAddress = MapPhysicalMemory(TEMPERATURE_XADC_ADDRESS);
}

double GetTemperature()
{
	DWORD dwVoltage;
	double temperature;

	temperature = 0;

	if (0 == _temperatureXadcAddress)
	{
		initTemperatureXadc();
	}
	
	dwVoltage = _temperatureXadcAddress[1];

	temperature = (dwVoltage * 0.7) / 21856;

	//reduce gain
	temperature *= 100 / 3.4;
	temperature *=  0.7;

	return temperature;

}

