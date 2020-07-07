#ifndef _FIC_H_
#define _FIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashing.h"
#include <string.h>
#define BUF_LEN 120

/** ---------- LISTAR TODOS OS DISTRITOS ---------- */

void listarDist()
{
    FILE *fic;
    char linha[120];
    fic = fopen("Distritos.txt", "r");

    if(!fic)
    {
        printf("\n>> Não foi possível abrir o ficheiro [Distritos.txt]\n");
        return;
    }
    printf("\n\n__________________________________________________\n\n");
    printf("-       Escolha o distrito correspondente        -\n");
    printf("__________________________________________________\n\n");

    while(!feof(fic))
    {
        if(fgets(linha, 120, fic) != NULL) /* Verifica se  leitura foi feita com sucesso */
            printf(">> %s", linha);
    }
    printf("\n__________________________________________________\n");
    fclose(fic);
}

/** ---------- LISTAR TODOS OS CONCELHOS, RELATIVOS A UM DADO DISTRITO ---------- */

void listarConc(char *dist)
{
    if(!dist)
    {
        printf("\n>>O distrito n�o existe\n");
        return;
    }

    FILE *fic;
    char linha[120];
    fic = fopen("Concelhos.txt", "r");
    char distritoFich[3];

    if(!fic)
    {
        printf("\n>> Não foi poss�vel abrir o ficheiro [Concelhos.txt]\n");
        return;
    }

    printf("\n\n__________________________________________________\n\n");
    printf("-      Escolha o concelho correspondente         -\n");
    printf("__________________________________________________\n\n");

    while(!feof(fic))
    {
        if(fgets(linha, 120, fic) != NULL) /* Verifica se  leitura foi feita com sucesso */
        {
            /* Recupero o ID do distrito, dentro dos ID de concelhos */

            int i;

            for(i = 0; i < 2; i++)
                distritoFich[i] = linha[i];

            distritoFich[2] = '\0';

            if(strcmp(distritoFich, dist) == 0) /* Verifica se existe o distrito no ficheiro */
            {
                for(i = 0; i < 2; i++)
                    memmove(&linha[0], &linha[1], strlen(linha)); /* Permite remover o primeiro n� do distrito do ficheiro de concelhos (facilita a visualiza��o) */

                printf(">> %s", linha);
            }
        }
    }
    printf("\n__________________________________________________\n");
    fclose(fic);
}

/** ---------- LISTAR TODAS AS FREGUESIAS, RELATIVAS A UM DADO CONCELHO ---------- */

void listarFreg(char *conc)
{
    if(!conc)
    {
        printf("\n>>O concelho n�o existe\n");
        return;
    }

    FILE *fic;
    char linha[120];
    fic = fopen("Freguesias.txt", "r");
    char concFich[5];

    if(!fic)
    {
        printf("\n>> Não foi possível abrir o ficheiro [Freguesias.txt]\n");
        return;
    }

    printf("\n\n__________________________________________________\n\n");
    printf("-      Escolha a freguesia correspondente        -\n");
    printf("__________________________________________________\n\n");

    while(!feof(fic))
    {
        if(fgets(linha, 120, fic) != NULL) /* Verifica se  leitura foi feita com sucesso */
        {
            /* Recupero o ID do concelho, dentro dos ID de freguesia */

            int i;

            for(i = 0; i < 4; i++)
                concFich[i] = linha[i];

            concFich[4] = '\0';

            if(strcmp(concFich, conc) == 0) /* Verifica se existe o concelho no ficheiro */
            {
                for(i = 0; i < 4; i++)
                  memmove(&linha[0], &linha[1], strlen(linha)); /* Permite remover os 4 primeiros n� do ID de freguesia do ficheiro de freguesias (facilita a visualiza��o) */

                printf(">> %s", linha);
            }
        }
    }
    printf("\n__________________________________________________\n");
    fclose(fic);
}

/** ---------- LER O FICHEIRO DOS REQUISITANTES  ---------- */

