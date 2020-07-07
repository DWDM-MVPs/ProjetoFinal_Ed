#ifndef _LISTH_
#define _LISTH_
#include <time.h>

/** ---------- LISTA ---------- */

typedef struct nodo{

    void *info;
    struct nodo *seg;

} NODO;

typedef struct{

    NODO *inicio;
    int nel;

} LISTA;

/** ---------- REQUISITANTE ---------- */

typedef struct{

    char id[10];
    char *nome;
    int diaNasc;
    int mesNasc;
    int anoNasc;
    char idFreguesia[7];
    LISTA *requisicao;

} REQUISITANTE;

/** ---------- LIVRO ---------- */

typedef struct{

    int ISBN;
    char *titulo;
    int ano;
    char *area;
    int requisitado;
    int numRequisicoes;

} LIVRO;

/** ---------- REQUISIÇÃO ---------- */



typedef struct
{
    char IdRequisitante[10];
    struct tm *DataRequisicao;
    int totalDiasDeRequisicao;
    struct tm *DataSupostaDaEntrega;
    struct tm *DataRealDaEntrega;
    LIVRO *pertence;

}REQUISICAO;

/** ---------- SOBRENOME ---------- */

typedef struct
{
    char *sobrenome;
    int nel;

} SOBRENOME;

#endif
