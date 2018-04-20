#ifndef RELAY_H
#define RELAY_H

#include "DataTypes.h"
#include <stdio.h>
#include <stdlib.h>

#define RELAY_GPIO_ADDRESS 0x41240000

class Relay
{

public:

	Relay(DWORD GpioAddress, BYTE PinIndex);

	void WriteValue(DWORD value);

	DWORD GetValue();
private:
	BYTE _pinIndex;
	PDWORD _relayGpioAddress;

};

#endif // !RELAY_H