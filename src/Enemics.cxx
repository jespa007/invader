#include "Invader.h"

INFO_ENEMY MatriuEnemicsStage1[MAX_ENEMICS_STAGE1];

void CarregarEnemicsStage1()
{


 MatriuEnemicsStage1[0].enemic = ENEMIC1;
 MatriuEnemicsStage1[0].ruta = 40;
 MatriuEnemicsStage1[0].ataca = 0;
 MatriuEnemicsStage1[0].x = 40;
 MatriuEnemicsStage1[0].y = -15;
 MatriuEnemicsStage1[0].temps = 410;

 MatriuEnemicsStage1[1].enemic = ENEMIC1;
 MatriuEnemicsStage1[1].ruta = 40;
 MatriuEnemicsStage1[1].ataca = 0;
 MatriuEnemicsStage1[1].x = 44;
 MatriuEnemicsStage1[1].y = -15;
 MatriuEnemicsStage1[1].temps = 430;


 MatriuEnemicsStage1[2].enemic = ENEMIC1; // Primer encuentro...
 MatriuEnemicsStage1[2].ruta = 40;
 MatriuEnemicsStage1[2].ataca = 0;
 MatriuEnemicsStage1[2].x = 48;
 MatriuEnemicsStage1[2].y = -15;
 MatriuEnemicsStage1[2].temps = 450;



 MatriuEnemicsStage1[3].enemic = METEORIT2;
 MatriuEnemicsStage1[3].ruta = 0;
 MatriuEnemicsStage1[3].ataca = 1;
 MatriuEnemicsStage1[3].x = 140;
 MatriuEnemicsStage1[3].y = -15;
 MatriuEnemicsStage1[3].temps = 4800; // Mitg Lluna

 MatriuEnemicsStage1[4].enemic = METEORIT2;
 MatriuEnemicsStage1[4].ruta = 0;
 MatriuEnemicsStage1[4].ataca = 1;
 MatriuEnemicsStage1[4].x = 144;
 MatriuEnemicsStage1[4].y = -15;
 MatriuEnemicsStage1[4].temps = 9000; // Cap al final.


 MatriuEnemicsStage1[5].enemic = ENEMIC9;  // El que et persegueix. (ruta 51)
 MatriuEnemicsStage1[5].ruta = 0;
 MatriuEnemicsStage1[5].ataca = 0;
 MatriuEnemicsStage1[5].x = 104;
 MatriuEnemicsStage1[5].y = -15;
 MatriuEnemicsStage1[5].temps = 3700;


 MatriuEnemicsStage1[6].enemic = ENEMIC4;
 MatriuEnemicsStage1[6].ruta = 55;
 MatriuEnemicsStage1[6].ataca = 1;
 MatriuEnemicsStage1[6].x = -15;
 MatriuEnemicsStage1[6].y = 40;
 MatriuEnemicsStage1[6].temps = 4000;


 MatriuEnemicsStage1[7].enemic = ENEMIC4;
 MatriuEnemicsStage1[7].ruta = 55;
 MatriuEnemicsStage1[7].ataca = 1;
 MatriuEnemicsStage1[7].x = -15;
 MatriuEnemicsStage1[7].y = 26;
 MatriuEnemicsStage1[7].temps = 4030;


 MatriuEnemicsStage1[8].enemic = ENEMIC4;
 MatriuEnemicsStage1[8].ruta = 55;
 MatriuEnemicsStage1[8].ataca = 1;
 MatriuEnemicsStage1[8].x = -15;
 MatriuEnemicsStage1[8].y = 10;
 MatriuEnemicsStage1[8].temps = 4060;


 MatriuEnemicsStage1[9].enemic = ENEMIC4;
 MatriuEnemicsStage1[9].ruta = 56;
 MatriuEnemicsStage1[9].ataca = 1;
 MatriuEnemicsStage1[9].x = 223;
 MatriuEnemicsStage1[9].y = 40;
 MatriuEnemicsStage1[9].temps = 4200;

 MatriuEnemicsStage1[10].enemic = ENEMIC4;
 MatriuEnemicsStage1[10].ruta = 56;
 MatriuEnemicsStage1[10].ataca = 1;
 MatriuEnemicsStage1[10].x = 223;
 MatriuEnemicsStage1[10].y = 26;
 MatriuEnemicsStage1[10].temps = 4230;

 MatriuEnemicsStage1[11].enemic = ENEMIC4;
 MatriuEnemicsStage1[11].ruta = 56;
 MatriuEnemicsStage1[11].ataca = 1;
 MatriuEnemicsStage1[11].x = 223;
 MatriuEnemicsStage1[11].y = 10;
 MatriuEnemicsStage1[11].temps = 4260;

 MatriuEnemicsStage1[12].enemic = ENEMIC8;
 MatriuEnemicsStage1[12].ruta = 0;
 MatriuEnemicsStage1[12].ataca = 1;
 MatriuEnemicsStage1[12].x = 30;
 MatriuEnemicsStage1[12].y = -15;
 MatriuEnemicsStage1[12].temps = 4500;


 MatriuEnemicsStage1[13].enemic = ENEMIC8;
 MatriuEnemicsStage1[13].ruta = 0;
 MatriuEnemicsStage1[13].ataca = 1;
 MatriuEnemicsStage1[13].x = 180;
 MatriuEnemicsStage1[13].y = -15;
 MatriuEnemicsStage1[13].temps = 4500;


 MatriuEnemicsStage1[14].enemic = ENEMIC8;
 MatriuEnemicsStage1[14].ruta = 0;
 MatriuEnemicsStage1[14].ataca = 1;
 MatriuEnemicsStage1[14].x = 30;
 MatriuEnemicsStage1[14].y = -15;
 MatriuEnemicsStage1[14].temps = 4600;


 MatriuEnemicsStage1[15].enemic = ENEMIC8;
 MatriuEnemicsStage1[15].ruta = 0;
 MatriuEnemicsStage1[15].ataca = 1;
 MatriuEnemicsStage1[15].x = 180;
 MatriuEnemicsStage1[15].y = -15;
 MatriuEnemicsStage1[15].temps = 4600;


 MatriuEnemicsStage1[16].enemic = METEORIT3;
 MatriuEnemicsStage1[16].ruta = 0;
 MatriuEnemicsStage1[16].ataca = 1;
 MatriuEnemicsStage1[16].x = 104;
 MatriuEnemicsStage1[16].y = -15;
 MatriuEnemicsStage1[16].temps = 4650;


 MatriuEnemicsStage1[17].enemic = ENEMIC8;
 MatriuEnemicsStage1[17].ruta = 0;
 MatriuEnemicsStage1[17].ataca = 1;
 MatriuEnemicsStage1[17].x = 30;
 MatriuEnemicsStage1[17].y = -15;
 MatriuEnemicsStage1[17].temps = 4700;

 MatriuEnemicsStage1[18].enemic = ENEMIC8;
 MatriuEnemicsStage1[18].ruta = 0;
 MatriuEnemicsStage1[18].ataca = 1;
 MatriuEnemicsStage1[18].x = 180;
 MatriuEnemicsStage1[18].y = -15;
 MatriuEnemicsStage1[18].temps = 4700;

 MatriuEnemicsStage1[19].enemic = METEORIT2;
 MatriuEnemicsStage1[19].ruta = 0;
 MatriuEnemicsStage1[19].ataca = 1;
 MatriuEnemicsStage1[19].x = 104;
 MatriuEnemicsStage1[19].y = -15;
 MatriuEnemicsStage1[19].temps = 4900;

 MatriuEnemicsStage1[20].enemic = METEORIT2;
 MatriuEnemicsStage1[20].ruta = 0;
 MatriuEnemicsStage1[20].ataca = 0;
 MatriuEnemicsStage1[20].x = 100;
 MatriuEnemicsStage1[20].y = -15;
 MatriuEnemicsStage1[20].temps = 4905;



 MatriuEnemicsStage1[21].enemic = METEORIT2;
 MatriuEnemicsStage1[21].ruta = 0;
 MatriuEnemicsStage1[21].ataca = 0;
 MatriuEnemicsStage1[21].x = 110;
 MatriuEnemicsStage1[21].y = -15;
 MatriuEnemicsStage1[21].temps = 4905;


 MatriuEnemicsStage1[22].enemic = METEORIT1;
 MatriuEnemicsStage1[22].ruta = 0;
 MatriuEnemicsStage1[22].ataca = 0;
 MatriuEnemicsStage1[22].x = 104;
 MatriuEnemicsStage1[22].y = -15;
 MatriuEnemicsStage1[22].temps = 4910;


 MatriuEnemicsStage1[23].enemic = ENEMIC7;
 MatriuEnemicsStage1[23].ruta = 0;
 MatriuEnemicsStage1[23].ataca = 1;
 MatriuEnemicsStage1[23].x = 70;
 MatriuEnemicsStage1[23].y = -15;
 MatriuEnemicsStage1[23].temps = 5000;


 MatriuEnemicsStage1[24].enemic = ENEMIC7;
 MatriuEnemicsStage1[24].ruta = 0;
 MatriuEnemicsStage1[24].ataca = 1;
 MatriuEnemicsStage1[24].x = 100;
 MatriuEnemicsStage1[24].y = -15;
 MatriuEnemicsStage1[24].temps = 5050;


 MatriuEnemicsStage1[25].enemic = ENEMIC7;
 MatriuEnemicsStage1[25].ruta = 0;
 MatriuEnemicsStage1[25].ataca = 1;
 MatriuEnemicsStage1[25].x = 130;
 MatriuEnemicsStage1[25].y = -15;
 MatriuEnemicsStage1[25].temps = 5100;

 MatriuEnemicsStage1[26].enemic = ENEMIC6;
 MatriuEnemicsStage1[26].ruta = 47;
 MatriuEnemicsStage1[26].ataca = 1;
 MatriuEnemicsStage1[26].x = 10;
 MatriuEnemicsStage1[26].y = 190;
 MatriuEnemicsStage1[26].temps = 9400;

 MatriuEnemicsStage1[27].enemic = ENEMIC6;
 MatriuEnemicsStage1[27].ruta = 47;
 MatriuEnemicsStage1[27].ataca = 1;
 MatriuEnemicsStage1[27].x = 10;
 MatriuEnemicsStage1[27].y = 190;
 MatriuEnemicsStage1[27].temps = 9420;

 MatriuEnemicsStage1[28].enemic = ENEMIC6;
 MatriuEnemicsStage1[28].ruta = 47;
 MatriuEnemicsStage1[28].ataca = 1;
 MatriuEnemicsStage1[28].x = 10;
 MatriuEnemicsStage1[28].y = 190;
 MatriuEnemicsStage1[28].temps = 9440;


 MatriuEnemicsStage1[29].enemic = METEORIT1;
 MatriuEnemicsStage1[29].ruta = 0;
 MatriuEnemicsStage1[29].ataca = 0;
 MatriuEnemicsStage1[29].x = 104;
 MatriuEnemicsStage1[29].y = -15;
 MatriuEnemicsStage1[29].temps = 400;

 MatriuEnemicsStage1[30].enemic = METEORIT2;
 MatriuEnemicsStage1[30].ruta = 0;
 MatriuEnemicsStage1[30].ataca = 0;
 MatriuEnemicsStage1[30].x = 50;
 MatriuEnemicsStage1[30].y = -15;
 MatriuEnemicsStage1[30].temps = 230;

 MatriuEnemicsStage1[31].enemic = METEORIT2;
 MatriuEnemicsStage1[31].ruta = 0;
 MatriuEnemicsStage1[31].ataca = 0;
 MatriuEnemicsStage1[31].x = 180;
 MatriuEnemicsStage1[31].y = -15;
 MatriuEnemicsStage1[31].temps = 4500;



 MatriuEnemicsStage1[32].enemic = ENEMIC1;
 MatriuEnemicsStage1[32].ruta = 41;
 MatriuEnemicsStage1[32].ataca = 0;
 MatriuEnemicsStage1[32].x = 170;
 MatriuEnemicsStage1[32].y = -15;
 MatriuEnemicsStage1[32].temps = 500;

 MatriuEnemicsStage1[33].enemic = ENEMIC1;
 MatriuEnemicsStage1[33].ruta = 41;
 MatriuEnemicsStage1[33].ataca = 0;
 MatriuEnemicsStage1[33].x = 166;
 MatriuEnemicsStage1[33].y = -15;
 MatriuEnemicsStage1[33].temps = 520;

 MatriuEnemicsStage1[34].enemic = ENEMIC1;
 MatriuEnemicsStage1[34].ruta = 41;
 MatriuEnemicsStage1[34].ataca = 0;
 MatriuEnemicsStage1[34].x = 162;
 MatriuEnemicsStage1[34].y = -15;
 MatriuEnemicsStage1[34].temps = 540;



 MatriuEnemicsStage1[35].enemic = ENEMIC3;
 MatriuEnemicsStage1[35].ruta = 0;
 MatriuEnemicsStage1[35].ataca = 1;
 MatriuEnemicsStage1[35].x = 20;
 MatriuEnemicsStage1[35].y = -15;
 MatriuEnemicsStage1[35].temps = 3500;


 MatriuEnemicsStage1[36].enemic = ENEMIC3;
 MatriuEnemicsStage1[36].ruta = 0;
 MatriuEnemicsStage1[36].ataca = 1;
 MatriuEnemicsStage1[36].x = 190;
 MatriuEnemicsStage1[36].y = -15;
 MatriuEnemicsStage1[36].temps = 3500;


 MatriuEnemicsStage1[37].enemic = ENEMIC6;
 MatriuEnemicsStage1[37].ruta = 47;
 MatriuEnemicsStage1[37].ataca = 1;
 MatriuEnemicsStage1[37].x = 10;
 MatriuEnemicsStage1[37].y = 190;
 MatriuEnemicsStage1[37].temps = 9200;


 MatriuEnemicsStage1[38].enemic = ENEMIC6;
 MatriuEnemicsStage1[38].ruta = 48;
 MatriuEnemicsStage1[38].ataca = 1;
 MatriuEnemicsStage1[38].x = 190;
 MatriuEnemicsStage1[38].y = 190;
 MatriuEnemicsStage1[38].temps = 9220;

 MatriuEnemicsStage1[39].enemic = ENEMIC6;
 MatriuEnemicsStage1[39].ruta = 47;
 MatriuEnemicsStage1[39].ataca = 1;
 MatriuEnemicsStage1[39].x = 10;
 MatriuEnemicsStage1[39].y = 190;
 MatriuEnemicsStage1[39].temps = 9250;


 MatriuEnemicsStage1[40].enemic = ENEMIC6;
 MatriuEnemicsStage1[40].ruta = 48;
 MatriuEnemicsStage1[40].ataca = 1;
 MatriuEnemicsStage1[40].x = 190;
 MatriuEnemicsStage1[40].y = 190;
 MatriuEnemicsStage1[40].temps = 9300;


 MatriuEnemicsStage1[41].enemic = ENEMIC8;
 MatriuEnemicsStage1[41].ruta = 0;
 MatriuEnemicsStage1[41].ataca = 1;
 MatriuEnemicsStage1[41].x = 180;
 MatriuEnemicsStage1[41].y = -15;
 MatriuEnemicsStage1[41].temps = 1650;


 MatriuEnemicsStage1[42].enemic = ENEMIC1;
 MatriuEnemicsStage1[42].ruta = 43;
 MatriuEnemicsStage1[42].ataca = 1;
 MatriuEnemicsStage1[42].x = 20;
 MatriuEnemicsStage1[42].y = -15;
 MatriuEnemicsStage1[42].temps = 900;


 MatriuEnemicsStage1[43].enemic = ENEMIC1;
 MatriuEnemicsStage1[43].ruta = 42;
 MatriuEnemicsStage1[43].ataca = 1;
 MatriuEnemicsStage1[43].x = 160;
 MatriuEnemicsStage1[43].y = -15;
 MatriuEnemicsStage1[43].temps = 900;

 MatriuEnemicsStage1[44].enemic = ENEMIC6;
 MatriuEnemicsStage1[44].ruta = 47;
 MatriuEnemicsStage1[44].ataca = 1;
 MatriuEnemicsStage1[44].x = 10;
 MatriuEnemicsStage1[44].y = 190;
 MatriuEnemicsStage1[44].temps = 9000;


 MatriuEnemicsStage1[45].enemic = ENEMIC6;
 MatriuEnemicsStage1[45].ruta = 47;
 MatriuEnemicsStage1[45].ataca = 1;
 MatriuEnemicsStage1[45].x = 10;
 MatriuEnemicsStage1[45].y = 190;
 MatriuEnemicsStage1[45].temps = 9050;


 MatriuEnemicsStage1[46].enemic = ENEMIC6;
 MatriuEnemicsStage1[46].ruta = 48;
 MatriuEnemicsStage1[46].ataca = 1;
 MatriuEnemicsStage1[46].x = 190;
 MatriuEnemicsStage1[46].y = 190;
 MatriuEnemicsStage1[46].temps = 9100;


 MatriuEnemicsStage1[47].enemic = ENEMIC6;
 MatriuEnemicsStage1[47].ruta = 48;
 MatriuEnemicsStage1[47].ataca = 1;
 MatriuEnemicsStage1[47].x = 190;
 MatriuEnemicsStage1[47].y = 190;
 MatriuEnemicsStage1[47].temps = 9150;


 MatriuEnemicsStage1[48].enemic = ENEMIC8;
 MatriuEnemicsStage1[48].ruta = 0;
 MatriuEnemicsStage1[48].ataca = 1;
 MatriuEnemicsStage1[48].x = 130;
 MatriuEnemicsStage1[48].y = -15;
 MatriuEnemicsStage1[48].temps = 1800;


 MatriuEnemicsStage1[49].enemic = ENEMIC1;
 MatriuEnemicsStage1[49].ruta = 40;
 MatriuEnemicsStage1[49].ataca = 1;
 MatriuEnemicsStage1[49].x = 160;
 MatriuEnemicsStage1[49].y = -15;
 MatriuEnemicsStage1[49].temps = 2000;

 MatriuEnemicsStage1[50].enemic = ENEMIC1;
 MatriuEnemicsStage1[50].ruta = 41;
 MatriuEnemicsStage1[50].ataca = 1;
 MatriuEnemicsStage1[50].x = 40;
 MatriuEnemicsStage1[50].y = -15;
 MatriuEnemicsStage1[50].temps = 2000;

 MatriuEnemicsStage1[51].enemic = ENEMIC1;
 MatriuEnemicsStage1[51].ruta = 43;
 MatriuEnemicsStage1[51].ataca = 1;
 MatriuEnemicsStage1[51].x = 40;
 MatriuEnemicsStage1[51].y = -15;
 MatriuEnemicsStage1[51].temps = 2100;

 MatriuEnemicsStage1[52].enemic = ENEMIC1;
 MatriuEnemicsStage1[52].ruta = 42;
 MatriuEnemicsStage1[52].ataca = 1;
 MatriuEnemicsStage1[52].x = 160;
 MatriuEnemicsStage1[52].y = -15;
 MatriuEnemicsStage1[52].temps = 2100;

 MatriuEnemicsStage1[53].enemic = ENEMIC1;
 MatriuEnemicsStage1[53].ruta = 43;
 MatriuEnemicsStage1[53].ataca = 1;
 MatriuEnemicsStage1[53].x = 40;
 MatriuEnemicsStage1[53].y = -15;
 MatriuEnemicsStage1[53].temps = 2150;

 MatriuEnemicsStage1[54].enemic = ENEMIC1;
 MatriuEnemicsStage1[54].ruta = 42;
 MatriuEnemicsStage1[54].ataca = 1;
 MatriuEnemicsStage1[54].x = 160;
 MatriuEnemicsStage1[54].y = -15;
 MatriuEnemicsStage1[54].temps = 2150;

 MatriuEnemicsStage1[55].enemic = ENEMIC1;
 MatriuEnemicsStage1[55].ruta = 43;
 MatriuEnemicsStage1[55].ataca = 1;
 MatriuEnemicsStage1[55].x = 40;
 MatriuEnemicsStage1[55].y = -15;
 MatriuEnemicsStage1[55].temps = 2200;

 MatriuEnemicsStage1[56].enemic = ENEMIC1;
 MatriuEnemicsStage1[56].ruta = 42;
 MatriuEnemicsStage1[56].ataca = 1;
 MatriuEnemicsStage1[56].x = 160;
 MatriuEnemicsStage1[56].y = -15;
 MatriuEnemicsStage1[56].temps = 2200;



 MatriuEnemicsStage1[57].enemic = ENEMIC1;
 MatriuEnemicsStage1[57].ruta = 43;
 MatriuEnemicsStage1[57].ataca = 1;
 MatriuEnemicsStage1[57].x = 40;
 MatriuEnemicsStage1[57].y = -15;
 MatriuEnemicsStage1[57].temps = 2250;

 MatriuEnemicsStage1[58].enemic = ENEMIC1;
 MatriuEnemicsStage1[58].ruta = 42;
 MatriuEnemicsStage1[58].ataca = 1;
 MatriuEnemicsStage1[58].x = 160;
 MatriuEnemicsStage1[58].y = -15;
 MatriuEnemicsStage1[58].temps = 2250;


 MatriuEnemicsStage1[59].enemic = ENEMIC1;
 MatriuEnemicsStage1[59].ruta = 43;
 MatriuEnemicsStage1[59].ataca = 1;
 MatriuEnemicsStage1[59].x = 40;
 MatriuEnemicsStage1[59].y = -15;
 MatriuEnemicsStage1[59].temps = 2300;

 MatriuEnemicsStage1[60].enemic = ENEMIC1;
 MatriuEnemicsStage1[60].ruta = 42;
 MatriuEnemicsStage1[60].ataca = 1;
 MatriuEnemicsStage1[60].x = 160;
 MatriuEnemicsStage1[60].y = -15;
 MatriuEnemicsStage1[60].temps = 2300;

 MatriuEnemicsStage1[61].enemic = ENEMIC1;
 MatriuEnemicsStage1[61].ruta = 43;
 MatriuEnemicsStage1[61].ataca = 1;
 MatriuEnemicsStage1[61].x = 40;
 MatriuEnemicsStage1[61].y = -15;
 MatriuEnemicsStage1[61].temps = 2350;

 MatriuEnemicsStage1[62].enemic = ENEMIC1;
 MatriuEnemicsStage1[62].ruta = 42;
 MatriuEnemicsStage1[62].ataca = 1;
 MatriuEnemicsStage1[62].x = 160;
 MatriuEnemicsStage1[62].y = -15;
 MatriuEnemicsStage1[62].temps = 2350;



 MatriuEnemicsStage1[63].enemic = METEORIT1;
 MatriuEnemicsStage1[63].ruta = 0;
 MatriuEnemicsStage1[63].ataca = 0;
 MatriuEnemicsStage1[63].x = 90;
 MatriuEnemicsStage1[63].y = -15;
 MatriuEnemicsStage1[63].temps = 1730;

 MatriuEnemicsStage1[64].enemic = METEORIT2;
 MatriuEnemicsStage1[64].ruta = 0;
 MatriuEnemicsStage1[64].ataca = 0;
 MatriuEnemicsStage1[64].x = 40;
 MatriuEnemicsStage1[64].y = -15;
 MatriuEnemicsStage1[64].temps = 1780;

 MatriuEnemicsStage1[65].enemic = METEORIT3;
 MatriuEnemicsStage1[65].ruta = 0;
 MatriuEnemicsStage1[65].ataca = 0;
 MatriuEnemicsStage1[65].x = 130;
 MatriuEnemicsStage1[65].y = -15;
 MatriuEnemicsStage1[65].temps = 1950;


 MatriuEnemicsStage1[66].enemic = ENEMIC2;
 MatriuEnemicsStage1[66].ruta = 47;
 MatriuEnemicsStage1[66].ataca = 1;
 MatriuEnemicsStage1[66].x = 10;
 MatriuEnemicsStage1[66].y = 190;
 MatriuEnemicsStage1[66].temps = 3300;

 MatriuEnemicsStage1[67].enemic = ENEMIC2;
 MatriuEnemicsStage1[67].ruta = 47;
 MatriuEnemicsStage1[67].ataca = 1;
 MatriuEnemicsStage1[67].x = 10;
 MatriuEnemicsStage1[67].y = 190;
 MatriuEnemicsStage1[67].temps = 3350;

 MatriuEnemicsStage1[68].enemic = ENEMIC2;
 MatriuEnemicsStage1[68].ruta = 47;
 MatriuEnemicsStage1[68].ataca = 1;
 MatriuEnemicsStage1[68].x = 10;
 MatriuEnemicsStage1[68].y = 190;
 MatriuEnemicsStage1[68].temps = 3400;






 MatriuEnemicsStage1[69].enemic = ENEMIC2;
 MatriuEnemicsStage1[69].ruta = 48;
 MatriuEnemicsStage1[69].ataca = 1;
 MatriuEnemicsStage1[69].x = 190;
 MatriuEnemicsStage1[69].y = 190;
 MatriuEnemicsStage1[69].temps = 3500;

 MatriuEnemicsStage1[70].enemic = ENEMIC2;
 MatriuEnemicsStage1[70].ruta = 48;
 MatriuEnemicsStage1[70].ataca = 1;
 MatriuEnemicsStage1[70].x = 190;
 MatriuEnemicsStage1[70].y = 190;
 MatriuEnemicsStage1[70].temps = 3550;

 MatriuEnemicsStage1[71].enemic = ENEMIC2;
 MatriuEnemicsStage1[71].ruta = 48;
 MatriuEnemicsStage1[71].ataca = 1;
 MatriuEnemicsStage1[71].x = 190;
 MatriuEnemicsStage1[71].y = 190;
 MatriuEnemicsStage1[71].temps = 3600;



 MatriuEnemicsStage1[72].enemic = ENEMIC4;
 MatriuEnemicsStage1[72].ruta = 55;
 MatriuEnemicsStage1[72].ataca = 1;
 MatriuEnemicsStage1[72].x = -15;
 MatriuEnemicsStage1[72].y = 100;
 MatriuEnemicsStage1[72].temps = 7000;


 MatriuEnemicsStage1[73].enemic = ENEMIC4;
 MatriuEnemicsStage1[73].ruta = 55;
 MatriuEnemicsStage1[73].ataca = 1;
 MatriuEnemicsStage1[73].x = -15;
 MatriuEnemicsStage1[73].y = 60;
 MatriuEnemicsStage1[73].temps = 7030;


 MatriuEnemicsStage1[74].enemic = ENEMIC4;
 MatriuEnemicsStage1[74].ruta = 55;
 MatriuEnemicsStage1[74].ataca = 1;
 MatriuEnemicsStage1[74].x = -15;
 MatriuEnemicsStage1[74].y = 20;
 MatriuEnemicsStage1[74].temps = 7060;


 MatriuEnemicsStage1[75].enemic = ENEMIC4;
 MatriuEnemicsStage1[75].ruta = 56;
 MatriuEnemicsStage1[75].ataca = 1;
 MatriuEnemicsStage1[75].x = 223;
 MatriuEnemicsStage1[75].y = 100;
 MatriuEnemicsStage1[75].temps = 7200;

 MatriuEnemicsStage1[76].enemic = ENEMIC4;
 MatriuEnemicsStage1[76].ruta = 56;
 MatriuEnemicsStage1[76].ataca = 1;
 MatriuEnemicsStage1[76].x = 223;
 MatriuEnemicsStage1[76].y = 60;
 MatriuEnemicsStage1[76].temps = 7230;

 MatriuEnemicsStage1[77].enemic = ENEMIC4;
 MatriuEnemicsStage1[77].ruta = 56;
 MatriuEnemicsStage1[77].ataca = 1;
 MatriuEnemicsStage1[77].x = 223;
 MatriuEnemicsStage1[77].y = 20;
 MatriuEnemicsStage1[77].temps = 7260;


 MatriuEnemicsStage1[78].enemic = ENEMIC9; // RUTA 51 
 MatriuEnemicsStage1[78].ruta = 0;
 MatriuEnemicsStage1[78].ataca = 1;
 MatriuEnemicsStage1[78].x = 104;
 MatriuEnemicsStage1[78].y = -15;
 MatriuEnemicsStage1[78].temps = 9060;


 MatriuEnemicsStage1[79].enemic = ENEMIC3;
 MatriuEnemicsStage1[79].ruta = 0;
 MatriuEnemicsStage1[79].ataca = 1;
 MatriuEnemicsStage1[79].x = 104;
 MatriuEnemicsStage1[79].y = -15;
 MatriuEnemicsStage1[79].temps = 8200;

 MatriuEnemicsStage1[80].enemic = ENEMIC8;
 MatriuEnemicsStage1[80].ruta = 0;
 MatriuEnemicsStage1[80].ataca = 1;
 MatriuEnemicsStage1[80].x = 0;
 MatriuEnemicsStage1[80].y = -15;
 MatriuEnemicsStage1[80].temps = 9600;

 MatriuEnemicsStage1[81].enemic = ENEMIC8;
 MatriuEnemicsStage1[81].ruta = 0;
 MatriuEnemicsStage1[81].ataca = 1;
 MatriuEnemicsStage1[81].x = 16;
 MatriuEnemicsStage1[81].y = -15;
 MatriuEnemicsStage1[81].temps = 9600;

 MatriuEnemicsStage1[82].enemic = ENEMIC8;
 MatriuEnemicsStage1[82].ruta = 0;
 MatriuEnemicsStage1[82].ataca = 1;
 MatriuEnemicsStage1[82].x = 32;
 MatriuEnemicsStage1[82].y = -15;
 MatriuEnemicsStage1[82].temps = 9600;

 MatriuEnemicsStage1[83].enemic = ENEMIC8;
 MatriuEnemicsStage1[83].ruta = 0;
 MatriuEnemicsStage1[83].ataca = 1;
 MatriuEnemicsStage1[83].x = 170;
 MatriuEnemicsStage1[83].y = -15;
 MatriuEnemicsStage1[83].temps = 9600;


 MatriuEnemicsStage1[84].enemic = ENEMIC8;
 MatriuEnemicsStage1[84].ruta = 0;
 MatriuEnemicsStage1[84].ataca = 1;
 MatriuEnemicsStage1[84].x = 186;
 MatriuEnemicsStage1[84].y = -15;
 MatriuEnemicsStage1[84].temps = 9600;

 MatriuEnemicsStage1[85].enemic = ENEMIC8;
 MatriuEnemicsStage1[85].ruta = 0;
 MatriuEnemicsStage1[85].ataca = 1;
 MatriuEnemicsStage1[85].x = 202;
 MatriuEnemicsStage1[85].y = -15;
 MatriuEnemicsStage1[85].temps = 9600;

 MatriuEnemicsStage1[86].enemic = ENEMIC8;
 MatriuEnemicsStage1[86].ruta = 0;
 MatriuEnemicsStage1[86].ataca = 1;
 MatriuEnemicsStage1[86].x = 0;
 MatriuEnemicsStage1[86].y = -15;
 MatriuEnemicsStage1[86].temps = 9616;

 MatriuEnemicsStage1[87].enemic = METEORIT1;
 MatriuEnemicsStage1[87].ruta = 0;
 MatriuEnemicsStage1[87].ataca = 1;
 MatriuEnemicsStage1[87].x = 16;
 MatriuEnemicsStage1[87].y = -15;
 MatriuEnemicsStage1[87].temps = 9616;

 MatriuEnemicsStage1[88].enemic = ENEMIC8;
 MatriuEnemicsStage1[88].ruta = 0;
 MatriuEnemicsStage1[88].ataca = 1;
 MatriuEnemicsStage1[88].x = 32;
 MatriuEnemicsStage1[88].y = -15;
 MatriuEnemicsStage1[88].temps = 9616;



 MatriuEnemicsStage1[89].enemic = ENEMIC8;
 MatriuEnemicsStage1[89].ruta = 0;
 MatriuEnemicsStage1[89].ataca = 1;
 MatriuEnemicsStage1[89].x = 170;
 MatriuEnemicsStage1[89].y = -15;
 MatriuEnemicsStage1[89].temps = 9616;

 MatriuEnemicsStage1[90].enemic = METEORIT3;
 MatriuEnemicsStage1[90].ruta = 0;
 MatriuEnemicsStage1[90].ataca = 1;
 MatriuEnemicsStage1[90].x = 186;
 MatriuEnemicsStage1[90].y = -15;
 MatriuEnemicsStage1[90].temps = 9616;

 MatriuEnemicsStage1[91].enemic = ENEMIC8;
 MatriuEnemicsStage1[91].ruta = 0;
 MatriuEnemicsStage1[91].ataca = 1;
 MatriuEnemicsStage1[91].x = 202;
 MatriuEnemicsStage1[91].y = -15;
 MatriuEnemicsStage1[91].temps = 9616;
                      

 MatriuEnemicsStage1[92].enemic = ENEMIC8;
 MatriuEnemicsStage1[92].ruta = 0;
 MatriuEnemicsStage1[92].ataca = 1;
 MatriuEnemicsStage1[92].x = 0;
 MatriuEnemicsStage1[92].y = -15;
 MatriuEnemicsStage1[92].temps = 9632;

 MatriuEnemicsStage1[93].enemic = ENEMIC8;
 MatriuEnemicsStage1[93].ruta = 0;
 MatriuEnemicsStage1[93].ataca = 1;
 MatriuEnemicsStage1[93].x = 16;
 MatriuEnemicsStage1[93].y = -15;
 MatriuEnemicsStage1[93].temps = 9632;

 MatriuEnemicsStage1[94].enemic = ENEMIC8;
 MatriuEnemicsStage1[94].ruta = 0;
 MatriuEnemicsStage1[94].ataca = 1;
 MatriuEnemicsStage1[94].x = 32;
 MatriuEnemicsStage1[94].y = -15;
 MatriuEnemicsStage1[94].temps = 9632;
                      

 MatriuEnemicsStage1[95].enemic = ENEMIC8;
 MatriuEnemicsStage1[95].ruta = 0;
 MatriuEnemicsStage1[95].ataca = 1;
 MatriuEnemicsStage1[95].x = 170;
 MatriuEnemicsStage1[95].y = -15;
 MatriuEnemicsStage1[95].temps = 9632;

 MatriuEnemicsStage1[96].enemic = ENEMIC8;
 MatriuEnemicsStage1[96].ruta = 0;
 MatriuEnemicsStage1[96].ataca = 1;
 MatriuEnemicsStage1[96].x = 186;
 MatriuEnemicsStage1[96].y = -15;
 MatriuEnemicsStage1[96].temps = 9632;

 MatriuEnemicsStage1[97].enemic = ENEMIC8;
 MatriuEnemicsStage1[97].ruta = 0;
 MatriuEnemicsStage1[97].ataca = 1;
 MatriuEnemicsStage1[97].x = 202;
 MatriuEnemicsStage1[97].y = -15;
 MatriuEnemicsStage1[97].temps = 9632;
                      


 MatriuEnemicsStage1[98].enemic = ENEMIC1;
 MatriuEnemicsStage1[98].ruta = 43;
 MatriuEnemicsStage1[98].ataca = 1;
 MatriuEnemicsStage1[98].x = 20;
 MatriuEnemicsStage1[98].y = -15;
 MatriuEnemicsStage1[98].temps = 950;

 MatriuEnemicsStage1[99].enemic = ENEMIC1;
 MatriuEnemicsStage1[99].ruta = 43;
 MatriuEnemicsStage1[99].ataca = 1;
 MatriuEnemicsStage1[99].x = 20;
 MatriuEnemicsStage1[99].y = -15;
 MatriuEnemicsStage1[99].temps = 1000;

 MatriuEnemicsStage1[100].enemic = ENEMIC1;
 MatriuEnemicsStage1[100].ruta = 43;
 MatriuEnemicsStage1[100].ataca = 1;
 MatriuEnemicsStage1[100].x = 20;
 MatriuEnemicsStage1[100].y = -15;
 MatriuEnemicsStage1[100].temps = 1050;

 MatriuEnemicsStage1[101].enemic = ENEMIC1;
 MatriuEnemicsStage1[101].ruta = 41;
 MatriuEnemicsStage1[101].ataca = 1;
 MatriuEnemicsStage1[101].x = 10;
 MatriuEnemicsStage1[101].y = -15;
 MatriuEnemicsStage1[101].temps = 940;

 MatriuEnemicsStage1[102].enemic = ENEMIC1;
 MatriuEnemicsStage1[102].ruta = 40;
 MatriuEnemicsStage1[102].ataca = 1;
 MatriuEnemicsStage1[102].x = 200;
 MatriuEnemicsStage1[102].y = -15;
 MatriuEnemicsStage1[102].temps = 940;

 MatriuEnemicsStage1[103].enemic = ENEMIC1;
 MatriuEnemicsStage1[103].ruta = 42;
 MatriuEnemicsStage1[103].ataca = 1;
 MatriuEnemicsStage1[103].x = 180;
 MatriuEnemicsStage1[103].y = -15;
 MatriuEnemicsStage1[103].temps = 950;

 MatriuEnemicsStage1[104].enemic = ENEMIC1;
 MatriuEnemicsStage1[104].ruta = 42;
 MatriuEnemicsStage1[104].ataca = 1;
 MatriuEnemicsStage1[104].x = 180;
 MatriuEnemicsStage1[104].y = -15;
 MatriuEnemicsStage1[104].temps = 1000;

 MatriuEnemicsStage1[105].enemic = ENEMIC1;
 MatriuEnemicsStage1[105].ruta = 42;
 MatriuEnemicsStage1[105].ataca = 1;
 MatriuEnemicsStage1[105].x = 180;
 MatriuEnemicsStage1[105].y = -15;
 MatriuEnemicsStage1[105].temps = 1050;


 MatriuEnemicsStage1[106].enemic = ENEMIC1;
 MatriuEnemicsStage1[106].ruta = 41;
 MatriuEnemicsStage1[106].ataca = 1;
 MatriuEnemicsStage1[106].x = 10;
 MatriuEnemicsStage1[106].y = -15;
 MatriuEnemicsStage1[106].temps = 1300;


 MatriuEnemicsStage1[107].enemic = ENEMIC1;
 MatriuEnemicsStage1[107].ruta = 40;
 MatriuEnemicsStage1[107].ataca = 1;
 MatriuEnemicsStage1[107].x = 200;
 MatriuEnemicsStage1[107].y = -15;
 MatriuEnemicsStage1[107].temps = 1300;




}
