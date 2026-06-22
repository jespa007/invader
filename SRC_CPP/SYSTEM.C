#include "ALL_LIB.h"

uint32_t BIOS_GetTicks();

#define PIT_HZ      1193182UL
#define PIT_MS_DIV  1193UL
#define PIT_MS_RND  596UL

tick_t System_GetTicks(){

    uint32_t bios;
    uint16_t pit;

    do
    {
        bios = BIOS_GetTicks();
        pit = PIT_Read();
    }
    while (bios != BIOS_GetTicks());

    return (bios << 16) | (65535u - pit);
}

uint32_t System_TicksToMS(uint32_t _ticks){
    return (_ticks + PIT_MS_RND) / PIT_MS_DIV;
}

