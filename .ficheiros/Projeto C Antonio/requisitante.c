#ifndef _REQ_H_
#define _REQ_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "hashing.h"
#include "lista.h"

/** ---------- CRIAR REQUISITANTE ---------- */

REQUISITANTE *criarReq()
{
    REQUISITANTE *aux = (REQUISITANTE *)malloc(sizeof(REQUISITANTE));
    aux->requisicao = NULL;
    return aux;
}

/** ---------- PREENCHER REQUISITANTE ---------- */

int preencherReq(REQUISITANTE *req, int ultimoId)
{
    if(!req)
    {
        printf("\n>>O requisitante não existe\n");
        return 0;
    }

    if(!ultimoId)
    {
        printf("\n>> Ocorreu um erro na leitura do ultimo ID\n");
        return 0;
    }

    printf("\n\n__________________________________________________\n");
    printf("\n-        Registo de um novo requisitante         -");
    printf("\n__________________________________________________\n\n");

    char stringNome[100];
    char temp;

    /* Pedir o nome do requisitante */

    printf("\n>> Nome: ");
    scanf("%c",&temp);
    scanf("%[^\n]", stringNome); /* Poder ler nomes com espaços */

    req->nome = (char *)malloc((strlen(stringNome) + 1) * sizeof(char));
    strcpy(req->nome, stringNome);

    char data[40];
    char numDistString[7];
    char numConcString[3];

    /* Pedir e validar a data de nascimento do requisitante */

    do
    {
        printf("\n>> Data de nascimento: ");

        printf("\n\n\t>> Dia: ");
        scanf("%02d", &(req->diaNasc));

        printf("\n\t>> Mês: ");
        scanf("%02d", &(req->mesNasc));

        printf("\n\t>> Ano: ");
        scanf("%d", &(req->anoNasc));

        sprintf(data, "%d-%d-%d", req->diaNasc, req->mesNasc, req->anoNasc);

    } while(validarDataNasc(data) == 0);

    char idFreg[7];

    /* Pedir e validar o ID de freguesia do requisitante */

    do
    {
        /* Pedir o distrito */

        listarDist();

        printf("\n>> Local de residencia:\n");

        int numDist, numConc, numFreg;

        do
        {
            printf("\n\t>> Distrito: ");
            scanf("%02d", &numDist);

        }while(numDist < 1 || numDist > 18);

        /* Pedir o concelho */

        sprintf(numDistString, "%02d", numDist);

        listarConc(numDistString);

        printf("\n\t>> Concelho: ");
        scanf("%02d", &numConc);

        /* Pedir a freguesia */

        sprintf(numConcString, "%02d", numConc);
        strcat(numDistString, numConcString);

        listarFreg(numDistString);

        printf("\n\t>> Freguesia: ");
        scanf("%02d", &numFreg);

        sprintf(idFreg, "%02d%02d%02d", numDist, numConc, numFreg);

        strcpy((req->idFreguesia), idFreg);

    } while(validarIDFreg(idFreg, "Freguesias.txt") == 0);

    /* Criar um novo ID para o requisitante */

    char idReqString[10];

    ultimoId = devolveProxMultiplo(ultimoId); /* Calcula o próximo ID que corresponde aos requisitos */

    sprintf(idReqString, "%09d", ultimoId);
    strcpy(req->id, idReqString);

    return ultimoId;
}

/** ---------- MOSTRAR OS DADOS DE UM REQUISITANTE ---------- */

void mostrarReq(REQUISITANTE *req)
{
    if(!req)
    {
        printf("\n>> O requisitante não existe\n");
        return;
    }

    printf("\n\n__________________________________________________\n\n");
    printf("-          Requisitante Nº %s            -", req->id);
    printf("\n__________________________________________________\n");

    printf("\n\n>> Nome: %s", req->nome);

    printf("\n\n>> Data de nascimento: %02d/%02d/%04d", req->diaNasc, req->mesNasc, req->anoNasc);

    printf("\n\n>> ID freguesia: %s\n", req->idFreguesia);
}

