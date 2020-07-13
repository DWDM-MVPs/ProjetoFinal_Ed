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
    FILE* ficheiro = fopen("dados/livros.txt", "r");

    // VARIAVEIS PARA GUARDAR A LINHA E TAL
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
                case 1: livro->ISBN = atoi(coluna); break;
                case 2: strcpy(livro->Area, coluna); break;
                case 3: strcpy(livro->Titulo, coluna); break;
                case 4: strcpy(livro->Fornecedor, coluna); break;
                case 5: livro->AnoDePublicacao = atoi(coluna); break;
                case 6: livro->Disponivel = atoi(coluna); break;
                case 7: livro->NumeroDeRequisicoes = atoi(coluna); break;
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

    // FECHA O FICHEIRO DOS LIVROS
    fclose(ficheiro);
}






#endif
