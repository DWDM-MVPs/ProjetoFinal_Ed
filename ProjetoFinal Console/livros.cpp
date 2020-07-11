#ifndef _LIVROS_CPP_
#define _LIVROS_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "livros.h"

LIVRO *Criar_Livro()
{
    LIVRO *livro = (LIVRO *)malloc(sizeof(LIVRO));

    livro->ISBN = 0;
    livro->AnoDePublicacao = 0;
    livro->NumeroDeRequisicoes = 0;

    return livro;
}

LISTA_LIVROS *Criar_ListaLivros()
{
    LISTA_LIVROS *lista_livros = (LISTA_LIVROS *)malloc(sizeof(LISTA_LIVROS));

    lista_livros->Inicio = NULL;
    lista_livros->QuantidadeDeLivros = 0;

    return lista_livros;
}

CATEGORIA *Criar_Categoria()
{
    CATEGORIA *categoria = (CATEGORIA *)malloc(sizeof(CATEGORIA));

    categoria->Seguinte = NULL;
    categoria->ListaDeLivros = NULL;
    categoria->NumeroDeRequisicoes = 0;

    return categoria;
}

LISTA_CATEGORIAS *Criar_ListaCategorias()
{
    LISTA_CATEGORIAS *lista_categorias = (LISTA_CATEGORIAS *)malloc(sizeof(LISTA_CATEGORIAS));

    lista_categorias->Inicio = NULL;
    lista_categorias->Quantidade = 0;

    return lista_categorias;
}






LIVRO *Criar_Livro_Preenchido(int isbn, char *titulo, char *autor, char *area, int anoDePublicacao, int numeroDeRequisicoes)
{
    LIVRO *livro = Criar_Livro();

    livro->ISBN = isbn;
    strcpy(livro->Titulo, titulo);
    strcpy(livro->Autor, autor);
    strcpy(livro->Area, area);
    livro->AnoDePublicacao = anoDePublicacao;
    livro->NumeroDeRequisicoes = numeroDeRequisicoes;

    return livro;
}





// ADICIONA UM LIVRO A LISTA
void AdicionarLivroNaLista(LISTA_CATEGORIAS *hl, LISTA_LIVROS *lista_livros, LIVRO *livro)
{
    if (!lista_livros || !livro) return;

    // ADICIONA O LIVRO A LSITA
    livro->Seguinte = lista_livros->Inicio;
    lista_livros->Inicio = livro;

    // ADICIONA 1 AO VALOR DA QUANTIDADE DE LIVROS NA LISTA
    lista_livros->QuantidadeDeLivros = lista_livros->QuantidadeDeLivros + 1;

    hl->Quantidade = hl->Quantidade + 1;
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





// ADICIONA UM LIVRO AO 'HASHING_LIVROS'
// E CRIA UMA NOVA CATEGORIA CASO AINDA NÃO EXISTA
void AdicionarLivro(LISTA_CATEGORIAS *hl, LIVRO *livro)
{
    if (!hl || !livro) return;

    // METE NA VARIAVEL A CATEGORIA EXISTENTE
    CATEGORIA *categoria = ExisteCategoria(hl, livro);

    // CASO NAO EXISTA ESSA CATEGORIA, CRIA UMA NOVA
    if (!categoria)
    {
        // CRIA UMA NOVA CATEGORIA
        categoria = Criar_Categoria();

        // CRIA A LISTA DE LIVROS VAZIA PARA ESSA CATEGORIA
        categoria->ListaDeLivros = Criar_ListaLivros();

        // DA O NOME A CATEGORIA
        strcpy(categoria->Nome, livro->Area);

        // ADICIONA O LIVRO NA NOVA CATEGORIA
        AdicionarLivroNaLista(hl, categoria->ListaDeLivros, livro);

        // CASO NAO HAJA NENHUMA AREA
        if (!hl->Inicio)
        {
            // METE A NOVA CATEGORIA NO INICIO DA LISTA DAS CATEGORIAS
            hl->Inicio = categoria;
        }
    }
    // CASO EXISTA A CATEGORIA
    else
    {
        // METE LA O LIVRINHO
        AdicionarLivroNaLista(hl, categoria->ListaDeLivros, livro);
    }
    return;
}




#endif
