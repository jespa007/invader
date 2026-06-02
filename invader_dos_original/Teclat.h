#define TECLA_TRUE 0xFF
#define TECLA_FALSE 0x00

		/*SCAN-CODES*/

#define AMUNT      72
#define DRETA      77
#define ESQUERRA   75
#define AVALL      80

#define DISPAR     82
#define BOMBA      83
#define INTRO      224
#define ESCAPE     1
#define P          25



void InstalarTeclat(void);

/* Instala la rutina per a la detecció del SCAN-CODES */

void DesinstalarTeclat(void);
/* Desinstala la rutina per a la detecció dels SCAN-CODES */

