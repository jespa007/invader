/*  SMIXC is Copyright 1995 by Ethan Brodsky.  All rights reserved      */
/*  MIXER.C  Traducci¢n Espa¤ol: Oswaldo Varela C.  */

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <dos.h>
#include <alloc.h>
#include <mem.h>

#define DECIMAL 	0
#define HEX     	1
#define TRUE  	1
#define FALSE 	0
#define ON  	1
#define OFF 	0

#include "sb\detect.cpp"
#include "sb\xms.cpp"
#include "sb\smix.cpp"
#include "sb\volumen.cpp"

#define SHAREDEMB    /* Undefine this to store all sounds in separate EMBs */


int baseio, irq, dma, dma16;

SOUND *sonidos[NUMSOUNDS];
/************************************************************************/
void ourexitproc(void)
{
	int i;
	for (i=0; i < NUMSOUNDS; ++i)
		if (sonidos[i] != NULL)
			free_sound(sonidos+i);
	#ifdef SHAREDEMB
		shutdown_sharing();
	#endif
}
/************************************************************************/
void loadsounds(char *nombre){
	int i;
	if (!init_xms()){
		printf("ERROR:  No se puede inicializar la memoria extendida\n");
		printf("HIMEM.SYS debe estar instalado\n");
		exit(EXIT_FAILURE);
	}
	if (getfreexms() < XMSREQUIRED){
		printf("ERROR:  Memoria expandida insuficiente\n");
		exit(EXIT_FAILURE);
	}
//        printf("Cargando Sonidos...\n");
	#ifdef SHAREDEMB
		init_sharing();
	#endif
	if (!open_sound_resource_file(nombre)){
		printf("ERROR:  No se puede cargar el archivo especificado.\n");
		exit(EXIT_FAILURE);
	}
	for (i=0; i < NUMSOUNDS; i++)
		load_sound(&(sonidos[i]), sonidos_key[i]);
	close_sound_resource_file();
        atexit(ourexitproc); 
}
/************************************************************************/
void freesounds(void){
	int i;
	for (i=0; i < NUMSOUNDS; i++)
		free_sound(sonidos+i);
	#ifdef SHAREDEMB
		shutdown_sharing();
	#endif
}
/************************************************************************/
void init_mix(void){
	clrscr();
	printf("----------------------------------------------\n");
	printf("Sound Mixing Library v1.30 por:  Ethan Brodsky\n");
	printf("Modificaciones y traducci¢n: Oswaldo Varela C.\n");
	if (!detect_settings(&baseio, &irq, &dma, &dma16)){
		printf("ERROR:  Variable BLASTER inv lida o no existente!\n");
		printf("por ejemplo: SET BLASTER A220 I5 D1\n");
		exit(EXIT_FAILURE);
	}
	else{
		if (!init_sb(baseio, irq, dma, dma16)){
			printf("ERROR:  al inicializar la tarjeta de sonido!\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("BaseIO=%Xh     IRQ%u     DMA8=%u     DMA16=%u\n", baseio, irq, dma, dma16);
	printf("DSP version %.1u.%.2u:  ", dspversion>>8, dspversion&0xFF);
	if (sixteenbit)
		printf("16-bit, ");
	else
		printf("8-bit, ");
	if (autoinit)
		printf("Auto-inicializado\n");
	else
		printf("Ciclo-Simple\n");
	init_mixing();
	textcolor(14);
	cprintf("Sound Blaster OK...\n");
	delay(1000);textcolor(7);
}
/************************************************************************/
void shutdown(void){
	shutdown_mixing();
	shutdown_sb();
}
/*************************************************************************/

