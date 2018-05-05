#include "Log.h"
#include <time.h>


Log* Log::_instance = 0;

Log* Log::GetInstance()
{
	if (!_instance)
	{
		_instance = new Log();
	}

	return _instance;
}

Log::Log()
{
	_notificationFile = fopen("/var/www/html/Log", "w+");
	fprintf(_notificationFile, "[ ");
}

void Log::WriteLog(const char *Message)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	fseek(_notificationFile, 0, SEEK_END);
	fprintf(_notificationFile, "{\"Date\" : \"%d-%d-%d %d:%d:%d\", \"Message\" : \"%s\"},", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, Message);
	fflush(_notificationFile);
}