int lerFicheiroReq(HASHING *hashingDist, char *nomeFic)
{
    if(!hashingDist)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return 0;
    }

    FILE *fic;
    char linha[120];
    char linhaInteira[120];
    fic = fopen(nomeFic, "r");
    char *info[4]; /* 0: ID / 1: Nome / 2: Data de nascimento / 3: ID freguesia */
    char ultimoIdFich[10];

    if(!fic)
    {
        printf("\n>> Não foi possível abrir o ficheiro [%s]\n", nomeFic);
        return 0;
    }

    while(!feof(fic))
    {
        if(fgets(linha, 120, fic) != NULL) /* Verifica se  leitura foi feita com sucesso */
        {
            int pos = 0;
            strcpy(linhaInteira, linha);
            char *elemento = strtok(linha, "\t");

            while (elemento != NULL) /* Guardar toda a informa��o de um requisitante separada, no array info */
            {
                info[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char));
                strcpy(info[pos], elemento);
                pos++;
                elemento = strtok(NULL, "\t");
            }

            /* Validar o ID do requisitante */

            int validadeID = validarIdReq(info[0]);

            if(validadeID == 0)
                registarErro(linhaInteira, 1); /* Códigos de erro: 1: ID / 2: Data de nascimento / 3: ID freguesia */

            else /* O ID do requisitante é válido */
            {
                strcpy(ultimoIdFich, info[0]);

                /* Validar a data de nascimento */

                int validadeData = validarDataNasc(info[2]);

                if(validadeData == 0)
                    registarErro(linhaInteira, 2); /* C�digos de erro: 1: ID / 2: Data de nascimento / 3: ID freguesia */

                else /* A data de nascimento � v�lida */
                {
                    int tam = strlen(info[3]);
                    info[3][tam-1] = '\0';

                    /* Validar o ID da freguesia */

                    int validadeIDFreg = validarIDFreg(info[3], "Freguesias.txt");

                    if(validadeIDFreg == 0)
                        registarErro(linhaInteira, 3); /* Códigos de erro: 1: ID / 2: Data de nascimento / 3: ID freguesia */

                    else /* O ID de freguesia � v�lido */
                    {
                        NODO *nodoReq = criarNodo();
                        nodoReq->info = criarReq();
                        REQUISITANTE *req = nodoReq->info;

                        int tamID = strlen(info[0]);
                        info[0][tamID] = '\0'; /* Adicionar char NULL no �ltimo */
                        strcpy(req->id, info[0]); /* Inserir o ID do requisitante */

                        strcpy(req->idFreguesia, info[3]); /* Inserir o ID de freguesia do requisitante */

                        req->nome = info[1];

                        int dia, mes, ano;
                        int validadeFormato = sscanf(info[2], "%d-%d-%04d", &dia, &mes, &ano);
                        req->diaNasc = dia; /*Inserir o dia de nascimento */
                        req->mesNasc = mes; /*Inserir o mes de nascimento */
                        req->anoNasc = ano; /*Inserir o ano de nascimento */

                        inserirReq(hashingDist, nodoReq);
                    }
                }
            }

            /* Devemos libertar o espa�o alocado para o array info, excepto para o nome */

            free(info[0]);
            free(info[2]);
            free(info[3]);
        }
    }
    fclose(fic);
    return atoi(ultimoIdFich);
}

/** ---------- LER O FICHEIRO DOS LIVROS ---------- */

int lerFicheiroLivro(HASHING *hashingliv)
{
    FILE *fic;
    char linha [120];
    int cont = 0;

    fic = fopen("livros.txt", "r");

    if(!fic)
    {
        printf("\n>> Não foi possível abrir o ficheiro.\n");
        return 0;
    }

    char *info[22]; /* ISBN - titulo - ano - area - estado de requisição - numéro de requisições */

    while(!feof(fic))
    {
        if(fgets(linha, 120, fic) != NULL)
        {
            int pos = 0;
            char *elemento = strtok(linha, "\t");

            while(elemento != NULL)
            {
                info[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char));
                strcpy(info[pos], elemento);
                pos++;
                elemento = strtok(NULL, "\t");
            }

            NODO *nodoLivro = criarNodo();
            LIVRO *liv = criarLiv();

            liv->ISBN = atoi(info[0]);
            liv->titulo = info[1];
            liv->ano = atoi(info[2]);
            liv->area = info[3];
            liv->requisitado = atoi(info[4]);
            liv->numRequisicoes = atoi(info[5]);

            nodoLivro->info = (void *)liv;
            inserirLivro(hashingliv, nodoLivro);
            cont++;
        }
    }
    fclose(fic);
    return cont;
}



#endif
