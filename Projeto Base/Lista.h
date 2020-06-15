#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus
{
    int CODIGO;
    char NOME[100];
    char CIDADE[50];
    //char *NOME;
    // char *CIDADE;
}Virus;


/*
JOSE FRANCISCO M. MORGADOXXXXXXXXXXXXXXXXXXX
IVAN  SD SD SD S DSD  DSD S DS DS D XXXXXXXX
JORGE BEM LOUREIRO MATOS XXXXXXXXXXXXXXXXXXX
CARLOS SIMOESXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/

typedef struct no
{
    Virus *Info;
    struct no *Prox;
}NO;

typedef struct lista
{
    NO *Inicio;
    int NEL;
}Lista;
#endif // LISTA_H_INCLUDED
