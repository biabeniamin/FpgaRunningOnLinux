#include <stdio.h>
#include <stdlib.h>
#include "DataTypes.h"

#define DMA1_GPIO_ADDRESS 0x40400000
#define DMA2_GPIO_ADDRESS 0x40410000

struct DMA_STRUCT
{
	DWORD DmaAddress;
	PDWORD DmaMappedAddress;
};

typedef struct DMA_STRUCT DMA, *PDMA;

DMA DmaInit(DWORD DmaAddress);

void DmaReset(PDMA Dma);

void DmaTransfer(PDMA Dma,
	DWORD DmaPhysAddress);

void DmaStart(PDMA Dma,
	DWORD DataSize);
