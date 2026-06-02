/* Turbo C++ 3.0                                                       */
/* Oswaldo Varela C.                                                   */
/* Tab size: 3                                                         */

/* Utilize la opcion Change Dir en el menu File y escoja la carpeta que
	contiene este archivo, para que el compilador encuentre los archivos*/
#define NUMSOUNDS 6     /* Cambie este parametro si a¤adi¢ mas sonidos */
#define XMSREQUIRED 4000 /* memoria en kbytes, que requiere sus sonidos */

char *sonidos_key[NUMSOUNDS] = { /* aqui debe definir las claves de su */
         "ALIZE",                                                         /* archivo de sonido, lea el archivo  */
         "RAMNSTEIN",                                                         /* leame.txt para detalles sobre esto */
         "LINKIN",
         "ANDRE00",
         "ANDRE01",
         "MAKINA",
};

#include "sb\mixer.h"	/*solo debe incluir este archivo para usar Sound Blaster*/

void main(){
	/* Inicializa SMIX */
	init_mix();
        loadsounds("SND\\sonidos.snd");// archivo de sonidos
	printf("\nEl motor jet ha sido encendido...\n");
	printf("Presione una tecla...\n");
	start_sound(sonidos[0], 0, ON);	// comienza motor jet con loop
	getch();									// hasta que se presione una tecla
	printf("El motor jet ha sido detenido...\n");
	printf("Presione una tecla...\n\n");
	stop_sound(0);							// detiene motor jet
	printf("Crash activado\n");
	printf("Presione una tecla para salir...\n");
	start_sound(sonidos[2], 2, FALSE);
	getch();
	stop_sound(2);		// se detiene crash si todavia esta en reproduccion
	/* Desactiva SMIX */
	 shutdown();
	/* Libera memoria de sonidos */
	 freesounds();
}

