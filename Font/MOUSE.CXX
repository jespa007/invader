#include "mouse.h"


/*
   ษอออออออออออออออออออออป
   บ                     บ
   บ  UTILITATS RATOLI   บ
   บ                     บ
   ศอออออออออออออออออออออผ
*/






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


void Posicio_Mouse(tPosicio *MOUSE)
{
 int X = MOUSE->x ,Y = MOUSE->y;

     asm{
	 mov AX,03h
	 int 33h
         shr CX,1
         mov X,CX
         mov Y,DX
	}

  (MOUSE->x)=X;
  (MOUSE->y)=Y;

}




void MostrarPunter(void)
{
 asm{
     mov AX,1
     int 33h
    }
}

void OcultarPunter(void)
{
 asm{
     mov AX,2
     int 33h
    }
}



int Buto_Pitjat(void)
{
 // Ens entrega el buto pitjat.
 asm{
     mov AX,05h
     mov BX,00h
     int 33h
    }
     return _AX;
}







