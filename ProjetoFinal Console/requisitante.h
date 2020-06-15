#ifndef REQUISITANTE_H_INCLUDED
#define REQUISITANTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data
{
    int Dia;
    int Mes;
    int Ano;
} Data;

typedef struct requisitante
{
    int ID;
    char Nome[100];
    Data DataDeNascimento;
    char ID_Freguesia[6];
} Requisitante;

#endif // REQUISITANTE_H_INCLUDED
