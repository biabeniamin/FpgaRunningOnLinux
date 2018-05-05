#pragma once
#include <stdlib.h>
#include <stdio.h>
class Log
{
private:
	Log();
	static Log *_instance;
	FILE *_notificationFile;
public:
	static Log* GetInstance();
	

	void WriteLog(const char*);

};


