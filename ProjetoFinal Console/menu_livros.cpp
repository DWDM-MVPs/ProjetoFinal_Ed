#ifndef _MENU_LIVROS_CPP_
#define _MENU_LIVROS_CPP_

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

extern void ImprimirMenu(const char *titulo);
extern void ImprimirFuncao(const char *titulo);
extern void ImprimirDuplo(const char *funcao, const char *menu);

extern LISTA_CATEGORIAS *Criar_ListaCategorias();
extern LIVRO *Criar_Livro_Preenchido(int isbn, char *titulo, char *autor, char *area, int anoDePublicacao, int numeroDeRequisicoes);
extern void GuardarLivro(LISTA_CATEGORIAS *hl, LIVRO *livro);
extern LIVRO *Wizard_Livro(LISTA_CATEGORIAS *hl);




void MensagemNaoExistemLivros()
{
    printf("Não existem Livros.");
    PAUSE_CLS;
}


















// FAZ O PRINTF DE TODAS AS INFORMACOES DO LIVRO
void MostrarLivro(LIVRO *livro)
{
    printf("ISBN: %d", livro->ISBN);
    printf("\nTitulo: %s", livro->Titulo);
    printf("\nAutor: %s", livro->Autor);
    printf("\nCategoria: %s", livro->Area);
    printf("\nAno de Publicação: %d", livro->AnoDePublicacao);
    printf("\nNúmero de Requisições: %d", livro->NumeroDeRequisicoes);
    printf("\nFornecedor: %s", livro->Fornecedor);
}





// USA O MOSTRARLIVRO() PARA LISTAR TODOS OS LIVROS QUE EXISTEM
void MostrarLivrosPorArea(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("Mostrar Livros por Area", "Livros");

    if (hl->QuantidadeDeLivros == 0)
    {
        MensagemNaoExistemLivros();
        return;
    }

    // PARA FAZER LOOP PELAS CATEGORIAS
    CATEGORIA *categoria = hl->Inicio;

    // FAZ LOOP PELAS CATEGORIAS
    while (categoria)
    {
        // PARA FAZER LOOP PELOS LIVROS
        LIVRO *livro = categoria->Inicio;

        printf("\n# ========= < Area: %s >\n\n", categoria->Nome);

        // FAZ LOOP PELOS LIVROS
        while (livro)
        {
            // FAZ PRINTF DE TODAS AS INFORMACOES DO LIVRO
            MostrarLivro(livro);
            printf("\n\n");

            // SELECIONA O LIVRO SEGUINTE NO LOOP
            livro = livro->Seguinte;
        }

        // SELECIONA A CATEGORIA SEGUINTE NO LOOP
        categoria = categoria->Seguinte;
    }

    PAUSE_CLS;
}





// MOSTRA A AREA COM MAIS LIVROS
void MostrarAreaComMaisLivros(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("Mostrar Area com mais Livros", "Livros");

    if (hl->QuantidadeDeLivros == 0)
    {
        MensagemNaoExistemLivros();
        return;
    }

    // PARA FAZER O LOOP PELAS CATEGORIAS
    CATEGORIA *categoria = hl->Inicio;

    // PARA GUARDAR A CATEGORIA COM MAIS LIVROS
    CATEGORIA *maior_categoria = NULL;
    int maxLivros = 0;

    // FAZ LOOP PELAS CATEGORIAS
    while (categoria)
    {
        // SE A QUANTIDADE DE LIVROS NA CATEGORIA FOI MAIOR DO QUE A QUANTIDADE DE LIVROS DA ATUAL CATEGORIA COM MAIS LIVROS
        if (categoria->QuantidadeDeLivros > maxLivros)
        {
            // GUARDA A CATEGORIA NA VARIAVEL
            maior_categoria = categoria;
        }

        // SELECIONA A PROXIMA CATEGORIA
        categoria = categoria->Seguinte;
    }

    printf("Area com mais livros: %s", maior_categoria->Nome);

    PAUSE_CLS;
}





// VERIFICAR SE UM LIVRO EXISTE
// E IMPRIMIR OS SEUS DADOS
void PesquisarLivroPorISBN(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("Pesquisar Livro por ISBN", "Livros");

    if (hl->QuantidadeDeLivros == 0)
    {
        MensagemNaoExistemLivros();
        return;
    }

    // LE O ISBN DO UTILIZADOR
    int isbn = 0;
    printf("Insira o ISBN do livro a pesquisar: ");
    scanf("%d", &isbn);

    // GUARDA AS CATEGORIAS PARA FAZER LOOP POR ELAS
    CATEGORIA *categorias = hl->Inicio;

    // FAZ LOOP POR TODAS AS CATEGORIAS
    while (categorias)
    {
        LIVRO *livro = categorias->Inicio;

        // FAZ LOOP POR TODOS OS LIVROS
        while (livro)
        {
            // VERIFICA SE O ISBN DO LIVRO ATUAL NO LOOP CORRESPONDE AO INTRODUZIDO PELO UTILIZADOR
            if (livro->ISBN == isbn)
            {
                // IMPRIME AS INFORMAÇOES DO LIVRO
                printf("\nLivro encontrado!\n\n\n\nInformações do Livro encontrado:\n\n");
                MostrarLivro(livro);
                PAUSE_CLS;
                return;
            }

            // VAI PARA O LIVRO SEGUINTE
            livro = livro->Seguinte;
        }

        // VAI PARA A CATEGORIA SEGUINTE
        categorias = categorias->Seguinte;
    }

    printf("Não foi encontrado nenhum Livro com o ISBN %d", isbn);
    PAUSE_CLS;
}





