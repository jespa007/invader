#ifndef PART_H
 #define PART_H

#include  "definicions.h"

#define NOTIME -1


typedef struct _tAnimacio
{
 // Nota: Ser… circular o acabat en NULL depent del seu us.

 // P.e: - Si es una animaci¢ infinita ser  circular.(ex: un ocell que mou les ales repetidament).
 //      - Una explosi¢ acabar… en NULL quant hagi acabat.

 int actual;                            // Refer‚ncia al sprite actual de la part.
 int temps_frame;                       // Temps (o condicio) que es deixa fins a la propera imatge.
 int temps_actual;
 _tAnimacio *PSeguent;                   // Punter que apunta al seguent sprite.(o NULL)

}tAnimacio;

typedef tAnimacio *PAnimacio;


class tObjecte
{
private: // Funcions (o variables) privades.(Exclusives de la classe.)

    PAnimacio direccio[MAX_DIRECCIONS];     // Aixo compren les imatges compreses
                                            // en un canvi de direcci¢ x (<- | ->);
    PAnimacio PActual;

    int   Regalet;
    int Vitalitat;
    word  Score;
    int Invencible;

    int   posx,posy;
    int   insisteixe,insisteixd;
    int   direccio_anterior,direccio_actual;

    void copia(const tObjecte &Part);

public: // Funcions que manipulen les variables privades.

    tObjecte(); // Constructor per defecte.

    tObjecte & operator = (const tObjecte  &S);
    void  AfegirFrame(int Direccio,int Sprite,int TEMPS,int NUL);

    void  EntrarCoordenades(int POSX,int POSY);
    void  EntrarDades(long int Vitalitat,word Score,int Regalet,int I);
    void  ActualitzarCoordenades(int POSX,int POSY);
    void  EscriureActual();
    void  Centre();
    void  Dreta();
    void  Esquerra();
    void  SeguentFrame(int TransicioMoviment,int TransicioPosicio);
    int   PotCanviarDireccio();

    int   SpriteActual();
    int   ActualEsNul();

    int   DecrementarVitalitat(int N); // Retorna la vitalitat...
    int   Power(); // Retorna la vitalitat...
    int   EsInvencible();

    int   Puntuacio();
    int   Regal();
    int   CondicioCanviFrame();

     ~tObjecte(); // Destructor per defecte.(Destructores, k soys unos destructores!!! ) :).

};


// typedef part *tObjecte;

#endif
