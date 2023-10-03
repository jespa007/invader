#ifndef PART_H
 #define PART_H

#define NOTIME -1

typedef struct tAnimacio
{
 // Nota: Ser… circular o acabat en NULL depent del seu us.

 // P.e: - Si es una animaci¢ infinita ser  circular.(ex: un ocell que mou les ales repetidament).
 //      - Una explosi¢ acabar… en NULL quant hagi acabat.

 int actual;                            // Refer‚ncia al sprite actual de la part.
 word temps;                            // Temps que es deixa fins a la propera imatge.
 word temps_actual;                     // Temps actual.
 tAnimacio *PSeguent;                   // Punter que apunta al seguent sprite.(o NULL)

};

typedef tAnimacio *PAnimacio;


class tObjecte
{
private: // Funcions (o variables) privades.(Exclusives de la classe.)

    PAnimacio direccio[MAX_DIRECCIONS];     // Aixo compren les imatges compreses
                                            // en un canvi de direcci¢ x (<- | ->);
    PAnimacio PActual;

    int   Regalet;
    long int Vitalitat;
    int   posx,posy;
    int   insisteixe,insisteixd;
    int   direccio_anterior,direccio_actual;

    void copia(const tObjecte &Part);

public: // Funcions que manipulen les variables privades.

    tObjecte(); // Constructor per defecte.

    tObjecte & operator = (const tObjecte  &S);
    void  AfegirFrame(int Direccio,int Sprite,int TEMPS,int NUL);

    void  EntrarCoordenades(int POSX,int POSY);
    void  EntrarVitalitat(long int Vitalitat);
    void  EntrarScore(int Score);
    void  ActualitzarCoordenades(int POSX,int POSY);
    void  EscriureActual(word VSCREEN);
    void  Centre();
    void  Dreta();
    void  Esquerra();
    void  SeguentFrame();
    int   SpriteActual();
    int   EsNul();
    void  DecrementarVitalitat(int N);
    int   HihaVitalitat();
//    void Centre();
//    void Dreta();
//    void Esquerra();
//    void SeguentAnimacio();
//    void CoordenadesActuals(int *x,int *y);

     ~tObjecte(); // Destructor per defecte.(Destructores, k soys unos destructores!!! ) :).

};


// typedef part *tObjecte;

#endif
