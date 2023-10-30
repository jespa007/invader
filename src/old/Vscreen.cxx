#include "Invader.h"


/*
   ��������������������ͻ
   �                    �
   �  UTILITATS VSCREEN �
   �                    �
   ��������������������ͼ
*/


char  * VScreen()
{

 return (char *)malloc(64000);

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



char *VSBuffer(word tamany)
{

 return (char*)malloc(tamany);

}





void Flip_VScreen(char *dest,char *src) // Volca un buffers de treball (320x200)...
{
	

#ifdef _WINDOWS
 _asm{
     push esi
     push edi
     mov edi,dest
     mov esi,src
     mov ecx,16000
     rep movsd
     pop esi
     pop edi
    }
#endif
}

/*
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
*/




int CarregarImatgeVScreen(const char *nom,char *VScreen)
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









void Lliurar_VSBuffer(char *VSbuffer)
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



/*
word Segment(byte *VSbuffer)
{
 return FP_SEG(VSbuffer);
}
*/