#include "Dma.h"
#include "Memory.h"

DMA DmaInit(DWORD DmaAddress)
{
	DMA dma;

	dma.DmaAddress = DmaAddress;
	dma.DmaMappedAddress = MapPhysicalMemory(DmaAddress);

	return dma;
}

void DmaReset(PDMA Dma)
{
	if (0 == Dma)
	{
		return;
	}

	if (0 == Dma->DmaMappedAddress)
	{
		return;
	}

	Dma->DmaMappedAddress[0] = 4;
	Dma->DmaMappedAddress[0] = 0;
}

void DmaTransfer(PDMA Dma,
	DWORD DmaDataPhysAddress)
{
	if (0 == Dma)
	{
		return;
	}

	if (0 == Dma->DmaMappedAddress)
	{
		return;
	}

	//writing address to 0x18 offset
	Dma->DmaMappedAddress[6] = DmaDataPhysAddress;
}

void DmaStart(PDMA Dma,
	DWORD DataSize)
{
	//start dma
	Dma->DmaMappedAddress[0] = 0x10003;

	//writing buffer length
	Dma->DmaMappedAddress[10] = DataSize;
}