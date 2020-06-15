#ifndef REQUISITANTE_H_INCLUDED
#define REQUISITANTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data
{
    int Dia;
    int Mes;
    int Ano;
};

typedef struct Requisitante
{
    int ID;
    char Nome[100];
    Data DataDeNascimento;
    char ID_Freguesia[6];
};

#endif // REQUISITANTE_H_INCLUDED
