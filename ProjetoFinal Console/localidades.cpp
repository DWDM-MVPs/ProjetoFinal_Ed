#ifndef _LOCALIDADES_CPP_
#define _LOCALIDADES_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "localidades.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;




LISTA_LOCALIDADES *Criar_ListaLocalidades()
{
    LISTA_LOCALIDADES *lista_localidades = (LISTA_LOCALIDADES *)malloc(sizeof(LISTA_LOCALIDADES));

    lista_localidades->InicioConcelhos = NULL;
    lista_localidades->InicioDistritos = NULL;
    lista_localidades->InicioFreguesias = NULL;

    return lista_localidades;
}

CONCELHO *Criar_Concelho()
{
    CONCELHO *concelho = (CONCELHO *)malloc(sizeof(CONCELHO));

    concelho->ID = 0;
    concelho->Seguinte = NULL;

    return concelho;
}

CONCELHO *Criar_Concelho_Preenchido(int id, char nome[100])
{
    CONCELHO *concelho = Criar_Concelho();

    concelho->ID = id;
    strcpy(concelho->Nome, nome);

    return concelho;
}

DISTRITO *Criar_Distrito()
{
    DISTRITO *distrito = (DISTRITO *)malloc(sizeof(DISTRITO));

    distrito->ID = 0;
    distrito->Seguinte = NULL;

    return distrito;
}

DISTRITO *Criar_Distrito_Preenchido(int id, char nome[100])
{
    DISTRITO *distrito = Criar_Distrito();

    distrito->ID = id;
    strcpy(distrito->Nome, nome);

    return distrito;
}

FREGUESIA *Criar_Freguesia()
{
    FREGUESIA *freguesia = (FREGUESIA *)malloc(sizeof(FREGUESIA));

    freguesia->ID = 0;
    freguesia->Seguinte = NULL;

    return freguesia;
}

FREGUESIA *Criar_Freguesia_Preenchida(int id, char nome[100])
{
    FREGUESIA *freguesia = Criar_Freguesia();

    freguesia->ID = id;
    strcpy(freguesia->Nome, nome);

    return freguesia;
}

void GuardarConcelho(LISTA_LOCALIDADES *hz, CONCELHO *concelho)
{
    concelho->Seguinte = hz->InicioConcelhos;
    hz->InicioConcelhos = concelho;
}

void GuardarDistrito(LISTA_LOCALIDADES *hz, DISTRITO *distrito)
{
    distrito->Seguinte = hz->InicioDistritos;
    hz->InicioDistritos = distrito;
}

void GuardarFreguesia(LISTA_LOCALIDADES *hz, FREGUESIA *freguesia)
{
    freguesia->Seguinte = hz->InicioFreguesias;
    hz->InicioFreguesias = freguesia;
}




#endif