/** ---------- MOSTRAR A LISTA DE REQUISITANTES ---------- */

void mostrarListaReq(LISTA *lista)
{
    if(!lista)
    {
        printf("\n>> A lista de requisitantes não existe\n");
        return;
    }

    if(!lista->inicio)
    {
        printf("\n>> A lista de requisitantes está vazia (0 requisitantes)\n");
        return;
    }

    NODO *nodo = lista->inicio;

    while(nodo)
    {
        REQUISITANTE *dados = nodo->info;
        mostrarReq(dados);
        nodo = nodo->seg;
    }
}

/** ---------- DEVOLVER O NUMERO DE REQUISITANTES NA LISTA ---------- */

int contaReq(HASHING *hashingDist)
{
    if(!hashingDist)
    {
        printf("\n>>O hashing de distritos não existe\n");
        return;
    }

    NODO_HASHING *nodoHashing = hashingDist->inicio;
    int contador = 0;

    while(nodoHashing)
    {
        NODO *nodo = nodoHashing->lista->inicio;

        while(nodo)
        {
            contador++;
            nodo = nodo->seg;
        }
        nodoHashing = nodoHashing->seg;
    }
    return contador;
}

/** ---------- CALCULAR A IDADE DE UM DADO REQUISITANTE ---------- */

int calcularIdade(REQUISITANTE *req)
{
    if(!req)
    {
        printf("\n>> O requisitante não existe\n");
        return;
    }

    time_t tempo = time(NULL);
    struct tm tm = *localtime(&tempo);

    int ano = tm.tm_year + 1900;
    int mes = tm.tm_mon + 1;
    int dia = tm.tm_mday;
    int idade;

    if(mes < req->mesNasc) /* Neste caso, o requisitante ainda não fez anos */
    {
        idade = ano - req->anoNasc - 1;
        return idade;
    }

    else /* Neste caso, o requisitante nasceu antes do mês atual, ou neste mês */
    {
        if(mes == req->mesNasc) /* O requisitante vai fazer anos este mês, devemos conhecer o dia */
        {
            if(dia < req->diaNasc) /* Neste caso, o requisitante nasceu depois do dia de hoje (ainda não fez anos)  */
            {
                idade = ano - req->anoNasc - 1;
                return idade;
            }
        }
        idade = ano - req->anoNasc; /* O requisitante nasceu antes do mês atual */
        return idade;
    }
}

/** ---------- DETERMINAR A IDADE MAXIMA DE TODOS OS REQUISITANTES ---------- */

REQUISITANTE *idadeMax(HASHING *hashingDist)
{
    int max = 0;

    if(!hashingDist)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return NULL;
    }

    if(!hashingDist->inicio)
    {
        printf("\n>> O hashing de distritos está vazio (0 requisitantes)\n");
        return NULL;
    }

    NODO_HASHING *nodoHashing = hashingDist->inicio;
    REQUISITANTE *req;

    while(nodoHashing) /* Enquanto existir distritos */
    {
        NODO *aux = nodoHashing->lista->inicio; /* Buscar o primeiro requisitante daquele distrito */

        while(aux) /* Enquanto existir requisitantes naquele distrito */
        {
            int idade = calcularIdade((REQUISITANTE *)aux->info);

            if (idade > max)
            {
                max = idade;
                req = (REQUISITANTE *)aux->info;
            }
            aux = aux->seg;
        }
        nodoHashing = nodoHashing->seg;
    }
    return req;
}

/** ---------- DETERMINAR A IDADE MEDIA DE TODOS OS REQUISITANTES ---------- */

