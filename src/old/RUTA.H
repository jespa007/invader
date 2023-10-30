#ifndef RUTA_H
 #define RUTA_H

typedef struct MOV
{

 tMoviment actual;
 int vel;
 int n_vegades;       // Si 0 vol dir que ACTUA AMB NORMALITAT!
 int condicio;        // Condicio
 MOV  *PSeguent;      //          
                      //          => 0 .- Si (0) Sense condicio !!!
                      //          => 1 .- 
                      //          => 2 .- 
                      //          => 3 .- 
                      //          => 4 .- 
};

typedef MOV *PMoviments;


class tRuta
{

 PMoviments PARTS;
 PMoviments PActual;

 int x,y;
 int P_Actual;
 int N_Moviments;
 int M_Actual;     // Moviments fets actualment. (cas de que no sigui infinit!!!)

 void tRuta::copia(const tRuta &Ruta);

public:

 tRuta();
 tRuta & tRuta::operator = (tRuta const &S);

 void AfegirMoviment(const tMoviment &M,int vel,int condicio,int n_vegades);

 int EsNul();

// SeguentMoviment(); // Crea el nou moviment... (en funcio de la condici�.)

void EntrarCoordenades(int x,int y);
void SeguentPosicio(int *x,int *y,int myposx,int myposy,int velx,int vely,int DIM); // Seguent Posicio del moviment...

int TransicioYPosicioSeguent();
int TransicioYMovimentSeguent();

int N();


 ~tRuta();

};



#endif
