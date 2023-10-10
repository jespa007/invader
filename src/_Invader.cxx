#include "invader.h"
#include "struct.cc"
#include "test.cc"



#define CUA_DISPARS_ENEMICS 0
#define CUA_MY_SHOTS        1


void Quit(byte *);

tInvader::tInvader()
{

 Retard_Bomba = RETARD_DISPAR_INICIAL;
 ImpacteBomba = FALS;
 RetardDestruccioBoss = 0;
 RetardFiNau = 0;
 EsActiu = FALS;
 Puntuacio = 0;

 BossDestroyed = FALS;
 SequenciaDestruccioBoss = FALS;

 MyPosY=ALTURA_PANTALLA_JOC; MyPosX=112;
 MyPowerUp = 1;
 MySpeedUp = 1;
 Retard_Dispar = RETARD_DISPAR_INICIAL;
 NauImpactada = FALS;
 HeTiratBomba=FALS;
 Bombes = 3;

 EnemyShots=MyShots=NULL;

 EnemicsAeris=EnemicsTerrestres=NULL;
 Items=NULL;
 Explosions=NULL;

}

word tInvader::EntregarBombes()
{
 return(Bombes);
}

void tInvader::EntrarBombes(int B)
{
 Bombes = B;
}




dword tInvader::PuntuacioActual()
{
 return(Puntuacio);
}

void tInvader::AfegirEnemic(int x,int y,int tipus,int ruta,int ataca)
{
 byte Motiu0[]={"No tens prou memoria pels enemics.\0"};
 PEnemics PNou = NULL;

 if((tipus>0) && (tipus<=MAX_CONJUNT))
 {

  PNou = new ENEMIC;
 
  if(PNou == NULL)
  {
   tInvader::~tInvader();
   UnLoadStage1();
   Quit(Motiu0);
  }

  PNou -> Enemic = Conjunts[tipus];
  PNou -> Ruta = Moviments[ruta];
  PNou -> Ruta.EntrarCoordenades(x,y);
  PNou -> tipus = tipus;
  PNou -> x = x;
  PNou -> y = y;
  PNou -> Enemic.ActualitzarCoordenades(x,y);
  PNou -> vol_atacar = ataca;

  if((tipus >= 16)&&(tipus <= MAX_CONJUNT)) // Es enemic terrestre...
  {
   PNou->PSeguent = EnemicsTerrestres;
   EnemicsTerrestres = PNou;
  }
  else // Es enemic Aeri...
  {
   PNou->PSeguent = EnemicsAeris;
   EnemicsAeris = PNou;
  }
 }

}


void tInvader::CrearDispar(int x,int y,int dispar,int direccio,int cua)
{
 byte Motiu0[]={"No tens prou memoria pels dispars.\0"};
 PShots PNou = NULL;

 if((dispar > 6)&&(dispar < 14))
 {
  PNou = new SHOT;

  if(PNou == NULL)
  {
   tInvader::~tInvader();
   UnLoadStage1();
   Quit(Motiu0);
  }

  PNou -> Shot = Objectes[dispar];
  PNou -> Moviment = Moviments[direccio];

  PNou -> x = x;
  PNou -> y = y;

  PNou -> Moviment.EntrarCoordenades(x,y);


  if(cua == CUA_DISPARS_ENEMICS)
  {

   PNou -> PSeguent = EnemyShots;
   EnemyShots = PNou;

  }
  else
  {

   PNou -> PSeguent = MyShots;
   MyShots = PNou;

  }
 }

}

void tInvader::CrearExplosio(int x,int y,int tipus)
{
 byte Motiu0[]={"No tens prou memoria per les explosions.\0"};
 PExplosions PNou = NULL;


  PNou = new EXPLOSIO;

  if(PNou == NULL)
  {
   tInvader::~tInvader();
   UnLoadStage1();
   Quit(Motiu0);
  }

  PNou -> x = x;
  PNou -> y = y;

  PNou -> Explosio = Objectes[tipus];
  
  PNou -> PSeguent = Explosions;
  Explosions = PNou;
  


}

void tInvader::AfegirItem(int x,int y,int tipus,int ruta)
{
 byte Motiu0[]={"No tens prou memoria per els items.\0"};
 PItems PNou = NULL;


  PNou = new ITEM;

  if(PNou == NULL)
  {
   tInvader::~tInvader();
   UnLoadStage1();
   Quit(Motiu0);
  }

  PNou -> x = x;
  PNou -> y = y;

  PNou -> Item = Objectes[tipus];
  PNou -> tipus = tipus;
  PNou -> Moviment = Moviments[ruta];
  PNou -> Moviment.EntrarCoordenades(x,y);

  PNou -> PSeguent = Items;
  Items = PNou;



}



