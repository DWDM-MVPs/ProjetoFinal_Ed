#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "livros.h"
#include "requisitantes.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;

#define MSG_SUCESSO "Pedido efetuado com sucesso!";





static HASHING_LIVROS *hl;





LIVRO *Criar_Livro()
{
    LIVRO *livro = (LIVRO *)malloc(sizeof(LIVRO));

    livro->ISBN = 0;
    livro->AnoDePublicacao = 0;
    livro->NumeroDeRequisicoes = 0;

    return livro;
}

NO_LIVRO *Criar_NoLivro()
{
    NO_LIVRO *no_livro = (NO_LIVRO *)malloc(sizeof(NO_LIVRO));

    no_livro->Livro = NULL;
    no_livro->Seguinte = NULL;

    return no_livro;
}

LISTA_LIVROS *Criar_ListaLivros()
{
    LISTA_LIVROS *lista_livros = (LISTA_LIVROS *)malloc(sizeof(LISTA_LIVROS));

    lista_livros->Inicio = NULL;
    lista_livros->QuantidadeDeLivros = 0;

    return lista_livros;
}

    NO_HASHING_LIVRO *Criar_NoHashingLivro()
{
    NO_HASHING_LIVRO *no_hashing_livro = (NO_HASHING_LIVRO *)malloc(sizeof(NO_HASHING_LIVRO));

    no_hashing_livro->Seguinte = NULL;
    no_hashing_livro->NumeroDeRequisicoes = 0;

    return no_hashing_livro;
}

HASHING_LIVROS *Criar_HashingLivro()
{
    HASHING_LIVROS *hashing_livros = (HASHING_LIVROS *)malloc(sizeof(HASHING_LIVROS));

    hashing_livros->Inicio = NULL;
    hashing_livros->Quantidade = 0;

    return hashing_livros;
}











void ImprimirMenu(char titulo[100])
{
    printf("# ===================== # > %s < # ===================== #\n\n", titulo);
}





bool AnoBissexto(int ano)
{
     return ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0;
}





