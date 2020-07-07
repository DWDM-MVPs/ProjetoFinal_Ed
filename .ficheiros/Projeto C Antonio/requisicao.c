#ifndef _REQUISICAO_H_
#define _REQUISICAO_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "hashing.h"
#include "lista.h"
#define BUF_LEN 256

/** ---------- CRIAR E PREENCHER REQUISIÇÃO ---------- */

void CriarEpreencherRequisicao(LIVRO *liv, REQUISITANTE *req)
{
    if(!liv)
    {
        printf("\n>> O livro não existe\n");
        return;
    }

    if(!req)
    {
        printf("\n>> O requisitante não existe\n");
        return;
    }

    if(liv->requisitado == 1)
    {
        printf("\n>> O livro não está disponível\n");
        return;
    }

    REQUISICAO *requisicao = (REQUISICAO *)malloc(sizeof(REQUISICAO));
    requisicao->DataRealDaEntrega = NULL;

    if(!requisicao)
    {
        printf("\n>> A requisição não foi criada\n");
        return;
    }

    NODO *nodoRequisicao = criarNodo();

    if(!nodoRequisicao)
    {
        printf("\n>> Ocorreu um erro na criação do nodo de requisições\n");
        return;
    }

    LISTA *testelist = req->requisicao;

    /* É sempre inserido no inicio da lista pois assim as mais atuais ficam sempre em primeiro e as mais antigas para o fim */

    if(testelist)
    {
        req->requisicao->nel++;
        nodoRequisicao->seg = req->requisicao->inicio;
        nodoRequisicao->info = requisicao;
        req->requisicao->inicio = nodoRequisicao;
    }

    if(!testelist) /* Neste caso, o requisitante ainda não tem nenhuma requisição */
    {

        LISTA *listaRequisicoes = criarLista();
        listaRequisicoes->nel = 0;

        if(!listaRequisicoes)
        {
            printf("\n>> Ocorreu um erro na criação da lista de requisições\n");
            return;
        }

        /* É sempre inserido no inicio da lista pois assim as mais atuais ficam sempre em primeiro e as mais antigas para o fim */

        listaRequisicoes->nel++;
        nodoRequisicao->seg = NULL;
        nodoRequisicao->info = requisicao;
        listaRequisicoes->inicio = nodoRequisicao;
        req->requisicao = listaRequisicoes;
    }
    printf("\n\n__________________________________________________\n");
    printf("\n-       Registo de uma nova requisição         -");
    printf("\n__________________________________________________\n");

    int variavelInt;
    time_t variavelTime;
    char buf[BUF_LEN] = {0};

    /* Gravar o id do Requisitante na Requisição */
    char *id = req->id;
    strcpy(requisicao->IdRequisitante, id);

    /* Defenir a que livro a requisição pertence */
    requisicao->pertence = liv;

    if(!requisicao->pertence)
    {
        printf("\n>> Não foi adicionado livro à requisição\n");
        return;
    }

    /* Pôr o livro que está a ser requisitado em estado de requisição */
    liv->numRequisicoes += 1;

    /* Pôr o livro que está a ser requisitado em estado de requisição */
    liv->requisitado = 1;

    /* Mostrar e gravar a data a requisição atual */
    variavelTime = time(NULL);

    /* Conferir a variavel tempo ficou com a data atual */
    if (variavelTime == -1)
    {
        printf("\n>> Ocorreu um erro na função time()\n");
        return;
    }
    requisicao->DataRequisicao = localtime(&variavelTime);

    /* Conferir a estrutura da data de requisição ficou com a data atual */

    if (requisicao->DataRequisicao == NULL)
    {
        printf("\n>> Ocorreu um erro na função localtime()\n");
        return ;
    }
    /* Mostrar a requisição atual */

    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "\n>> Data da requisição: %H:%M:%S  %A %d de %B de %Y", requisicao->DataRequisicao);
    printf("\n %s\n\n",buf);

    /* Verificar se o numero de dias da requisição está correto */
    do
    {
        /* Pedir numero de dias de duração da requisição */

        printf("\n>> Introduza a duração, em dias, da requisição: ");
        scanf("%d", &variavelInt);

        if(variavelInt > 30)
                printf("\n\t>> Por favor, introduza os dias de requisição dentro do limite máximo aceitável da requisição (até 30 dias)\n");

        if(variavelInt <= 0)
                printf("\n\t>> Por favor, introduza os dias de requisição dentro do limite minimo aceitável da requisição (até 30 dias)\n");

    } while(variavelInt <= 0 || variavelInt > 30);

    requisicao->totalDiasDeRequisicao = variavelInt;

    /* esta lista é a lista de dias que cada mês tem */
    static int days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    struct tm *aux;

    aux = localtime(&variavelTime);

    /* Conferir a struct tempo ficou com a data atual */

    if (aux == NULL)
    {
        printf("\n>> A função localtime() falhou\n");
        return;
    }

    /* Esta função irá receber se o ano é bissexto e ajustar a estrutura do dia dos meses */
    corrige_meses(aux->tm_year, days_in_month);

    /* Função que atualiza a data da struct tm */
    /* Utilizar aux neste for e depois da função igualar ao que queremos */
    /* O for percorre dia a dia e vai acertando os meses e o ano e o dia da semana */
    /* Função que atualiza a data da struct tm */
    /* Utilizar aux neste for e depois da função igualar ao que queremos */
    /* O for percorre dia a dia e vai acertando os meses e o ano e o dia da semana */

    for(int i = 1;i <= variavelInt; i++)
    {
        /* Verificar o dia da semana e somar um dia ou voltar ao inicio da semana */
        if(aux->tm_wday == 6)
           aux->tm_wday = 0;

        else
            aux->tm_wday += 1;

        /* Acrescenta o dia do mês e acerta o mes e o ano conforme a necessidade */
        aux->tm_yday += 1;
        aux->tm_mday += 1;
        if(aux->tm_mday > days_in_month[aux->tm_mon] )
        {
            aux->tm_mday = 1;
            aux->tm_mon += 1;

            if(aux->tm_mon > 11)
            {
               aux->tm_mon = 0;
               aux->tm_year += 1;
               aux->tm_yday = 0;
               corrige_meses(aux->tm_year,days_in_month); /* Corrigir o mes de fevereiro conforme o ano */
            }
        }
    }
    /* Mostrar e gravar a data da suposta entrega do livro */
    requisicao->DataSupostaDaEntrega = aux;

    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "\n>> Data limite de entrega: %H:%M:%S  %A %d de %B de %Y\n", requisicao->DataSupostaDaEntrega);
    printf("\n %s\n",buf);
}

