#ifndef __TECLAT_H
 #define  __TECLAT_H

#include "definicions.h"

#ifdef __SDL__

#include "SDL/SDL.h"

extern Uint8 *tecla; 

void InicialitzarTeclat();

unsigned TeclaAmunt();
 
unsigned TeclaAvall();

unsigned TeclaEsquerra();

unsigned TeclaDreta(); 

unsigned TeclaEscape();

unsigned  TeclaKeyPad0();

unsigned TeclaPeriode();

unsigned Tecla_p();



unsigned TeclaMes();

unsigned TeclaMenys();




#endif

#endif