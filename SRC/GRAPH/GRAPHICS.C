#include "GRAPH\@GRAPH.H"

struct{
    uint16_t width;
    uint16_t height;
}g_graphics;

void Graphics_Init(uint16_t _width, uint16_t _height){
    
    memset(&g_graphics,0,sizeof(g_graphics));
    if(ModeX_Init(_width,_height) == true){
        g_graphics.width = _width;
        g_graphics.height = _height;
    }
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

void        Graphics_Begin(){
    ModeX_Begin();
    ModeX_Clear(0);
}

void Graphics_SetPalette(uint8_t far * _palette,uint8_t _start,uint8_t _end){

 uint16_t end = (_end<<1)+(_end<<0); // final*=3;
 uint16_t start = (_start<<1)+(_start<<0); // inici*=3;
 end=(end-start)+3;
 asm{
     lds si,_palette //???//
     add si,[start]
     mov dx,3c8h // Direccio del registre d' escritura de la paleta DAC (Digital Analog Converter) //
     xor al,al // mov al,0 //
     out dx,al // Enviem el valor llegit al la paleta //
     inc dx // Ara dx es 3c9 podem escriure o llegir //
     mov cx,[end] // 256x3 posicions que hem de fer referencia. //
     rep outsb // Escriu en el port DX i incrementa SI+1//
    }
}

void Graphics_PutPixel(int _x, int _y, uint8_t _color){

    /*Mode13

 int despl = (_y<<8)+(_y<<6)+_x; // 320*y+x

 asm{
        mov ax, VIDEO_SEGMENT
        mov es, ax
        mov di, despl
        mov al, _color
        mov es:[di], al
    }*/
}

void Graphics_PutBlock(Point _dst,Rect _src,  const Surface * _surface) {
    ModeX_PutBlock(_dst,_src,_surface);
}

void Graphics_PutSprite(Point _dst,Rect _src,  const Surface * _surface, uint8_t _transparent_color) {
    ModeX_PutSprite(_dst,_src,_surface, _transparent_color);

   /* GraphicsCommand *command = &g_graphics.commands[g_graphics.command_count++];

    command->type = GRAPHICS_COMMAND_SPRITE;
    command->dst_rect = _dst;
    command->src_rect = _src;
    command->transparent_color = _transparent_color;*/
}


void        Graphics_DrawText(int _x, int _y, uint8_t _color, const char *_text, ...){

}

void Graphics_Update(void) {
    ModeX_Update();
}

void        Graphics_End(){
    ModeX_Flush();
}


void Graphics_DeInit(){
    ModeX_DeInit();
    memset(&g_graphics, 0, sizeof(g_graphics));
}