/** ---------- MOSTRAR OS DADOS DE UMA REQUISIÇÃO ---------- */

void mostrarRequisicao(REQUISICAO *requisicao)
{
    if(!requisicao)
    {
        printf("\n>> A requisição não existe\n");
        return;
    }
    char buf[BUF_LEN] = {0};

    printf("\n\n__________________________________________________\n");
    printf("-             Requisição do livro               -\n");
    printf("__________________________________________________\n");

    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "\n>> Data da requisição: %H:%M:%S  %A %d de %B de %Y\n", requisicao->DataRequisicao);
    printf("\n%s.",buf);

    printf("\n Total de dias de requisição: %d dias.",requisicao->totalDiasDeRequisicao);

    /* Prazo que acaba os dias da requisição */
    char teste[BUF_LEN] = {0};

    memset(teste, 0, BUF_LEN);
    strftime(teste, BUF_LEN, "\n>> Data de limite entrega: %H:%M:%S  %A %d de %B de %Y", requisicao->DataSupostaDaEntrega);
    printf("\n%s.",teste);

    /* Foi entregue ou não? */
    if(requisicao->DataRealDaEntrega == NULL)
        printf("\n>> O livro não foi entregue\n");

    else
    {
        memset(buf, 0, BUF_LEN);
        strftime(buf, BUF_LEN, "%H:%M:%S  %A %d de %B de %Y", requisicao->DataRealDaEntrega);

        printf("\n>> O livro foi entregue em %s.",buf);
    }
}

/** ---------- MOSTRAR A LISTA DE REQUISIÇÕES ---------- */

void mostrarListaRequisicoes(HASHING *hashdist)
{
    if(!hashdist)
    {
        printf("\n>> O hashing de distritos não existe\n");
        return;
    }

    NODO_HASHING *nodoHashing = hashdist->inicio;
    int cont = 0;

    while(nodoHashing)
    {
        NODO *nodoRequisitante = nodoHashing->lista->inicio;

        while(nodoRequisitante)
        {
            REQUISITANTE *dadosRequisitante = nodoRequisitante->info;

            if(dadosRequisitante->requisicao)
            {
                NODO *nodoRequisicao = dadosRequisitante->requisicao->inicio;

                while(nodoRequisicao)
                {
                    REQUISICAO *dadosRequisicao = nodoRequisicao->info;

                    mostrarRequisicao(dadosRequisicao);
                    cont++;
                    nodoRequisicao = nodoRequisicao->seg;
                }
            }
            nodoRequisitante = nodoRequisitante->seg;
        }

    nodoHashing = nodoHashing->seg;
    }

    printf("\n>> Requisitantes: %d\n",cont);
}

