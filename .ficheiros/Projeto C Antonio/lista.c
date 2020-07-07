/** ---------- INCLUDES ---------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashing.h"
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define BUF_LEN 256

/** ---------- CRIAR UMA NOVA LISTA ---------- */

LISTA *criarLista()
{
    LISTA *aux = (LISTA *)malloc(sizeof(LISTA));
    aux->inicio = NULL;
    aux->nel = 0;

    return aux;
}

/** ---------- DESTRUIR UMA DADA LISTA ---------- */

void destruirLista(LISTA *lista, void (*func)(void *))
{
    //if(!lista)
   //    return;

    NODO *auxNodo = lista->inicio;
    NODO *aux = NULL;

    while(auxNodo)
    {
        aux = auxNodo->seg;
        (*func)(auxNodo->info);
        free(auxNodo);
        auxNodo = aux;
    }
    free(lista);
    lista = NULL;
}

/** ---------- DESTRUIR REQUISICAO ---------- */

void destruirRequisicao(void *requisicao)
{
    if(!requisicao)
    {
        printf("\n>> A requisi��o n�o existe\n");
        return;
    }

    REQUISICAO *requi = (REQUISICAO *)requisicao;

    requi->DataSupostaDaEntrega = NULL;
    free(requi->DataSupostaDaEntrega);

    requi->DataRealDaEntrega = NULL;
    free(requi->DataRealDaEntrega);

    requi->DataRequisicao = NULL;
    free(requi->DataRequisicao);

    requi = NULL;
    free(requi);
}


/** ---------- DESTRUIR REQUISITANTE ---------- */

void destruirRequisitante(void *requisitante)
{
    if(!requisitante)
    {
        printf("\n>> O requisitante n�o existe\n");
        return;
    }

    REQUISITANTE *req = (REQUISITANTE *)requisitante;
    req->nome = NULL;
    free(req->nome);

    if(req->requisicao)
        destruirLista(req->requisicao, destruirRequisicao);

    req->requisicao = NULL;
    req = NULL;
    free(req);
}

/** ---------- DESTRUIR LIVRO ---------- */

void destruirLivro(void *livro)
{
    if(!livro)
    {
        printf("\n>> O livro n�o existe\n");
        return;
    }

    LIVRO *liv = (LIVRO *)livro;

    liv->area = NULL;
    free(liv->area);

    liv->titulo = NULL;
    free(liv->titulo);
    free(liv);
}

/** ---------- CRIAR UM NOVO NODO DE LISTA ---------- */

NODO *criarNodo()
{
    NODO *aux = (NODO *)malloc(sizeof(NODO));
    aux->seg = NULL;
    /* Na implementa��o, devemos alocar mem�ria para o campo info (do tipo correspondente) */

    return aux;
}


/** ---------- INSERIR NA LISTA (INICIO) ---------- */

void inserirInicio(LISTA *lista, NODO *nodo)
{
    if(!lista)
    {
        printf("\n>> A lista n�o existe\n");
        return;
    }

    if(!nodo)
    {
        printf("\n>> A informa��o n�o existe\n");
        return;
    }

    nodo->seg = lista->inicio;
    lista->inicio = nodo;
    lista->nel++;
}

/** ---------- CALCULAR A MEMORIA TOTAL DA ESTRUTURA ---------- */

int MemoriaTotalEstrutura(HASHING *hashLivros, HASHING *hashReq)
{
    if(!hashLivros)
        return 0;

    if(!hashReq)
        return 0;

    int memTotal = 0;

    memTotal += MemoriaHashingLivros(hashLivros);
    memTotal += MemoriaHashingRequisitantes(hashReq);

    return memTotal;
}

/** ---------- TAMANHO REQUISITANTE ---------- */

int tamanhoRequisitante(REQUISITANTE *req)
{
    if(!req)
        return 0;

    int mem = 0;

    mem += sizeof(REQUISITANTE);
    mem += (strlen(req->nome)+1)*sizeof(char);

    return mem;
}

/** ---------- TAMANHO REQUISI��O ---------- */

int tamanhoRequisicao(REQUISICAO *req)
{
    if(!req)
        return 0;

    int mem = 0;

    mem += sizeof(REQUISICAO);
    mem += (strlen(req->IdRequisitante)+1)*sizeof(char);

    return mem;
}


/** ---------- TAMANHO LIVROS ---------- */

int tamanhoLivro(LIVRO *liv)
{
    if(!liv)
        return 0;

    int mem = 0;

    mem += sizeof(LIVRO);
    mem += (strlen(liv->titulo)+1)*sizeof(char);

    return mem;
}

/** ---------- MEMORIA HASHING REQUISITANTES ---------- */

int MemoriaHashingRequisitantes(HASHING *hashReq)
{
    if(!hashReq)
        return 0;

    /** Cria��o da variavel de memoria e do n� do hashing */
    int mem = 0;
    NODO_HASHING *aux = hashReq->inicio;

    while(aux) /** Enquanto existir n� do hashing (ou seja, cidades) */
    {
        /** Adicionar a estrutura lista � memoria e copia do no do requisitante */
        mem += sizeof(LISTA); /** juntar a memoria da lista dos requisitantes */
        NODO *aux_Req = aux->lista->inicio;

        while(aux_Req) /** Enquanto houver requisitantes */
        {

            REQUISITANTE *nodoRequisitante = aux_Req->info;

            mem += sizeof(NODO); /** juntar a memoria do n� dos requisitantes */
            mem += tamanhoRequisitante(nodoRequisitante);/** juntar a memoria da informa��o do requisitante */

            mem += sizeof(LISTA); /** juntar a memoria da lista das requisi��es */

            if(nodoRequisitante->requisicao != NULL)
            {
            NODO *nodoRequisicao = nodoRequisitante->requisicao->inicio;

                while(nodoRequisicao)  /** Enquanto o n� de requisicao existir */
                {
                    mem += sizeof(NODO);  /** juntar a memoria do n� das requisi��es */
                    mem += tamanhoRequisicao(nodoRequisicao->info); /** juntar a memoria das informacoes da requisicao */


                    nodoRequisicao = nodoRequisicao->seg; /** Requisi��o seguinte */
                }
            }


            aux_Req = aux_Req->seg; /** Requisitante seguinte */

        }

    aux = aux->seg; /** Distrito seguinte */

    }

return mem;

}

/** ---------- MEMORIA HASHING LIVROS ---------- */

int MemoriaHashingLivros(HASHING *hashLiv)
{
    if(!hashLiv)
        return 0;

    /** Cria��o da variavel de memoria e do n� do hashing */
    int mem = 0;
    NODO_HASHING *aux = hashLiv->inicio;

    while(aux) /** Enquanto existir n� do hashing (ou seja, areas) */
    {
        /** Adicionar a estrutura lista � memoria e copia do no do livro */
        mem += sizeof(LISTA); /** juntar a memoria da lista dos livros */
        NODO *aux_Liv = aux->lista->inicio;

        while(aux_Liv) /** Enquanto os livros existirem */
        {
            mem += sizeof(NODO); /** juntar a memoria do n� dos livros */
            mem += tamanhoLivro(aux_Liv->info);/** juntar a memoria da informa��o do livro */

            aux_Liv = aux_Liv->seg; /** Livro seguinte */
        }
    aux = aux->seg; /** Area seguinte */

    }

return mem;
}