void tInvader::TirarBomba()
{
 if(!(HeTiratBomba)&&Bombes>0)
 {
  HeTiratBomba = CERT;
  //if(SB) start_sound(sonidos[24],24,OFF);

  Bomba = Objectes[ITEM3];
  Bomba.EntrarCoordenades(MyPosX,MyPosY);
  MovBomba = Moviments[ElMeuMoviment(MyPosX,MyPosY,112-4,96-4,16)];
  MovBomba.EntrarCoordenades(MyPosX,MyPosY);
  XBomba=MyPosX;YBomba=MyPosY;

 }
}


void tInvader::InicialitzaNau()
{

 Retard_Dispar = RETARD_DISPAR_INICIAL;
 Retard_Bomba = RETARD_DISPAR_INICIAL;


 Jo = Conjunts[PERSONATGE];
 MyPosY=216; MyPosX=108;

 Jo.AfegirObjecte(Objectes[TURBO],0,16,NO,50);

 MyMov = Moviments[52];
 MyMov.EntrarCoordenades(MyPosX,MyPosY);

 Jo.ActualitzarCoordenades(MyPosX,MyPosY);
// if(SB) start_sound(sonidos[9],9,OFF);

 NauImpactada = FALS;
 EsActiu = CERT;

}

void tInvader::FinalitzarNau()
{

 Retard_Dispar = RETARD_DISPAR_INICIAL;
 Retard_Bomba = RETARD_DISPAR_INICIAL;
 Jo = Conjunts[PERSONATGE];
 Jo.AfegirObjecte(Objectes[TURBO],0,16,NO,50);

 MyMov = Moviments[20];
 MyMov.EntrarCoordenades(MyPosX,MyPosY);

 Jo.ActualitzarCoordenades(MyPosX,MyPosY);
// if(SB) start_sound(sonidos[9],9,OFF);

 NauImpactada = FALS;
 EsActiu = CERT;

}



int tInvader::NauDestruida()
{
 if(NauImpactada)
 {
  NauImpactada = FALS;
  return(CERT);
 }
 else return(FALS);
}


int tInvader::BOSSDESTROYED()
{
 return(BossDestroyed);
}


void tInvader::DestruirNau()
{

// if(SB) start_sound(sonidos[16],16,OFF);
 CrearExplosio(MyPosX-8,MyPosY-8,EXPLOSIO2);

 if(MyPowerUp > 1) MyPowerUp --;
 NauImpactada = CERT;
 EsActiu = FALS;

}

void tInvader::DestruirTot()
{
 int x,y;
 PEnemics PActual,PAnterior;
 PShots   PSActual,PSAnterior;
  


 if((PActual = EnemicsAeris)!=NULL)
 {
  do{

    PActual->Enemic.Reset();

    while(!PActual -> Enemic.ActualEsNul())
    {
     if(Sprites[PActual->Enemic.SpriteActual()].impactable)
     {

      PActual->Enemic.RetornarOffsetActual(&x,&y);

      CrearExplosio(PActual->x+x,PActual->y+y,EXPLOSIO1);
//      if(SB) {start_sound(sonidos[23],23,OFF);}

      Puntuacio +=  PActual->Enemic.ScoreActual();

      PActual->Enemic.EliminarActual();
    
     
     }else PActual -> Enemic.Seguent();
    }

   PActual = PActual -> PSeguent;

  }while(PActual!=NULL);

 }


 if((PActual = EnemicsTerrestres)!=NULL)
 {

  do{

    PActual->Enemic.Reset();

    while(!PActual -> Enemic.ActualEsNul())
    {
     if(Sprites[PActual->Enemic.SpriteActual()].impactable)
     {

      PActual->Enemic.RetornarOffsetActual(&x,&y);

      CrearExplosio(PActual->x+x,PActual->y+y,EXPLOSIO1);
//      if(SB) {start_sound(sonidos[23],23,OFF);}

      Puntuacio +=  PActual->Enemic.ScoreActual();

      PActual->Enemic.EliminarActual();
    
     }else PActual -> Enemic.Seguent();
    }

   PActual = PActual -> PSeguent;

  }while(PActual!=NULL);
 }







 if((PSActual = EnemyShots)!=NULL)
 {
  do{

      PSAnterior = PSActual;

      CrearExplosio(PSAnterior->x,PSAnterior->y,EXPLOSIO1);

      PSActual = PSActual -> PSeguent;

      delete PSAnterior;
    

  }while(PSActual!=NULL);
 }

 EnemyShots = NULL;
 EnemicsAeris = NULL; 


}

