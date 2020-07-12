#ifndef _MENU_REQUISITANTES_CPP_
#define _MENU_REQUISITANTES_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "requisitantes.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;

extern void ImprimirMenu(const char *titulo);
extern void ImprimirFuncao(const char *titulo);
extern void ImprimirDuplo(const char *funcao, const char *menu);

extern LISTA_REQUISITANTES *Criar_ListaRequisitantes();
extern REQUISITANTE *Criar_Requisitante_Preenchido(int id, char nome[100], DATA *data_de_nascimento, int numero_requisicoes, int id_freguesia);
extern void GuardarRequisitante(LISTA_REQUISITANTES *hr, REQUISITANTE *requisitante);
extern REQUISITANTE *Wizard_Requisitante(LISTA_REQUISITANTES *hr);




void MensagemNaoExistemRequisitantes()
{
    printf("Não existem requisitantes.");
    PAUSE_CLS;
}


















// FAZ O PRINTF DE TODAS AS INFORMACOES DO LIVRO
void MostrarRequisitante(REQUISITANTE *requisitante)
{
    printf("ID: %d", requisitante->ID);
    printf("\nNome: %s", requisitante->Nome);
    printf("\nID da Freguesia: %d", requisitante->ID_Freguesia);
    printf("\nData de Nascimento: %d/%d/%d", requisitante->DataDeNascimento->Dia, requisitante->DataDeNascimento->Mes, requisitante->DataDeNascimento->Ano);
    printf("\nNúmero de Requisições: %d", requisitante->NumeroRequisicoes);
}



void ListarRequisitantes(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Listar Requisitantes", "Requisitantes");

    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // GUARDA O PRIMEIRO REQUISITANTE NA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP PELOS REQUISITANTES
    while (requisitante)
    {
        // MOSTRA AS INFORMACOES DO REQUISITANTE
        MostrarRequisitante(requisitante);

        // SELECIONA O REQUISITANTE SEGUINTE
        requisitante = requisitante->Seguinte;
    }

    PAUSE_CLS;
}




void CriarRequisitante(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("WIZARD: Criar novo Requisitante", "Requisitantes");
    REQUISITANTE *r = Wizard_Requisitante(hr);
    CLS;

    ImprimirFuncao("Requisitante criado com sucesso!");
    MostrarRequisitante(r);
    PAUSE_CLS;
}




void PesquisarRequisitantePorNome(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Pesquisar Requisitante por Nome", "Requisitantes");

    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    char nome[100];
    char temp;

    // LE UM NOME DE REQUISITANTE DO UTILIZADOR
    printf("Insira o Nome do Requisitante a pesquisar: ");
    scanf("%c",&temp);
    scanf("%[^\n]", nome);

    // GUARDA O PRIMEIRO REQUISITANTE DA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP PELOS REQUISITANTES
    while (requisitante)
    {
        if (requisitante->Nome == nome)
        {
            printf("\Requisitante encontrado!\n\n\n\nInformações do Requisitante encontrado:\n\n");
            MostrarRequisitante(requisitante);
            PAUSE_CLS;
            return;
        }

        // SELECIONA O PROXIMO REQUISITANTE
        requisitante = requisitante->Seguinte;
    }

    printf("Não foi encontrado nenhum Requisitante com o Nome %s", nome);
    PAUSE_CLS;
}





void MenuRequisitantes(LISTA_REQUISITANTES *hr)
{
    ImprimirMenu("Requisitantes");

    CriarRequisitante(hr);
    ListarRequisitantes(hr);
}


#endif
