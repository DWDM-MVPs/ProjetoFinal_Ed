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


static LISTA_CATEGORIAS *hl;








void ImprimirMenu(char titulo[100])
{
    printf("# ===================== # > %s < # ===================== #\n\n", titulo);
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
}





// USA O MOSTRARLIVRO() PARA LISTAR TODOS OS LIVROS QUE EXISTEM
void MostrarLivrosPorArea()
{
    ImprimirMenu("Mostrar Livros por Area");

    // PARA FAZER LOOP PELAS CATEGORIAS
    CATEGORIA *categoria = hl->Inicio;

    // FAZ LOOP PELAS CATEGORIAS
    while (categoria)
    {
        // PARA FAZER LOOP PELOS LIVROS
        LIVRO *livro = categoria->ListaDeLivros->Inicio;

        printf("\n# ========= < Area: %s >\n\n", categoria->Nome);

        // FAZ LOOP PELOS LIVROS
        while (livro)
        {
            // FAZ PRINTF DE TODAS AS INFORMACOES DO LIVRO
            MostrarLivro(livro);

            // SELECIONA O LIVRO SEGUINTE NO LOOP
            livro = livro->Seguinte;
        }

        // SELECIONA A CATEGORIA SEGUINTE NO LOOP
        categoria = categoria->Seguinte;
    }

    PAUSE_CLS;
}





// MOSTRA A AREA COM MAIS LIVROS
void MostrarAreaComMaisLivros()
{
    ImprimirMenu("Mostrar Area com mais Livros");

    // PARA FAZER O LOOP PELAS CATEGORIAS
    CATEGORIA *categoria = hl->Inicio;

    // PARA GUARDAR A CATEGORIA COM MAIS LIVROS
    CATEGORIA *maior_categoria = NULL;
    int maxLivros = 0;

    // FAZ LOOP PELAS CATEGORIAS
    while (categoria)
    {
        // SE A QUANTIDADE DE LIVROS NA CATEGORIA FOI MAIOR DO QUE A QUANTIDADE DE LIVROS DA ATUAL CATEGORIA COM MAIS LIVROS
        if (categoria->ListaDeLivros->QuantidadeDeLivros > maxLivros)
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
void PesquisarLivroPorISBN()
{
    if (hl->Quantidade == 0) return;

    ImprimirMenu("Pesquisar Livro por ISBN");

    // LE O ISBN DO UTILIZADOR
    int isbn = 0;
    printf("Insira o ISBN do livro a pesquisar: ");
    scanf("%d", &isbn);

    // GUARDA AS CATEGORIAS PARA FAZER LOOP POR ELAS
    CATEGORIA *categorias = hl->Inicio;

    // FAZ LOOP POR TODAS AS CATEGORIAS
    while (categorias)
    {
        LIVRO *livro = categorias->ListaDeLivros->Inicio;

        // FAZ LOOP POR TODOS OS LIVROS
        while (livro)
        {
            // VERIFICA SE O ISBN DO LIVRO ATUAL NO LOOP CORRESPONDE AO INTRODUZIDO PELO UTILIZADOR
            if (livro->ISBN == isbn)
            {
                // IMPRIME AS INFORMAÇOES DO LIVRO
                printf("\nLivro encontrado!\n\n\n\nInformações do livro encontrado:\n\n");
                MostrarLivro(livro);
                return;
            }

            // VAI PARA O LIVRO SEGUINTE
            livro = livro->Seguinte;
        }

        // VAI PARA A CATEGORIA SEGUINTE
        categorias = categorias->Seguinte;
    }

    printf("Não foi encontrado nenhum livro com o ISBN %d", isbn);
    PAUSE_CLS;
}





void EncontrarLivroMaisRecente()
{
    if (hl->Quantidade == 0) return;

    ImprimirMenu("Encontrar Livro mais recente");

    CATEGORIA *categorias = hl->Inicio;

    LIVRO *livro_mais_recente = NULL;
    int maxAno = 0;

    while (categorias)
    {
        LIVRO *livro = categorias->ListaDeLivros->Inicio;

        while (livro)
        {
            if (livro->AnoDePublicacao > maxAno)
            {
                livro_mais_recente = livro;
                maxAno = livro_mais_recente->AnoDePublicacao;
            }

            livro = livro->Seguinte;
        }

        categorias = categorias->Seguinte;
    }

    printf("\n\nLivro mais recente encontrado:\n\n");
    MostrarLivro(livro_mais_recente);

    PAUSE_CLS;
}





void EncontrarLivroMaisRequisitado()
{
    if (hl->Quantidade == 0) return;

    ImprimirMenu("Encontrar Livro mais Requisitado");

    CATEGORIA *categorias = hl->Inicio;

    LIVRO *livro_mais_requisitado = NULL;
    int requisicoes = 0;

    while (categorias)
    {
        LIVRO *livro = categorias->ListaDeLivros->Inicio;

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

    printf("\n\Livro mais requisitado encontrado:\n\n");
    MostrarLivro(livro_mais_requisitado);

    PAUSE_CLS;
}





void EncontrarCategoriasComMaisRequisicoes()
{
    if (!hl || !hl->Inicio) return;

    ImprimirMenu("Encontrar area com mais Requisições");

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






// PEDE INPUT AO UTILIZADOR
// E CRIA UM LIVRO NOVO
LIVRO *Wizard_Livro()
{
    ImprimirMenu("WIZARD: Criar novo Livro");

    int isbn;
    char titulo[100];
    char autor[100];
    char area[100];
    int anoDePublicacao;

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



    printf("\nLivro criado com sucesso!");
    PAUSE_CLS;
    return Criar_Livro_Preenchido(isbn, titulo, autor, area, anoDePublicacao, 0);
}














int main()
{
    setlocale(LC_ALL, "");

    hl = Criar_ListaCategorias();

    LIVRO *l = Wizard_Livro();
    CLS;
    ImprimirMenu("Livro criado");
    MostrarLivro(l);
    PAUSE_CLS;
    AdicionarLivro(l);

    MostrarLivrosPorArea();
    MostrarAreaComMaisLivros();

    PesquisarLivroPorISBN();

    EncontrarLivroMaisRecente();

	return 0;
}
