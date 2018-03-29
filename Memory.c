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

	virtualAddress = mmap(NULL, 65535, PROT_READ | PROT_WRITE, MAP_SHARED, _memory, PhysAddress); // Memory map AXI Lite register block

	return virtualAddress;
}
