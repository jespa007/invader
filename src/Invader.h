#ifndef INVADER_H
 #define INVADER_H

#include "Teclat.h"

#include "definicions.h"

#include "Vscreen.h"

#include "Moviment.h"
#include "Objecte.h"
#include "Conjunt.h"





class tInvader
{

 tObjecte Objectes[MAX_OBJECTE]; // Objectes...
 tConjunt Conjunts[MAX_CONJUNT]; // Conjunts...
 tMoviment Moviments[MAX_MOVIMENT];
// tRuta Rutes[MAX_RUTA];



 typedef struct SHOT
 {
  int x,y;
  tObjecte  Shot;
  tMoviment Moviment;
  SHOT *PSeguent;
 };

 typedef struct EXPLOSIO
 {
  int x,y;
  tObjecte Explosio;
  EXPLOSIO *PSeguent;
 };


 typedef struct ENEMIC
 {
  int x,y;
  tConjunt  Enemic;
  tMoviment  Ruta;

  int tipus;
  int vol_atacar;
  ENEMIC *PSeguent;
 };

 typedef struct ITEM
 {
  int x,y;
  tObjecte Item;
  tMoviment  Moviment;
  int tipus;
  ITEM *PSeguent;
 };

 typedef SHOT *PShots;
 typedef ENEMIC *PEnemics;
 typedef ITEM *PItems;
 typedef EXPLOSIO *PExplosions;

 PShots EnemyShots,MyShots;
 PEnemics EnemicsAeris,EnemicsTerrestres;
 PItems Items;
 PExplosions Explosions;

 tConjunt Jo;
 tMoviment MyMov;

 tObjecte Bomba;
 tMoviment MovBomba;
 
 int Vides;
 int MyPosY,MyPosX;
 int MyPowerUp;
 int MySpeedUp;
 int Retard_Dispar;
 int NauImpactada;
 int EsActiu;
 int BossDestroyed;
 int SequenciaDestruccioBoss;
 int XBoss,YBoss;
 int RetardDestruccioBoss;
 int RetardFiNau;
 dword Puntuacio;
 int HeTiratBomba;
 int Bombes;
 int XBomba,YBomba;
 int Retard_Bomba;
 int ImpacteBomba;

public:

 tInvader();


 void LoadStage1();

 void AfegirEnemic(int x,int y,int tipus,int ruta,int ataca);
 void CrearDispar(int x,int y,int dispar,int direccio,int cua);
 void CrearExplosio(int x,int y,int tipus);
 void AfegirItem(int x,int y,int tipus,int ruta);

 int  Checkit(int x,int y,int power,int dimensio);

 int NauDestruida();
 void DestruirNau();

// int CheckAll();
 int BOSSDESTROYED();
 void DestruirTot();
 void DestruirEnemicsAeris();
 void DestruirBales();

 word EntregarBombes();
 void EntrarBombes(int B);

 void TirarBomba();

 void InicialitzaNau();
 void FinalitzarNau();


 dword PuntuacioActual();
 void SeguentPosicio();
// FinalitzarNau();
// int BossDestroyed();
 void Actualitzar();

// InicialitzaStage2();
// InicialitzaStage3();
// InicialitzaStage4();
// InicialitzaStage5();
// InicialitzaStage6();

 void UnLoadStage1();

/*****-__TEST__-*****/

 void VisualitzarSprites();

 void VisualitzarBlocs();

 void VisualitzarObjectes();

 void VisualitzarConjunts();

 void ProbarMoviments();

 void TestMoviments();

 void TestRutes();

 void TestDispars();


 ~tInvader();
};


#endif