int idadeMedia(HASHING *hashingDist)
{
    if(!hashingDist)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return 0;
    }

    if(!hashingDist->inicio)
    {
        printf("\n>> O hashing de distritos está vazio (0 requisitantes)\n");
        return 0;
    }

    NODO_HASHING *nodoHahing = hashingDist->inicio;
    int totalReq = 0, media = 0;
    float soma = 0.0;

    while(nodoHahing) /* Enquanto houver distritos */
    {
        NODO *aux = nodoHahing->lista->inicio; /* Bscar o primeiro requisitante da cidade */

        while(aux) /* Enquanto houver requisitantes naquele distrito */
        {
            int idadeReq = calcularIdade((REQUISITANTE *)aux->info);
            soma += idadeReq;
            totalReq++;
            aux = aux->seg; /* Requisitante seguinte */
        }
        nodoHahing = nodoHahing->seg;  /* Distrito seguinte */
    }
    media = soma / totalReq;
    return media;
}

/** ---------- DETERMINAR O NUMERO DE REQUISITANTES, QUE TÊM A IDADE > A IDADE INSERIDA PELO UTILIZADOR ---------- */

int idadeSup(HASHING *hashingDist)
{
    if(!hashingDist)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return 0;
    }

    if(!hashingDist->inicio)
    {
        printf("\n>> O hashing de distritos está vazio (0 requisitantes)\n");
        return 0;
    }

    int totalReq = 0;
    int idadeLimitadora;

    do
    {
        printf("\n>> Insira a idade limite (exclusive): ");
        scanf("%d", &idadeLimitadora);

    }while(idadeLimitadora <= 0 || idadeLimitadora > 100);

    NODO_HASHING *nodoHashing = hashingDist->inicio;

    while(nodoHashing) /* Enquanto houver distritos */
    {
        NODO *auxReq = nodoHashing->lista->inicio; /* Buscar o primeiro requisitante do distrito */

        while(auxReq) /* Enquanto houver requisitantes naquele distrito */
        {
            int idade = calcularIdade((REQUISITANTE *)auxReq->info);

            if (idade > idadeLimitadora)
                    totalReq++;

            auxReq = auxReq->seg;
        }
        nodoHashing = nodoHashing->seg;
    }
    return totalReq;
}

/** ---------- VALIDAR O ID DE CADA REQUISITANTE ---------- */

int validarIdReq(char id[10]) /* 0: inválido / 1: válido */
{
    if(!id)
    {
        printf("\n>> Ocorreu um erro na leitura do ID do requisitante\n");
        return 0;
    }

    /* Verificar se o ID contem 9 algarismos */

    int tamanho = (int)strlen(id);

    if(tamanho != 9)
        return 0;

    /* Verificar se a soma dos 9 algarismos é um multiplo de 10 */

    int i;
    int soma = 0;

    for(i = 0; i < tamanho; i++)
        soma += (int)id[i]-'0'; /* Transformar um char em int (com o devido código ASCII) */

    if(soma % 10 == 0) /* Se o resto da soma for igual a 0, indicará a validade do ID */
        return 1;

    return 0;
}


/** ---------- VALIDAR O ID DA FREGUESIA DO REQUISITANTE  ---------- */

int validarIDFreg(char idFreg[7], char *nomeFic)
{
    if(!idFreg)
    {
        printf("\n>> Ocorreu um erro na leitura do ID de freguesia\n");
        return;
    }

    int tamanho = strlen(idFreg);

    if(tamanho != 6)
        return 0;

    FILE *fic;
    char linha[120];
    fic = fopen(nomeFic, "r");

    if(!fic)
    {
        printf("\n>> Não foi possível abrir o ficheiro [%s]\n", nomeFic);
        fclose(fic);
        return 0;
    }

    while(!feof(fic))
    {
        if(fgets(linha, 120, fic) != NULL) /* Verifica se  leitura foi feita com sucesso */
        {
            char *found = strstr(linha, idFreg);
            if(found != NULL)
            {
                fclose(fic);
                return 1;
            }
        }
    }
    fclose(fic);
    return 0;
}

/** ---------- VERIFICAR SE EXISTE O REGISTO DO SOBRENOME, DANDO UM SOBRENOME ---------- */

