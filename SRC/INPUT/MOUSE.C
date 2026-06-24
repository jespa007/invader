#include "INPUT\@INPUT.H"

bool Mouse_Init(){
    asm{
        xor AX,AX  // Iniciant AX a 0.
        int 33h    // Int 33 = Mouse via MS-DOS.
    }

    return _AX!=0;
}
/*
void Mouse_Position(tPosicio *MOUSE)
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

}*/




void Mouse_ShowCursor(void)
{
 asm{
     mov AX,1
     int 33h
    }
}

void Mouse_HideCursor(void)
{
 asm{
     mov AX,2
     int 33h
    }
}



int Mouse_BPressed(void)
{
 // Ens entrega el buto pitjat.
 asm{
     mov AX,05h
     mov BX,00h
     int 33h
    }
     return _AX;
}