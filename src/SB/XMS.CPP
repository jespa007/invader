/*  SMIXC is Copyright 1995 by Ethan Brodsky.  All rights reserved      */
/*  XMS.C  Oswaldo Varela C.  */
#include <mem.h>

typedef struct{
	unsigned long length;         /* longitud debe ser multiplo de 2 */
	unsigned int  sourcehandle;
	unsigned long sourceoffset;
	unsigned int  desthandle;
	unsigned long destoffset;
} MOVEPARAMS;

  int xms_instalado();
  void xms_inicia();
  unsigned int xms_leeversion();
  unsigned int xms_leememlibre();
  int xms_reserva(int far *handle, unsigned int size);
  int xms_cambiareserva(int handle, unsigned int newsize);
  int xms_libera(int far *handle);
  int xms_mover(MOVEPARAMS far *params);

#pragma option -w- // Desactiva warnings
/* Desactiva stack overflow checking. */
#pragma option -N-

/*************************************************************************/
static void far *xms_driver = NULL;  /* Puntero al driver XMS */
/*************************************************************************/
int xms_instalado(){
	asm mov  ax, 0x4300
	asm int  0x2F
	if (_AL == 0x80) return 1;
	else return 0;
}
/*************************************************************************/
void xms_inicia(){
	 asm mov  ax, 0x4310
	 asm int  0x2F
	 asm mov  word ptr [xms_driver], bx
	 asm mov  word ptr [xms_driver+2], es
}
/*************************************************************************/
unsigned int xms_leeversion(){
	 asm mov  ah, 0x00
	 asm call [xms_driver]
}
/*************************************************************************/
unsigned int xms_leememlibre(){
	 asm mov  ah, 0x08
	 asm call [xms_driver]
	 asm mov  ax, dx
}
/*************************************************************************/
int xms_reserva(int far *handle, unsigned int size){
	 asm	mov  ah, 0x09
	 asm	mov  dx, size
	 asm	call [xms_driver]
	 asm	les  di, [handle]
	 asm	mov  es:[di], dx
}
/*************************************************************************/
int xms_cambiareserva(int handle, unsigned int newsize){
	 asm mov  ah, 0x0F
	 asm mov  bx, newsize
	 asm mov  dx, handle
	 asm call [xms_driver]
}
/*************************************************************************/
int xms_libera(int far *handle){
	 asm mov  ah, 0x0A
	 asm les  di, [handle]
	 asm mov  dx, es:[di]
	 asm call [xms_driver]
	 asm mov  word ptr es:[di], 0
}
/*************************************************************************/
int xms_mover(MOVEPARAMS far *params){
	 asm push ds
	 asm push es
	 asm mov  ax, ds
	 asm mov  es, ax
	 asm mov  ah, 0x0B
	 asm lds  si, [params]
	 asm call es:[xms_driver]        // necesario para trabajar en Huge model
	 asm pop  es
	 asm pop  ds
}
#pragma option -w  // Re-activa warnings
