#include "Light.h"
#include "Memory.h"
#include "Log.h"
#include <stdio.h>

//PDWORD _relayGpioAddress = 0;
#define RELAY_GPIO_ADDRESS 0x41240000
#define PIN_INDEX 3

Light::Light()
	: Relay(RELAY_GPIO_ADDRESS, 2)
{
	
}

void Light::TurnOn()
{
	//Log::GetInstance()->WriteLog("The light was turned on");
	WriteValue(0);
}

void Light::TurnOff()
{
	//Log::GetInstance()->WriteLog("The light was turned off");
	WriteValue(1);
}
void Light::Switch()
{
	WriteValue(GetValue() ^ 1);
}