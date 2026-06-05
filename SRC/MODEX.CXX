#include "MoDeX.h"



word OffPagX[3][4] = // MAX_MODES = 3 i MAX_PAGINES = 4
{

 0, 19200, 38400, 57600,              /* MODE 1x4  */
 0, 80, 38400, 38480,                 /* MODE 2x2  */
 0, 80, 160, 240                      /* MODE 4x1  */

};



int Array_Desp[3] =
{
 0,
 1,
 2
};


word mode_actual = 0; // VARIABLE GLOBAL QUE COMPREN EL MODE ACTUAL DEL MODE X!.



void SetMode320_200X()
{
 // Iniciem mode GRAFIC NORMAL ...

 SetMode13();

 WaitVRetrace();

 RegisterOut(SEQU_ADDR,0x04,0x06); //  forcem el bit CHAIN-4 a 0.
 RegisterOut(CRTC_ADDR,0x17,0xe3); // ajust mode paraules.
 RegisterOut(CRTC_ADDR,0x14,0x00); // ajust mode dobles paraules.


/*

 // Configurem el mode NO LINEAL ...

 RegisterOut(GRAC_ADDR,0x05,RegisterIn(GRAC_ADDR,0x05) & 0xEF);
 RegisterOut(GRAC_ADDR,0x06,RegisterIn(GRAC_ADDR,0x06) & 0xFD);
 RegisterOut(SEQU_ADDR,0x04,RegisterIn(SEQU_ADDR,0x04) & 0xF7);

 // ...distancia entre paraules de 16 BITS...

 RegisterOut(CRTC_ADDR,0x14,RegisterIn(CRTC_ADDR,0xBF) & 0xBF);

 // ...distancia entre paraules de 8 BITS.

 RegisterOut(CRTC_ADDR,0x17,RegisterIn(CRTC_ADDR,0x17) | 0x40);

 // Llestos!*/

 ClearScreenX(NEGRE,0x0F);
 mode_actual = 0;

}


void SetMode_320x240X()
{
  SetMode320_200X();                           


  outportb(0x3C2, 0xE3);
  outportw(CRTC_ADDR, 0x2C11);    /* permetre escritura */
  outportw(CRTC_ADDR, 0x0D06);    /* Total vertical */
  outportw(CRTC_ADDR, 0x3E07);    /* Overflow Register */
  outportw(CRTC_ADDR, 0xEA10);    /* Vertical retrace start */
  outportw(CRTC_ADDR, 0xAC11);    /* Vertical ret end y Write prot.*/
  outportw(CRTC_ADDR, 0xDF12);    /* Vertical display enable end */
  outportw(CRTC_ADDR, 0xE715);    /* Start vertical blanking */
  outportw(CRTC_ADDR, 0x0616);    /* End vertical blanking */



}


void ClearScreenX(byte COLOR, char PAGE)
{
 // Seleccionem les p…gines i...

 RegisterOut(SEQU_ADDR,0x02,PAGE);

 // ...borrem!

 asm{

   mov ax,VIDEO
   mov es,ax
   xor di,di
   mov ah,COLOR
   mov al,COLOR
   mov cx,32000
   rep stosw

 }

}

void PutPixelX(word X,word Y,byte COLOR,byte page)
{
 word D;

 // Seleccio del pla i...


 RegisterOut(SEQU_ADDR,0x02, 0x01 << (X & 3));

 D= OffPagX[mode_actual][page] + ((( (Y<<6) + (Y<<4) ) << Array_Desp[mode_actual]) + (X >> 2));
 
 //.. posem el pixel.(Offset = 80*y + x/4)

 asm{

  mov ax,VIDEO
  mov es,ax
  mov di,[D]
  mov al,COLOR
  mov es:[di],al
  stosb
  
 }
}


int CarregarImatgeX(word X,word Y,byte *nom,word AMPLADA,word ALTURA,byte PAGE)
{
 // Carrega imatges mes grans de 320 x 200 a una PAGINA en MODE X...
 word x;
 word y;
 FILE *file;

 if( (file = fopen (nom,"rb")) == NULL)
 {
  return 0;
 }

 for(y=Y;(!feof(file))&&y<Y+ALTURA;y++)
  for(x=X;(!feof(file))&&x<X+AMPLADA;x++)
  {
   PutPixelX(x,y,fgetc(file),PAGE);
  }

 fclose(file);

 return 1;
}





byte GetPixelX(word X,word Y,byte page)
{
 // Seleccio del pla i...

 RegisterOut(SEQU_ADDR,0x02,page);

 //.. agafem el pixel.(Offset = 80*y+x/4)

 asm{
  push es
  mov ax,VIDEO
  mov es,ax
  mov ax,Y
  shl ax,6
  mov bx,Y
  shl bx,4
  add ax,bx
  mov bx,X
  shr bx,2
  add ax,bx
  mov di,ax
  mov al,es:[di]
  pop es
  
 }
 return (_AL);

}



void Flip_VScreenX(byte page,word segment)
{

 word O = OffPagX[mode_actual][page];
 int i,j;



 for(i=0;i<4;i++)
 {
    RegisterOut(SEQU_ADDR,0x02, 0x01 << i);

    asm{
      push dx

      mov ax,VIDEO
      mov es,ax
      mov di,[O]
      mov ax,segment
      mov ds,ax
      mov si,[i]

      mov cx,16000


    }

    buclePla: 
    asm{

     mov al,ds:[si]  // AL = DS:[SI];
     mov es:[di],al  // ES:[DI] = AL;

     add si,4
     inc di

     dec cx       // mentre (cx > 0) fer

     jnz buclePla


     pop dx
    }
   
   
   
 }


}









void SetDimX(byte DIM)
{
 // Ens posar la configuracio de 1x4,2x2 o 4x1.

 if(DIM==DIM1x4) mode_actual=0;
 else if(DIM==DIM2x2)mode_actual = 1;
 else mode_actual=2;
 SetOffsetRegister(DIM);

}


void SetPageX(int page)
{
 // Ens coloca directament a la pagina de 4 que hi han.

 SetStartAddress(OffPagX[mode_actual][page]);
}




