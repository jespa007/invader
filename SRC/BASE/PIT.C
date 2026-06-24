
#include "BASE/@BASE.H"

uint16_t PIT_Read(){
    
    uint16_t value;

    asm{
        mov al,00h
        out 43h,al

        in  al,40h
        mov ah,al

        in  al,40h
        xchg al,ah

        mov value,ax
    }

    return value;
}