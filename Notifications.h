#pragma once
#include <stdlib.h>
#include <stdio.h>
class Notifications
{
private:
	Notifications();
	static Notifications *_instance;
	FILE *_notificationFile;
public:
	static Notifications* GetInstance();
	

	void SendNotification(int id);

};


