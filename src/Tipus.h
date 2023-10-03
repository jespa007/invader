#include "stdio.h"

#if defined(_WINDOWS) || defined(_LINUX)
	#define __SDL__
#endif

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long dword;

// DEFINICIO DE TIPUS

#ifdef __SDL__
	typedef SDL_Color tColor;

	#define ColorIgual(color1,color2) ((color1.r == color2.r)&&(color1.g == color2.g)&&(color1.b == color2.b))


#endif

typedef tColor tPaleta[256];

// EXCLUSIUS ALS SPRITES.


typedef char *tImatge;

typedef struct
{

 int dimx,dimy;
 tImatge imatge;
 int retard_dispar; // 0...MAX_DISPAR*DIFICULTAT
 int agresiu;  // 0 (No ho es), != 0 (ens diu el tipus de dispar a dispar…)...
 int invencible;  // es te en compte si decreix la seva vitalitat al ser impactat (CERT o FALS).
 int impactable;  // CERT/FALS
 int vx,vy;

}tSprite;











