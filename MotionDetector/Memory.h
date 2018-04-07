#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "DataTypes.h"

PDWORD MapPhysicalMemory(DWORD PhysAddress);

void Dump(PDWORD Address);
