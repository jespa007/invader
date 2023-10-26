#define INVADER_FRAME_DIMENSIONS_8X8        8   // DISPARS PETITS...
#define INVADER_MAX_FRAMES_8X8              17
#define INVADER_NUM_ROWS_FRAMES_8X8         1

#define INVADER_FRAME_DIMENSIONS_16X16      16  // SPRITES NORMALS,EXPLOSIONS,ETC...
#define INVADER_MAX_FRAMES_16X16            67
#define INVADER_NUM_ROWS_FRAMES_16X16       4

#define INVADER_FRAME_DIMENSIONS_32X32      32  // GRANS EXPLOSIONS O GRANS NAUS.
#define INVADER_MAX_FRAMES_32X32            5
#define INVADER_NUM_ROWS_FRAMES_32X32       1

#define INVADER_FRAME_DIMENSIONS_64X64      64  // ENEMIC FINAL DE FASE.
#define INVADER_MAX_FRAMES_64X64            1


void Invader::loadEntities(){
    Image *sprites=Image::get("SPRITES1.RAW");
    /*size_t explosion_type_id=entity_manager->newType((EntityTypeConfiguration)(

    ){
       .max=10
	    ,.properties=0
	    ,.entity_animations={
            EntityAnimationOptions(){
                {
                    sprite_frames={
                        Frame(){	
                            .image=sprites
                            ,.time=200
                            ,.crop={112,8,16,16}
                        },
                        ,Frame(){	
                            .image=sprites
                            ,.time=200
                            ,.crop={112+16,8,16,16}
                        }
                        ,Frame(){
                        image=.sprites
                            ,.time=200
                            ,.crop={112+16+16,8,16,16}
                        }
                    }
                }
            }
        }
    });*/
  /*Objectes[EXPLOSIO1].AfegirFrame(1,MAX_SPR_8X8+7,5,SI);
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
  Objectes[COMPORTES_ESQUERRA].AfegirFrame(1,MAX_SPR_8X8+62,5,NO);*/
}