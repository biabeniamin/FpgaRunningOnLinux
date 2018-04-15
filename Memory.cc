#include "Memory.h"

int _memory = -1;

int openMemory()
{
	_memory = open("/dev/mem", O_RDWR | O_SYNC); // Open /dev/mem which represents the whole physical memory
}

PDWORD MapPhysicalMemory(DWORD PhysAddress)
{
	PDWORD virtualAddress;
	if (-1 == _memory)
	{
		openMemory();
	}

	virtualAddress = (PDWORD)mmap(NULL, 65535, PROT_READ | PROT_WRITE, MAP_SHARED, _memory, PhysAddress); // Memory map AXI Lite register block

	return virtualAddress;
}

void Dump(PDWORD Address)
{
	for (int i = 0; i < 5; i++)
	{
		printf("[%x]: ", Address + i * 0x10);
		for (int j = 0; j < 4; j++)
		{
			printf("%x\t", *(PDWORD)((DWORD)Address + i * 0x10 + j * 0x4));
		}
		printf("\n");
	}
	printf("\n");
}