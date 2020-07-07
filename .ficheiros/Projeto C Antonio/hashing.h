#include "lista.h"

/** ---------- NODO DE HASHING ---------- */

typedef struct nodo_hashing
{
    char *nome;
    struct nodo_hashing *seg;
    LISTA *lista;
    char numero [3];

} NODO_HASHING;

/** ---------- HASHING ---------- */

typedef struct
{
    NODO_HASHING *inicio;
    int nel;

} HASHING;







