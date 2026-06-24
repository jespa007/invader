#include "BASE/@BASE.H"


uint32_t BIOS_GetTicks(){
    uint32_t t1, t2;

    // read and make 
    do
    {
        t1 = *((uint32_t far *)MK_FP(0x40,0x6C));
        t2 = *((uint32_t far *)MK_FP(0x40,0x6C));
    }
    while (t1 != t2);

    return t1;
}