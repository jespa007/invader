		   /*-______________-*\__  ˙   ˙            ˙
  ˙       ˙     )-/                    \_)   ˙      ˙
    ˙            | (  SOUND BLASTER 16  |_) ˙      ˙     ˙ 
 .         ˙    )-\                    /_)   ˙    ˙
   ˙   ˙           \*_---------------_*/


#define NUMSOUNDS 26     /* Cambie este parametro si a§adi¢ mas sonidos */
#define XMSREQUIRED 600 /* memoria en kbytes, que requiere sus sonidos */



char *sonidos_key[NUMSOUNDS] = { /* aqui debe definir las claves de su */
	 "ALIZE",                /* archivo de sonido, lea el archivo  */
	 "RAMNSTEIN",                                                         /* leame.txt para detalles sobre esto */
	 "LINKIN",
	 "ANDRE00",
	 "ANDRE01",
	 "MAKINA",
	 "C_OK",
	 "C_OPTION",
	 "INVADER",
	 "TURBO",
	 "SHOT1",
	 "WARNING",
	 "ATENTION",
	 "ALARMA",
	 "MECANIC",
	 "EXPLOS0",
	 "EXPLOS2",
	 "SHOT0",
	 "FEBLE",
	 "SHOT2",
	 "POWERUP",
	 "TRO",
	 "NAUMARE0",
	 "EXPLOS1",
	 "BOMBOUT",
	 "BOMBERUP"

};



#include "sb\mixer.h"   /*solo debe incluir este archivo para usar Sound Blaster*/


// CANÄONS DE INTRO I MêS... YEAAAAAAH

char SB = FALS;
char effect = 0;



void interrupt SONIDOS(__CPPARGS)
{

/*
 if(temps < 2) temps++;
 else temps = 1;
*/


 if(SB)
 {
  switch(effect)
  {
   case '2' : start_sound(sonidos[2], 0, OFF);effect = '0'; // Mode off...
  }
 }

// oldhandler();
};

