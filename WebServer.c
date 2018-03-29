#include "WebServer.h"
#include "Relay.h"

FILE *_file;

void openFile()
{
	_file = fopen("/var/www/html/relayStatus", "r");
}

void CheckWebServer()
{
	if (0 == _file)
	{
		openFile();
	}

	int te;
	fscanf(_file, "%d", &te);
	fseek(_file, 0, SEEK_SET);
	printf("%d \n", te);

	if (1 == te)
	{
		TurnOnLight();
	}

	if (0 == te)
	{
		TurnOffLight();
	}
}