bool DataValida(DATA *data)
{
    // VERIFICA OS DIAS MAXIMOS PARA CADA MES
    if (data->Dia < 1 || data->Dia > 31)
    {
        return false;
    }
    if (data->Mes < 1 || data->Mes > 12)
    {
        return false;
    }
    // ANO BISSEIXTO (COISO DE FEVEREIRO)
    if (data->Mes == 2)
    {
        if (AnoBissexto(data->Ano))
        {
            return (data->Dia <= 29);
        }
        else
        {
            return (data->Dia <= 28);
        }
    }
    // MESES QUE SO TEM 30 DIAS
    if (data->Mes == 4 || data->Mes == 6 || data->Mes == 9 || data->Mes == 11)
    {
        return (data->Dia <= 30);
    }

    // SE NAO FALHAR NADA DEVOLVE TRUE, PORQUE A DATA E VALIDA
    return true;
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





// ADICIONA UM LIVRO À LISTA
void AdicionarLivroNaLista(LISTA_LIVROS *lista_livros, LIVRO *livro)
{
    if (!lista_livros || !livro) return;

    // CRIAR UM COISO COM O LIVRO
    NO_LIVRO *no_livro = Criar_NoLivro();
    no_livro->Livro = livro;

    // SE A LISTA JA TIVER LIVROS
    if (lista_livros->Inicio)
    {
        // FAZ O LIVRO ATUAL APONTAR PARA O LIVRO QUE SUPOSTAMENTE ESTAVA EM PRIMEIRO NA LISTA
        no_livro->Seguinte = lista_livros->Inicio;
    }
    // METE O LIVRO CRIADO AQUI NO INICIO DA LISTA
    lista_livros->Inicio = no_livro;

    lista_livros->QuantidadeDeLivros = lista_livros->QuantidadeDeLivros + 1;
}





// VERIFICA SE UMA CATEGORIA JÁ EXISTE
NO_HASHING_LIVRO *ExisteCategoria(LIVRO *livro)
{
    if (!hl || !livro) return NULL;

    // PARA FAZER LOOP PELAS CATEGORIAS
    NO_HASHING_LIVRO *no_hashing_livro = hl->Inicio;

    // FAZ LOOP PELAS CATEGORIAS
    while(no_hashing_livro)
    {
        // VERIFICA SE A CATEGORIAS EXISTE
        if(strcasecmp(no_hashing_livro->Nome, livro->Area) == 0)
        {
            // SE A CATEGORIA EXISTIR, DEVOLVE A CATEGORIA
            return no_hashing_livro;
        }

        // SELECIONA A CATEGORIA SEGUINTE
        no_hashing_livro = no_hashing_livro->Seguinte;
    }

    return NULL;
}





// ADICIONA UM LIVRO AO 'HASHING_LIVROS'
// E CRIA UMA NOVA CATEGORIA CASO AINDA NÃO EXISTA
void AdicionarLivro(LIVRO *livro)
{
    if (!hl || !livro) return;

    // METE NA VARIAVEL A CATEGORIA EXISTENTE
    NO_HASHING_LIVRO *no_hashing_livro = ExisteCategoria(livro);

    // CASO NAO EXISTA ESSA CATEGORIA, CRIA UMA NOVA
    if (!no_hashing_livro)
    {
        // CRIA UMA NOVA CATEGORIA
        no_hashing_livro = Criar_NoHashingLivro();

        // CRIA A LISTA DE LIVROS VAZIA PARA ESSA CATEGORIA
        no_hashing_livro->ListaDeLivros = Criar_ListaLivros();

        // DA O NOME A CATEGORIA
        strcpy(no_hashing_livro->Nome, livro->Area);

        // ADICIONA O LIVRO NA NOVA CATEGORIA
        AdicionarLivroNaLista(no_hashing_livro->ListaDeLivros, livro);

        // CASO NAO HAJA NENHUMA AREA
        if (!hl->Inicio)
        {
            // METE A NOVA CATEGORIA NO INICIO DA LISTA DAS CATEGORIAS
            hl->Inicio = no_hashing_livro;
        }
    }
    // CASO EXISTA A CATEGORIA
    else
    {
        // METE LA O LIVRINHO
        AdicionarLivroNaLista(no_hashing_livro->ListaDeLivros, livro);
    }
    return;
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
    NO_HASHING_LIVRO *no_hashing_livro = hl->Inicio;

    // FAZ LOOP PELAS CATEGORIAS
    while (no_hashing_livro)
    {
        // PARA FAZER LOOP PELOS LIVROS
        NO_LIVRO *no_livro = no_hashing_livro->ListaDeLivros->Inicio;

        printf("\n# ========= < Area: %s >\n\n", no_hashing_livro->Nome);

        // FAZ LOOP PELOS LIVROS
        while (no_livro)
        {
            // FAZ PRINTF DE TODAS AS INFORMACOES DO LIVRO
            MostrarLivro(no_livro->Livro);

            // SELECIONA O LIVRO SEGUINTE NO LOOP
            no_livro = no_livro->Seguinte;
        }

        // SELECIONA A CATEGORIA SEGUINTE NO LOOP
        no_hashing_livro = no_hashing_livro->Seguinte;
    }

    PAUSE_CLS;
}





// MOSTRA A AREA COM MAIS LIVROS
void MostrarAreaComMaisLivros()
{
    ImprimirMenu("Mostrar Area com mais Livros");

    // PARA FAZER O LOOP PELAS CATEGORIAS
    NO_HASHING_LIVRO *categoria = hl->Inicio;

    // PARA GUARDAR A CATEGORIA COM MAIS LIVROS
    NO_HASHING_LIVRO *maior_categoria = NULL;
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
void *PesquisarLivroPorISBN()
{
    ImprimirMenu("Pesquisar Livro por ISBN");
    int isbn = 0;

    printf("Insira o ISBN do livro a pesquisar: ");
    scanf("%d", &isbn);

    NO_HASHING_LIVRO *categorias = hl->Inicio;

    while (categorias)
    {
        LISTA_LIVROS *lista_livros = categorias->ListaDeLivros;

        while (lista_livros)
        {
            NO_LIVRO *no_livro = lista_livros->Inicio;

            if (no_livro->Livro->ISBN == isbn)
            {
                printf("\nLivro encontrado!\n\n\n\nInformações do livro encontrado:\n\n");
                MostrarLivro(no_livro->Livro);

                return NULL;
            }
        }
    }

    printf("Não foi encontrado nenhum livro com o ISBN %d", isbn);
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

    hl = Criar_HashingLivro();

    LIVRO *l = Wizard_Livro();
    CLS;
    ImprimirMenu("Livro criado");
    MostrarLivro(l);
    PAUSE_CLS;
    AdicionarLivro(l);

    MostrarLivrosPorArea();
    MostrarAreaComMaisLivros();

    PesquisarLivroPorISBN();

	return 0;
}
