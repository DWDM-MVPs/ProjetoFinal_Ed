#ifndef _LIV_H_
#define _LIV_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "hashing.h"
#include "lista.h"
#include <conio.h>
#define BUF_LEN 120

/** ---------- CRIAR LIVRO ---------- */

LIVRO *criarLiv()
{
    LIVRO *aux = (LIVRO *)malloc(sizeof(LIVRO));
    aux->ISBN = 0;
    aux->numRequisicoes = 0;
    aux->requisitado = 0;
    return aux;
}

/** ---------- VALIDAR AREA DO LIVRO ---------- */

int validarArea(char *area)
{
    if(!area)
    {
        printf("\n>> Ocorreu um erro na leitura da area\n");
        return 0;
    }
    int tamanho = strlen(area);

    if(tamanho != 3)
    {
        printf("\n>>Por favor insira uma area com tres digitos.");
        return 0;
    }


    return 1;
}

/** ---------- VALIDAR O ISBN DE UM LIVRO ---------- */

int validarISBN(int ISBN)
{
    if(!ISBN)
    {
        printf("\n>> Ocorreu um erro na leitura do ISBN\n");
        return;
    }
    char isbnStr[15];

    sprintf(isbnStr, "%d", ISBN);
    int tamanho = strlen(isbnStr);

    if(tamanho != 8)
    {
        printf("\n>>Por favor insira um numero com oito algarismos.");
        return 0;
    }


    return 1;
}

/** ---------- PROCURAR UM LIVRO, DANDO O ISBN ---------- */

LIVRO *existeLivDandoISBN(HASHING *hashingLiv, int isbnProcurar) /* O ENUNCIADO ESTIPULA QUE DEVEMOS MOSTRAR O LIVRO, POR ENQUANTO SÓ O ESTAMOS A ENVIAR */
{
    if(!hashingLiv)
    {
        printf("\n>> O hashing de livros não existe\n");
        return NULL;
    }


    if(!hashingLiv->inicio)
    {
        printf("\n>> O hashing de livros está vazio (0 livros)\n");
        return NULL;
    }


    if(!isbnProcurar)
    {
        printf("\n>> O ISBN do livro não existe\n");
        return NULL;
    }



    NODO_HASHING *nodoHash = hashingLiv->inicio;


    while(nodoHash)
    {
        NODO *nodo = nodoHash->lista->inicio;


        while(nodo)
        {
            LIVRO *infoLiv = nodo->info;


            if(isbnProcurar == infoLiv->ISBN)
                return nodo->info;



            nodo = nodo->seg;
        }
        nodoHash = nodoHash->seg;
    }
}

/** ---------- PREENCHER OS DADOS DE UM LIVRO ---------- */

void preencherLivro(LIVRO *li)
{
    char stringTitulo[100];
    char stringArea[100];
    char temp;

    printf("\n\n__________________________________________________\n");
    printf("\n-            Registo de um novo livro            -");
    printf("\n__________________________________________________\n\n");

    int validadeArea, validadeISBN;

    do
    {
        printf("\n>> Area (3 primeiros caracteres): ");
        scanf("%s", stringArea);
        validadeArea = validarArea(stringArea);

    } while(validadeArea == 0);

    li->area = (char *)malloc((strlen(stringArea) + 1) * sizeof(char));
    strcpy(li->area, stringArea);

    do
    {
        printf("\n>> ISBN: ");
        scanf("%d", &(li->ISBN));
        validadeISBN = validarISBN(li->ISBN);

    } while(validadeISBN == 0);

    printf("\n>> Titulo: ");
    scanf("%c",&temp);
    scanf("%[^\n]", stringTitulo);
    li->titulo = (char *)malloc((strlen(stringTitulo) + 1) * sizeof(char));
    strcpy(li->titulo, stringTitulo);

    time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    int anoAtual = current_time->tm_year + 1900;

    do
    {
        printf("\n>> Ano: ");
        scanf("%d", &(li->ano));

    } while(li->ano < 1900 || li->ano > anoAtual);
}

