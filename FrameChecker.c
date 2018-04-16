#include "FrameChecker.h"
#include "Dma.h"

DMA _dmaCurrent;
DMA _dmaLast;
PDWORD _adder = 0;

#define DMA_CURRENT 0x40400000
#define DMA_LAST 0x40410000
#define ADDER 0x43C60000

void initFrameChecker()
{
	_dmaCurrent = DmaInit(DMA_CURRENT);
	_dmaLast = DmaInit(DMA_LAST);
	_adder = MapPhysicalMemory(ADDER);
	printf("%x %x %x \n", _dmaCurrent.DmaMappedAddress, _dmaLast.DmaMappedAddress, _adder);
}

DWORD GetPixelsDelta(DWORD CurrentFrame,
	DWORD LastFrame,
	DWORD FrameSize)
{
	if (0 == _adder)
	{
		initFrameChecker();
	}
//	printf("Resetting\n");

	DmaReset(&_dmaCurrent);
	DmaReset(&_dmaLast);

//	printf("Start adder\n");
	_adder[0] = 0x1;
	//adder[8] = 18;

	//Dump(_adder);
	/*
	
	PDWORD dmaMem = MapPhysicalMemory(CurrentFrame);
	PDWORD dmaMem2 = MapPhysicalMemory(LastFrame);
	Dump(dmaMem);
	Dump(dmaMem2);
	for (int i = 0; i < 1000; i++)
	{
	dmaMem[i] = dmaMem2[i];
	}

	Dump(dmaMem);
	Dump(dmaMem2);*/
	//dmaMem[0] = 0;

//	Dump(_dmaCurrent.DmaMappedAddress);


//	Dump(_dmaLast.DmaMappedAddress);

//	printf("Setting dma\n");

	DmaTransfer(&_dmaCurrent,
		CurrentFrame);

	DmaTransfer(&_dmaLast,
		LastFrame);

	DmaStart(&_dmaLast,
		FrameSize);
	DmaStart(&_dmaCurrent,
		FrameSize);

//	Dump(_dmaCurrent.DmaMappedAddress);
//	Dump(_dmaLast.DmaMappedAddress);
	//printf("Dump adder! \n");
	return _adder[0xC];
	Dump(_adder);
	
	return 0;
}
