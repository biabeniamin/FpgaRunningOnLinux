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

	if (0 == _temperatureXadcAddress)
	{
		initTemperatureXadc();
	}
	
	dwVoltage = _temperatureXadcAddress[1];

	return dwVoltage;

}

