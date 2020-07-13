#ifndef _FICHEIROS_CPP_
#define _FICHEIROS_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "livros.h"
#include "localidades.h"
#include "requisitantes.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;



extern LIVRO *Criar_Livro();
extern bool ValidarLivro(LIVRO *livro);
extern void GuardarLivro(LISTA_CATEGORIAS *hl, LIVRO *livro);
// LE LIVROS
void LerLivros(LISTA_CATEGORIAS *hl)
{
    // ABRE O FICHEIRO PARA LEITURA
    FILE* ficheiro = fopen("dados\\livros.txt", "r");

    // VERIFICA QUE NAO HOUVE NENHUM ERRO COM O FICHEIRO
    if (!ficheiro)
    {
        // MOSTRA UMA MENSAGEM DE ERRO
        printf("Ocorreu um erro ao usar o ficheiro 'livros.txt'.");
        PAUSE;
        return;
    }

    // VARIAVEL PARA GUARDAR A LINHA EM LEITURA
    char linha[1000];

    // FAZ LOOP POR TODAS AS LINHAS
    while (fgets(linha, 1000, ficheiro))
    {
        // DIVIDE A LINHA A CADA "TAB"
        char *coluna = strtok(linha, "\t");

        // GUARDA O LIVRO ATUALMENTE A SER LIDO
        LIVRO *livro = Criar_Livro();

        // FAZ LOOP PELAS COLUNAS
        int i;
        for (i = 0; coluna; i++)
        {
            switch (i)
            {
                case 0: livro->ISBN = atoi(coluna); break;
                case 1: strcpy(livro->Titulo, coluna); break;
                case 2: strcpy(livro->Autor, coluna); break;
                case 3: strcpy(livro->Area, coluna); break;
                case 4: livro->AnoDePublicacao = atoi(coluna); break;
                case 5: livro->NumeroDeRequisicoes = atoi(coluna); break;
                case 6: livro->Disponivel = atoi(coluna); break;
                case 7: strcpy(livro->Fornecedor, coluna); break;
            }

            // SELECIONA A COLUNA SEGUINTE
            coluna = strtok(NULL, "\t");
        }

        // VERIFICA SE O LIVRO E VALIDO
        // E GUARDA O LIVRO CASO ELE SEJA VALIDO
        if (ValidarLivro(livro))
        {
            // GUARDA O LIVRO
            GuardarLivro(hl, livro);
        }
    }

    // FECHA O FICHEIRO
    fclose(ficheiro);
}



// GUARDA TODOS OS LIVROS
void GravarLivros(LISTA_CATEGORIAS *hl)
{
    // ABRE O FICHEIRO PARA ESCRITA
    FILE *ficheiro = fopen("dados\\livros.txt", "w");

    // VERIFICA QUE NAO HOUVE NENHUM ERRO COM O FICHEIRO
    if (!ficheiro)
    {
        // MOSTRA UMA MENSAGEM DE ERRO
        printf("Ocorreu um erro ao usar o ficheiro 'livros.txt'.");
        PAUSE;
        return;
    }

    // SELECIONA A PRIMERA CATEGORIA DA LISTA
    CATEGORIA* categoria = hl->Inicio;

    // FAZ LOOP POR TODAS AS CATEGORIAS
    while(categoria)
    {
        // SELECIONA O PRIMEIRO LIVRO DA CATEGORIA
        LIVRO *livro = categoria->Inicio;

        // FAZ LOOP POR TODOS OS LIVROS
        while(livro)
        {
            // ESCREVE AS INFORMACOES DO LIVRO NO FICHEIRO
            fprintf(ficheiro, "%d\t%s\t%s\t%s\t%d\t%d\t%d\t%s", livro->ISBN, livro->Titulo, livro->Autor, livro->Area, livro->AnoDePublicacao, livro->NumeroDeRequisicoes, livro->Disponivel, livro->Fornecedor);

            // SELECIONA O LIVRO SEGUINTE
            livro = livro->Seguinte;
        }

        // SELECIONA A CATEGORIA SEGUINTE
        categoria = categoria->Seguinte;
    }

    // FECHA O FICHEIRO
    fclose(ficheiro);
}


