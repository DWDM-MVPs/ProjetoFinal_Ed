#include "Lista.h"


extern void MostrarVirus(Virus *V);
extern void DestruirVirus(Virus *V);
//-------------------------------

Lista *CriarLista()
{
    Lista *L = (Lista *)malloc(sizeof(Lista));
    L->Inicio = NULL;
    L->NEL = 0;
    return L;
}
void Destruir_Lista(Lista *L)
{
    if (!L) return;
    NO *Aux = NULL;
    NO *P = L->Inicio;
    while (P)
    {
        Aux = P->Prox;
        DestruirVirus(P->Info);
        P = Aux;
    }
    free(L);
}

void Mostrar_Lista(Lista *L)
{
    if (!L) return;
    NO *P = L->Inicio;
    while (P)
    {
        MostrarVirus(P->Info);
        P = P->Prox;
    }
}

void Inserir_Lista(Lista *L, Virus *V)
{
    if (!L) return;
    NO *X = (NO *)malloc(sizeof(NO));
    X->Info = V;
    X->Prox = L->Inicio;
    L->Inicio = X;
    L->NEL++;
}

