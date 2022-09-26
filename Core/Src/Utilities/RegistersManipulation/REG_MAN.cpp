#include "REG_MAN.h"

uint8_t getIndex(uint32_t n)
{
    uint8_t index;
    for(index = 0; index < 32; index++)
    {
        if(((1 << index) & n))break;

    }
    return index;
}