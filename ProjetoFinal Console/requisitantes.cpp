#ifndef _REQUISITANTES_CPP_
#define _REQUISITANTES_CPP_

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

DATA *Criar_Data_Preenchida(int dia, int mes, int ano)
{
    DATA *data = (DATA *)malloc(sizeof(DATA));

    data->Dia = dia;
    data->Mes = mes;
    data->Ano = ano;

    return data;
}

REQUISITANTE *Criar_Requisitante()
{
    REQUISITANTE *requisitante = (REQUISITANTE *)malloc(sizeof(REQUISITANTE));

    requisitante->DataDeNascimento = NULL;
    requisitante->NumeroRequisicoes = 0;
    requisitante->Seguinte = NULL;

    return requisitante;
}

LISTA_REQUISITANTES *Criar_ListaRequisitantes()
{
    LISTA_REQUISITANTES *lista_requisitantes = (LISTA_REQUISITANTES *)malloc(sizeof(LISTA_REQUISITANTES));

    lista_requisitantes->Inicio = NULL;
    lista_requisitantes->Quantidade = 0;

    return lista_requisitantes;
}

REQUISICAO *Criar_Requisicao()
{
    REQUISICAO *requisicao = (REQUISICAO *)malloc(sizeof(REQUISICAO));

    requisicao->DataRequisicao = NULL;
    requisicao->Seguinte = NULL;

    return requisicao;
}



bool AnoBissexto(int ano)
{
     return ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0;
}

bool DataValida(int dia, int mes, int ano)
{
    // VERIFICA OS DIAS MAXIMOS PARA CADA MES
    if (dia < 1 || dia > 31)
    {
        return false;
    }
    if (mes < 1 || mes > 12)
    {
        return false;
    }
    // ANO BISSEIXTO (COISO DE FEVEREIRO)
    if (mes == 2)
    {
        if (AnoBissexto(ano))
        {
            return (dia <= 29);
        }
        else
        {
            return (dia <= 28);
        }
    }
    // MESES QUE SO TEM 30 DIAS
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        return (dia <= 30);
    }

    // SE NAO FALHAR NADA DEVOLVE TRUE, PORQUE A DATA E VALIDA
    return true;
}









REQUISITANTE *Criar_Requisitante_Preenchido(int id, char nome[100], DATA *data_de_nascimento, int numero_requisicoes, int id_freguesia)
{
    REQUISITANTE *requisitante = Criar_Requisitante();

    requisitante->ID = id;
    strcpy(requisitante->Nome, nome);
    requisitante->DataDeNascimento = data_de_nascimento;
    requisitante->NumeroRequisicoes = numero_requisicoes;
    requisitante->ID_Freguesia = id_freguesia;

    return requisitante;
}

void GuardarRequisitante(LISTA_REQUISITANTES *hr, REQUISITANTE *requisitante)
{
    if (!hr || !requisitante) return;

    requisitante->Seguinte = hr->Inicio;
    hr->Inicio = requisitante;

    hr->Quantidade = hr->Quantidade + 1;
}



DATA *Wizard_Data()
{
    DATA *data = NULL;

    while (!data)
    {
        int dia;
        int mes;
        int ano;

        printf("Insira o Dia: ");
        scanf("%d", &dia);

        printf("Insira o número do Mes: ");
        scanf("%d", &mes);

        printf("Insira o Ano: ");
        scanf("%d", &ano);

        if (DataValida(dia, mes, ano))
        {
            data = Criar_Data_Preenchida(dia, mes, ano);
        }
        else
        {
            printf("Data invalida");
            PAUSE_CLS;
        }
    }

    return data;
}



REQUISITANTE *Wizard_Requisitante(LISTA_REQUISITANTES *hr)
{
    int id;
    char nome[100];
    DATA *nascimento;
    int id_freguesia;

    char temp;

    printf("Insira o ID do Requisitante: ");
    scanf("%d", &id);

    printf("Insira o Nome do Requisitante: ");
    scanf("%c",&temp);
    scanf("%[^\n]", nome);


    printf("Insira a Data de Nascimento do Requisitante: \n");
    nascimento = Wizard_Data();


    printf("Insira o ID da Freguesia do Requisitante: ");
    scanf("%d", &id_freguesia);


    REQUISITANTE *requisitante = Criar_Requisitante_Preenchido(id, nome, nascimento, 0, id_freguesia);
    GuardarRequisitante(hr, requisitante);

    return requisitante;
}




#endif
