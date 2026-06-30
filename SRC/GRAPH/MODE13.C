#include "GRAPH\@GRAPH.H"

void Mode13_Init(){
    
    asm{
         mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,13h  // AL Mode 320 x 200 a 256 colors. 
        int 10h
    }
}

void Mode13_PutBlock(
    int _x,int _y
    ,uint8_t far * _block
    ,uint16_t _block_width
    ,uint16_t _block_height
    ,uint16_t MIN_AMPLADA
    ,uint16_t MIN_ALTURA
    ,uint16_t MAX_AMPLADA
    ,uint16_t MAX_ALTURA
    ,uint16_t SEGMENT
){



 asm{

  mov ax,[_y]
  mov bx,[_block_height]
  add ax,bx
  cmp ax,[MIN_ALTURA]
  jge si1
  jmp NoPutSprite

 }

si1:

 asm{

  mov ax,[_x]
  mov bx,[_block_width]
  add ax,bx
  cmp ax,[MIN_AMPLADA]
  jge si2
  jmp NoPutSprite
 
 }

si2:

 asm{

  push ds
  mov es,[SEGMENT]
  lds si,_block
  mov ax,[_y]
  mov bx,[_y]
  shl ax,8
  shl bx,6
  add ax,bx
  add ax,[_x]
  mov di,ax

  mov bx,0

 }

NovaLinea: asm mov cx,0;
NouPixel:

 asm{

  mov ax,[_y]
  add ax,bx
  cmp ax,[MIN_ALTURA]
  jge cond1
  jmp NoPutPixel

 }

cond1:

 asm{

  mov ax,[_y]
  add ax,bx
  cmp ax,[MAX_ALTURA]
  jle cond2
  jmp NoPutPixel

 }

cond2:

 asm{

  mov ax,[_x]
  add ax,cx
  cmp ax,[MIN_AMPLADA]
  jge cond3
  jmp NoPutPixel

 }

cond3:

 asm{

  mov ax,[_x]
  add ax,cx
  cmp ax,[MAX_AMPLADA]
  jg  NoPutPixel

 }

PutPixel:

 asm{

  mov al,ds:[si]
  mov es:[di],al       // Posem el Pixel!!!

 }
 
 
NoPutPixel:

 asm{

  inc si
  inc di
  inc cx
  cmp cx,[_block_width]
  jne NouPixel
  add di,320
  sub di,[_block_width]
  inc bx
  cmp bx,[_block_height]
  jne NovaLinea

  pop ds

 }
  
NoPutSprite: 



}


void Mode13_DeInit(){
    
     asm{
        mov ah,00h  // AH = 0: Inicia el mode de Video 
        mov al,3h  // AL (00,02,03,07 = TEXTE). 
        int 10h
    }
}