#include "WebServer.h"
#include "Light.h"
#include "Door.h"

FILE * _lightFile;
FILE * _doorFile;
FILE * _temperatureFile;

Light _light;
Door *_pdoor = Door::GetInstance();

void openFile()
{
	_lightFile = fopen("/var/www/html/lightStatus", "w+");
	_doorFile = fopen("/var/www/html/doorStatus", "w+");
	_temperatureFile = fopen("/var/www/html/temperature", "w");
}

void CheckWebServer()
{
	DWORD lightCommand;
	DWORD doorCommand;

	lightCommand = 0;
	doorCommand = 0;

	if (0 == _lightFile)
	{
		openFile();
	}

	fseek(_lightFile, 0, SEEK_SET);
	fscanf(_lightFile, "%d", &lightCommand);

	fseek(_doorFile, 0, SEEK_SET);
	fscanf(_doorFile, "%d", &doorCommand);

	switch (lightCommand)
	{
	case 0:
		_light.TurnOff();
		break;
	case 1:
		_light.TurnOn();
		break;
	case 2:
		_light.Switch();
		fseek(_lightFile, 0, SEEK_SET);
		fprintf(_lightFile, "3");
		fflush(_lightFile);
		break;
	default:
		break;
	}

	if (1 == doorCommand)
	{
		_pdoor->Unlock();
		fseek(_doorFile, 0, SEEK_SET);
		fprintf(_doorFile, "0");
		fflush(_doorFile);
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