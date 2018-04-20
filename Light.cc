#include "Light.h"
#include "Memory.h"
#include <stdio.h>

//PDWORD _relayGpioAddress = 0;
#define RELAY_GPIO_ADDRESS 0x41240000
#define PIN_INDEX 3

Light::Light()
	: Relay(RELAY_GPIO_ADDRESS, 3)
{
	
}

void Light::TurnOn()
{
	WriteValue(1);
}

void Light::TurnOff()
{
	WriteValue(0);
}
void Light::Switch()
{
	WriteValue(GetValue() ^ 1);
}