/** ---------- VERIFICAR SE EXISTE A AREA DO LIVRO ---------- */

NODO_HASHING *existeArea(HASHING *hashing, LIVRO *livro)
{
    if(!hashing)
        return NULL;

    if(!hashing->inicio)
        return NULL;

    NODO_HASHING *aux = hashing->inicio;

    while(aux)
    {
        if(strcasecmp(aux->nome, livro->area) == 0)
            return aux;

        aux = aux->seg;
    }
    return NULL;
}

/** ---------- INSERIR UM LIVRO DENTRO DA RESPEITIVA AREA ---------- */

void inserirLivro(HASHING *hashing, NODO *nodoLivro)
{
    if(!hashing)
    {
        printf("\n>> O hashing de areas não existe\n");
        return;
    }

    if(!nodoLivro)
    {
        printf("\n>> O livro não existe\n");
        return;
    }

    LIVRO *livroInfo = nodoLivro->info;

    NODO_HASHING *areaCorrespondente = existeArea(hashing, livroInfo);

    if(areaCorrespondente != NULL)
        inserirInicio(areaCorrespondente->lista, nodoLivro);

    else
    {
        char stringTemp[50];
        strcpy(stringTemp, livroInfo->area);

        NODO_HASHING *nodoHashing = criarNodoHashing();

        nodoHashing->nome = (char *)malloc((strlen(stringTemp) + 1) * sizeof(char));

        strcpy(nodoHashing->nome, livroInfo->area);

        nodoHashing->lista = criarLista();
        inserirInicio(nodoHashing->lista, nodoLivro);

        inserirNodoHashing(hashing, nodoHashing);
    }
}

/** ---------- MOSTRAR OS DADOS DE UM LIVRO ---------- */

void mostrarLivros(LIVRO *liv)
{
    if(!liv)
    {
        printf("Não existe livros.");
        return;
    }

    printf("\n>> %s", liv->titulo);
    printf("\n____________________________________");
    printf("\n\n>> Ano: %d\n", liv->ano);
    printf("\n>> ISBN: %d\n", liv->ISBN);
    printf("\n>> Requisitado: ");
    if(liv->requisitado)
        printf("Sim\n");
    else
        printf("Não\n");

    printf("\n>> Requisições totais: %d\n\n", liv->numRequisicoes);
}

/** ---------- MOSTRAR A LISTA DE LIVROS ---------- */

int mostrarListaLiv(LISTA *lista, int count)
{
    NODO *nodo = lista->inicio;

    while(nodo)
    {
        LIVRO *dados = nodo->info;
        mostrarLivros(dados);
        nodo = nodo->seg;
        count++;
        if(count%5 == 0)
            pressioneQualquerTecla();
    }
    return count;
}

/** ---------- MOSTRAR TODOS OS LIVROS DIVIDODOS POR AREAS ---------- */

void mostrarArea(HASHING *hashingLiv)
{
    int count = 0;

    if(!hashingLiv)
    {
        printf("\n>> O hashing de livros não existe\n");
        return;
    }

    if(!hashingLiv->inicio)
    {
        printf("\n>> O hashing de livros está vazio (0 livros)\n");
        return;
    }

    NODO_HASHING *area = hashingLiv->inicio;

    while(area) /* Enquanto houver livros */
    {
        printf("\n\n_______________________________________________________\n\n");
        printf("-                         %s                         -", area->nome);
        printf("\n_______________________________________________________\n\n");

        if(area->lista)
            count = mostrarListaLiv(area->lista, count);

        area = area->seg;
    }
}

/** ---------- PROCURAR UM LIVRO, DANDO O ISBN ---------- */

