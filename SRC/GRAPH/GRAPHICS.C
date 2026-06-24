#include "GRAPH\@GRAPH.H"

#define VIDEO_SEGMENT 0xA000
#define VIDEO_OFFSET  0x0000
#define VGA_MEMORY ((unsigned char far *)MK_FP(VIDEO_SEGMENT, VIDEO_OFFSET))

void Graphics_Init(){
    asm{
         mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,13h  // AL Mode 320 x 200 a 256 colors. 
        int 10h
    }
}


void Graphics_PutPixel(int _x, int _y, uint8_t _color){

 int despl = (_y<<8)+(_y<<6)+_x; // 320*y+x

 asm{
        mov ax, VIDEO_SEGMENT
        mov es, ax
        mov di, despl
        mov al, _color
        mov es:[di], al
    }
}

void Graphics_DeInit(){
     asm{
        mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,3h  // AL (00,02,03,07 = TEXTE). 
        int 10h
    }
}
