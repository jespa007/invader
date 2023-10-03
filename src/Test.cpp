#include "definicions.h"
#include "Grafics.h"
#include "Mouse.h"
#include "Teclat.h"
#include "Paleta.h"
#include "Font.h"
#include "VScreen.h"
#define INTR 0x1C    /* The clock tick interrupt */

#define FACIL    0
#define MITJANA  1
#define DIFICIL  2

#define MAX_VIDES 4






                  /*-_________________-*\__  ú   ú            ú
  ú       ú     )-/                       \_)   ú      ú
    ú            | (  DEFINICIO DE TIPUS  |_) ú      ú     ú
 .         ú    )-\                       /_)   ú    ú
   ú   ú           \*_------------------_*/



// typedef byte far tBloc[AMPLADA_BLOC*ALTURA_BLOC];

                  /*-____________________-*\__  ú   ú            ú
  ú       ú     )-/                          \_)   ú      ú
    ú            | (  CAP€ALERA DE FUNCIONS  |_) ú      ú     ú
 .         ú    )-\                          /_)   ú    ú
   ú   ú           \*_---------------------_*/



int menu();
void options();

//void interrupt ( *oldhandler)(__CPPARGS);
//void interrupt SONIDOS(__CPPARGS);


//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Estructures del joc³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

int game();
void credits();
void gameover();

//  ÚÄÄÄÄÄÄ¿
//  ³Altres³
//  ÀÄÄÄÄÄÄÙ




//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Gestio de Sortida³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ






                   /*-_______________-*\__  ú   ú            ú
  ú       ú     )-/                     \_)   ú      ú
    ú            | (  VARIABLES GLOBALS |_) ú      ú     ú 
 .         ú    )-\                     /_)   ú    ú
   ú   ú           \*_----------------_*/

 tImatge Blocs[MAX_BLOCS];
 byte *Mapa=NULL;

 tImatge Imatges[MAX_SPRITES]; // En aqui trobarem totes les imatges.
 tSprite Sprites[MAX_SPRITES]; // En aqui trobarem tots els sprites del joc.

 char BLOCINVERS[AMPLADA_BLOC*ALTURA_BLOC];




 /********************\
| VSCREENS NECESSARIES |
 \********************/

int Cheat = CERT;
int vides;
dword puntuacio=0;
dword maxima_puntuacio=0;
int dificultat = MITJANA;
word temps = 0;

char  * BUFFER1 = NULL; 
char  * BUFFER2 = NULL;
char  * BUFFER3 = NULL;
char  * BUFFER4 = NULL;

word VSCREEN1;
word VSCREEN2;
word VSCREEN3;
word VSCREEN4;

 /********************\
| PALETES NECESSARIES |
 \********************/


tPaleta paleta1,paleta2,paleta3,paleta4;


                   /*-__________-*\__  ú   ú            ú
  ú       ú     )-/                \_)   ú      ú
    ú            | (  FUNCIO MAIN  |_) ú      ú     ú 
 .         ú    )-\                /_)   ú    ú
   ú   ú           \*_-----------_*/


//  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
//  ³Propi del joc³
//  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

//#include "Effects.cc"
//#include "Text.cc"

//#include "Teclado.c"      // Per JASM & BMP

//#include "Ruta.cc"
//#include "Moviment.cc"
#include "Init.cc"
//#include "Scroll.cc"
#include "Menu.cc"
//#include "Conjunt.cc"


//#include "Part.cc"
//#include "Objecte.cc"

//#include "Test.cc"


//#include "Stage1.cc"

int main(int argc, char *argv[])
{
	char bloc[8*8];
	int i,posx=0,posy=50;
	tPosicio PosicioRatoli;
	tPaleta paleta;



	for(i = 0;i < 64;i++) bloc[i] = rand()%255;

	InicialitzarTeclat();
	SetVideo();
	
//	CarregarFontMonoTextura();

	
//	CarregarPaleta("grafics//paleta1.pal",paleta);


//VisualitzarPaleta();	
	
	do{
		
		if(TeclaAmunt()) posy--;
		if(TeclaAvall()) posy++;
		if(TeclaDreta()) posx++;
		if(TeclaEsquerra()) posx--;

/*		Posicio_Mouse(&PosicioRatoli);

		posx = PosicioRatoli.x;
		posy = PosicioRatoli.y;*/

		
		




		
		ClearScreen(0);
		
	
		PutBlock(posx,posy,bloc,8,8,0,0,AMPLADA_PANTALLA-1,ALTURA_PANTALLA-1);
	
		
		SDL_Flip(Video);
				
	}while(!TeclaEscape());


	exit(0);
}