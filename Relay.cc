#include "Relay.h"
#include "Memory.h"

PDWORD _relayGpioAddress = 0;

Relay::Relay(DWORD GpioAddress)
{
	_relayGpioAddress = MapPhysicalMemory(GpioAddress);
}

void Relay::WriteValue(DWORD value)
{
	_relayGpioAddress[0] = value;
}

DWORD Relay::GetValue()
{
	return _relayGpioAddress[0];
}
