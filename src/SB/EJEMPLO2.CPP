/* Turbo C++ 3.0                                                       */
/* Oswaldo Varela C.                                                   */

/* Utilize la opcion Change Dir en el menu File y escoja la carpeta que
	contiene este archivo, para que el compilador encuentre los archivos*/
#define NUMSOUNDS 6     /* Cambie este parametro si a¤adi¢ mas sonidos */
#define XMSREQUIRED 200 /* memoria en kbytes, que requiere sus sonidos */

char *sonidos_key[NUMSOUNDS] = {
	 "JET",
	 "GUN",
	 "CRASH",
	 "CANNON",
	 "LASER",
	 "GLASS",
};

#include "sb\mixer.h"

void main(){
	int  jet            = 0;
	unsigned short rate = 22000;
	char inkey;
	int  num;
	int lef=15,rig=15;// las variables de volumen varian entre 0 y 15
	int  stop;
	/* Inicializa SMIX */
	init_mix();
	loadsounds("datos\\sonidos.snd");	// archivo de sonidos
	printf("Presione:\n");
	printf("  J  Switch para motor jet\n");
	printf("  1  Machine Gun\n");
	printf("  2  Crash\n");
	printf("  3  Cannon\n");
	printf("  4  Laser\n");
	printf("  5  Breaking glass\n");
	printf("  <  Decrementa sampling rate\n");
	printf("  >  Incrementa sampling rate\n");
	printf("  R  Subir Volumen derecho\n");
	printf("  r  Bajar Volume derecho\n");
	printf("  L  Subir Volumen izquierdo\n");
	printf("  l  Bajar Volume izquierdo\n");
	printf("  S  Salir\n");
	stop = FALSE;
	_setcursortype(_NOCURSOR);
	do{
		/* Despliega la informaci¢n */
		cprintf("Conteo de voces:%2u   Sampling Rate:%6u   Volume: R:%2d,L:%2d", voicecount, rate, rig, lef);
		gotoxy(1, wherey());
		/* Si una tecla es presionada comienza un sonido */
		if (kbhit()){
			inkey = getch();
			if ((inkey == 'J') || (inkey == 'j')){	/* Jet engine */
				jet = !jet;
				if (jet) start_sound(sonidos[0], 0, ON);
				else stop_sound(0);
			}
			if ((inkey >= '0') && (inkey <= '5')){	 /* comienza un sonido */
				num = inkey - '0'; /* Convierte a entero */
				start_sound(sonidos[num], num, FALSE);
			}
			if ((inkey == '<') || (inkey == ',')){ /* Reduce sampling rate */
				rate -= 250;
				if (rate < 5000) rate = 5000;
				set_sampling_rate(rate);
			}
			if ((inkey == '>') || (inkey == '.')){ /* Increase sampling rate */
				rate += 250;
				if (rate > 48000U) rate = 48000U;
				set_sampling_rate(rate);
			}
			if(inkey == 'R'){ /* aumenta volumen derecho */
						if(rig<15)rig++;setmastervolume(lef,rig);
			}
			if(inkey == 'r'){	/* disminuye volumen derecho */
						if(rig>0)rig--;setmastervolume(lef,rig);
			}
			if(inkey == 'L'){ /* aumenta volumen izquierdo */
						if(lef<15)lef++;setmastervolume(lef,rig);
			}
			if(inkey == 'l'){ /* disminuye volumen izquierdo */
						if(lef>0)lef--;setmastervolume(lef,rig);
			}
			if((inkey == 's')||(inkey == 'S')) /* Termina el programa */
				  stop = TRUE;
		}
	}while (!stop);
	/* Detiene el motor jet */
	 if (jet)
		stop_sound(0);
	/* Desactiva SMIX */
	 shutdown();
	/* Libera memoria de sonidos */
	 freesounds();
}

