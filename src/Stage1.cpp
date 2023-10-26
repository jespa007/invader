#include "Invader.h"

#define INVADER_STAGE1_TILEMAP_WIDTH   7  
#define INVADER_STAGE1_TILEMAP_HEIGHT  77

void Stage1::load(){
    // load tilemap...
    short tiles[INVADER_STAGE1_TILEMAP_HEIGHT*INVADER_STAGE1_TILEMAP_WIDTH] = {
        47,47,47,47,47,47,47,  //
        47,47,47,47,47,47,47,  //  1 PANTALLA!!!
        47,47,47,47,47,47,47,  //
        47,47,47,47,47,47,47,  //
        47,47,47,47,47,47,47,  //
        47,47,47,47,47,47,47,  //
        47,47,47,47,47,47,47,  // Zona Boss !

        47,47,47,47,47,47,47,  
        37,37,37,37,37,37,37,
        37,37,37,37,37,37,37,
        37,37,37,37,37,37,37,
        37,37,37,37,37,37,37,
        37,37,37,37,37,37,37,
        37,37,37,37,37,37,37,

        38,37,37,37,38,37,37,
        40,37,39,37,37,37,37,
        39,38,39,40,39,38,40,
        37,40,39,37,40,38,37,
        37,39,42,38,37,37,37,
        37,40,39,39,37,39,37,  
        39,38,37,40,39,38,40,

        40,38,39,38,37,39,37,
        38,37,37,37,38,37,37,
        37,38,39,37,37,37,37,
        37,37,37,37,37,37,37,
        37,62,63,64,65,66,37,   
        55,56,57,58,59,60,61,
        48,49,50,51,52,53,54,  

        36,36,36,36,36,36,36,
        36,36,36,36,36,36,36,
        34,36,36,36,33,36,36,
        36,36,34,36,36,34,36,
        36,36,36,36,36,36,36,
        36,36,36,36,36,36,36,
        33,36,36,36,36,36,36,

        36,33,36,34,36,36,36,
        34,33,36,35,36,36,33,
        36,35,36,36,36,36,36,
        36,36,36,36,36,36,36,
        35,36,36,36,36,36,36,
        33,35,33,36,33,36,36,
        36,35,36,35,33,36,36,

        36,33,36,34,36,36,36,
        34,33,36,35,36,36,33,
        36,35,36,36,36,36,36,
        36,36,36,36,36,36,36,
        35,36,36,36,36,36,36,
        33,35,33,36,33,36,36,
        36,35,36,35,33,36,36,

        14,15,16,17,18,19,20,
        21,22,23,24,25,26,27,
        37,28,29,30,31,32,37,   // La lluna la pruna,Vestida de dol...
        37,40,39,39,37,39,37,  
        39,38,37,40,39,38,40,
        37,38,40,37,37,37,37,
        37,37,39,37,37,37,37,



        38,37,37,37,38,37,37,
        40,37,39,37,37,37,37,
        39,38,39,40,39,38,40,
        37,40,39,37,40,38,37,
        37,39,40,38,37,37,37,
        37,40,39,39,37,39,37,  
        39,38,37,40,39,38,40,

        39,37,40,37,37,37,37,
        37,37,37,37,37,37,37,
        37,37,38,39,38,37,37,
        37,37,37,38,37,40,37,
        37,37,37,37,38,37,37,
        39,38,37,40,39,38,40,
        38,39,40,40,40,39,38,

        37,40,38,40,37,37,37,
        37,39,37,38,37,37,37,
        37,38,39,40,37,37,37,
        37,37,37,38,37,40,37,
        39,38,37,40,39,38,40,
        0,1,2,3,4,5,6,        // Planeta Terra...
        7,8,9,10,11,12,13
    };              


     /* from block 48 and upper are inverted */
    for(k=48;k<MAX_BLOCS;k++)
    {

        for(j=0;j<=((AMPLADA_BLOC)*(AMPLADA_BLOC)-1);j++)
        Blocs[k][j] = Blocs[k-48+14][BLOCINVERS[j]];
     }
     // may be an special flag the flips horizontally, or set properties for blocs or hardcode flip the image 

     



    tilemap=new Tilemap();

    tilemap->setup(
        Image::get("BLOCK1.RAW")
        ,tiles
        ,INVADER_STAGE1_TILEMAP_WIDTH
        ,INVADER_STAGE1_TILEMAP_HEIGHT
        ,INVADER_TILE_WIDTH
        ,INVADER_TILE_HEIGHT
    );

    // load entitites
 entities[0].impactable = NO;
  entities[0].invencible = NO;
  entities[0].agresiu = NO;
  entities[0].retard_dispar = 0;
  entities[0].vx = entities[0].vy = 2;
  entities[0].dimx = entities[0].dimy = 8;
  
  entities[1].impactable = NO;
  entities[1].invencible = NO;
  entities[1].agresiu = NO;
  entities[1].retard_dispar = 0;
  entities[1].vx = entities[1].vy = 2;
  entities[1].dimx = entities[1].dimy = 8;
  
  entities[2].impactable = NO;
  entities[2].invencible = NO;
  entities[2].agresiu = NO;
  entities[2].retard_dispar = 0;
  entities[2].vx = entities[2].vy = 4;
  entities[2].dimx = entities[2].dimy = 8;

  entities[3].impactable = NO;
  entities[3].invencible = NO;
  entities[3].agresiu = NO;
  entities[3].retard_dispar = 0;
  entities[3].vx = entities[3].vy = 4;
  entities[3].dimx = entities[3].dimy = 8;

  entities[4].impactable = SI;
  entities[4].invencible = NO;
  entities[4].agresiu = NO;
  entities[4].retard_dispar = 0;
  entities[4].vx = entities[4].vy = 1;
  entities[4].dimx = entities[4].dimy = 8;

  for(i=5;i<17;i++)
  {
   entities[i].impactable = NO;
   entities[i].invencible = NO;
   entities[i].agresiu = NO;
   entities[i].retard_dispar = 0;
   entities[i].vx = entities[i].vy = 0;
   entities[i].dimx = entities[i].dimy = 8;
  }


  entities[17].impactable = NO;
  entities[17].invencible = NO;
  entities[17].agresiu = NO;
  entities[17].retard_dispar = 0;
  entities[17].vx = entities[17].vy = 4;
  entities[17].dimx = entities[17].dimy = 16;

  entities[18].impactable = NO;
  entities[18].invencible = NO;
  entities[18].agresiu = NO;
  entities[18].retard_dispar = 0;
  entities[18].vx = entities[18].vy = 4;
  entities[18].dimx = entities[18].dimy = 16;

  entities[19].impactable = NO;
  entities[19].invencible = NO;
  entities[19].agresiu = NO;
  entities[19].retard_dispar = 0;
  entities[19].vx = entities[19].vy = 4;
  entities[19].dimx = entities[19].dimy = 16;

  entities[20].impactable = NO;
  entities[20].invencible = NO;
  entities[20].agresiu = NO;
  entities[20].retard_dispar = 0;
  entities[20].vx = entities[20].vy = 4;
  entities[20].dimx = entities[20].dimy = 16;


 for(i=21;i<28;i++)
 {
  entities[i].impactable = NO;
  entities[i].invencible = NO;
  entities[i].agresiu = NO;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 0;
  entities[i].dimx = entities[i].dimy = 16;
 }

 // La meva nau...
 
 for(i=28;i<30;i++)
 {

  entities[i].impactable = SI;
  entities[i].invencible = NO;
  entities[i].agresiu = SI;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 2;
  entities[i].dimx = entities[i].dimy = 16;

 }

 for(i=30;i<33;i++)
 {
  entities[i].impactable = NO;
  entities[i].invencible = NO;
  entities[i].agresiu = NO;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 0;
  entities[i].dimx = entities[i].dimy = 16;
 }


  entities[33].impactable = SI;
  entities[33].invencible = NO;
  entities[33].agresiu = NO;
  entities[33].retard_dispar = 0;
  entities[33].vx = entities[33].vy = 1;
  entities[33].dimx = entities[33].dimy = 16;


  entities[34].impactable = NO;
  entities[34].invencible = NO;
  entities[34].agresiu = NO;
  entities[34].retard_dispar = 0;
  entities[34].vx = entities[34].vy = 0;
  entities[34].dimx = entities[34].dimy = 16;


  entities[35].impactable = SI;
  entities[35].invencible = NO;
  entities[35].agresiu = NO;
  entities[35].retard_dispar = 0;
  entities[35].vx = entities[35].vy = 1;
  entities[35].dimx = entities[35].dimy = 16;


  entities[36].impactable = NO;
  entities[36].invencible = NO;
  entities[36].agresiu = NO;
  entities[36].retard_dispar = 0;
  entities[36].vx = entities[36].vy = 0;
  entities[36].dimx = entities[36].dimy = 16;


 for(i=36;i<40;i++)
 {
  entities[i].impactable = NO;
  entities[i].invencible = NO;
  entities[i].agresiu = NO;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 1;
  entities[i].dimx = entities[i].dimy = 16;
 }


 for(i=40;i<43;i++)
 {
  entities[i].impactable = SI;
  entities[i].invencible = NO;
  entities[i].agresiu = BALA1;
  entities[i].retard_dispar = 100;
  entities[i].vx = entities[i].vy = 1;
  entities[i].dimx = entities[i].dimy = 16;
 }

 
  entities[43].impactable = SI;
  entities[43].invencible = NO;
  entities[43].agresiu = NO;
  entities[43].retard_dispar = 0;
  entities[43].vx = entities[43].vy = 2;
  entities[43].dimx = entities[43].dimy = 16;


  entities[44].impactable = SI;
  entities[44].invencible = NO;
  entities[44].agresiu = NO;
  entities[44].retard_dispar = 0;
  entities[44].vx = entities[44].vy = 2;
  entities[44].dimx = entities[44].dimy = 16;


  entities[45].impactable = SI;
  entities[45].invencible = NO;
  entities[45].agresiu = BALA3;
  entities[45].retard_dispar = SEGUENT_POSICIO_AMB_TRANSICIO_Y;
  entities[45].vx = entities[45].vy = 2;
  entities[45].dimx = entities[45].dimy = 16;


  entities[46].impactable = SI;
  entities[46].invencible = SI;
  entities[46].agresiu = NO;
  entities[46].retard_dispar = 0;
  entities[46].vx = entities[46].vy = 2;
  entities[46].dimx = entities[46].dimy = 16;

  entities[47].impactable = SI;
  entities[47].invencible = NO;
  entities[47].agresiu = NO;
  entities[47].retard_dispar = 0;
  entities[47].vx = entities[47].vy = 0;
  entities[47].dimx = entities[47].dimy = 16;

  entities[48].impactable = SI;
  entities[48].invencible = NO;
  entities[48].agresiu = BALA1;
  entities[48].retard_dispar = 9;
  entities[48].vx = entities[48].vy = 0;
  entities[48].dimx = entities[48].dimy = 16;

for(i=49;i<53;i++)
{
  entities[i].impactable = SI;
  entities[i].invencible = NO;
  entities[i].agresiu = NO;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 2;
  entities[i].dimx = entities[i].dimy = 16;
}


  entities[53].impactable = SI;
  entities[53].invencible = NO;
  entities[53].agresiu = NO;
  entities[53].retard_dispar = 0;
  entities[53].vx = entities[53].vy = 2;
  entities[53].dimx = entities[53].dimy = 16;


  entities[54].impactable = SI;
  entities[54].invencible = NO;
  entities[54].agresiu = NO;
  entities[54].retard_dispar = 0;
  entities[54].vx = entities[54].vy = 1;
  entities[54].dimx = entities[54].dimy = 16;

  entities[55].impactable = SI;
  entities[55].invencible = NO;
  entities[55].agresiu = BALA1;
  entities[55].retard_dispar = 0;
  entities[55].vx = entities[55].vy = 0;
  entities[55].dimx = entities[55].dimy = 16;

  entities[56].impactable = SI;
  entities[56].invencible = NO;
  entities[56].agresiu = NO;
  entities[56].retard_dispar = 0;
  entities[56].vx = entities[56].vy = 1;
  entities[56].dimx = entities[56].dimy = 16;


  entities[57].impactable = SI;
  entities[57].invencible = NO;
  entities[57].agresiu = NO;
  entities[57].retard_dispar = 0;
  entities[57].vx = entities[57].vy = 2;
  entities[57].dimx = entities[57].dimy = 16;

  entities[58].impactable = SI;      // BOLA 1...
  entities[58].invencible = NO;
  entities[58].agresiu = BALA1;
  entities[58].retard_dispar = 100;
  entities[58].vx = entities[58].vy = 2;
  entities[58].dimx = entities[58].dimy = 16;

  entities[59].impactable = SI;      // BOLA 2...
  entities[59].invencible = NO;
  entities[59].agresiu = BALA1;
  entities[59].retard_dispar = 100;
  entities[59].vx = entities[59].vy = 2;
  entities[59].dimx = entities[59].dimy = 16;

  entities[60].impactable = SI;       // ENEMIC 7
  entities[60].invencible = NO;
  entities[60].agresiu = BALA1;
  entities[60].retard_dispar = 100;
  entities[60].vx = entities[60].vy = 1;
  entities[60].dimx = entities[60].dimy = 16;


  entities[61].impactable = SI;
  entities[61].invencible = NO;
  entities[61].agresiu = BALA1;
  entities[61].retard_dispar = 100;
  entities[61].vx = entities[61].vy = 1;
  entities[61].dimx = entities[61].dimy = 16;


  entities[62].impactable = SI;
  entities[62].invencible = NO;
  entities[62].agresiu = BALA1;
  entities[62].retard_dispar = 100;
  entities[62].vx = entities[62].vy = 1;
  entities[62].dimx = entities[62].dimy = 16;


  entities[63].impactable = SI;
  entities[63].invencible = NO;
  entities[63].agresiu = BALA1;
  entities[63].retard_dispar = 100;
  entities[63].vx = entities[63].vy = 1;
  entities[63].dimx = entities[63].dimy = 16;


  entities[64].impactable = SI;    // TORRETA
  entities[64].invencible = NO;
  entities[64].agresiu = BALA1;
  entities[64].retard_dispar = 80;
  entities[64].vx = entities[64].vy = 1;
  entities[64].dimx = entities[64].dimy = 16;


  entities[65].impactable = SI;     // PERSEGUIDOR
  entities[65].invencible = NO;
  entities[65].agresiu = BALA1;
  entities[65].retard_dispar = 100;
  entities[65].vx = entities[65].vy = 1;
  entities[65].dimx = entities[65].dimy = 16;


  entities[66].impactable = SI;
  entities[66].invencible = NO;
  entities[66].agresiu = LASER1;
  entities[66].retard_dispar = RETARD_DISPAR >> dificultat;
  entities[66].vx = entities[66].vy = 2;
  entities[66].dimx = entities[66].dimy = 16;


  entities[67].impactable = SI;
  entities[67].invencible = NO;
  entities[67].agresiu = SI;
  entities[67].retard_dispar = 10;
  entities[67].vx = entities[67].vy = 2;
  entities[67].dimx = entities[67].dimy = 16;


  entities[68].impactable = SI;
  entities[68].invencible = SI;
  entities[68].agresiu = NO;
  entities[68].retard_dispar = 0;
  entities[68].vx = entities[68].vy = 1;
  entities[68].dimx = entities[68].dimy = 16;



  entities[69].impactable = SI;
  entities[69].invencible = SI;
  entities[69].agresiu = NO;
  entities[69].retard_dispar = 0;
  entities[69].vx = entities[69].vy = 1;
  entities[69].dimx = entities[69].dimy = 16;


  entities[70].impactable = SI;
  entities[70].invencible = SI;
  entities[70].agresiu = NO;
  entities[70].retard_dispar = 0;
  entities[70].vx = entities[70].vy = 1;
  entities[70].dimx = entities[70].dimy = 16;

  entities[71].impactable = SI;
  entities[71].invencible = NO;
  entities[71].agresiu = BALA1;
  entities[71].retard_dispar = 14;
  entities[71].vx = entities[71].vy = 1;
  entities[71].dimx = entities[71].dimy = 16;


  entities[72].impactable = SI;
  entities[72].invencible = NO;
  entities[72].agresiu = BALA1;
  entities[72].retard_dispar = RETARD_DISPAR >> dificultat;
  entities[72].vx = entities[72].vy = 1;
  entities[72].dimx = entities[72].dimy = 16;

 for(i=73;i<77;i++)
 {
  entities[i].impactable = NO;
  entities[i].invencible = NO;
  entities[i].agresiu = NO;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 1;
  entities[i].dimx = entities[i].dimy = 16;
 }

  entities[77].impactable = NO;
  entities[77].invencible = NO;
  entities[77].agresiu = ENEMICD;
  entities[77].retard_dispar = 24;
  entities[77].vx = entities[77].vy = 1;
  entities[77].dimx = entities[77].dimy = 16;



 for(i=78;i<82;i++)
 {
  entities[i].impactable = NO;
  entities[i].invencible = NO;
  entities[i].agresiu = NO;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 1;
  entities[i].dimx = entities[i].dimy = 16;
 }

  entities[82].impactable = NO;
  entities[82].invencible = NO;
  entities[82].agresiu = ENEMICE;
  entities[82].retard_dispar = 24;
  entities[82].vx = entities[82].vy = 1;
  entities[82].dimx = entities[82].dimy = 16;


  entities[83].impactable = NO;
  entities[83].invencible = NO;
  entities[83].agresiu = NO;
  entities[83].retard_dispar = 0;
  entities[83].vx = entities[83].vy = 4;
  entities[83].dimx = entities[83].dimy = 16;

// entities 32 X 32

for(i=84;i<88;i++)
{
  entities[i].impactable = NO;
  entities[i].invencible = NO;
  entities[i].agresiu = NO;
  entities[i].retard_dispar = 0;
  entities[i].vx = entities[i].vy = 0;
  entities[i].dimx = entities[i].dimy = 32;
}

  entities[88].impactable = SI;
  entities[88].invencible = NO;
  entities[88].agresiu = LASER2;
  entities[88].retard_dispar = 10;
  entities[88].vx = entities[88].vy = 4;
  entities[88].dimx = entities[88].dimy = 32;

// entities 64 X 64

  entities[89].impactable = NO;
  entities[89].invencible = NO;
  entities[89].agresiu = LASER1;
  entities[89].retard_dispar = 100;
  entities[89].vx = entities[89].vy = 1;
  entities[89].dimx = entities[89].dimy = 64;


  for(i=0;i<MAX_SPRITES;i++) entities[i].imatge = (tImatge) (Imatges[i]+2);


 // Inicialitzem Objectes...




  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+7,5,SI);
  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+8,5,SI);
  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+9,5,SI);
  Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+10,5,SI);


  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16,5,SI);
  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+1,5,SI);
  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+2,5,SI);
  Objectes[EXPLOSIO2].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+3,5,SI);
  Objectes[ENEMIC_1].EntrarDades(10<<dificultat,150,0,0);

  Objectes[TURBO].AfegirFrame(1,MAX_SPR_8X8+14,5,NO);
  Objectes[TURBO].AfegirFrame(1,MAX_SPR_8X8+15,5,NO);


  Objectes[IMPACTE].AfegirFrame(1,MAX_SPR_8X8+4,5,NO);
  Objectes[IMPACTE].AfegirFrame(1,MAX_SPR_8X8+5,5,NO);
  Objectes[IMPACTE].AfegirFrame(1,MAX_SPR_8X8+6,5,SI);

  Objectes[IMPACTE_BOMBA].AfegirFrame(1,MAX_SPR_8X8+2,10,NO);
  Objectes[IMPACTE_BOMBA].AfegirFrame(1,MAX_SPR_8X8+5,10,NO);
  Objectes[IMPACTE_BOMBA].AfegirFrame(1,MAX_SPR_8X8+6,10,SI);



  Objectes[ITEM1].AfegirFrame(1,MAX_SPR_8X8+20,0,NO);
  Objectes[ITEM2].AfegirFrame(1,MAX_SPR_8X8+21,0,NO);
  Objectes[ITEM3].AfegirFrame(1,MAX_SPR_8X8+22,0,NO);


  Objectes[BALA_ENEMIC_1].AfegirFrame(1,0,5,NO);
  Objectes[BALA_ENEMIC_1].AfegirFrame(1,1,5,NO);


  Objectes[BALA_ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+66,0,NO);

  Objectes[LA_MEVA_BALA_1].AfegirFrame(1,2,0,NO);
  Objectes[LA_MEVA_BALA_1].EntrarDades(10,150,0,0);

  Objectes[LA_MEVA_BALA_2].AfegirFrame(1,3,0,NO);
  Objectes[LA_MEVA_BALA_2].EntrarDades(10,150,0,0);

  Objectes[LA_MEVA_BALA_3].AfegirFrame(1,MAX_SPR_8X8,0,NO);
  Objectes[LA_MEVA_BALA_3].EntrarDades(20,0,0,0);


  Objectes[LA_MEVA_BALA_4].AfegirFrame(1,3,12,NO);
  Objectes[LA_MEVA_BALA_4].AfegirFrame(1,MAX_SPR_8X8+2,12,NO);
  Objectes[LA_MEVA_BALA_4].AfegirFrame(1,MAX_SPR_8X8+3,INFINIT,NO);
  Objectes[LA_MEVA_BALA_4].EntrarDades(25,0,0,0);

  Objectes[LA_MEVA_BALA_5].AfegirFrame(1,MAX_SPR_8X8+1,0,NO);
  Objectes[LA_MEVA_BALA_5].EntrarDades(20,0,0,0);


  Objectes[_PERSONATGE].AfegirFrame(0,MAX_SPR_8X8+11,0,NO);
  Objectes[_PERSONATGE].AfegirFrame(1,MAX_SPR_8X8+12,0,NO);
  Objectes[_PERSONATGE].AfegirFrame(2,MAX_SPR_8X8+13,0,NO);
  Objectes[_PERSONATGE].EntrarDades(2,0,0,200);


  Objectes[_CAIXA1].AfegirFrame(1,MAX_SPR_8X8+16,0,NO);
  Objectes[_CAIXA2].AfegirFrame(1,MAX_SPR_8X8+16,0,NO);
  Objectes[_CAIXA3].AfegirFrame(1,MAX_SPR_8X8+16,0,NO);

  Objectes[CAIXA_DESTRUIDA].AfegirFrame(1,MAX_SPR_8X8+17,2,SI);

  Objectes[_METEORIT1].AfegirFrame(1,MAX_SPR_8X8+18,0,NO);
  Objectes[_METEORIT1].EntrarDades(10<<dificultat,100,ITEM1,0);

  Objectes[_METEORIT2].AfegirFrame(1,MAX_SPR_8X8+18,0,NO);
  Objectes[_METEORIT2].EntrarDades(10<<dificultat,100,ITEM2,0);

  Objectes[_METEORIT3].AfegirFrame(1,MAX_SPR_8X8+18,0,NO);
  Objectes[_METEORIT3].EntrarDades(10<<dificultat,100,ITEM3,0);

  Objectes[METEORIT_DESTRUIT].AfegirFrame(1,MAX_SPR_8X8+19,5,SI);

  Objectes[ENEMIC_1].AfegirFrame(0,MAX_SPR_8X8+23,10,NO);
  Objectes[ENEMIC_1].AfegirFrame(1,MAX_SPR_8X8+24,10,NO);
  Objectes[ENEMIC_1].AfegirFrame(2,MAX_SPR_8X8+25,10,NO);
  Objectes[ENEMIC_1].EntrarDades(10<<dificultat,100,0,0);
  
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+26,SEGUENT_MOVIMENT_AMB_TRANSICIO_Y,NO);
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+27,6,NO);
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+28,12,NO);
  Objectes[ENEMIC_2].AfegirFrame(1,MAX_SPR_8X8+27,6,NO);
  Objectes[ENEMIC_2].EntrarDades(15<<dificultat,430,0,0);


  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+29,30,NO);
  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+30,5,NO);
  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+31,10,NO);
  Objectes[ENEMIC_3].AfegirFrame(1,MAX_SPR_8X8+30,5,NO);
  Objectes[ENEMIC_3].EntrarDades(15<<dificultat,300,0,0);

  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+32,5,NO);
  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+33,5,NO);
  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+34,5,NO);
  Objectes[ENEMIC_4].AfegirFrame(1,MAX_SPR_8X8+35,5,NO);
  Objectes[ENEMIC_4].EntrarDades(5<<dificultat,200,BALA3,0);


  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+36,SEGUENT_POSICIO_AMB_TRANSICIO_Y,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+37,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+38,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+39,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+40,SEGUENT_POSICIO_AMB_TRANSICIO_Y,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+39,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+38,0,NO);
  Objectes[ENEMIC_5].AfegirFrame(1,MAX_SPR_8X8+37,0,NO);
  Objectes[ENEMIC_5].EntrarDades(15<<dificultat,200,0,0);


  Objectes[ENEMIC_6].AfegirFrame(1,MAX_SPR_8X8+41,5,NO);
  Objectes[ENEMIC_6].AfegirFrame(1,MAX_SPR_8X8+42,5,NO);
  Objectes[ENEMIC_6].EntrarDades(20<<dificultat,150,0,0);

  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+43,5,NO);
  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+44,5,NO);
  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+45,5,NO);
  Objectes[ENEMIC_7].AfegirFrame(1,MAX_SPR_8X8+46,5,NO);
  Objectes[ENEMIC_7].EntrarDades(20<<dificultat,300,0,0);


  Objectes[ENEMIC_8].AfegirFrame(1,MAX_SPR_8X8+47,0,NO);
  Objectes[ENEMIC_8].EntrarDades(50<<dificultat,500,0,0);

  Objectes[ENEMIC_9].AfegirFrame(1,MAX_SPR_8X8+48,0,NO);
  Objectes[ENEMIC_9].EntrarDades(100<<dificultat,500,0,0);

  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+51,300,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+54,15,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_10].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_10].EntrarDades(200<<dificultat,1000,0,0);

  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+51,200,NO);  // iguaL
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+54,15,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_11].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_11].EntrarDades(200<<dificultat,1000,0,0);


  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+51,100,NO);  // iguaL
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+54,15,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+53,5,NO);
  Objectes[ENEMIC_12].AfegirFrame(1,MAX_SPR_8X8+52,5,NO);
  Objectes[ENEMIC_12].EntrarDades(400<<dificultat,1000,0,0);




  Objectes[ENEMIC_13].AfegirFrame(1,MAX_SPR_8X8+55,0,NO);

  Objectes[BOLA_ENERGIA].AfegirFrame(1,4,1,NO);
  Objectes[BOLA_ENERGIA].EntrarDades(700<<dificultat,2000,0,0);

  Objectes[_BOSS1].AfegirFrame(1,MAX_SPR_8X8+MAX_SPR_16X16+MAX_SPR_32X32,1,NO);

  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+56,200,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+57,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+58,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+59,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+60,50,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+59,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+58,5,NO);
  Objectes[COMPORTES_DRETA].AfegirFrame(1,MAX_SPR_8X8+57,5,NO);

  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+61,100,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+62,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+63,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+64,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+65,50,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+64,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+63,5,NO);
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+62,5,NO);

  // Definicio dels Conjunts..



  Conjunts[PERSONATGE].AfegirObjecte(Objectes[_PERSONATGE],0,0,NO,INFINIT);

