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








extern void LerLivros(LISTA_CATEGORIAS *hl);
void CarregarLivros(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("A ler Livros...", "Ficheiros");
    LerLivros(hl);
    printf("Livros lidos com sucesso!");
    PAUSE_CLS;
}

extern void GravarLivros(LISTA_CATEGORIAS *hl);
void GuardarLivros(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("A gravar Livros...", "Ficheiros");
    GravarLivros(hl);
    printf("Livros gravados com sucesso!");
    PAUSE_CLS;
}

extern void LerRequisitantes(LISTA_REQUISITANTES *hr);
void CarregarRequisitantes(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("A ler Requisitantes...", "Ficheiros");
    LerRequisitantes(hr);
    printf("Requisitantes lidos com sucesso!");
    PAUSE_CLS;
}

extern void GravarRequisitantes(LISTA_REQUISITANTES *hr);
void GuardarRequisitantes(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("A gravar Requisitantes...", "Ficheiros");
    GravarRequisitantes(hr);
    printf("Requisitantes gravados com sucesso!");
    PAUSE_CLS;
}

extern void LerConcelhos(LISTA_LOCALIDADES *hz);
extern void LerDistritos(LISTA_LOCALIDADES *hz);
extern void LerFreguesias(LISTA_LOCALIDADES *hz);
void LerLocalidades(LISTA_LOCALIDADES *hz)
{
    ImprimirDuplo("A ler Localidades...", "Ficheiros");
    LerConcelhos(hz);
    LerDistritos(hz);
    LerFreguesias(hz);
    printf("Localidades lidas com sucesso!");
    PAUSE_CLS;
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
