#include "Teclat.h"

#ifdef __SDL__

Uint8 *tecla; 

void InicialitzarTeclat()
{
 tecla = SDL_GetKeyState(NULL); 
}

unsigned TeclaAmunt() {SDL_PumpEvents();return tecla[SDLK_UP];}
 
unsigned TeclaAvall(){SDL_PumpEvents();return tecla[SDLK_DOWN];}

unsigned TeclaEsquerra() {SDL_PumpEvents();return tecla[SDLK_LEFT];}

unsigned TeclaDreta() {SDL_PumpEvents();return tecla[SDLK_RIGHT];}

unsigned TeclaEscape() {SDL_PumpEvents();return tecla[SDLK_ESCAPE];}

unsigned TeclaMes() {SDL_PumpEvents();return tecla[SDLK_KP_PLUS];}

unsigned TeclaMenys() {SDL_PumpEvents();return tecla[SDLK_KP_MINUS];}

unsigned Tecla_p() {SDL_PumpEvents();return tecla[SDLK_p];}

unsigned TeclaKeyPad0(){SDL_PumpEvents();return tecla[SDLK_KP0];}
unsigned TeclaPeriode(){SDL_PumpEvents();return tecla[SDLK_KP_PERIOD];}


#endif