
/***************************************************************************
 *                 LIBRERIA PARA EL CONTROL DEL TECLADO                    *
 *                                                                         *
 *      Esta libreria redirecciona la IRQ9 del teclado a una propia para   *
 *  la detecci¢n de los SCAN-CODES, de su pulsacion y de su dejada         *
 *      Para el almacenamiento de estos SCAN-CODES tendremos un vector de  *
 *  BOOLEAN en el que almacenaremos TRUE cuando la tecla sea pulsada y     *
 *  FALSE cuando se suelte.                                                *
 ***************************************************************************/

#include <stdio.h>
#include <dos.h>
#include "teclado.h"

#define TECLA_TRUE 0xFF
#define TECLA_TECLA_FALSE 0x00
#define TecladoInt 0x09


#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

char letras[128];


void interrupt (*IRQ9_PROC)(__CPPARGS);

void RutinaAux(void)
{
bucle:
asm      {
	 mov    ah,0x01
	 int    0x16
	 jz     salida
	 mov    ah,0
	 int    0x16
	 jmp    bucle}
salida:
}

void interrupt Rutina(__CPPARGS)
{unsigned char actual;

  actual=inportb(0x60);

/////////////////////////////
/*
  aux=inportb(0x61);
  aux=(aux | 0x80);
  outportb(0x61,aux);
  aux=(aux & 0x7F);
  outportb(0x61,aux);*/
////////////////////////////////
  if (actual<0x80)
     letras[actual]=TECLA_TRUE;
  else
     letras[actual-0x80]=TECLA_FALSE;
  outportb(0x20,0x20);

  //asm pushf;
  IRQ9_PROC();
  RutinaAux();

}

void InstalarTeclado()
{int    i;

  for (i=0;i<128;i++)
      letras[i]=TECLA_FALSE;
  IRQ9_PROC=getvect(TecladoInt);
  setvect(TecladoInt,Rutina);
}

void DesinstalarTeclado()
{
  setvect(TecladoInt,IRQ9_PROC);
}

/*void main(void)
{int fin;
 char i;
  InstalarTeclado();
  fin=TECLA_FALSE;
  while (!fin)
    for (i=1;i>0;i++)
	if (letras[i])
           fin=TECLA_TRUE;
  DesinstalarTeclado();
}*/
