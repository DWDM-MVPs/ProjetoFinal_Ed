#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro
{
    int CODIGO;
    char *NOME;
    char *CIDADE;
} Livro, Virus;

typedef struct no
{
    Livro *Info;
    struct no *Prox;
} No, NO;

typedef struct lista
{
    No *Inicio;
    int NEL;
} Lista;

#endif // LISTA_H_INCLUDED