LIVRO *existeLiv(HASHING *hashingLiv)
{
    if(!hashingLiv)
    {
        printf("\n>> O hashing de livros não existe\n");
        return NULL;
    }

    if(!hashingLiv->inicio)
    {
        printf("\n>> O hashing de livros está vazio (0 livros)\n");
        return NULL;
    }

    int isbnProcurar;

    printf("\n>> ISBN a procurar: ");
    scanf("%d", &isbnProcurar);
    printf("\n");

    NODO_HASHING *nodoHash = hashingLiv->inicio;

    while(nodoHash)
    {
        NODO *nodo = nodoHash->lista->inicio;

        while(nodo)
        {
            LIVRO *infoLiv = nodo->info;

            if(isbnProcurar == infoLiv->ISBN)
                return nodo->info;


            nodo = nodo->seg;
        }
        nodoHash = nodoHash->seg;
    }
}

/** ---------- LISTAR OS LIVROS ATUALMENTE REQUISITADOS (ORGANIZADOS POR ÁREA) ---------- */

void ListarLivRequisitados(HASHING *hashingLiv)
{
    if(!hashingLiv)
    {
        printf("\n>> O hashing de livros não existe\n");
        return;
    }

    if(!hashingLiv->inicio)
    {
        printf("\n>> o hashing de livros está vazio (0 areas)\n");
        return;
    }

    NODO_HASHING *nodoHashing = hashingLiv->inicio;

    while(nodoHashing) /* Percorrer as areas dos livros */
    {
        printf("\n_______________________________________________________\n\n");
        printf("-                         %s                         -", nodoHashing->nome);
        printf("\n_______________________________________________________\n\n");

        NODO *nodoLiv = nodoHashing->lista->inicio;

        while(nodoLiv) /* Percorrer os livros */
        {
            LIVRO *liv = nodoLiv->info;

            if(liv->requisitado) /* Verificar se o livro está requisitado */
                mostrarLivros(liv);

            nodoLiv = nodoLiv->seg;
        }
        nodoHashing = nodoHashing->seg;
    }
    printf("\n_______________________________________________________\n\n");
}

/** ---------- DETERMINAR QUAL O LIVRO MAIS REQUISITADO ---------- */

LIVRO *livMaisRequisitado(HASHING *hashingLiv)
{
    if(!hashingLiv)
    {
        printf("\n>> O hashing de livros não existe\n");
        return NULL;
    }

    if(!hashingLiv->inicio)
    {
        printf("\n>> O hashing de livros está vazio (0 livros)\n");
        return NULL;
    }

    int numRequisicoes = 0;
    LIVRO *livroDevolver = NULL;
    NODO_HASHING *nodoHash = hashingLiv->inicio;

    while(nodoHash)
    {
        NODO *nodo = nodoHash->lista->inicio;

        while(nodo)
        {
            LIVRO *infoLivro = nodo->info;

            if(infoLivro->numRequisicoes > numRequisicoes)
            {
                numRequisicoes = infoLivro->numRequisicoes;
                livroDevolver = infoLivro;
            }
            nodo = nodo->seg;
        }
        nodoHash = nodoHash->seg;
    }
    return livroDevolver;
}

/** ---------- DETERMINAR QUAL A AREA MAIS REQUISITADA ---------- */

NODO_HASHING *areaMaisRequisitada(HASHING *hashingLiv)
{
    if(!hashingLiv)
    {
        printf("\n>> O hashing de livros não existe\n");
        return NULL;
    }

    if(!hashingLiv->inicio)
    {
        printf("\n>> O hashing de livros está vazio (0 livros)\n");
        return NULL;
    }
    int requisitadosAtual = 0;
    int requisitadosMaior = 0;
    NODO_HASHING *areaDevolver = NULL;
    NODO_HASHING *area = hashingLiv->inicio;

    while(area)
    {
        NODO *nodo = area->lista->inicio;

        while(nodo)
        {
            LIVRO *liv = nodo->info;

            if(liv->requisitado)
                requisitadosAtual++;

            nodo = nodo->seg;
        }
        if(requisitadosAtual > requisitadosMaior)
        {
            areaDevolver = area;
            requisitadosMaior = requisitadosAtual;
        }
        requisitadosAtual = 0;
        area = area->seg;
    }
    return areaDevolver;
}
#endif