extern REQUISITANTE *Criar_Requisitante();
extern DATA *Criar_Data();
extern bool ValidarData(DATA *data);
extern void GuardarRequisitante(LISTA_REQUISITANTES *hr, REQUISITANTE *requisitante);
// LE TODOS OS REQUISITANTES DO FICHEIRO
void LerRequisitantes(LISTA_REQUISITANTES *hr)
{
    // ABRE O FICHEIRO PARA ESCRITA
    FILE *ficheiro = fopen("dados\\requisitantes.txt", "w");

    // VERIFICA QUE NAO HOUVE NENHUM ERRO COM O FICHEIRO
    if (!ficheiro)
    {
        // MOSTRA UMA MENSAGEM DE ERRO
        printf("Ocorreu um erro ao usar o ficheiro 'requisitantes.txt'.");
        PAUSE;
        return;
    }

    // VARIAVEL PARA GUARDAR A LINHA EM LEITURA
    char linha[1000];

    // FAZ LOOP POR TODAS AS LINHAS
    while (fgets(linha, 1000, ficheiro))
    {
        // DIVIDE A LINHA A CADA "TAB"
        char *coluna = strtok(linha, "\t");

        // GUARDA O REQUISITANTE ATUALMENTE A SER LIDO
        REQUISITANTE *requisitante = Criar_Requisitante();
        // GUARDA A DATA ATUALMENTE A SER LIDA
        DATA *nascimento = Criar_Data();

        // FAZ LOOP PELAS COLUNAS
        int i;
        for (i = 0; coluna; i++)
        {
            switch (i)
            {
                case 0: requisitante->ID = atoi(coluna); break;
                case 1: strcpy(requisitante->Nome, coluna); break;
                case 2: nascimento->Dia = atoi(coluna); break;
                case 3: nascimento->Mes = atoi(coluna); break;
                case 4: nascimento->Ano = atoi(coluna); break;
                case 5: strcpy(requisitante->ID_Freguesia, coluna); break;
            }

            // SELECIONA A COLUNA SEGUINTE
            coluna = strtok(NULL, "\t");
        }

        // VERIFICA SE A DATA E VALIDA
        // E GUARDA O REQUISITANTE CASO A DATA SEJA VALIDA
        if (ValidarData(nascimento))
        {
            // METE A VARIAVEL 'NASCIMENTO' DENTRO DO REQUISITANTE
            requisitante->DataDeNascimento = nascimento;

            // GUARDA O LIVRO
            GuardarRequisitante(hr, requisitante);
        }
    }

    // FECHA O FICHEIRO
    fclose(ficheiro);
}


// GRAVA TODOS OS REQUISITANTES NO FICHEIRO
void GravarRequisitantes(LISTA_REQUISITANTES *hr)
{
    // ABRE O FICHEIRO PARA ESCRITA
    FILE *ficheiro = fopen("dados\\requisitantes.txt", "w");

    // VERIFICA QUE NAO HOUVE NENHUM ERRO COM O FICHEIRO
    if (!ficheiro)
    {
        // MOSTRA UMA MENSAGEM DE ERRO
        printf("Ocorreu um erro ao usar o ficheiro 'requisitantes.txt'.");
        PAUSE;
        return;
    }

    // SELECIONA A PRIMERA CATEGORIA DA LISTA
    REQUISITANTE* requisitante = hr->Inicio;

    // FAZ LOOP POR TODAS AS CATEGORIAS
    while(requisitante)
    {
        // ESCREVE AS INFORMACOES DO LIVRO NO FICHEIRO
        fprintf(ficheiro, "%d\t%s\t%d\t%d\t%d\t%s", requisitante->ID, requisitante->Nome, requisitante->DataDeNascimento->Dia, requisitante->DataDeNascimento->Mes, requisitante->DataDeNascimento->Ano, requisitante->ID_Freguesia);

        // SELECIONA O LIVRO SEGUINTE
        requisitante = requisitante->Seguinte;
    }

    // FECHA O FICHEIRO
    fclose(ficheiro);
}



