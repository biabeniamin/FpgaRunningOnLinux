#include "WebServer.h"
#include "Relay.h"

FILE * _relayFile;
FILE * _temperatureFile;

void openFile()
{
	_relayFile = fopen("/var/www/html/relayStatus", "r");
	_temperatureFile = fopen("/var/www/html/temperature", "w");
}

void CheckWebServer()
{
	if (0 == _relayFile)
	{
		openFile();
	}

	int te;
	fscanf(_relayFile, "%d", &te);
	fseek(_relayFile, 0, SEEK_SET);
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

void WriteTemperatureToWebServer(double Temperature)
{
	if (0 == _temperatureFile)
	{
		openFile();
	}

	fseek(_temperatureFile, 0, SEEK_SET);
	fprintf(_temperatureFile, "%f", Temperature);
}