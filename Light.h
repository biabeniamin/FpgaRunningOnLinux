#ifndef LIGHT_H
#define LIGHT_H

#include "Relay.h"
#include "DataTypes.h"
#include <stdio.h>
#include <stdlib.h>

class Light: public Relay
{

public:

	Light();

	void TurnOn();

	void TurnOff();

	void Switch();

};

#endif // !LIGHT_H