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





static LISTA_CATEGORIAS *hl;





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





// ADICIONA UM LIVRO A LISTA
void AdicionarLivroNaLista(LISTA_LIVROS *lista_livros, LIVRO *livro)
{
    if (!lista_livros || !livro) return;

    // ADICIONA O LIVRO A LSITA
    livro->Seguinte = lista_livros->Inicio;
    lista_livros->Inicio = livro;

    // ADICIONA 1 AO VALOR DA QUANTIDADE DE LIVROS NA LISTA
    lista_livros->QuantidadeDeLivros = lista_livros->QuantidadeDeLivros + 1;
}





// VERIFICA SE UMA CATEGORIA J� EXISTE
CATEGORIA *ExisteCategoria(LIVRO *livro)
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
// E CRIA UMA NOVA CATEGORIA CASO AINDA N�O EXISTA
void AdicionarLivro(LIVRO *livro)
{
    if (!hl || !livro) return;

    // METE NA VARIAVEL A CATEGORIA EXISTENTE
    CATEGORIA *categoria = ExisteCategoria(livro);

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
        AdicionarLivroNaLista(categoria->ListaDeLivros, livro);

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
        AdicionarLivroNaLista(categoria->ListaDeLivros, livro);
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
    printf("\nAno de Publica��o: %d", livro->AnoDePublicacao);
    printf("\nN�mero de Requisi��es: %d", livro->NumeroDeRequisicoes);
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
                // IMPRIME AS INFORMA�OES DO LIVRO
                printf("\nLivro encontrado!\n\n\n\nInforma��es do livro encontrado:\n\n");
                MostrarLivro(livro);
                return;
            }

            // VAI PARA O LIVRO SEGUINTE
            livro = livro->Seguinte;
        }

        // VAI PARA A CATEGORIA SEGUINTE
        categorias = categorias->Seguinte;
    }

    printf("N�o foi encontrado nenhum livro com o ISBN %d", isbn);
    PAUSE_CLS;
}





void EncontrarLivroMaisRecente()
{
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

    printf("Insira o T�tulo do Livro: ");
    scanf("%c",&temp);
    scanf("%[^\n]", titulo);


    printf("Insira o Autor do Livro: ");
    scanf("%c",&temp);
    scanf("%[^\n]", autor);


    printf("Insira a Area do Livro: ");
    scanf("%c",&temp);
    scanf("%[^\n]", area);


    printf("Insira o Ano de Publica��o do Livro: ");
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
