                   /*-______________-*\__  ú   ú            ú
  ú       ú     )-/                    \_)   ú      ú
    ú            | (  SOUND BLASTER 16  |_) ú      ú     ú 
 .         ú    )-\                    /_)   ú    ú
   ú   ú           \*_---------------_*/


#define NUMSOUNDS 6     /* Cambie este parametro si a¤adi¢ mas sonidos */
#define XMSREQUIRED 2700 /* memoria en kbytes, que requiere sus sonidos */



char *sonidos_key[NUMSOUNDS] = { /* aqui debe definir las claves de su */
	 "JET",								/* archivo de sonido, lea el archivo  */
	 "GUN",								/* leame.txt para detalles sobre esto */
	 "CRASH",
	 "CANNON",
	 "LASER",
	 "GLASS",
};



#include "sb\mixer.h"	/*solo debe incluir este archivo para usar Sound Blaster*/


// CAN€ONS DE INTRO I MS... YEAAAAAAH

char SB = FALS;
char effect = 0;



void interrupt SONIDOS(__CPPARGS)
{

 temps ++;

 if(SB)
 {
  switch(effect)
  {
   case '2' : start_sound(sonidos[2], 0, OFF);effect = '0'; // Mode off...
  }
 }

};
