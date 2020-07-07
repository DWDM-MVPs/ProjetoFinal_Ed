#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashing.h"

/** ---------- CRIAR UM NOVO HASHING ---------- */

HASHING *criarHashing()
{
    HASHING *aux = (HASHING *)malloc(sizeof(HASHING));
    aux->inicio = NULL;
    aux->nel = 0;

    return aux;
}

/** ---------- DESTRUIR HASHING ---------- */

void destruirHashing(HASHING *hashing, void (*func)(void *))
{
    if(!hashing) /* Verifica se o hashing existe */
    {
        printf("\n>> O hashing não existe\n");
        return;
    }

    NODO_HASHING *auxNodoHash = hashing->inicio; /* Começo no primeiro NODO do hashing */
    NODO_HASHING *auxHash = NULL;

    while(auxNodoHash) /* Enquanto houver NODOS no hashing */
    {
        destruirLista(auxNodoHash->lista, (*func)); /* Destruir a lista dentro do NODO de hashing */

        /* Libertar a memória do NODO do hashing */

        auxHash = auxNodoHash->seg;

        auxNodoHash->nome = NULL;
        free(auxNodoHash->nome);

        free(auxNodoHash);

        auxNodoHash = auxHash;
    }
    auxNodoHash = NULL;
    auxHash = NULL;
    hashing = NULL;
    free(hashing);
}

/** ---------- CRIAR UM NOVO NODO DE HASHING ---------- */

NODO_HASHING *criarNodoHashing()
{
    NODO_HASHING *aux = (NODO_HASHING *)malloc(sizeof(NODO_HASHING));
    aux->seg = NULL;
    aux->lista = NULL;
}

/** ---------- INSERIR UM NODO NO HASHING ---------- */

void inserirNodoHashing(HASHING *hashing, NODO_HASHING *nodoHashing)
{
    if(!hashing)
    {
        printf("\n>> O hashing não existe\n");
        return;
    }

    if(!nodoHashing)
    {
        printf("\n>> A informação não existe\n");
        return;
    }

    nodoHashing->seg = hashing->inicio;
    hashing->inicio = nodoHashing;
    hashing->nel++;
}

/** ---------- VERIFICAR SE EXISTE O DISTRITO DO REQUISITANTE ---------- */

NODO_HASHING *existeDist(HASHING *hashing, REQUISITANTE *req)
{
    if(!hashing)
        return NULL;

    if(!hashing->inicio)
        return NULL;

    char numDist[3];

    memset(numDist, '\0', sizeof(numDist)); /* Esta linha permite limpar, para poder usar o strncpy() */
    strncpy(numDist, req->idFreguesia, 2);
    numDist[2] = '\0';

    NODO_HASHING *aux = hashing->inicio;

    while(aux)
    {
        if(strcmp(aux->numero, numDist) == 0) /* Se o número do distrito corresponde ao número inserido pelo requisitante */
            return aux;

        aux = aux->seg;
    }

    return NULL; /* Não encontrou nenhum distrito */
}

/** ---------- INSERIR UM NOVO REQUISITANTE NO HASHING ---------- */

void inserirReq(HASHING *hashing, NODO *nodoReq)
{
    if(!hashing)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return;
    }

    if(!nodoReq)
    {
        printf("\n>> O requisitante não existe\n");
        return;
    }

    REQUISITANTE *reqInfo = nodoReq->info;

    NODO_HASHING *distCorrespondente = existeDist(hashing, reqInfo);

    if(distCorrespondente != NULL) /* O distrito do requisitante já foi criado */
        inserirInicio(distCorrespondente->lista, nodoReq);

    else
    {
        char stringTemp[50];
        char idDist [3];
        int distEncontrado = 0;

        /* Recuperaro ID de distrito */

        memset(idDist, '\0', sizeof(idDist));
        strncpy(idDist, reqInfo->idFreguesia, 2);
        idDist[3] = 0;

        /* Ler o ficheiro de distritos para poder inserir o nome correspondente */

        FILE *fic;
        char linha[120];
        fic = fopen("Distritos.txt", "r");

        if(!fic)
        {
            printf("\n>> Não foi possível abrir o ficheiro [Distritos.txt]\n");
            strcpy(stringTemp, "INDETERMINADO"); /* Para não perder os dados do requisitante, ele é inserido isoladamente */
            strcpy(idDist, "99");
        }

        else
        {
             while(!feof(fic))
            {
                if(fgets(linha, 120, fic) != NULL) /* Verifica se  leitura foi feita com sucesso */
                {
                    char *found = strstr(linha, idDist);

                    if(found != NULL) /* Foi encontrado o distrito correspondente */
                    {
                        strcpy(stringTemp, linha);
                        distEncontrado = 1;
                    }
                }
            }

            if(distEncontrado == 0) /* Caso o distrito não seja encontrado */
            {
                strcpy(stringTemp, "INDETERMINADO"); /* Como o ID de freguesia é sempre validado, esta situação não deveria acontecer */
                strcpy(idDist, "99"); /* Isto permite inserir numa categoria à parte */
            }
        }

        NODO_HASHING *nodoHashing = criarNodoHashing();

        nodoHashing->nome = (char *)malloc((strlen(stringTemp) + 1) * sizeof(char));
        strcpy(nodoHashing->nome, stringTemp);

        strcpy(nodoHashing->numero, idDist);

        nodoHashing->lista = criarLista();
        inserirInicio(nodoHashing->lista, nodoReq);

        inserirNodoHashing(hashing, nodoHashing);
    }
}

/** ---------- MOSTRAR TODOS OS REQUISITANTES DOS DISTRITOS ---------- */

void mostrarDist(HASHING *hashingDist)
{
    if(!hashingDist)
    {
        printf("O hashing de distritos não existe.");
        return;
    }

    if(!hashingDist->inicio)
    {
        printf("O hashing de distritos está vazio (0 requisitantes).");
        return;
    }

    NODO_HASHING *dist = hashingDist->inicio;

    while(dist) /* Enquanto houver distritos */
    {
        printf("\n____________________ %s ____________________\n\n", dist->nome);

        mostrarListaReq(dist->lista);

        dist = dist->seg;
    }
}




