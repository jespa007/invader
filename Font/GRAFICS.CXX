#include "grafics.h"

/*
   ษออออออออออออออออออออออออออออออออออออออออออออป
   บ                                            บ
   บ INICIALITZACIONS MODE VIDEO <-> TEXT       บ
   บ                                            บ
   ศออออออออออออออออออออออออออออออออออออออออออออผ
                                                  */



void SetMode13(void) // Mode Video.
{
 asm{
     mov ah,00h  // AH = 0: Inicia el mode de Video 
     mov al,13h  // AL Mode 320 x 200 a 256 colors. 
     int 10h
    }


 // Configurem el mode LINEAL ...

 RegisterOut(GRAC_ADDR,0x05,RegisterIn(GRAC_ADDR,0x05) | 0x10);
 RegisterOut(GRAC_ADDR,0x06,RegisterIn(GRAC_ADDR,0x06) | 0x02);
 RegisterOut(SEQU_ADDR,0x04,RegisterIn(SEQU_ADDR,0x04) | 0x08);

 // ...distancia entre paraules NO de 16 BITS...

 RegisterOut(CRTC_ADDR,0x14,RegisterIn(CRTC_ADDR,0xBF) | 0x40);

 // ...distancia entre paraules de 8 BITS.

 RegisterOut(CRTC_ADDR,0x17,RegisterIn(CRTC_ADDR,0x17) & 0xBF);

 // Llestos!


}


void SetMode3(void) // Mode Text.
{
 asm{
     mov ah,00h  // AH = 0: Inicia el mode de Video 
     mov al,3h  // AL (00,02,03,07 = TEXTE). 
     int 10h
    }
}



/*
   ษออออออออออออออออออออออออออออออออออออออออออออป
   บ                                            บ
   บ UTILITATS GRAFICS A 320 x 200 a 256 colors บ
   บ                                            บ
   ศออออออออออออออออออออออออออออออออออออออออออออผ
                                                  */




void ClearScreen(byte color, word segment)

// - Funcio que neteja la pantalla.

{
 asm{
     push es
     mov es,[segment] // Moc l' adrea  base de la memoria de video (0xA000) o
     xor di,di // Equivalent a moure di=0 pero mes rapid.
     mov ah,[color] // Mou contingut de color a la pos baixa de "ax".
     mov al,[color] // Mou contingut de color a la pos alta de "ax".
     mov cx,32000 // repetim 32000 cops el color entrat .[0][1][2]๚๚๚๚๚[32000].
     rep stosw // el repetir es de tipus word + r…pid (2 pixels per cop ihaaaa!!!
     pop es
    }
}


void PutPixel(word x, word y, byte color, word segment)

// - Funcio que posa un punt a la pantalla. (b…sic).

{
 word despl = (y<<8)+(y<<6)+x; // Realitza un offset de 320*y+x.

 asm{
     mov es,[segment] // A on volem colocar el pixel.
     mov di,[despl]
     mov al,[color]
     mov es:[di],al
    }
}

byte GetPixel(unsigned int x,unsigned int y,unsigned int segment)
{
 unsigned O=(y<<8)+(y<<6)+x;
 asm{
     mov ax,segment
     mov es,ax
     mov di,[O]
     mov al,es:[di]
    }
    return _AL;
}


void PColor(int x,int y,word segment)
{

  rectangle_ple(0,0,72,24,NEGRE,VIDEO);
  OutText(0,0,"Color:\0",0,0,0,FONTMT,VIDEO);
  Visualitzar_Numero(48,0,dword(GetPixel(x,y,segment)),3,0,VIDEO);
  OutText(0,8,"X:\0",0,0,0,FONTMT,VIDEO);
  Visualitzar_Numero(16,8,dword(x),3,0,VIDEO);
  OutText(0,16,"Y:\0",0,0,0,FONTMT,VIDEO);
  Visualitzar_Numero(16,16,dword(y),3,0,VIDEO);

}




void GetBlock(unsigned int X,unsigned int Y,unsigned char *desti,unsigned int gruix,unsigned int alt,unsigned char far *BUFF)
{
 // Carrega un tros de block a un punter buffer declarat.

 unsigned int i,j;


 for(i=Y;i<=Y+alt-1;i++)
 {
  memcpy(desti+(i-Y)*(gruix),BUFF+320*i+X,gruix);
 }

}


void PutBlock(int X,int Y,byte far * BLOC,word AMPLADA,word ALTURA,word MIN_AMPLADA,word MIN_ALTURA,word MAX_AMPLADA,word MAX_ALTURA,word SEGMENT)
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
  lds si,BLOC
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









/*
   ษออออออออออออออออออออออออออออออออป
   บ                                บ
   บ          GEOMETRIA             บ
   บ                                บ
   ศออออออออออออออออออออออออออออออออผ
                                                                         */       



void recta_horitzontal(unsigned int x,unsigned int y,unsigned int gruix,byte color,unsigned int segment)
{

 word desp=(y<<8)+(y<<6)+x;

 asm{
     mov es,[segment]
     mov di,[desp]
     mov cx,[gruix]
     mov al,[color]
     mov es:[di],al
     rep stosb
    }
}


void recta_vertical(unsigned int x,unsigned y,unsigned int alt,byte color,unsigned int segment)
{
 word desp=(y<<8)+(y<<6)+x;
 asm{
     mov es,[segment]
     mov di,[desp]
     mov cx,[alt]
     mov al,[color]
    }
    
 bucleRECTA:;
 asm{
     mov es:[di],al
     add di,320
     dec cx
     jnz bucleRECTA
    }

}


void rectangle_ple(unsigned int x,unsigned y,unsigned int gruix,unsigned int alt,byte color,unsigned int segment)
{

 int i;
 for(i=0;i<gruix;i++) recta_vertical(x+i,y,alt,color,segment);

}

void rectangle(unsigned int x,unsigned int y,unsigned int gruix,unsigned int alt,byte color)
{
 recta_horitzontal(x,y,gruix,color,VIDEO);
 recta_horitzontal(x,y+alt,gruix,color,VIDEO);
 recta_vertical(x,y,alt+1,color,VIDEO);
 recta_vertical(x+gruix,y,alt+1,color,VIDEO);
}






