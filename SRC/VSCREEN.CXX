#include "vscreen.h"


/*
   ��������������������ͻ
   �                    �
   �  UTILITATS VSCREEN �
   �                    �
   ��������������������ͼ
*/


byte  * VScreen(word *VScreen)
{
 byte *p = NULL;

 p = (byte *)malloc(word(64000L));

 p = (byte *) MK_FP( FP_SEG(p) , 0 );

 (*VScreen) = FP_SEG(p);

 return (p);


/*
 word numero = tamany/16;
 asm{
     mov ah,48h        // Peticio de segment. (int 48h) //
     mov bx,[numero]   // Demanem un segment de 4000*16=64000 //
     int 21h           // interrupcio de dos (el S.O ens otorga el segment) //
    }
   return _AX;
*/

}



byte *VSBuffer(word tamany)
{

 return (byte*)malloc(tamany);

}





void Flip_VScreen(word desti,word origen)
{

 asm{
     push ds
     push es
     mov ds,[origen]
     xor si,si
     mov es,[desti]
     xor di,di
     mov cx,32000
     rep movsw
     pop es
     pop ds
    }

}


void Flip_VScreen(word desti,word origen,word tamany = 64000)
{

 asm{
     push ds
     push es
     mov ds,[origen]
     xor si,si
     mov es,[desti]
     xor di,di
     mov cx,[tamany]
     shr cx,1
     rep movsw
     pop es
     pop ds
    }

}





int CarregarImatgeVScreen(byte *nom,byte far *VScreen)
{
 int i,j;

 // Carrega imatges de 320 x 200 a una VSCREEN...

 FILE *file = NULL;

 if( (file = fopen (nom,"rb")) == NULL)
 {
  return 0;
 }


 for(i=0;i<200;i++)
  for(j=0;j<320;j++) fread(VScreen+(i*320)+j,1,1,file);


// fread(VScreen,64000L,1,file);

 fclose(file);

 return 1;
}









void Lliurar_VSBuffer(byte *VSbuffer)
{
 free(VSbuffer);
}

/*
void Lliurar_VScreen(word *VSbuffer)
{

 free (VSbuffer);

 
 asm{
     mov ah,49h
     mov es,[VSbuffer]
     int 21h
    }
  
}
*/




word Segment(byte *VSbuffer)
{
 return FP_SEG(VSbuffer);
}
