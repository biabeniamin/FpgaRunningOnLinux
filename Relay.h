#ifndef RELAY_H
#define RELAY_H

#include "DataTypes.h"
#include <stdio.h>
#include <stdlib.h>

class Relay
{

public:

	Relay(DWORD GpioAddress);

	void WriteValue(DWORD value);

	DWORD GetValue();

};

#endif // !RELAY_H