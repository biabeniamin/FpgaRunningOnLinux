#include "Notifications.h"
#include <stdlib.h>
#include <stdio.h>

Notifications* Notifications::_instance = 0;

Notifications* Notifications::GetInstance()
{
	if (!_instance)
	{
		_instance = new Notifications();
	}

	return _instance;
}

Notifications::Notifications()
{
}

void Notifications::SendNotification(int id)
{
	printf("Test \n");
	system("wget --output-document=temp -q http://automations.avramiancuturda.ro/actionTriggered.php?actionId=1");
}