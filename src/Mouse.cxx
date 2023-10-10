#include "invader.h"


/*
   ���������������������ͻ
   �                     �
   �  UTILITATS RATOLI   �
   �                     �
   ���������������������ͼ
*/





/*
int Init_Mouse(void)
// Inicia el ratol�, si no el detecta retorna un 0 patatero.
{
 asm{
     xor AX,AX  // Iniciant AX a 0.
     int 33h    // Int 33 = Mouse via MS-DOS.
    }
 if(_AX!=0) return CERT;
 else return FALS;
}
*/

void Posicio_Mouse(tPosicio *MOUSE)
{
 SDL_PumpEvents();
 SDL_GetMouseState(&MOUSE->x, &MOUSE->y);
}




void MostrarPunter(void)
{
 /*asm{
     mov AX,1
     int 33h
    }*/
}

void OcultarPunter(void)
{
 /*asm{
     mov AX,2
     int 33h
    }*/
}



int Buto_Pitjat(void)
{
	char buto;

	SDL_PumpEvents();
	if(buto = SDL_GetMouseState(NULL,NULL)) return (buto == SDL_BUTTON(1))? BUTO_MOUSE_ESQUERRE: BUTO_MOUSE_DRET ;
  
	return 0;
}