void tInvader::DestruirEnemicsAeris()
{
 int x,y;
 PEnemics PActual,PAnterior;
  


 if((PActual = EnemicsAeris)!=NULL)
 {

  do{


    PActual->Enemic.Reset();


    while(!PActual -> Enemic.ActualEsNul())
    {

     if(Sprites[PActual->Enemic.SpriteActual()].impactable)
     {

      PActual->Enemic.RetornarOffsetActual(&x,&y);

      switch(PActual->Enemic.RegaletActual())
      {
       case ITEM1:AfegirItem(PActual->x+x,PActual->y+y,ITEM1,46);
                 CrearExplosio(PActual->x+x,PActual->y+y,METEORIT_DESTRUIT);
  //               if(SB) {start_sound(sonidos[23],23,OFF);}
				 break;

       case ITEM2:CrearExplosio(PActual->x+x,PActual->y+y,METEORIT_DESTRUIT);
 //                if(SB) {start_sound(sonidos[23],23,OFF);}
		   break;
       case ITEM3:AfegirItem(PActual->x+x,PActual->y+y,ITEM3,46);
            
                 CrearExplosio(PActual->x+x,PActual->y+y,METEORIT_DESTRUIT);
//                 if(SB) {start_sound(sonidos[23],23,OFF);}
				 break;

       case BALA3:CrearDispar(PActual->x+8+x,PActual->y+16+y,7,36,CUA_DISPARS_ENEMICS);
                 CrearDispar(PActual->x+8+x,PActual->y+16+y,7,0,CUA_DISPARS_ENEMICS);
                 CrearDispar(PActual->x+8+x,PActual->y+16+y,7,3,CUA_DISPARS_ENEMICS);
                 CrearExplosio(PActual->x+x,PActual->y+y,EXPLOSIO1);
//                 if(SB) {start_sound(sonidos[23],23,OFF);}
				 break;
       default:   CrearExplosio(PActual->x+x,PActual->y+x,EXPLOSIO1);
//                 if(SB) {start_sound(sonidos[23],23,OFF);}
      }

      Puntuacio +=  PActual->Enemic.ScoreActual();

      PActual->Enemic.EliminarActual();
    
     }else PActual -> Enemic.Seguent();



   }


   PActual = PActual->PSeguent;

  }while(PActual!=NULL);

// EnemicsAeris = NULL;

 }



}


void tInvader::DestruirBales()
{
 int x,y;
 PShots   PSActual,PSAnterior;
  

 if((PSActual = EnemyShots)!=NULL)
 {
  do{

      PSAnterior = PSActual;

      CrearExplosio(PSAnterior->x,PSAnterior->y,EXPLOSIO1);

      PSActual = PSActual -> PSeguent;

      delete PSAnterior;
    

  }while(PSActual!=NULL);
 }

 EnemyShots = NULL;


}






int tInvader::Checkit(int x,int y,int power,int dimensio)
{
 int offsetdispar;
 int EX,EY;
 PEnemics  PActual,PAnterior;



 PActual = EnemicsTerrestres;

 while(PActual != NULL)
 {

  PActual->Enemic.Reset();


  while(!PActual->Enemic.ActualEsNul())
  {
	   PActual->Enemic.RetornarOffsetActual(&EX,&EY);

	   if(HiHaInterseccio(PActual->x+EX,PActual->y+EY,x,y,Sprites[PActual->Enemic.SpriteActual()].dimx,dimensio)&&(Sprites[PActual->Enemic.SpriteActual()].impactable))
	   {
		if(!Sprites[PActual->Enemic.SpriteActual()].invencible) {/*if(SB) start_sound(sonidos[18],18,OFF);*/}
		else
		{
		// if(SB) {start_sound(sonidos[14],14,OFF);}
		}

		if(!PActual->Enemic.DecrementarVitalitatActual(power))
		{

		 if((PActual->tipus == BOSS1)&&(PActual->Enemic.PartDebil()))
		 {
			 DestruirTot();// Destruccio Aeris,Terrestres i dispars...
			 SequenciaDestruccioBoss = CERT;
			 XBoss = PActual -> x;
			 YBoss = PActual -> y;

		  //   AventDestruccioBoss();
        
		  //   BossDestroyed = CERT;
		 }
		 else
		 {

		  Puntuacio +=  PActual->Enemic.ScoreActual();

		  PActual->Enemic.EliminarActual();
		  CrearExplosio(PActual->x+EX,PActual->y+EY,EXPLOSIO1);
	//      if(SB) {start_sound(sonidos[23],23,OFF);}

		 }
    
		}
		else
		{
		 offsetdispar = (Sprites[PActual->Enemic.SpriteActual()].dimx % 16) >> 1;

		 if(!PActual->Enemic.ConjuntEsNul())PActual->Enemic.AfegirObjecte(Objectes[IMPACTE],EX - offsetdispar,EY-offsetdispar,0,10);
		}

		return 1;
	   }
	   else PActual->Enemic.Seguent();
	  }

	  PActual = PActual->PSeguent;

 }


 PActual = EnemicsAeris;

 while(PActual != NULL)
 {

  PActual->Enemic.Reset();

  while(!PActual->Enemic.ActualEsNul())
  {
   
   PActual->Enemic.RetornarOffsetActual(&EX,&EY);

   if(HiHaInterseccio(PActual->x+EX,PActual->y+EY,x,y,Sprites[PActual->Enemic.SpriteActual()].dimx,dimensio)&&(Sprites[PActual->Enemic.SpriteActual()].impactable))
   {
    
		if(!Sprites[PActual->Enemic.SpriteActual()].invencible) {/*if(SB) start_sound(sonidos[18],18,OFF);*/}
		else
		{
		// if(SB) {start_sound(sonidos[14],14,OFF);}
		}

		if(!PActual->Enemic.DecrementarVitalitatActual(power))
		{
			 switch(PActual->Enemic.RegaletActual())
			 {
				  case ITEM1:AfegirItem(PActual->x+EX,PActual->y+EY,ITEM1,46);
        
							 CrearExplosio(PActual->x+EX,PActual->y+EY,METEORIT_DESTRUIT);         //if(SB) {start_sound(sonidos[23],23,OFF);}
							 break;
				  case ITEM2:    
							 CrearExplosio(PActual->x+EX,PActual->y+EY,METEORIT_DESTRUIT);         //if(SB) {start_sound(sonidos[23],23,OFF);}
				  break;

				  case ITEM3:AfegirItem(PActual->x+EX,PActual->y+EY,ITEM3,46);

							 CrearExplosio(PActual->x+EX,PActual->y+EY,METEORIT_DESTRUIT);         //if(SB) {start_sound(sonidos[23],23,OFF);}
							 break;

				  case BALA3:CrearDispar(PActual->x+EX+8,PActual->y+EY+16,7,38,CUA_DISPARS_ENEMICS);
							 CrearDispar(PActual->x+EX+8,PActual->y+EY+16,7,0,CUA_DISPARS_ENEMICS);
							 CrearDispar(PActual->x+EX+8,PActual->y+EY+16,7,2,CUA_DISPARS_ENEMICS);
							 CrearExplosio(PActual->x+EX,PActual->y+EY,EXPLOSIO1);//if(SB) {start_sound(sonidos[23],23,OFF);}
							 break;
				  default:   
							 CrearExplosio(PActual->x+EX,PActual->y+EY,EXPLOSIO1);
						   //  if(SB) {start_sound(sonidos[23],23,OFF);}
							 break;
			 }


                 
			 Puntuacio +=  PActual->Enemic.ScoreActual();

			 PActual->Enemic.EliminarActual();



		}
		else
		{

			 offsetdispar = (Sprites[PActual->Enemic.SpriteActual()].dimx % 16) >> 1;


			 if(!PActual->Enemic.ConjuntEsNul())
			 {
				 PActual->Enemic.AfegirObjecte(Objectes[IMPACTE],EX - offsetdispar,EY-offsetdispar,0,10);
			 }

		}

		return (1);


   }
   else
   {
	   PActual->Enemic.Seguent();
   }

  }

  PActual = PActual->PSeguent;
 }

 return (0);
}










