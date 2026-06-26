#include "SRC\GRAPH\@GRAPH.H"


struct{
    uint16_t width;
    uint16_t height;
}g_graphics;

void Graphics_Init(uint16_t _width, uint16_t _height){
    
    g_graphics.width = _width;
    g_graphics.height = _height;

    Mode13_Init();
}

uint16_t    Graphics_GetWidth(){
    return g_graphics.width;
}

uint16_t    Graphics_GetHeight(){
    return g_graphics.height;
}

void        Graphics_ClearScreen(uint8_t _color){
 asm{
     push es
     mov ax,VIDEO_SEGMENT // Set es VIDEO_SEGMENT
     mov es,ax
     xor di,di // di=0
     mov ah,[_color] // Move _color contents to ah/al.
     mov al,[_color] // 
     mov cx,32000 
     rep stosw // repeat 32000 times _color value x2
     pop es
    }
}

void Graphics_WaitVRetrace(){

    asm mov dx,0x3DA
  et1:
    asm{ 
	in al,dx
	and al,0x08
	jnz et1
       }
  et2:
    asm { 
	 in al,dx
	 and al,0x08
	 jz et2
	}

}

void        Graphics_Begin(){
    Graphics_ClearScreen(0);
}

void        Graphics_End(){
    Graphics_WaitVRetrace();
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

void        Graphics_DrawText(int _x, int _y, uint8_t _color, const char *_text, ...){

}

void Graphics_DeInit(){
    Mode13_DeInit();
}
