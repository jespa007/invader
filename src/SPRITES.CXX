#include "invader.h"



void PutSprite(int X,int Y,byte far * SPRITE,word AMPLADA,word ALTURA,word MIN_AMPLADA,word MIN_ALTURA,word MAX_AMPLADA,word MAX_ALTURA,char ColorMascara,word SEGMENT)
{


 asm{

  mov ax,[Y]
  mov bx,[ALTURA]
  add ax,bx
  cmp ax,[MIN_ALTURA]
  jge si1
  jmp NoPutSprite

 }

si1:

 asm{

  mov ax,[X]
  mov bx,[AMPLADA]
  add ax,bx
  cmp ax,[MIN_AMPLADA]
  jge si2
  jmp NoPutSprite
 
 }

si2:

 asm{

  push ds
  mov es,[SEGMENT]
  lds si,SPRITE
  mov ax,[Y]
  mov bx,[Y]
  shl ax,8
  shl bx,6
  add ax,bx
  add ax,[X]
  mov di,ax

  mov bx,0

 }

NovaLinea: asm mov cx,0;
NouPixel:

 asm{

  mov ax,[Y]
  add ax,bx
  cmp ax,[MIN_ALTURA]
  jge cond1
  jmp NoPutPixel

 }

cond1:

 asm{

  mov ax,[Y]
  add ax,bx
  cmp ax,[MAX_ALTURA]
  jle cond2
  jmp NoPutPixel

 }

cond2:

 asm{

  mov ax,[X]
  add ax,cx
  cmp ax,[MIN_AMPLADA]
  jge cond3
  jmp NoPutPixel

 }

cond3:

 asm{

  mov ax,[X]
  add ax,cx
  cmp ax,[MAX_AMPLADA]
  jle cond4
  jmp NoPutPixel

 }
  
cond4:


 asm{

  mov al,ds:[si]
  cmp al,[ColorMascara]
  je  NoPutPixel

  mov es:[di],al       // Posem el Pixel!!!

 }
 
 
 NoPutPixel:

 asm{

  inc si
  inc di
  inc cx
  cmp cx,[AMPLADA]
  jne NouPixel
  add di,320
  sub di,[AMPLADA]
  inc bx
  cmp bx,[ALTURA]
  jne NovaLinea

  pop ds

 }
  
NoPutSprite: 


}
