#include "Relay.h"
#include "Memory.h"

#define UPPER_PART(POSITON) (((1ull << (31 - (POSITON))) - 1) << ((POSITON) + 1 ))
#define LOWER_PART(POSITON) ((1ull << POSITON) - 1)
#define GET_BIT(NUMBER, POSITION) (((NUMBER) >> ((DWORD)POSITION)) & 0x1)

#define REPLACE_X_BIT(NUMBER, POSITION, BIT) (((NUMBER) & UPPER_PART(POSITION)) | ((BIT) << (POSITION)) | ((NUMBER) & LOWER_PART(POSITION)))



Relay::Relay(DWORD GpioAddress, BYTE PinIndex)
{
	_relayGpioAddress = MapPhysicalMemory(GpioAddress);
	_pinIndex = PinIndex;
}

void Relay::WriteValue(DWORD value)
{
	//printf("%x %x %x %x \n", value, _pinIndex, _relayGpioAddress[0], REPLACE_X_BIT(_relayGpioAddress[0], _pinIndex, GET_BIT(value, 0)));
	_relayGpioAddress[0] = REPLACE_X_BIT(_relayGpioAddress[0], _pinIndex, GET_BIT(value, 0));
}

DWORD Relay::GetValue()
{
	return GET_BIT(_relayGpioAddress[0], _pinIndex);
}
