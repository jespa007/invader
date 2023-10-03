#include "mouse.h"


/*
   ษอออออออออออออออออออออป
   บ                     บ
   บ  UTILITATS RATOLI   บ
   บ                     บ
   ศอออออออออออออออออออออผ
*/





/*
int Init_Mouse(void)
// Inicia el ratolก, si no el detecta retorna un 0 patatero.
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
#ifdef __SDL__
 SDL_PumpEvents();
 SDL_GetMouseState(&MOUSE->x, &MOUSE->y);
#endif
  


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

#ifdef __SDL__
	SDL_PumpEvents();
	if(buto = SDL_GetMouseState(NULL,NULL)) return (buto == SDL_BUTTON(1))? BUTO_MOUSE_ESQUERRE: BUTO_MOUSE_DRET ;
#endif
  
	return 0;
}







