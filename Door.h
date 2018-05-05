#pragma once
#include "Relay.h"
class Door :
	public Relay
{
private:
	Door();
	static Door *_instance;

public:
	static Door* GetInstance();
	

	void Unlock();

	void Lock();

};