//  Conjunts[BALA].AfegirObjecte(Objectes[BALA_ENEMIC1],0,0,NO,INFINIT);
//  Conjunts[LASER].AfegirObjecte(Objectes[BALA_ENEMIC2],0,0,NO,INFINIT);


  Conjunts[ENEMIC1].AfegirObjecte(Objectes[ENEMIC_1],0,0,NO,INFINIT);

  Conjunts[ENEMIC2].AfegirObjecte(Objectes[ENEMIC_2],0,0,NO,INFINIT);
  Conjunts[ENEMIC3].AfegirObjecte(Objectes[ENEMIC_3],0,0,NO,INFINIT);
  Conjunts[ENEMIC4].AfegirObjecte(Objectes[ENEMIC_4],0,0,NO,INFINIT);
  Conjunts[ENEMIC5].AfegirObjecte(Objectes[ENEMIC_5],0,0,NO,INFINIT);
  Conjunts[ENEMIC6].AfegirObjecte(Objectes[ENEMIC_6],0,0,NO,INFINIT);
  Conjunts[ENEMIC7].AfegirObjecte(Objectes[ENEMIC_7],0,0,NO,INFINIT);
  Conjunts[ENEMIC8].AfegirObjecte(Objectes[ENEMIC_8],0,0,NO,INFINIT);
  Conjunts[ENEMIC9].AfegirObjecte(Objectes[ENEMIC_9],0,0,NO,INFINIT);
  Conjunts[ENEMIC10].AfegirObjecte(Objectes[ENEMIC_10],0,0,NO,INFINIT);
  Conjunts[ENEMIC11].AfegirObjecte(Objectes[ENEMIC_11],0,0,NO,INFINIT);
  Conjunts[ENEMIC12].AfegirObjecte(Objectes[ENEMIC_12],0,0,NO,INFINIT);
  Conjunts[ENEMIC13].AfegirObjecte(Objectes[ENEMIC_13],0,0,NO,INFINIT);

  Conjunts[METEORIT1].AfegirObjecte(Objectes[_METEORIT1],0,0,NO,INFINIT);
  Conjunts[METEORIT2].AfegirObjecte(Objectes[_METEORIT2],0,0,NO,INFINIT);
  Conjunts[METEORIT3].AfegirObjecte(Objectes[_METEORIT3],0,0,NO,INFINIT);

  Conjunts[CAIXA1].AfegirObjecte(Objectes[_CAIXA1],0,0,NO,INFINIT);
  Conjunts[CAIXA2].AfegirObjecte(Objectes[_CAIXA2],0,0,NO,INFINIT);
  Conjunts[CAIXA3].AfegirObjecte(Objectes[_CAIXA3],0,0,NO,INFINIT);


  Conjunts[BOSS1].AfegirObjecte(Objectes[_BOSS1],0,0,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[ENEMIC_10],8,25,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[ENEMIC_11],40,25,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[ENEMIC_12],24,40,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[COMPORTES_DRETA],48,0,NO,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[BOLA_ENERGIA],28,10,SI,INFINIT);
  Conjunts[BOSS1].AfegirObjecte(Objectes[COMPORTES_ESQUERRA],0,0,NO,INFINIT);


    


    /*public:
	int max;
	uint16_t properties;
	std::unordered_map<std::string, EntityAnimationOptions> entity_animations;
	Collider		*collider;
	int life_time;
	int move_time;
	std::function<void(Entity *)> *on_create;
	std::function<void(Entity *)> *on_update;

	EntityTypeConfiguration(){
		max=1;
		life_time=0;
		on_create=NULL;
		on_update=NULL;
		properties=0;
		collider=NULL;
		move_time=0;

	}*/
    }

    update(){
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

        if(!(PActual->Enemic.ConjuntEsNul())&&!(PActual->Ruta.EsNul())&&((PActual->x+entities[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->x<=AMPLADA_PANTALLA_JOC+4)&&((PActual->y+entities[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->y<=ALTURA_PANTALLA_JOC))
        {

        if(!(SequenciaDestruccioBoss&&PActual->tipus==BOSS1))
        {

        if(PActual->vol_atacar)
        {

            while(!PActual->Enemic.ActualEsNul())
            {
            if(dispar = PActual->Enemic.ActualVolDisparar(&x,&y,PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(entities[PActual->Enemic.SpriteActual()].vx)))
            {

            switch(dispar)
            {
            

            case BALA1:CrearDispar(PActual->x+x-4,PActual->y+y-4,BALA_ENEMIC_1,ElMeuMoviment(PActual->x+x+4,PActual->y+y+4,MyPosX,MyPosY,8),CUA_DISPARS_ENEMICS);break;
            case LASER1:CrearDispar(PActual->x+(entities[PActual->Enemic.SpriteActual()].dimx>>1)-4,PActual->y+entities[PActual->Enemic.SpriteActual()].dimy,BALA_ENEMIC_2,0,CUA_DISPARS_ENEMICS);break;
            case ENEMICD:AfegirEnemic(PActual->x+x-4,PActual->y+y-4,ENEMIC5,49,1); //ElMeuMoviment(PActual->x+x,PActual->y+y,MyPosX,MyPosY,16)
            case ENEMICE:AfegirEnemic(PActual->x+x-4,PActual->y+y-4,ENEMIC5,53,1);break; //ElMeuMoviment(PActual->x+x,PActual->y+y,MyPosX,MyPosY,16)

            }
            }

            PActual->Enemic.Seguent();
            }
            

        }

        

        PActual->Ruta.SeguentPosicio(&(PActual->x),&(PActual->y),MyPosX,MyPosY,entities[PActual->Enemic.SpriteActual()].vx,entities[PActual->Enemic.SpriteActual()].vy,PActual->Enemic.DimensioMax());
        PActual->Enemic.ActualitzarCoordenades(PActual->x,PActual->y);
        }

        if(!(SequenciaDestruccioBoss && PActual->tipus==BOSS1&&(RetardDestruccioBoss>200)))
        {
            if(!(SequenciaDestruccioBoss&&PActual->tipus==BOSS1&&RetardDestruccioBoss>30))PActual->Enemic.ActualitzarConjunt(PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(entities[PActual->Enemic.SpriteActual()].vx));
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
            if(!(PActual->Enemic.ConjuntEsNul())&&!(PActual->Ruta.EsNul())&&((PActual->x+entities[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->x<=AMPLADA_PANTALLA_JOC+4)&&((PActual->y+entities[PActual->Enemic.DimensioMax()].dimx)>=0)&&(PActual->y<=ALTURA_PANTALLA_JOC)&& !( (p=HiHaInterseccio(MyPosX,MyPosY,PActual->x,PActual->y,16,entities[PActual->Enemic.SpriteActual()].dimx)&&!(Jo.EsInvencible())&&EsActiu)) )
            {

        
            if(PActual->vol_atacar)
            {
            while(!PActual->Enemic.ActualEsNul())
            {
                if((dispar = PActual->Enemic.ActualVolDisparar(&x,&y,PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(entities[PActual->Enemic.SpriteActual()].vx))) != 0)
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

            PActual->Ruta.SeguentPosicio(&(PActual->x),&(PActual->y),MyPosX,MyPosY,entities[PActual->Enemic.SpriteActual()].vx,entities[PActual->Enemic.SpriteActual()].vy,PActual->Enemic.DimensioMax());
            PActual->Enemic.ActualitzarCoordenades(PActual->x,PActual->y);
            PActual->Enemic.ActualitzarConjunt(PActual->Ruta.TransicioMoviment(),PActual->Ruta.TransicioPosicio(entities[PActual->Enemic.SpriteActual()].vx));
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
        if((!PShotActual->Moviment.EsNul())&&((PShotActual->x+entities[PShotActual->Shot.SpriteActual()].dimx)>=0)&&(PShotActual->x<=(AMPLADA_PANTALLA_JOC+4))&&((PShotActual->y+entities[PShotActual->Shot.SpriteActual()].dimy)>=0)&&(PShotActual->y<=(ALTURA_PANTALLA_JOC+4))&&!(  (p=HiHaInterseccio(MyPosX,MyPosY,PShotActual->x,PShotActual->y,16,entities[PShotActual->Shot.SpriteActual()].dimx)&&!(Jo.EsInvencible())&&EsActiu)))
        {

            PShotActual -> Moviment.SeguentPosicio(&(PShotActual->x),&(PShotActual->y),MyPosX,MyPosY,entities[PShotActual->Shot.SpriteActual()].vx,entities[PShotActual->Shot.SpriteActual()].vy,entities[PShotActual->Shot.SpriteActual()].dimx);
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
        
            if((!PShotActual->Moviment.EsNul())&&((PShotActual->x+entities[PShotActual->Shot.SpriteActual()].dimx)>=0)&&(PShotActual->x<=(AMPLADA_PANTALLA_JOC+4))&&((PShotActual->y+entities[PShotActual->Shot.SpriteActual()].dimy)>=0)&&(PShotActual->y<=(ALTURA_PANTALLA_JOC+4))&&!(I=Checkit(PShotActual->x,PShotActual->y,PShotActual->Shot.Power(),entities[PShotActual->Shot.SpriteActual()].dimx)))
            {
                    PShotActual -> Moviment.SeguentPosicio(&(PShotActual->x),&(PShotActual->y),MyPosX,MyPosY,entities[PShotActual->Shot.SpriteActual()].vx,entities[PShotActual->Shot.SpriteActual()].vy,entities[PShotActual->Shot.SpriteActual()].dimx);
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
        if((!PIActual->Moviment.EsNul())&&((PIActual->x+entities[PIActual->Item.SpriteActual()].dimx)>=0)&&(PIActual->x<=(AMPLADA_PANTALLA_JOC+4))&&((PIActual->y+entities[PIActual->Item.SpriteActual()].dimy)>=0)&&(PIActual->y<=(ALTURA_PANTALLA_JOC+4))&&!(  (p=HiHaInterseccio(MyPosX,MyPosY,PIActual->x,PIActual->y,16,entities[PIActual->Item.SpriteActual()].dimx))&&EsActiu) )
        {

            PIActual -> Moviment.SeguentPosicio(&(PIActual->x),&(PIActual->y),MyPosX,MyPosY,entities[PIActual->Item.SpriteActual()].vx,entities[PIActual->Item.SpriteActual()].vy,entities[PIActual->Item.SpriteActual()].dimx);
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


            if(!BossPresent)
            {
                if((temps % 2 == 0)&&(ypos>7))
                {
            
                if(j<60 && up) {j+=3;ModificarColorPaleta(j,j,j,COLOR_MASCARA);} else up=0;
                if(j>3 && !up) {j-=3;ModificarColorPaleta(j,j,j,COLOR_MASCARA);} else up=1;

                }
            }
            else
            {
                if(j<60 && up) {j+=3;ModificarColorPaleta(j,0,0,224);} else up=0;
                if(j>3 && !up) {j-=3;ModificarColorPaleta(j,0,0,224);} else up=1;
                if(k>0) {k-=3;ModificarColorPaleta(k,k,k,COLOR_MASCARA);}
            }
            
            if(temps > 100)
            {
            Scrollejar(ypos,yscroll,0,VSCREEN1);
            if(((temps%5)==0)&&(ypos>0))
            {

                /*
                if((yscroll % ALTURA_BLOC) == 0) {yscroll = 1;ypos--;}
                else yscroll++;
                */

            }
            }

            for(i=0;i<ALTURA_PANTALLA;i++) memcpy(BUFFER1+(i<<8)+(i<<6)+AMPLADA_PANTALLA,Panell+i*(320-AMPLADA_PANTALLA),(320-AMPLADA_PANTALLA));

            if((ypos==7)&&!Entrat2)
            {
            if(SB) start_sound(sonidos[3],3,OFF);
            if(SB) start_sound(sonidos[13],3,ON);
            if(SB) start_sound(sonidos[12],3,OFF);
            k=0;
            Invader.AfegirEnemic(75,192,20,62,0);
            ModificarColorPaleta(k,k,k,COLOR_MASCARA);
            Entrat2 = CERT;
            }






            for(i=0;i<MAX_ENEMICS_STAGE1;i++)
            {
            if(MatriuEnemicsStage1[i].temps==temps)
            {
                Invader.AfegirEnemic(MatriuEnemicsStage1[i].x,MatriuEnemicsStage1[i].y,MatriuEnemicsStage1[i].enemic,MatriuEnemicsStage1[i].ruta,MatriuEnemicsStage1[i].ataca);
            }
            
            }


            if((temps>2200&&temps<2900)&&(temps%10==0)) Invader.AfegirEnemic(10+rand()%190,-15,METEORIT2,59,1);

            if((temps>5000&&temps<8000)&&(temps%20==0))
            {
            Invader.AfegirEnemic(50+rand()%100,-15,ENEMIC1,59+rand()%3,1);
            }

            if((temps>6000&&temps<7000)&&(temps%40==0))
            {
            Invader.AfegirEnemic(50+rand()%100,-15,ENEMIC7,0,1);
            }

            if((temps>7000&&temps<9000)&&(temps%40==0))
            {
            Invader.AfegirEnemic(-15,10+rand()%100,ENEMIC6,44,1);
            }

            if((temps>7500&&temps<9000)&&(temps%50==0))
            {
            Invader.AfegirEnemic(223,10+rand()%100,ENEMIC6,45,1);
            }


            if(temps==11050)
            {
            for(i=1;i<10;i++) Invader.AfegirEnemic(i*20,-15,ENEMIC5,59,1);
            }

            if(temps==11100)
            {
            for(i=1;i<10;i++) Invader.AfegirEnemic(i*20,-15,ENEMIC5,59,1);
            }



            if(temps==3200)
            {
            Invader.AfegirEnemic(20,-15,ENEMIC8,0,1);
            Invader.AfegirEnemic(104,-15,ENEMIC1,59,1);
            Invader.AfegirEnemic(190,-15,ENEMIC8,0,1);
            }




            if(RetardTro == 0)
            {
            k=63;
            if(SB)start_sound(sonidos[21],21,OFF);
            RetardTro = 100 + rand()&550;

            }
            else
            {
            if(BossPresent) RetardTro--;
            }

            if((ypos==1&&yscroll==2)&&!Entrat1)
            {
            if(SB)
            {stop_sound(3);
                stop_sound(12);
                stop_sound(13);
                start_sound(sonidos[4], 4, ON);
                start_sound(sonidos[11],11,OFF);
            }
            for(i=1;i<10;i++) Invader.AfegirEnemic(i*20,-15,ENEMIC5,59,1);
            Invader.AfegirEnemic(80,-61,20,50,1);
            BossPresent = CERT;
            k=0;RetardTro = 100 + rand()%500;
            Entrat1 = CERT;
            }


            if(Invader.NauDestruida()) {RetardInici = 0;NauInicialitzada=FALS;}

            if(!NauInicialitzada)
            {
            if(RetardInici<100) RetardInici++;
            else {vida; if(!((vida<0))){Invader.InicialitzaNau();Invader.EntrarBombes(3);NauInicialitzada = CERT;}}
            }
            OutText(230,75,"Puntuacio:\0",3,0,0,FONTMT,VSCREEN1);

            if(vida<0)  Visualitzar_Numero(225,141,0,5,3,VSCREEN1);
            else  Visualitzar_Numero(225,141,vida,5,3,VSCREEN1);
            Visualitzar_Numero(246,90,puntuacio=(dword)Invader.PuntuacioActual(),7,3,VSCREEN1);
            Visualitzar_Numero(225,166,(dword)Invader.EntregarBombes(),5,3,VSCREEN1);

            Visualitzar_Numero(0,0,(dword)coreleft()+(dword)farcoreleft(),7,2,VSCREEN1);


            Invader.Actualitzar();



            if(letras[P]&&(Retard_Pausa==0))
            {
            while(letras[P]);
            while(!letras[P]);
            Retard_Pausa = MAX_RETARD_PAUSA;
            }


            WaitVRetrace();
            Flip_VScreen(VIDEO,VSCREEN1);

            if(Retard_Pausa>0) Retard_Pausa--;
            if(!BossPresent) temps ++;

    }

}

