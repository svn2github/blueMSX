#ifndef ROMMAPPER_MATRAINK_H
#define ROMMAPPER_MATRAINK_H
 
#include "MsxTypes.h"

int romMapperMatraINKCreate(char* filename, UInt8* romData, 
                             int size, int slot, int sslot, int startPage);

#endif
