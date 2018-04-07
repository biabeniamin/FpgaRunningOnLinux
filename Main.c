#include <stdio.h>
#include "Keyboard.h"
#include "DataTypes.h"
#include "WebServer.h"
#include "Temperature.h"
#include "FrameChecker.h"
#include "Memory.h"

#define GRANTED_PIN 0x123A




int main()
{

	InitKeyboard();

	/*GetPixelsDelta(0x2e100000, 
		0x2e200000,
		100);*/

	while (1)
	{
		CheckKeyboardNewKeyPressed();
		CheckWebServer();
		WriteTemperatureToWebServer(GetTemperature());
		printf("Temperature is %f \n", GetTemperature());

		if (GRANTED_PIN == (GetKeyboardPin() & 0xFFFF))
		{
			printf("Can enter \n");
			return 0;
		}
		else
		{
			printf("%x \n", GetKeyboardPin());
		}
		usleep(500 * 1000);
	}

	for (int i = 0; i < 10; i++)
	{
		

		printf("%x \n", GetKeyboardPin());

		
	}

	return 0;
}

