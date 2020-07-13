#ifndef _LIVROS_CPP_
#define _LIVROS_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "livros.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;

LIVRO *Criar_Livro()
{
    LIVRO *livro = (LIVRO *)malloc(sizeof(LIVRO));

    livro->ISBN = 0;
    livro->AnoDePublicacao = 0;
    livro->NumeroDeRequisicoes = 0;

    return livro;
}

CATEGORIA *Criar_Categoria()
{
    CATEGORIA *categoria = (CATEGORIA *)malloc(sizeof(CATEGORIA));

    categoria->Seguinte = NULL;
    categoria->Inicio = NULL;
    categoria->QuantidadeDeLivros = 0;
    categoria->NumeroDeRequisicoes = 0;

    return categoria;
}

LISTA_CATEGORIAS *Criar_ListaCategorias()
{
    LISTA_CATEGORIAS *lista_categorias = (LISTA_CATEGORIAS *)malloc(sizeof(LISTA_CATEGORIAS));

    lista_categorias->Inicio = NULL;
    lista_categorias->NumeroDeRequisicoes = 0;
    lista_categorias->QuantidadeDeLivros = 0;

    return lista_categorias;
}






// CRIA UM LIVRO COM AS INFROMAÇOES ESSENCIAIS
LIVRO *Criar_Livro_Preenchido(int isbn, char *titulo, char *autor, char *area, int anoDePublicacao, int numeroDeRequisicoes, char *fornecedor)
{
    LIVRO *livro = Criar_Livro();

    livro->ISBN = isbn;
    strcpy(livro->Titulo, titulo);
    strcpy(livro->Autor, autor);
    strcpy(livro->Area, area);
    livro->AnoDePublicacao = anoDePublicacao;
    livro->NumeroDeRequisicoes = numeroDeRequisicoes;
    strcpy(livro->Fornecedor, fornecedor);

    return livro;
}




// VERIFICA SE UM LIVRO COM O ISBN INTRODUZIDO EXISTE OU NAO
bool ExisteISBN(LISTA_CATEGORIAS *hl, int isbn)
{
    // VERIFICA SE EXISTEM LIVROS
    // E SE NAO EXISTIREM LIVROS DEVOLVE FALSE
    if (hl->QuantidadeDeLivros == 0) return false;

    // SELECIONA A PRIMEIRA CATEGORIA
    CATEGORIA *categoria = hl->Inicio;

    // FAZ LOOP POR TODAS AS CATEGORIAS
    while (categoria)
    {
        // SELECIONA O PRIMEIRO LIVRO DA CATEGORIA
        LIVRO *livro = categoria->Inicio;

        // FAZ LOOP PELOS LIVRO NA LISTA
        while (livro)
        {
            if (livro->ISBN == isbn)
            {
                return true;
            }

            // SELECIONA O LIVRO SEGUINTE
            livro = livro->Seguinte;
        }

        // SELECIONA A CATEGORIA SEGUINTE
        categoria = categoria->Seguinte;
    }

    // RETURN FALSE PORQUE NAO HA NENHUM LIVRO COM O ISBN PROCURADO
    return false;
}





// VERIFICA SE UMA CATEGORIA JÁ EXISTE
CATEGORIA *ExisteCategoria(LISTA_CATEGORIAS *hl, LIVRO *livro)
{
    if (!hl || !livro) return NULL;

    // PARA FAZER LOOP PELAS CATEGORIAS
    CATEGORIA *categorias = hl->Inicio;

    // FAZ LOOP PELAS CATEGORIAS
    while(categorias)
    {
        // VERIFICA SE A CATEGORIAS EXISTE
        if(strcasecmp(categorias->Nome, livro->Area) == 0)
        {
            // SE A CATEGORIA EXISTIR, DEVOLVE A CATEGORIA
            return categorias;
        }

        // SELECIONA A CATEGORIA SEGUINTE
        categorias = categorias->Seguinte;
    }

    return NULL;
}





// GUARDA UM LIVRO NA LISTA DE LIVROS
void GuardarLivro(LISTA_CATEGORIAS *hl, LIVRO *livro)
{
    if (!hl || !livro) return;

    // VERIFICA SE A CATEGORIA JA EXISTE
    CATEGORIA *categoria = ExisteCategoria(hl, livro);

    // CASO A CATEGORIA AINDA NAO EXISTA
    if (!categoria)
    {
        // CRIA A CATEGORIA
        categoria = Criar_Categoria();

        // DA O NOME DA CATEGORIA DO LIVRO A CATEGORIA CRIADA EM CIMA
        strcpy(categoria->Nome, livro->Area);

        // ADICIONA A CATEGORIA A LISTA DE CATEGORIAS
        categoria->Seguinte = hl->Inicio;
        hl->Inicio = categoria;
    }

    // METE O LIVRO NA CATEGORIA
    livro->Seguinte = categoria->Inicio;
    categoria->Inicio = livro;

    // ADICIONA 1 A QUANTIDADE DE LIVROS EXISTENTE
    categoria->QuantidadeDeLivros = categoria->QuantidadeDeLivros + 1;
    hl->QuantidadeDeLivros = hl->QuantidadeDeLivros + 1;
}





bool ValidarLivro(LIVRO *livro)
{
    if (livro->AnoDePublicacao < 0) return false;
    if (livro->Area == NULL) return false;
    if (livro->Autor == NULL) return false;
    if (livro->Disponivel == NULL) return false;
    if (livro->Fornecedor == NULL) return false;
    if (livro->ISBN < 0) return false;
    if (livro->NumeroDeRequisicoes < 0) return false;
    if (livro->Titulo == NULL) return false;

    return true;
}





// PEDE INPUT AO UTILIZADOR
// E CRIA UM LIVRO NOVO
LIVRO *Wizard_Livro(LISTA_CATEGORIAS *hl)
{
    int isbn;
    char titulo[100];
    char autor[100];
    char area[100];
    int anoDePublicacao;
    char fornecedor[100];

    char temp;

    printf("Insira o ISBN do Livro: ");
    scanf("%d", &isbn);

    printf("Insira o Título do Livro: ");
    scanf("%c",&temp);
    scanf("%[^\n]", titulo);


    printf("Insira o Autor do Livro: ");
    scanf("%c",&temp);
    scanf("%[^\n]", autor);


    printf("Insira a Area do Livro: ");
    scanf("%c",&temp);
    scanf("%[^\n]", area);


    printf("Insira o Ano de Publicação do Livro: ");
    scanf("%d", &anoDePublicacao);


    printf("Insira o Fornecedor do Livro: ");
    scanf("%c", &temp);
    scanf("%[^\n]", fornecedor);


    LIVRO *livro = Criar_Livro_Preenchido(isbn, titulo, autor, area, anoDePublicacao, 0, fornecedor);
    GuardarLivro(hl, livro);

    return livro;
}




#endif
