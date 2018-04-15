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
}

DWORD GetPixelsDelta(DWORD CurrentFrame,
	DWORD LastFrame,
	DWORD FrameSize)
{
	if (0 == _adder)
	{
		initFrameChecker();
	}
	DmaReset(&_dmaCurrent);
	DmaReset(&_dmaLast);

	_adder[0] = 0x1;
	//adder[8] = 18;



	DmaTransfer(&_dmaCurrent,
		CurrentFrame);

	DmaTransfer(&_dmaLast,
		LastFrame);

	DmaStart(&_dmaLast,
		FrameSize);
	DmaStart(&_dmaCurrent,
		FrameSize);

	return _adder[0xC];
}