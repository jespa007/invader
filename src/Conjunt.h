#ifndef CONJUNT_H
 #define CONJUNT_H


typedef struct _conjunt_objectes
{

 tObjecte actual;
 int part_debil;
 int offsetx,offsety;
 int retard_dispar;
 int temps; // Restant per abandonar el conjunt...
 _conjunt_objectes *PSeguent;

}conjunt_objectes;

typedef conjunt_objectes *PObjectes;

class tConjunt
{

 PObjectes OBJECTES,PActual;

 int Actiu;

 void copia(const tConjunt &Conjunt);

public:

 tConjunt();
 tConjunt & operator = (const tConjunt  &S);


 void EntrarEstatInicial(int Estat,int Retard);


 void AfegirObjecte(tObjecte const &Objecte,int OFFSETX,int OFFSETY,int PART_DEBIL,int TEMPS);
 void ActualitzarCoordenades(int X,int Y);
 void ActualitzarConjunt(int TransicioMoviment,int TransicioPosicio);
 void EscriureObjectes();

 int DimensioMax();
 int DecrementarVitalitatActual(int N);
 int RegaletActual();
 word ScoreActual();

 int SpriteActual();
 int ActualVolDisparar(int *x,int *y,int ,int);
 void RetornarOffsetActual(int *X,int *Y);

 void Reset();
 void Seguent();
 int ActualEsNul();
 int ConjuntEsNul();
 int PartDebil();

 void EliminarActual();

 int EsActiu();
 int EsInvencible();

 ~tConjunt();
};


#endif
