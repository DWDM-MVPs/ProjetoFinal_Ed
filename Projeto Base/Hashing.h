#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#include "Lista.h"

//---------------------------------

typedef struct no_has
{
    char CHAVE[20];
    struct no_has *Prox_Chave;
    Lista *LVirus;
}NO_HAS;

typedef struct
{
    NO_HAS *Inicio;
    int NUM_CHAVES;
}Hashing;




#endif // HASHING_H_INCLUDED
