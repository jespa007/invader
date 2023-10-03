#ifndef __VSCREEN__
#define __VSCREEN__

#include "definicions.h"

 //  ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
 //  ³Utilitats VSCREEN³
 //  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

 char * VScreen();

 void Flip_VScreen(char *DESTI,char *ORIGEN);
 //void Flip_VScreen(word DESTI,word ORIGEN);

 int CarregarImatgeVScreen(const char *nom,char *VScreen);

 void Lliurar_VSBuffer(char *VIRTUAL_SCREEN_BUFFER);


#endif