SOBRENOME *existeSobrenome(LISTA *listaSobrenomes, char *nome)
{
    if(!listaSobrenomes)
        return NULL;

    if(!listaSobrenomes->inicio)
        return NULL;

    if(!nome)
        return NULL;

    NODO *aux = listaSobrenomes->inicio;

    while(aux) /* Percorrer todos os sobrenomes */
    {
        SOBRENOME *sobreN = aux->info;
        char *nomeExistente = sobreN->sobrenome;

        if(strcmp(nomeExistente, nome) == 0)
            return sobreN;
        aux = aux->seg;
    }
    return NULL;
}

/** ---------- DETERMINAR O SOBRENOME MAIS USADO ---------- */

SOBRENOME *devolverMaisUsado(LISTA *listaSobrenomes)
{
    if(!listaSobrenomes)
    {
        printf("\n>> A lista de sobrenomes não existe\n");
        return NULL;
    }

    if(!listaSobrenomes->inicio)
    {
        printf("\n>> A lista de sobrenomes está vazia (0 requisitantes)\n");
        return NULL;
    }
    NODO *nodo = listaSobrenomes->inicio;
    SOBRENOME *maisUsado = nodo->info;

    while(nodo)
    {
        SOBRENOME *sobrenome = nodo->info;
        if(sobrenome->nel > maisUsado->nel)
            maisUsado = nodo->info;
        nodo = nodo->seg;
    }
    return maisUsado;
}

/** ---------- DESTRUIR SOBRENOME ---------- */

void destruirSobrenome(void *sobrenome)
{
    if(!sobrenome)
    {
        printf("\n>> Ocorreu um erro na leitura do sobrenome\n");
        return;
    }

    SOBRENOME *sobreN = (SOBRENOME *)sobrenome;
    free(sobreN->sobrenome);
    free(sobreN);
}

/** ---------- IDADE COM MAIS REQUISITANTES ---------- */

void IdadeComMaisResquesitantes(HASHING *hashingDist)
{
    int guardarValores[100];
    int idade, j, idadeLimitadora, jmax = 0, totalReq = 0, max = 0;

    if(!hashingDist)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return 0;
    }

    if(!hashingDist->inicio)
    {
        printf("\n>> O hashing de distritos está vazio (0 requisitantes)\n");
        return 0;
    }
    NODO_HASHING *nodoHashing = hashingDist->inicio;

    for(j = 0; j < 100; j++)
        guardarValores[j] = 0;

    while(nodoHashing) /* Enquanto houver distritos */
    {
        NODO *auxReq = nodoHashing->lista->inicio; /* Buscar o primeiro requisitante do distrito */

        while(auxReq) /* Enquanto houver requisitantes naquele distrito */
        {
            idade = calcularIdade((REQUISITANTE *)auxReq->info);

            guardarValores[idade]+= 1;
            auxReq = auxReq->seg;
        }
        nodoHashing = nodoHashing->seg;
    }

    for(j = 0; j < 100; j++)
    {
        if(guardarValores[j]>max)
        {
            jmax = j;
            max = guardarValores[j];
        }
    }
    printf("\n>> Idade com mais requisitantes: %d anos (x %d requisitantes)\n", jmax ,max);
}

REQUISITANTE *encontrarReqAtravesID(HASHING *hashingDist, char *IDRequisitante)
{
    if(!hashingDist)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return NULL;
    }


    if(!hashingDist->inicio)
    {
        printf("\nO hashing de distritos está vazio (0 requisitantes).");
        return NULL;
    }

    if(!IDRequisitante)
    {
        printf("\nO hashing de distritos não existe.\n");
        return NULL;
    }

    NODO_HASHING *nodoHashing = hashingDist->inicio;

    while(nodoHashing) /* enquanto houver distritos */
    {
        NODO *nodoReq = nodoHashing->lista->inicio; /* Buscar o primeiro requisitante do distrito */

        while(nodoReq) /* enquanto houver requisitantes naquele distrito */
        {
            REQUISITANTE *reqInfo = (REQUISITANTE *)nodoReq->info;

            if(strcasecmp(reqInfo->id, IDRequisitante) == 0)
                return reqInfo;

            nodoReq = nodoReq->seg;
        }
        nodoHashing = nodoHashing->seg;
    }
    return NULL;
}

#endif
