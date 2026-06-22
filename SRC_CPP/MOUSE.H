#ifndef MOUSE_H
 #define MOUSE_H

#include "all_lib.h"



#define BUTO_MOUSE_DRET 2
#define BUTO_MOUSE_ESQUERRE 1


typedef struct tPosicio
{

 int x,y;

};


//  ÚÄÄÄÄÄÄÄÄ¿
//  ³ Ratoli ³
//  ÀÄÄÄÄÄÄÄÄÙ


    int Init_Mouse(void);
    void Posicio_Mouse(tPosicio *MOUSE);
    void MostrarPunter(void);
    void OcultarPunter(void);
    int Buto_Pitjat(void); // Retorna el n§ de BUTO.

#endif
