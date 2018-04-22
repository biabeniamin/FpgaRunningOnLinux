#include "Notifications.h"


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
	_notificationFile = fopen("/var/www/html/notification", "w");
}

void Notifications::SendNotification(int id)
{
	printf("Test \n");
	//system("wget --output-document=temp -q http://automations.avramiancuturda.ro/actionTriggered.php?actionId=1");
	fseek(_notificationFile, 0, SEEK_SET);
	fprintf(_notificationFile, "%d", id);
	fflush(_notificationFile);
}