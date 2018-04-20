#include "Door.h"
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
	: Relay(RELAY_GPIO_ADDRESS, 2)
{
}

void Door::Unlock()
{
	WriteValue(1);
	usleep(1000 * 1000);
	WriteValue(0);
	usleep(1000 * 1000);
}

void Door::Lock()
{

}