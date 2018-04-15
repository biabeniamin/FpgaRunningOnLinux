#include "Light.h"
#include "Memory.h"

//PDWORD _relayGpioAddress = 0;
#define RELAY_GPIO_ADDRESS 0x41240000
#define PIN_INDEX 3

Light::Light()
	: Relay(RELAY_GPIO_ADDRESS)
{
	
}

void Light::TurnOn()
{
	WriteValue(GetValue() | (1 << PIN_INDEX));
}

void Light::TurnOff()
{
	WriteValue(GetValue() & (~(1ul << PIN_INDEX)));
}