/** ---------- MOSTRAR AS REQUISIÇÕES DE UM DADO REQUISITANTE ---------- */

void mostrarRequisicoesDoRequisitante(REQUISITANTE *req)
{
    if(!req)
    {
        printf("\n>> O requisitante não existe\n");
        return;
    }

    if(!req->requisicao)
    {
        printf("\n>> O requisitante não tem requisições\n");
        return;
    }

    if(!req->requisicao->inicio)
    {
        printf("\n>> O requisitante não tem requisições");
        return;
    }

    NODO *nodo = req->requisicao->inicio;

    while(nodo)
    {
        REQUISICAO *dados = nodo->info;
        mostrarRequisicao(dados);
        nodo = nodo->seg;
    }
}


/** ---------- DEVOLVER REQUISIÇÃO RECEBENDO UM LIVRO ---------- */

REQUISICAO *devolverRequisicaoAtivaDeUmLivro(LIVRO *liv,HASHING *hashdist)
{

    if(!liv)
    {
        printf("\n>> O livro não existe\n");
        return NULL;
    }

    if(!hashdist)
    {
        printf("\n>> O hashing não existe\n");
        return NULL;
    }

    if(liv->requisitado == 0)
    {
        printf("\n>> O livro não está requisitado");
        return NULL;
    }

    NODO_HASHING *nodoHashing = hashdist->inicio;

    while(nodoHashing)
    {
        NODO *nodoRequisitante = nodoHashing->lista->inicio;

        while(nodoRequisitante)
        {
            REQUISITANTE *dadosRequisitante = nodoRequisitante->info;

            if(dadosRequisitante->requisicao) /* Aqui recuperamos os requisitantes com requisições */
            {
                NODO *nodoRequisicao = dadosRequisitante->requisicao->inicio;

                while(nodoRequisicao)
                {
                    REQUISICAO *dadosRequisicao = nodoRequisicao->info;

                    if(dadosRequisicao->pertence->ISBN == liv->ISBN) /* O livro com o mesmo ISBN foi encontrado */
                        return dadosRequisicao;

                    nodoRequisicao = nodoRequisicao->seg;
                }
            }
            nodoRequisitante = nodoRequisitante->seg;
        }
        nodoHashing = nodoHashing->seg;
    }
    return NULL;
}


/** ---------- DEVOLVER UM LIVRO REQUISITADO ---------- */

void devolverLivroRequisitado(LIVRO *liv,HASHING *hashDist){

    if(!liv)
    {
        printf("\n>> O livro não existe\n");
        return;
    }

    if(liv->requisitado == 0)
    {
        printf("\n>> O livro não está requisitado\n");
        return;
    }

    /* Verificamos se este livro está requisitado e com o ISBN vamos procurar pela requisição deste livro  */

    REQUISICAO *requisicao = devolverRequisicaoAtivaDeUmLivro(liv,hashDist);

    if(!requisicao)
    {
        printf(">> A requisição não existe\n");
        return;
    }

    if(requisicao->DataRealDaEntrega != NULL)
    {
        printf("\n>> A requisição já foi finalizada\n");
        return;
    }

    char buf[BUF_LEN];
    time_t TempoAtual;
    TempoAtual = time(NULL);

    /* Conferir a variavel tempo ficou com a data atual */

    if (TempoAtual == -1)
    {
        printf("\n>> A função time() falhou\n");
        return;
    }

    requisicao->DataRealDaEntrega = localtime(&TempoAtual); /* Indicamos a data real da entrega */

    /* Conferir a variavel tempo ficou com a data atual */

    if (requisicao->DataRealDaEntrega == NULL)
    {
        printf("\n>> A função localtime() falhou, na adesão da data real da entrega\n");
        return ;
    }

    memset(buf, 0, BUF_LEN);
    strftime(buf, BUF_LEN, "\n>> Entrega realizada: %H:%M:%S  %A %d de %B de %Y\n", requisicao->DataRealDaEntrega);
    printf("%s",buf);

    /*Tornar estado do livro como não reuqisitado */

    liv->requisitado = 0;

    printf("\n>> O livro foi devolvido com sucesso\n");
}


#endif
