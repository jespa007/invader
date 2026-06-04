#ifndef __DEFINICIONS_H_
#define __DEFINICIONS_H_

/*************\
| DEFINICIONS |
\*************/

// Determinació a la plataforma que treballarà el compilador...
#include "stdlib.h"
#include "stdio.h"

#if defined(_WINDOWS) || defined(_LINUX)
#ifndef __SDL__
 #define __SDL__
#endif
 
 #include "conio.h"
 #include "memory.h"
 #include "string.h"
 #include "SDL/SDL.h"
#endif

#include "Tipus.h"
#include "Paleta.h"

/********************************\
| DEFINICIONS DE SPRITES i BLOCS |
\********************************/

#define SEGON 1000
#define COLOR_MASCARA  227

// Respecte la PANTALLA

#define MAX_BLOCS 70

#define AMPLADA_BLOC 32
#define ALTURA_BLOC  32

#define AMPLADA_PANTALLA_JOC 224
#define ALTURA_PANTALLA_JOC  192

#define MAX_BLOCS_X  word(AMPLADA_PANTALLA/AMPLADA_BLOC)   // 7 blocs per ser exactes
#define MAX_BLOCS_Y  77    // N§ de blocs verticals


#define MAX_LLETRES_X  word(260/AMPLADA_LLETRAM)   // 20 lletres per ser exactes.
#define MAX_LLETRES_Y  80


#define NUMERO_BLOCS_X  AMPLADA_PANTALLA/AMPLADA_BLOC  // 7 per ser exactes
#define NUMERO_BLOCS_Y  ALTURA_PANTALLA/ALTURA_BLOC  // 6 per ser exactes


#define NUMERO_LLETRES_X  word(260/AMPLADA_LLETRAM)  // 20 per ser exactes
#define NUMERO_LLETRES_Y  word(195/ALTURA_LLETRAM)  // 13 per ser exactes


/**************************\
| ATTRIBUTS DELS OBJECTES  |
\**************************/

#define PASSIU           0
#define BALA_ENEMIC      1
#define ENEMIC_AERI      2
#define ENEMIC_TERRESTRE 3
#define EXPLOSIU         4

#define LA_MEVA_BALA     5


#define MAX_DIRECCIONS 3        // Esquerra , Dreta i Normal.
#define MAX_TIME       50      // m…xim de tics que es deixa per la animaci¢ per canvi de temps m…xima!

#define MAX_POWERUP  5
#define MAX_BOMBERS  5

#define RETARD_DEL_MEU_DISPAR  10
#define RETARD_DISPAR_INICIAL 90
#define MAX_RETARD_PAUSA      10;

#define RETARD_BOMBA 20

#define SI 1
#define NO 0

#define EXPLOSIO1      0
#define EXPLOSIO2      1

#define TURBO          2

#define IMPACTE        3

#define ITEM1          4
#define ITEM2          5
#define ITEM3          6

#define BALA_ENEMIC_1  7
#define BALA_ENEMIC_2  8

#define LA_MEVA_BALA_1 9 //  [.] 
#define LA_MEVA_BALA_2 10 // [.] . [.]
#define LA_MEVA_BALA_3 11 // . [..] .


#define LA_MEVA_BALA_4 12 //[..] ..  [..]
#define LA_MEVA_BALA_5 13 //[..] [...] [..]

#define _PERSONATGE         14


#define _METEORIT1           15
#define _METEORIT2           16
#define _METEORIT3           17

#define _CAIXA1              18
#define _CAIXA2              19
#define _CAIXA3              20

#define METEORIT_DESTRUIT    21
#define CAIXA_DESTRUIDA      22

#define ENEMIC_1            23
#define ENEMIC_2            24
#define ENEMIC_3            25
#define ENEMIC_4            26
#define ENEMIC_5            27
#define ENEMIC_6            28
#define ENEMIC_7            29
#define ENEMIC_8            30
#define ENEMIC_9            31

#define ENEMIC_10           32
#define ENEMIC_11           33
#define ENEMIC_12           34

#define ENEMIC_13           35


#define BOLA_ENERGIA        36
#define _BOSS1              37
#define COMPORTES_DRETA     38
#define COMPORTES_ESQUERRA  39
#define IMPACTE_BOMBA       40

// Conjunts...

#define PERSONATGE 0

#define BALA       1
#define LASER      2