void tInvader::Actualitzar() // Checkejat i dibuixat de totes les naus...
{
 int EX,EY;
 int p=FALS;
 int I=FALS;
 int x,y,dispar;
 PEnemics  PActual,PAnterior;
 PShots    PShotActual,PShotAnterior;
 PExplosions PExActual,PExAnterior;
 PItems   PIActual,PIAnterior;

 // Actualitzar Enemics (TERRESTRES I AERIS)... (Si vol dispar� tamb� li donarem la oportunitat.)


 if((PActual = EnemicsTerrestres)!= NULL)
 {

  

  while(PActual != NULL)
  {



  PActual->Enemic.Reset();

  if(!(PActual->Enemic.ConjuntEsNul())&&!(PActual->Ruta.EsNul())&&((PActual->x+Sprites[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->x<=AMPLADA_PANTALLA_JOC+4)&&((PActual->y+Sprites[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->y<=ALTURA_PANTALLA_JOC))
  {

  if(!(SequenciaDestruccioBoss&&PActual->tipus==BOSS1))
  {

   if(PActual->vol_atacar)
   {

    while(!PActual->Enemic.ActualEsNul())
    {
     if(dispar = PActual->Enemic.ActualVolDisparar(&x,&y,PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(Sprites[PActual->Enemic.SpriteActual()].vx)))
     {

      switch(dispar)
      {
       

       case BALA1:CrearDispar(PActual->x+x-4,PActual->y+y-4,BALA_ENEMIC_1,ElMeuMoviment(PActual->x+x+4,PActual->y+y+4,MyPosX,MyPosY,8),CUA_DISPARS_ENEMICS);break;
       case LASER1:CrearDispar(PActual->x+(Sprites[PActual->Enemic.SpriteActual()].dimx>>1)-4,PActual->y+Sprites[PActual->Enemic.SpriteActual()].dimy,BALA_ENEMIC_2,0,CUA_DISPARS_ENEMICS);break;
       case ENEMICD:AfegirEnemic(PActual->x+x-4,PActual->y+y-4,ENEMIC5,49,1); //ElMeuMoviment(PActual->x+x,PActual->y+y,MyPosX,MyPosY,16)
       case ENEMICE:AfegirEnemic(PActual->x+x-4,PActual->y+y-4,ENEMIC5,53,1);break; //ElMeuMoviment(PActual->x+x,PActual->y+y,MyPosX,MyPosY,16)

      }
     }

    PActual->Enemic.Seguent();
    }
     

   }

   

   PActual->Ruta.SeguentPosicio(&(PActual->x),&(PActual->y),MyPosX,MyPosY,Sprites[PActual->Enemic.SpriteActual()].vx,Sprites[PActual->Enemic.SpriteActual()].vy,PActual->Enemic.DimensioMax());
   PActual->Enemic.ActualitzarCoordenades(PActual->x,PActual->y);
   }

   if(!(SequenciaDestruccioBoss && PActual->tipus==BOSS1&&(RetardDestruccioBoss>200)))
   {
    if(!(SequenciaDestruccioBoss&&PActual->tipus==BOSS1&&RetardDestruccioBoss>30))PActual->Enemic.ActualitzarConjunt(PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(Sprites[PActual->Enemic.SpriteActual()].vx));
    PActual->Enemic.EscriureObjectes();
   }
    PActual=PActual->PSeguent;
   

  }
  else
  {


   if(PActual == EnemicsTerrestres)
   {
    EnemicsTerrestres = PActual->PSeguent;
    PAnterior = PActual;
    PActual = PActual -> PSeguent;
   }
   else
   {
    PAnterior = EnemicsTerrestres;
    while(PAnterior->PSeguent != PActual) PAnterior = PAnterior -> PSeguent;
    PAnterior->PSeguent = PActual -> PSeguent;
    PAnterior = PActual;
    PActual = PActual->PSeguent;
   }
   delete PAnterior;
  }
 }
}

 p=FALS;


 if((PActual = EnemicsAeris)!= NULL)
 {

  PActual->Enemic.Reset();

  while(PActual != NULL)
  {

 
/// Aqui peta al 5e cop....
    if(!(PActual->Enemic.ConjuntEsNul())&&!(PActual->Ruta.EsNul())&&((PActual->x+Sprites[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->x<=AMPLADA_PANTALLA_JOC+4)&&((PActual->y+Sprites[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->y<=ALTURA_PANTALLA_JOC)&& !( (p=HiHaInterseccio(MyPosX,MyPosY,PActual->x,PActual->y,16,Sprites[PActual->Enemic.SpriteActual()].dimx)&&!(Jo.EsInvencible())&&EsActiu)) )
    {

 
     if(PActual->vol_atacar)
     {
      while(!PActual->Enemic.ActualEsNul())
      {
        if((dispar = PActual->Enemic.ActualVolDisparar(&x,&y,PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(Sprites[PActual->Enemic.SpriteActual()].vx))) != 0)
        {

         switch(dispar)
         {
       
          case BALA1:CrearDispar(PActual->x+x-4,PActual->y+y-4,7,ElMeuMoviment(PActual->x+x,PActual->y+y,MyPosX,MyPosY,8),CUA_DISPARS_ENEMICS);break;
          case BALA3:CrearDispar(PActual->x+8,PActual->y+16,7,36,CUA_DISPARS_ENEMICS);
                     CrearDispar(PActual->x+8,PActual->y+16,7,0,CUA_DISPARS_ENEMICS);
                     CrearDispar(PActual->x+8,PActual->y+16,7,3,CUA_DISPARS_ENEMICS);break;

         }
        }

       PActual->Enemic.Seguent();
      }
     } 

    PActual->Ruta.SeguentPosicio(&(PActual->x),&(PActual->y),MyPosX,MyPosY,Sprites[PActual->Enemic.SpriteActual()].vx,Sprites[PActual->Enemic.SpriteActual()].vy,PActual->Enemic.DimensioMax());
    PActual->Enemic.ActualitzarCoordenades(PActual->x,PActual->y);
    PActual->Enemic.ActualitzarConjunt(PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(Sprites[PActual->Enemic.SpriteActual()].vx));
    PActual->Enemic.EscriureObjectes();
    PActual=PActual->PSeguent;

   }
   else
   {

    if(p)
    {

     DestruirNau();
     PActual->Enemic.RetornarOffsetActual(&x,&y);

     switch(PActual->Enemic.RegaletActual())
     {
      case ITEM1:AfegirItem(PActual->x+x,PActual->y+y,ITEM1,46);
                 CrearExplosio(PActual->x+x,PActual->y+y,METEORIT_DESTRUIT);
//                 if(SB) {start_sound(sonidos[23],23,OFF);}
				   break;
      case ITEM2:CrearExplosio(PActual->x+x,PActual->y+y,METEORIT_DESTRUIT);
//                 if(SB) {start_sound(sonidos[23],23,OFF);}
				 break;
      case ITEM3:AfegirItem(PActual->x+x,PActual->y+y,ITEM3,0);
                 CrearExplosio(PActual->x+x,PActual->y+y,METEORIT_DESTRUIT);
//                 if(SB) {start_sound(sonidos[23],23,OFF);}
				 break;
      case BALA3:CrearDispar(PActual->x+8+x,PActual->y+16+y,7,36,CUA_DISPARS_ENEMICS);
                 CrearDispar(PActual->x+8+x,PActual->y+16+y,7,0,CUA_DISPARS_ENEMICS);
                 CrearDispar(PActual->x+8+x,PActual->y+16+y,7,3,CUA_DISPARS_ENEMICS);
                 CrearExplosio(PActual->x+x,PActual->y+y,EXPLOSIO1);
 //                if(SB) {start_sound(sonidos[23],23,OFF);}
				 break;

      default:   CrearExplosio(PActual->x+x,PActual->y+y,EXPLOSIO1);
                 //if(SB) {start_sound(sonidos[23],23,OFF);}
		  break;

     }
    }


    if(PActual == EnemicsAeris)
    {
     EnemicsAeris = PActual->PSeguent;
     PAnterior = PActual;
     PActual = PActual -> PSeguent;
    }
    else
    {
     PAnterior = EnemicsAeris;
     while(PAnterior->PSeguent != PActual) PAnterior = PAnterior -> PSeguent;
     PAnterior->PSeguent = PActual -> PSeguent;
     PAnterior = PActual;
     PActual = PActual->PSeguent;
    }

    delete PAnterior;

  

   }
 }
}


 

 // Per tots els nodes, per tots els conjunts i per tots els objectes...

 // Actualitzar (BALES)...

 p=FALS;

 PShotActual = EnemyShots;

  while(PShotActual != NULL)
  {
   if((!PShotActual->Moviment.EsNul())&&((PShotActual->x+Sprites[PShotActual->Shot.SpriteActual()].dimx)>=0)&&(PShotActual->x<=(AMPLADA_PANTALLA_JOC+4))&&((PShotActual->y+Sprites[PShotActual->Shot.SpriteActual()].dimy)>=0)&&(PShotActual->y<=(ALTURA_PANTALLA_JOC+4))&&!(  (p=HiHaInterseccio(MyPosX,MyPosY,PShotActual->x,PShotActual->y,16,Sprites[PShotActual->Shot.SpriteActual()].dimx)&&!(Jo.EsInvencible())&&EsActiu)))
   {

    PShotActual -> Moviment.SeguentPosicio(&(PShotActual->x),&(PShotActual->y),MyPosX,MyPosY,Sprites[PShotActual->Shot.SpriteActual()].vx,Sprites[PShotActual->Shot.SpriteActual()].vy,Sprites[PShotActual->Shot.SpriteActual()].dimx);
    PShotActual -> Shot.ActualitzarCoordenades(PShotActual->x,PShotActual->y);
    PShotActual -> Shot.EscriureActual();
    PShotActual -> Shot.SeguentFrame(0,0);

    PShotActual = PShotActual -> PSeguent;
   }
   else
   {

    if(p)
    {

     DestruirNau();

     CrearExplosio(PShotActual->x,PShotActual->y,EXPLOSIO1);
            
    }

   if(PShotActual == EnemyShots)
   {
    EnemyShots = PShotActual->PSeguent;

    PShotAnterior = PShotActual;

    PShotActual = PShotActual -> PSeguent;
   }
   else
   {
    PShotAnterior = EnemyShots;

    while(PShotAnterior->PSeguent != PShotActual) PShotAnterior = PShotAnterior -> PSeguent;

    PShotAnterior->PSeguent = PShotActual -> PSeguent;

    PShotAnterior = PShotActual;
    PShotActual = PShotActual->PSeguent;
   }
   delete PShotAnterior;

   }
  }
  



if(SequenciaDestruccioBoss)
{
 if(RetardDestruccioBoss < 500)
 {
  if(RetardDestruccioBoss < 400)
  {
   if(RetardDestruccioBoss % 20 == 0)
   {
    CrearExplosio(rand()%64+XBoss,rand()%64+YBoss,EXPLOSIO2);
//    if(SB) start_sound(sonidos[16],16,OFF);
   }
  }
  if(RetardDestruccioBoss == 499) FinalitzarNau();
 }
 else
 {
  if(RetardFiNau < 100)
  {

   RetardFiNau ++;
  }
  else BossDestroyed = CERT;

 }RetardDestruccioBoss++;
}


 PShotActual = MyShots;

  
 while(PShotActual != NULL)
 {
 
	 if((!PShotActual->Moviment.EsNul())&&((PShotActual->x+Sprites[PShotActual->Shot.SpriteActual()].dimx)>=0)&&(PShotActual->x<=(AMPLADA_PANTALLA_JOC+4))&&((PShotActual->y+Sprites[PShotActual->Shot.SpriteActual()].dimy)>=0)&&(PShotActual->y<=(ALTURA_PANTALLA_JOC+4))&&!(I=Checkit(PShotActual->x,PShotActual->y,PShotActual->Shot.Power(),Sprites[PShotActual->Shot.SpriteActual()].dimx)))
   	 {
			PShotActual -> Moviment.SeguentPosicio(&(PShotActual->x),&(PShotActual->y),MyPosX,MyPosY,Sprites[PShotActual->Shot.SpriteActual()].vx,Sprites[PShotActual->Shot.SpriteActual()].vy,Sprites[PShotActual->Shot.SpriteActual()].dimx);
			PShotActual -> Shot.ActualitzarCoordenades(PShotActual->x,PShotActual->y);
			PShotActual -> Shot.SeguentFrame(0,0);
			PShotActual -> Shot.EscriureActual();

			PShotActual = PShotActual -> PSeguent;
	 }
	 else // El meu dispar ha xoxat -> S'ha de borrar.
	 {

		   if(PShotActual == MyShots)
		   {
				MyShots = PShotActual -> PSeguent;
				PShotAnterior = PShotActual;
				PShotActual = PShotActual -> PSeguent;
		   }
		   else
		   {

				PShotAnterior = MyShots;

				while(PShotAnterior->PSeguent != PShotActual) PShotAnterior = PShotAnterior -> PSeguent;

				PShotAnterior->PSeguent = PShotActual -> PSeguent;
				PShotAnterior = PShotActual;
				PShotActual = PShotActual->PSeguent;
			}
			delete PShotAnterior;

	}
  }
 



 p=FALS;

 // Per tots els nodes, per tots els objectes...

 // Actualitzar (ITEMS)...


 PIActual = Items;

  while(PIActual != NULL)
  {
   if((!PIActual->Moviment.EsNul())&&((PIActual->x+Sprites[PIActual->Item.SpriteActual()].dimx)>=0)&&(PIActual->x<=(AMPLADA_PANTALLA_JOC+4))&&((PIActual->y+Sprites[PIActual->Item.SpriteActual()].dimy)>=0)&&(PIActual->y<=(ALTURA_PANTALLA_JOC+4))&&!(  (p=HiHaInterseccio(MyPosX,MyPosY,PIActual->x,PIActual->y,16,Sprites[PIActual->Item.SpriteActual()].dimx))&&EsActiu) )
   {

    PIActual -> Moviment.SeguentPosicio(&(PIActual->x),&(PIActual->y),MyPosX,MyPosY,Sprites[PIActual->Item.SpriteActual()].vx,Sprites[PIActual->Item.SpriteActual()].vy,Sprites[PIActual->Item.SpriteActual()].dimx);
    PIActual -> Item.ActualitzarCoordenades(PIActual->x,PIActual->y);
    PIActual -> Item.EscriureActual();
    PIActual -> Item.SeguentFrame(0,0);

    PIActual = PIActual -> PSeguent;
   }
   else
   {
    if(p)
    {
     switch(PIActual->tipus)
     {
      case ITEM1:/*if(SB) start_sound(sonidos[20],20,OFF);*/if(MyPowerUp<MAX_POWERUP) MyPowerUp++;break;
      case ITEM3://if(SB) start_sound(sonidos[25],25,OFF);
                 if(Bombes<MAX_BOMBERS) Bombes++;break;

     
     }
    }

   if(PIActual == Items)
   {
    Items = PIActual->PSeguent;
    PIAnterior = PIActual;
    PIActual = PIActual -> PSeguent;
   }
   else
   {
    PIAnterior = Items;
    while(PIAnterior->PSeguent != PIActual) PIAnterior = PIAnterior -> PSeguent;
    PIAnterior->PSeguent = PIActual -> PSeguent;
    PIAnterior = PIActual;
    PIActual = PIActual->PSeguent;
   }
   delete PIAnterior;

   }
  }
 



 // Per tots els nodes, per tots els objectes...


 // Actualitzar (EXPLOSIONS)...

 PExActual = Explosions;

 while(PExActual != NULL)
 {

  if(!PExActual -> Explosio.ActualEsNul())
  {
   PExActual -> Explosio.ActualitzarCoordenades(PExActual->x,PExActual->y);
   PExActual -> Explosio.EscriureActual();
   PExActual -> Explosio.SeguentFrame(0,0);
   PExActual = PExActual -> PSeguent;
  }
  else
  {
   if(PExActual == Explosions)
   {
    Explosions = PExActual->PSeguent;
    PExAnterior = PExActual;
    PExActual = PExActual -> PSeguent;
   }
   else
   {
    PExAnterior = Explosions;
    while(PExAnterior->PSeguent != PExActual) PExAnterior = PExAnterior -> PSeguent;
    PExAnterior->PSeguent = PExActual -> PSeguent;
    PExAnterior = PExActual;
    PExActual = PExActual->PSeguent;
   }
   delete PExAnterior;
  }


 }


 if(HeTiratBomba)
 {
  if((XBomba>(112-25))&&(YBomba>(96-25))&&(XBomba<(112+25))&&(YBomba<(96+25)))
  {
   if(!ImpacteBomba)
   {
    Bomba = Objectes[IMPACTE_BOMBA];
//  if(SB)  start_sound(sonidos[15],15,OFF);
    DestruirBales();

    DestruirEnemicsAeris();
    ImpacteBomba = CERT;
   }
   else
   {
    
    if(!Bomba.ActualEsNul())
    {
     Bomba.SeguentFrame(0,0);Bomba.EscriureActual();
    }
    else{  HeTiratBomba = FALS;ImpacteBomba = FALS;}
    
   }

  }
  else
  {
  
   Bomba.ActualitzarCoordenades(XBomba,YBomba);
   Bomba.EscriureActual();
   
   MovBomba.SeguentPosicio(&XBomba,&YBomba,0,0,3,3,16);
  }

 }



 // Per tots els nodes, per tots els objectes...

 // Actualitzar-me...

if(EsActiu)
{
 if(RetardDestruccioBoss<500)
 {
  if(MyMov.MovimentsActuals()<36) MyMov.SeguentPosicio(&MyPosX,&MyPosY,0,0,1,1,16);
  else MyMov.SeguentPosicio(&MyPosX,&MyPosY,0,0,MySpeedUp,MySpeedUp,16);
 }
 else MyMov.SeguentPosicio(&MyPosX,&MyPosY,0,0,4,4,16);




 if(TECLA_DISPAR &&(Retard_Dispar <= 0))
 {

  switch(MyPowerUp)
  {
   case 1://if(SB) start_sound(sonidos[17],17,OFF);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_1,20,1);break;
   case 2://if(SB) start_sound(sonidos[17],17,OFF);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_1,20,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_2,18,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_2,22,1);break;
   case 3://if(SB) start_sound(sonidos[10],10,OFF);
          CrearDispar(MyPosX,MyPosY,LA_MEVA_BALA_3,20,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_2,18,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_2,22,1);break;
   case 4://if(SB) start_sound(sonidos[10],10,OFF);
          CrearDispar(MyPosX,MyPosY,LA_MEVA_BALA_3,20,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_4,18,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_4,22,1);break;
   case 5://if(SB) start_sound(sonidos[19],19,OFF);
          CrearDispar(MyPosX,MyPosY,LA_MEVA_BALA_3,20,1);
          CrearDispar(MyPosX,MyPosY-4,LA_MEVA_BALA_5,20,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_4,18,1);
          CrearDispar(MyPosX+4,MyPosY,LA_MEVA_BALA_4,22,1);break;



  }

  Retard_Dispar=RETARD_DEL_MEU_DISPAR;
 }
 else  if(Retard_Dispar>0)Retard_Dispar--;
 
 if(TECLA_BOMBA&&!(HeTiratBomba)&&Retard_Bomba<=0&&Bombes>0)
 {
   TirarBomba();
   Bombes--;
   Retard_Bomba = RETARD_BOMBA;
 }
 else if(Retard_Bomba>0)Retard_Bomba--;

 
 Jo.ActualitzarCoordenades(MyPosX,MyPosY);
 Jo.ActualitzarConjunt(0,0);
 Jo.EscriureObjectes();

}

}



















tInvader::~tInvader()
{
 PShots PActualS,PAnteriorS;
 PEnemics PActualE,PAnteriorE;
 PItems PActualI,PAnteriorI;
 PExplosions PActualEx,PAnteriorEx;



 // Nodes AERIS

 if((PActualE = EnemicsAeris)!= NULL)
 {
  do{

   PAnteriorE = PActualE;
   PActualE = PActualE -> PSeguent;
   delete PAnteriorE;

  }while(PActualE != NULL);

 }


 // Nodes TERRESTRES

 if((PActualE = EnemicsTerrestres)!= NULL)
 {
  do{

   PAnteriorE = PActualE;
   PActualE = PActualE -> PSeguent;
   delete PAnteriorE;

  }while(PActualE != NULL);

 }


 // Nodes ITEMS

 if((PActualI = Items)!= NULL)
 {
  do{

   PAnteriorI = PActualI;
   PActualI = PActualI -> PSeguent;
   delete PAnteriorI;

  }while(PActualI != NULL);

 }

 // Nodes DISPARS ENEMICS

 if((PActualS = EnemyShots)!= NULL)
 {
  do{

   PAnteriorS = PActualS;
   PActualS = PActualS -> PSeguent;
   delete PAnteriorS;

  }while(PActualS != NULL);

 }

 // Nodes ELS MEUS DISPARS

 if((PActualS = MyShots)!= NULL)
 {
  do{

   PAnteriorS = PActualS;
   PActualS = PActualS -> PSeguent;
   delete PAnteriorS;

  }while(PActualS != NULL);

 }


 // Nodes EXPLOSIONS

 if((PActualEx = Explosions)!= NULL)
 {
  do{

   PAnteriorEx = PActualEx;
   PActualEx = PActualEx -> PSeguent;
   delete PAnteriorEx;

  }while(PActualEx != NULL);

 }

 Items = NULL;
 EnemyShots = NULL;
 Explosions = NULL;
 MyShots = NULL;
 EnemicsTerrestres = EnemicsAeris = NULL;

}




