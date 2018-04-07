#include "Relay.h"
#include "Memory.h"

PDWORD _relayGpioAddress = 0;

void InitGpioRelay()
{
	_relayGpioAddress = MapPhysicalMemory(RELAY_GPIO_ADDRESS);
}

void TurnOnLight()
{
	if (0 == _relayGpioAddress)
	{
		InitGpioRelay();
	}
	_relayGpioAddress[0] = 8;
}

void TurnOffLight()
{
	if (0 == _relayGpioAddress)
	{
		InitGpioRelay();
	}
	_relayGpioAddress[0] = 0;
}