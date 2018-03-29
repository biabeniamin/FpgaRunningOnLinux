#include <stdio.h>
#include "Keyboard.h"
#include "DataTypes.h"
#include "WebServer.h"

#define GRANTED_PIN 0x123A

int main()
{
	InitKeyboard();

	while (1)
	{
		CheckKeyboardNewKeyPressed();
		CheckWebServer();

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