#define ENEMIC1    1
#define ENEMIC2    2
#define ENEMIC3    3 

#define ENEMICD   10
#define ENEMICE   20

#define ENEMIC4    4
#define ENEMIC5    5
#define ENEMIC6    6
#define ENEMIC7    7
#define ENEMIC8    8
#define ENEMIC9    9

#define METEORIT1   10
#define METEORIT2   11
#define METEORIT3   12

#define CAIXA1      13
#define CAIXA2      14
#define CAIXA3      15



#define ENEMIC10   16
#define ENEMIC11   17
#define ENEMIC12   18

#define ENEMIC13   19



#define BOSS1      20


// FRAMES

#define SEGUENT_POSICIO_AMB_TRANSICIO_Y -1
#define SEGUENT_MOVIMENT_AMB_TRANSICIO_Y -2

// DISPARS

#define BALA1   1  // Normal va cap a tu...
#define BALA2   2  // Laser, va recte a tu...
#define BALA3   3  // Laser, va recte a tu...
#define LASER1  4  // Llen‡a un enemic...
#define LASER2  5  // Llen‡a un enemic...


#define RETARD_DISPAR 200

// TEMPS


// RECTES

// TIPUS DE SPRITE I LA SEVA DIMENSIO, T'HO CREUS I JA ESTA! . OK?

#define DIM_SPR_8X8         8   // DISPARS PETITS...
#define MAX_SPR_8X8         17
#define N_FILES_SPR_8X8     (word(MAX_SPR_8X8/(320/DIM_SPR_8X8)) + 1)

#define DIM_SPR_16X16       16  // SPRITES NORMALS,EXPLOSIONS,ETC...
#define MAX_SPR_16X16       67
#define N_FILES_SPR_16X16   word((MAX_SPR_16X16/(320/DIM_SPR_16X16)) + 1)

#define DIM_SPR_32X32       32  // GRANS EXPLOSIONS O GRANS NAUS.
#define MAX_SPR_32X32       5
#define N_FILES_SPR_32X32   word((MAX_SPR_32X32/(320/DIM_SPR_32X32)) + 1)

#define DIM_SPR_64X64       64  // ENEMIC FINAL DE FASE.
#define MAX_SPR_64X64       1
#define N_FILES_SPR_64X64   word((MAX_SPR_64X64/(320/DIM_SPR_64X64)) + 1)


#define MAX_SPRITES         MAX_SPR_8X8+MAX_SPR_16X16+MAX_SPR_32X32+MAX_SPR_64X64

#define MAX_OBJECTE        43
#define MAX_CONJUNT        22
#define MAX_MOVIMENT       64
#define MAX_RUTA           60


extern tSprite Sprites[MAX_SPRITES];
extern tImatge Imatges[MAX_SPRITES];
extern tImatge Blocs[MAX_BLOCS];
extern byte *Mapa;
extern char *BUFFER1;
extern char *BUFFER2;
extern char *BUFFER3;


extern int BLOCINVERS[AMPLADA_BLOC*ALTURA_BLOC];

/***********************\
| DEFINICIONS DE TECLAT |
\***********************/

#define TECLA_AMUNT		TeclaAmunt() 
#define TECLA_AVALL		TeclaAvall() 
#define TECLA_DRETA		TeclaDreta() 
#define TECLA_ESQUERRA	TeclaEsquerra() 

#define TECLA_DISPAR	TeclaKeyPad0() 
#define TECLA_BOMBA		TeclaPeriode() 

#define TECLA_PAUSA		Tecla_p() 

#define TECLA_ESCAPE	TeclaEscape() 




/********************\
| DEFINICIONS DE JOC |
\********************/

extern int dificultat;
extern int Cheat;
extern int vides;
extern dword puntuacio;
extern dword maxima_puntuacio;
extern tPaleta paleta1,paleta2,paleta3;

/*************************\
| DEFINICIONS DE PANTALLA |
\*************************/

#ifdef __SDL__ // treballem sobre plataforma SDL per tant, la resolució pot ser variable.
	#define AMPLADA_PANTALLA		320
	#define ALTURA_PANTALLA			200
	
#endif



/********************\
| ALTRES DEFINICIONS |
\********************/

#define INFINIT -1

#define CERT 1
#define FALS 0

#define MARCA_FI_STRING '\0'


/*******************\
| VARIABLES GLOBALS |
\*******************/



/************\
| PROTOTIPUS |
\************/


#endif