
/***************************************************************************
 *                 LLIBRERIA PER EL CONTROL DEL TECLAT                     *
 *                                                                         *
 *      Aquesra llibreria redirecciona la IRQ9 del teclat a una propia per *
 *  a la detecció dels SCAN-CODES, de la seva polsació i deixar anar       *
 *      Per l'emmagatzemament dels SCAN-CODES tindrem un vector de         *
 *  BOOLEANS en el que guardarem TRUE quan la tecla estigui polsada i      *
 *  FALSE quan es deixi anar.                                              *
 ***************************************************************************/

#include <stdio.h>
#include <dos.h>
#include "teclat.h"

#define TECLA_TRUE 0xFF
#define TECLA_TECLA_FALSE 0x00
#define TeclatInt 0x09


#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

char lletras[128];	/*definim el vector de 128 posicions*/


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
sortida:
}


void interrupt Rutina(__CPPARGS)
{unsigned char actual;

  actual=inportb(0x60);	
/*  aux=inportb(0x61);
  aux=(aux | 0x80);
  outportb(0x61,aux);
  aux=(aux & 0x7F);
  outportb(0x61,aux);*/
  if (actual<0x80)
     lletras[actual]=TECLA_TRUE;
  else
     lletras[actual-0x80]=TECLA_FALSE;
  outportb(0x20,0x20);

  //asm pushf;
  IRQ9_PROC();
  RutinaAux();

}

void InstalarTeclat()
{int    i;

  for (i=0;i<128;i++)			/*inicialitzem a fals les tecles polsades*/
      lletras[i]=TECLA_FALSE;
  IRQ9_PROC=getvect(TeclatInt);		/*guardem la direcció de la rutina actual*/
  setvect(TeclatInt,Rutina);		/*posem la direcció de la nova rutina*/
}

void DesinstalarTeclat()
{
  setvect(TeclatInt,IRQ9_PROC);		/*tornem a la rutina original*/
}

/*void main(void)
{int fin;
 char i;
  InstalarTeclat();
  fi=TECLA_FALSE;
  while (!fin)
    for (i=1;i>0;i++)
	if (lletras[i])
           fi=TECLA_TRUE;
  DesinstalarTeclat();
}*/
