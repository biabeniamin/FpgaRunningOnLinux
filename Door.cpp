#include "Door.h"
#include "Log.h"
#include <unistd.h>

Door* Door::_instance = 0;

Door* Door::GetInstance()
{
	if (!_instance)
	{
		_instance = new Door();
	}

	return _instance;
}

Door::Door()
	: Relay(RELAY_GPIO_ADDRESS, 3)
{
}

void Door::Unlock()
{
	WriteValue(0);
	Log::GetInstance()->WriteLog("The door was unlocked");
	usleep(1000 * 1000);
	WriteValue(1);
	usleep(1000 * 1000);
	Log::GetInstance()->WriteLog("The door was locked");
}

void Door::Lock()
{
	WriteValue(0);
}