void EncontrarLivroMaisRecente(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("Encontrar Livro mais recente", "Livros");

    // VERIFICA SE EXISTEM LIVROS
    if (hl->QuantidadeDeLivros == 0)
    {
        MensagemNaoExistemLivros();
        return;
    }

    // SELECIONA A PRIMEIRA CATEGORIA
    CATEGORIA *categorias = hl->Inicio;

    // VARIAVEIS PARA FAZER A COMPARACAO
    LIVRO *livro_mais_recente = NULL;
    int maxAno = 0;

    // FAZ LOOP PELAS CATEGORIAS
    while (categorias)
    {
        // VAI BUSCAR O LIVRO A CATEGORIA
        LIVRO *livro = categorias->Inicio;

        // FAZ LOOP PELOS LIVROS DA CATEGORIA
        while (livro)
        {
            // VERIFICA SE O ANO DE PUBLICACAO DO LIVRO SELECIONADO E MAIOR QUE A DO ANO DO LIVRO ATUALMENTE GUARDADO NA COMPARACAO
            if (livro->AnoDePublicacao > maxAno)
            {
                livro_mais_recente = livro;
                maxAno = livro_mais_recente->AnoDePublicacao;
            }

            // SELECIONA O LIVRO SEGUINTE
            livro = livro->Seguinte;
        }

        // SELECIONA A CATEGORIA SEGUINTE
        categorias = categorias->Seguinte;
    }

    // IMPRIME O LIVRO
    printf("\n\nLivro mais recente encontrado:\n\n");
    MostrarLivro(livro_mais_recente);

    PAUSE_CLS;
}





void EncontrarLivroMaisRequisitado(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("Encontrar Livro mais Requisitado", "Livros");

    if (hl->QuantidadeDeLivros == 0)
    {
        MensagemNaoExistemLivros();
        return;
    }

    CATEGORIA *categorias = hl->Inicio;

    LIVRO *livro_mais_requisitado = NULL;
    int requisicoes = 0;

    while (categorias)
    {
        LIVRO *livro = categorias->Inicio;

        while (livro)
        {
            if (livro->NumeroDeRequisicoes > requisicoes)
            {
                livro_mais_requisitado = livro;
                requisicoes = livro->NumeroDeRequisicoes;
            }

            livro = livro->Seguinte;
        }

        categorias = categorias->Seguinte;
    }

    printf("\n\nLivro mais requisitado encontrado:\n\n");
    MostrarLivro(livro_mais_requisitado);

    PAUSE_CLS;
}





void EncontrarCategoriasComMaisRequisicoes(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("Encontrar area com mais Requisições", "Livros");

    if (!hl->QuantidadeDeLivros == 0)
    {
        MensagemNaoExistemLivros();
        return;
    }

    CATEGORIA *categorias = hl->Inicio;

    CATEGORIA *categoria_mais_requisitada = NULL;
    int requisicoes = 0;

    while (categorias)
    {
        if (categorias->NumeroDeRequisicoes > requisicoes)
        {
            categoria_mais_requisitada = categorias;
            requisicoes = categorias->NumeroDeRequisicoes;

            break;
        }

        categorias = categorias->Seguinte;
    }

    printf("\n\nCategoria mais requisitada encontrada:\n\n");
    printf("Nome: %s", categoria_mais_requisitada->Nome);
    printf("\nNúmero de Requisições: %d", categoria_mais_requisitada->NumeroDeRequisicoes);

    PAUSE_CLS;
}



void CriarLivro(LISTA_CATEGORIAS *hl)
{
    ImprimirDuplo("WIZARD: Criar novo Livro", "Livros");
    LIVRO *l = Wizard_Livro(hl);
    CLS;

    ImprimirFuncao("Livro criado com sucesso!");
    MostrarLivro(l);
    PAUSE_CLS;
}


















void MenuLivros(LISTA_CATEGORIAS *hl)
{
    int escolha = 0;
    do
    {
        ImprimirMenu("Gerir Livros");

        printf("\n1. Criar Livro");
        printf("\n2. Listar Livros por Area");
        printf("\n3. Mostrar Area com mais Livros");
        printf("\n4. Pesquisar Livro por ISBN");
        printf("\n5. Encontrar Livro mais recente");
        printf("\n\n0. Voltar");
        printf("\n\n\n\n\n »---> Escolha: ");

        scanf("%d", &escolha);

        CLS;

        switch(escolha)
        {
            case 1: CriarLivro(hl); break;
            case 2: MostrarLivrosPorArea(hl); break;
            case 3: MostrarAreaComMaisLivros(hl); break;
            case 4: PesquisarLivroPorISBN(hl); break;
            case 5: EncontrarLivroMaisRecente(hl); break;
        }
    } while (escolha != 0);
}
#endif