extern CONCELHO *Criar_Concelho();
extern void GuardarConcelho(LISTA_LOCALIDADES *hz, CONCELHO *concelho);
// LE CONCELHOS
void LerConcelhos(LISTA_LOCALIDADES *hz)
{
    // ABRE O FICHEIRO PARA LEITURA
    FILE *ficheiro = fopen("dados\\concelhos.txt", "r");

    // VERIFICA QUE NAO HOUVE NENHUM ERRO COM O FICHEIRO
    if (!ficheiro)
    {
        // MOSTRA UMA MENSAGEM DE ERRO
        printf("Ocorreu um erro ao usar o ficheiro 'concelhos.txt'.");
        PAUSE;
        return;
    }

    // VARIAVEL PARA GUARDAR A LINHA EM LEITURA
    char linha[1000];

    // FAZ LOOP POR TODAS AS LINHAS
    while (fgets(linha, 1000, ficheiro))
    {
        // DIVIDE A LINHA A CADA "TAB"
        char *coluna = strtok(linha, "\t");

        // GUARDA O CONCELHO ATUALMENTE A SER LIDO
        CONCELHO *concelho = Criar_Concelho();

        // FAZ LOOP PELAS COLUNAS
        int i;
        for (i = 0; coluna; i++)
        {
            switch (i)
            {
                case 0: concelho->ID = atoi(coluna); break;
                case 1: strcpy(concelho->Nome, coluna); break;
            }

            // SELECIONA A COLUNA SEGUINTE
            coluna = strtok(NULL, "\t");
        }

        // GUARDA O CONCELHO
        GuardarConcelho(hz, concelho);
    }

    // FECHA O FICHEIRO
    fclose(ficheiro);
}



extern DISTRITO *Criar_Distrito();
extern void GuardarDistrito(LISTA_LOCALIDADES *hz, DISTRITO *distrito);
// LE DISTRITOS
void LerDistritos(LISTA_LOCALIDADES *hz)
{
    // ABRE O FICHEIRO PARA LEITURA
    FILE *ficheiro = fopen("dados\\distritos.txt", "r");

    // VERIFICA QUE NAO HOUVE NENHUM ERRO COM O FICHEIRO
    if (!ficheiro)
    {
        // MOSTRA UMA MENSAGEM DE ERRO
        printf("Ocorreu um erro ao usar o ficheiro 'distritos.txt'.");
        PAUSE;
        return;
    }

    // VARIAVEL PARA GUARDAR A LINHA EM LEITURA
    char linha[1000];

    // FAZ LOOP POR TODAS AS LINHAS
    while (fgets(linha, 1000, ficheiro))
    {
        // DIVIDE A LINHA A CADA "TAB"
        char *coluna = strtok(linha, "\t");

        // GUARDA O DISTRITO ATUALMENTE A SER LIDO
        DISTRITO *distrito = Criar_Distrito();

        // FAZ LOOP PELAS COLUNAS
        int i;
        for (i = 0; coluna; i++)
        {
            switch (i)
            {
                case 0: distrito->ID = atoi(coluna); break;
                case 1: strcpy(distrito->Nome, coluna); break;
            }

            // SELECIONA A COLUNA SEGUINTE
            coluna = strtok(NULL, "\t");
        }

        // GUARDA O CONCELHO
        GuardarDistrito(hz, distrito);
    }

    // FECHA O FICHEIRO
    fclose(ficheiro);
}



extern FREGUESIA *Criar_Freguesia();
extern void GuardarFreguesia(LISTA_LOCALIDADES *hz, FREGUESIA *freguesia);
// LE FREGUESIAS
void LerFreguesias(LISTA_LOCALIDADES *hz)
{
    // ABRE O FICHEIRO PARA LEITURA
    FILE *ficheiro = fopen("dados\\freguesias.txt", "r");

    // VERIFICA QUE NAO HOUVE NENHUM ERRO COM O FICHEIRO
    if (!ficheiro)
    {
        // MOSTRA UMA MENSAGEM DE ERRO
        printf("Ocorreu um erro ao usar o ficheiro 'freguesias.txt'.");
        PAUSE;
        return;
    }

    // VARIAVEL PARA GUARDAR A LINHA EM LEITURA
    char linha[1000];

    // FAZ LOOP POR TODAS AS LINHAS
    while (fgets(linha, 1000, ficheiro))
    {
        // DIVIDE A LINHA A CADA "TAB"
        char *coluna = strtok(linha, "\t");

        // GUARDA A FREGUESIA ATUALMENTE A SER LIDA
        FREGUESIA *freguesia = Criar_Freguesia();

        // FAZ LOOP PELAS COLUNAS
        int i;
        for (i = 0; coluna; i++)
        {
            switch (i)
            {
                case 0: freguesia->ID = atoi(coluna); break;
                case 1: strcpy(freguesia->Nome, coluna); break;
            }

            // SELECIONA A COLUNA SEGUINTE
            coluna = strtok(NULL, "\t");
        }

        // GUARDA O CONCELHO
        GuardarFreguesia(hz, freguesia);
    }

    // FECHA O FICHEIRO
    fclose(ficheiro);
}


#endif
