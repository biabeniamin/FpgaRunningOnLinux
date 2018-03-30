#include <stdio.h>
#include "Keyboard.h"
#include "DataTypes.h"
#include "WebServer.h"
#include "Temperature.h"
#include "Dma.h"
#include "Memory.h"

#define GRANTED_PIN 0x123A

int main()
{
	InitKeyboard();

	PDWORD adder = MapPhysicalMemory(0x43C60000);

	adder[0] = 0x1;
	adder[8] = 18;

	Dump(adder);


	DMA dma = DmaInit(0x40400000);
	DMA dma2 = DmaInit(0x40410000);
	Dump(dma.DmaMappedAddress);
	printf("Resetting\n");
	DmaReset(&dma);
	DmaReset(&dma2);
	Dump(dma.DmaMappedAddress);
	DmaTransfer(&dma,
		0x2e100000);

	DmaTransfer(&dma2,
		0x2e200000);

	DmaStart(&dma,
		0x100);
	DmaStart(&dma2,
		0x100);

	Dump(dma.DmaMappedAddress);
	Dump(dma2.DmaMappedAddress);
	Dump(adder);

	return 0;

	while (1)
	{
		CheckKeyboardNewKeyPressed();
		CheckWebServer();
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

