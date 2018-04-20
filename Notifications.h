#pragma once
class Notifications
{
private:
	Notifications();
	static Notifications *_instance;
public:
	static Notifications* GetInstance();
	

	void SendNotification(int id);

};


