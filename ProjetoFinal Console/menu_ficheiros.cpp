#ifndef _MENU_FICHEIROS_CPP_
#define _MENU_FICHEIROS_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "livros.h"
#include "requisitantes.h"
#include "localidades.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;

extern void ImprimirMenu(const char *titulo);
extern void ImprimirFuncao(const char *titulo);
extern void ImprimirDuplo(const char *funcao, const char *menu);

void MensagemNaoExistemFicheiros()
{
    printf("Não existem Ficheiros.");
}








void CarregarLivros(LISTA_CATEGORIAS *hl)
{

}

void GuardarLivros(LISTA_CATEGORIAS *hl)
{

}

void CarregarRequisitantes(LISTA_REQUISITANTES *hr)
{

}

void GuardarRequisitantes(LISTA_REQUISITANTES *hr)
{

}

void LerLocalidades(LISTA_LOCALIDADES *hz)
{

}








void MenuFicheiros(LISTA_CATEGORIAS *hl, LISTA_REQUISITANTES *hr, LISTA_LOCALIDADES *hz)
{
    int escolha = 0;
    do
    {
        ImprimirMenu("Gerir Ficheiros");

        printf("\n1. Carregar Livros");
        printf("\n2. Guardar Livros");
        printf("\n3. Carregar Requisitantes");
        printf("\n4. Guardar Requisitantes");
        printf("\n5. Ler Distritos/Concelhos/Freguesias");
        printf("\n\n0. Sair");
        printf("\n\n\n\n\n »---> Escolha: ");

        scanf("%d", &escolha);

        CLS;

        switch(escolha)
        {
            extern void MenuLivros(LISTA_CATEGORIAS *hl);
            case 1: CarregarLivros(hl); break;
            case 2: GuardarLivros(hl); break;
            case 3: CarregarRequisitantes(hr); break;
            case 4: GuardarRequisitantes(hr); break;
            case 5: LerLocalidades(hz); break;
        }
    } while (escolha != 0);
}



#endif
