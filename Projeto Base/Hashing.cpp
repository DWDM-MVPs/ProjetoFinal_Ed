
#include "Hashing.h"


extern Lista *CriarLista();
extern void Inserir_Lista(Lista *L, Virus *V);
extern void Destruir_Lista(Lista *L);
extern void Mostrar_Lista(Lista *L);

//---------------------------------

Hashing *CriarHashing_PRO()
{
    Hashing *H = (Hashing *)malloc(sizeof(Hashing));
    if (!H) return NULL;
    H->Inicio = NULL;
    H->NUM_CHAVES = 0;
    return H;
}
NO_HAS *FuncaoHashing_Vector_Cidade(Hashing *H, const char *cid)
{
    if (!H) return NULL;
    NO_HAS *P = H->Inicio;
    while (P)
    {
        if (strcmp(P->CHAVE, cid) == 0)
            return P;
        P = P->Prox_Chave;
    }
    return NULL;
}

NO_HAS *FuncaoHashing_Vector(Hashing *H, Virus *V)
{
    /*
    if (!H) return NULL;
    NO_HAS *P = H->Inicio;
    while (P)
    {
        if (strcmp(P->CHAVE, V->CIDADE) == 0)
            return P;
        P = P->Prox_Chave;
    }
    return NULL;
    */
    return FuncaoHashing_Vector_Cidade(H, V->CIDADE);
}

void Add_Hashing_PRO(Hashing *H, Virus *X)
{
    if (!H) return;
    NO_HAS *P = FuncaoHashing_Vector(H, X);
    if (P == NULL)
    {
        P = (NO_HAS *)malloc(sizeof(NO_HAS));
        strcpy(P->CHAVE, X->CIDADE);
        P->LVirus = CriarLista();
        P->Prox_Chave = H->Inicio;
        H->Inicio = P;
        H->NUM_CHAVES++;
    }
    Inserir_Lista(P->LVirus, X);
}

void Mostrar_Hashing_PRO(Hashing *H)
{
    if (!H) return;
    NO_HAS *P = H->Inicio;
    printf("NUMERO-CHAVES = %d\n", H->NUM_CHAVES);
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        Mostrar_Lista(P->LVirus);
        P = P->Prox_Chave;
    }
}

void Destruir_Hashing_PRO(Hashing *H)
{
    if (!H) return;
    NO_HAS *Aux = NULL;
    NO_HAS *P = H->Inicio;
    while (P)
    {
        Aux = P->Prox_Chave;
        Destruir_Lista(P->LVirus);
        free(P);
        P = Aux;
    }
    free(H);
}
//-----------------------------
int ContarVirusCidade(Hashing *H, const char *nome_cid)
{
    if (!H) return 0;
    NO_HAS *P = FuncaoHashing_Vector_Cidade(H, nome_cid);
    if (!P) return 0;
    return P->LVirus->NEL;
}
//-----------------------------
//-----------------------------
//-----------------------------

