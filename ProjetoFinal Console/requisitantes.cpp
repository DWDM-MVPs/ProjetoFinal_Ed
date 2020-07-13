#ifndef _REQUISITANTES_CPP_
#define _REQUISITANTES_CPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "requisitantes.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;

DATA *Criar_Data_Preenchida(int dia, int mes, int ano)
{
    DATA *data = (DATA *)malloc(sizeof(DATA));

    data->Dia = dia;
    data->Mes = mes;
    data->Ano = ano;

    return data;
}

REQUISITANTE *Criar_Requisitante()
{
    REQUISITANTE *requisitante = (REQUISITANTE *)malloc(sizeof(REQUISITANTE));

    requisitante->ID = 0;
    requisitante->DataDeNascimento = NULL;
    requisitante->ListaRequisicoes = NULL;
    requisitante->Seguinte = NULL;

    return requisitante;
}

LISTA_REQUISITANTES *Criar_ListaRequisitantes()
{
    LISTA_REQUISITANTES *lista_requisitantes = (LISTA_REQUISITANTES *)malloc(sizeof(LISTA_REQUISITANTES));

    lista_requisitantes->Inicio = NULL;
    lista_requisitantes->Quantidade = 0;

    return lista_requisitantes;
}

REQUISICAO *Criar_Requisicao()
{
    REQUISICAO *requisicao = (REQUISICAO *)malloc(sizeof(REQUISICAO));

    requisicao->DataRequisicao = NULL;
    requisicao->Seguinte = NULL;

    return requisicao;
}

LISTA_REQUISICOES *Criar_ListaRequisicoes()
{
    LISTA_REQUISICOES *lista_requisicoes = (LISTA_REQUISICOES *)malloc(sizeof(LISTA_REQUISICOES));

    lista_requisicoes->Inicio = NULL;
    lista_requisicoes->NumeroTotalDeRequisicoes = 0;
    lista_requisicoes->RequisicoesAtivas = 0;

    return lista_requisicoes;
}


// DEVOLVE O TAMANHO DE UM INT
int TamanhoInt(int num)
{
    if (!(num > 10 || num < -10)) return 1;

    int tamanho = 0;
    while (num >= 10 || num <= -10)
    {
        printf("\n » %d", num);
        num = num / 10;
        tamanho = tamanho + 1;
    }
    return tamanho + 1;
}


// VERIFICA SE UM DADO ID E VALIDO E SE FOR DEVOLVE TRUE
bool ValidarIdRequisitante(int id)
{
    // VERIFICA SE O ID TEM 9 NUMEROS
    if (TamanhoInt(id) != 9) return false;

    // GUARDA A SOMA DO ID
    int soma = 0;

    // CALCULAR A SOMA
    int i = 0;
    for (i; i < 9; i++)
    {
        soma = soma + (id % 10);
        id = id / 10;
    }

    // VERIFICAR SE A SOMA E UM MULTIPLO DE 10
    return soma % 10 == 0;
}

bool AnoBissexto(int ano)
{
     return ano % 4 == 0 && ano % 100 != 0 || ano % 400 == 0;
}

bool ValidarData(DATA *data)
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



// LE TODOS OS REQUISITANTES DO FICHEIRO
void LerRequisitantes(LISTA_REQUISITANTES *hr)
{
    FILE *ficheiro = fopen(nomeFic, "r");
    char linha[120];
    char linhaInteira[120];
    char *info[4];
    char ultimoIdFich[10];

    while(!feof(ficheiro))
    {
        if(fgets(linha, 120, fic) != NULL)
        {
            int pos = 0;
            strcpy(linhaInteira, linha);
            char *elemento = strtok(linha, "\t");

            while (elemento != NULL)
            {
                info[pos] = (char *)malloc((strlen(elemento) + 1) * sizeof(char));
                strcpy(info[pos], elemento);
                pos++;
                elemento = strtok(NULL, "\t");
            }

            int validadeID = validarIdReq(info[0]);

            if(validadeID == 0)
                registarErro(linhaInteira, 1);

            else
            {
                strcpy(ultimoIdFich, info[0]);

                int validadeData = validarDataNasc(info[2]);

                if(validadeData == 0)
                    registarErro(linhaInteira, 2);

                else
                {
                    int tam = strlen(info[3]);
                    info[3][tam-1] = '\0';

                    int validadeIDFreg = validarIDFreg(info[3], "Freguesias.txt");

                    if(validadeIDFreg == 0)
                        registarErro(linhaInteira, 3);

                    else
                    {
                        NODO *nodoReq = criarNodo();
                        nodoReq->info = criarReq();
                        REQUISITANTE *req = nodoReq->info;

                        int tamID = strlen(info[0]);
                        info[0][tamID] = '\0';
                        strcpy(req->id, info[0]);

                        strcpy(req->idFreguesia, info[3]);

                        req->nome = info[1];

                        int dia, mes, ano;
                        int validadeFormato = sscanf(info[2], "%d-%d-%04d", &dia, &mes, &ano);
                        req->diaNasc = dia;
                        req->mesNasc = mes;
                        req->anoNasc = ano;

                        inserirReq(hashingDist, nodoReq);
                    }
                }
            }

            free(info[0]);
            free(info[2]);
            free(info[3]);
        }
    }
    fclose(fic);
    return atoi(ultimoIdFich);
}




// CRIA UM REQUISITANTE COM TODOS OS CAMPOS PREENCHIDOS
REQUISITANTE *Criar_Requisitante_Preenchido(int id, char nome[100], DATA *data_de_nascimento, int numero_requisicoes, char id_freguesia[6])
{
    REQUISITANTE *requisitante = Criar_Requisitante();

    requisitante->ID = id;
    strcpy(requisitante->Nome, nome);
    requisitante->DataDeNascimento = data_de_nascimento;
    requisitante->ListaRequisicoes = Criar_ListaRequisicoes();
    strcpy(requisitante->ID_Freguesia, id_freguesia);

    return requisitante;
}

void GuardarRequisitante(LISTA_REQUISITANTES *hr, REQUISITANTE *requisitante)
{
    if (!hr || !requisitante) return;

    requisitante->Seguinte = hr->Inicio;
    hr->Inicio = requisitante;

    hr->Quantidade = hr->Quantidade + 1;
}



// PESQUISA UM REQUISITANTE POR ID E DEVOLVE O REQUISITANTE ENCONTRADO
REQUISITANTE *PesquisarRequisitantePorId(LISTA_REQUISITANTES *hr, int id)
{
    // SELECIONA O PRIMEIRO REQUISITANTE
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP POR TODOS OS REQUISITANTES
    while (requisitante)
    {
        // VERIFICA SE O ID DO ATUAL REQUISITANTE EM LOOP CORRESPONDE AO ID FORNECIDO NOS PARAMETROS
        if (requisitante->ID == id)
        {
            // CASO CORRESPONDA, DEVOLVE O REQUISITANTE ENCONTRADO
            return requisitante;
        }

        // SELECIONA O PROXIMO REQUISITANTE
        requisitante = requisitante->Seguinte;
    }

    // CASO NAO TENHA SIDO ENCONTRADO NENHUM, DEVOLVE NULL
    return NULL;
}


// VALIDA AS INFORMACOES DE UM REQUISITANTE
bool ValidarRequisitante(REQUISITANTE *requisitante)
{
    // VERIFICA SE O ID E VALIDO
    if (!ValidarIdRequisitante(requisitante->ID)) return false;
    // VERIFICA SE A DATA DE NASCIMENTO E VALIDA
    else if (ValidarData(requisitante->DataDeNascimento)) return false;

    // DEVOLVE TRUE PORQUE AS INFORMACOES DO REQUISITANTE SAO VALIDAS
    return true;
}


// CRIA UM TIPO DE INTERFACE QUE PERMITE AO UTILIZADOR CRIAR UM REQUISITANTE
REQUISITANTE *Wizard_Requisitante(LISTA_REQUISITANTES *hr)
{
    int id;
    char nome[100];
    DATA *nascimento;
    char id_freguesia[6];

    char temp;

    while (true)
    {
        printf("Insira o ID do Requisitante: ");
        scanf("%d", &id);

        if (ValidarIdRequisitante(id) == false)
        {
            printf("\nO ID introduzido não é valido!");
        }
        else if (PesquisarRequisitantePorId(hr, id) != NULL)
        {
            printf("\nJá existe um Requisitante com esse ID!");
        }
        else break;
    }

    printf("Insira o Nome do Requisitante: ");
    scanf("%c",&temp);
    scanf("%[^\n]", nome);

    printf("Insira a Data de Nascimento do Requisitante: \n");
    while (!nascimento)
    {
        int dia;
        int mes;
        int ano;

        printf("Insira o Dia: ");
        scanf("%d", &dia);

        printf("Insira o número do Mes: ");
        scanf("%d", &mes);

        printf("Insira o Ano: ");
        scanf("%d", &ano);

        DATA *data = Criar_Data_Preenchida(dia, mes, ano);
        if (ValidarData(data))
        {
            nascimento = data;
        }
        else
        {
            printf("Data invalida");
            PAUSE_CLS;
        }
    }

    printf("Insira o ID da Freguesia do Requisitante: ");
    scanf("%c",&temp);
    scanf("%[^\n]", id_freguesia);


    REQUISITANTE *requisitante = Criar_Requisitante_Preenchido(id, nome, nascimento, 0, id_freguesia);
    GuardarRequisitante(hr, requisitante);

    return requisitante;
}



// CALCULA A IDADE DE UM REQUISITANTE COMPARADA A DATA ATUAL
int CalcularIdadeDoRequisitante(REQUISITANTE *requisitante)
{
    // VAI BUSCAR E GUARDAR A DATA DE NASCIMENTO DO UTILIZADOR
    DATA *nascimento = requisitante->DataDeNascimento;

    // VAI BUSCAR O TEMPO ATUAL
    time_t tempo = time(NULL);
    struct tm tm = *localtime(&tempo);

    // CALCULA A IDADE "BASE" DO REQUISITANTE
    int idadeBase = tm.tm_year + 1900 - nascimento->Ano;

    // PRIMEIRO VERIFICA SE O MES EM QUE O REQUISITANTE NASCEU JA PASSOU
    // SEGUNDO VERIFICA SE ESTAMOS NO MES EM QUE O REQUISITANTE NASCEU E VERIFICA SE O DIA EM QUE O REQUISITANTE NASCEU E HOJE OU JA PASSOU
    // E SE FOR VERDADEIRO DEVOLVE A 'IDADE BASE' PORQUE O REQUISITANTE JA FEZ ANOS ESTE ANO
    if (tm.tm_mon > nascimento->Mes || tm.tm_mon == nascimento->Mes && tm.tm_mday >= nascimento->Dia)
    {
        return idadeBase;
    }

    // O REQUISITANTE AINDA NAO FEZ ANOS ESTE ANO
    return idadeBase - 1;
}




// ADICIONA UMA REQUISICAO A LISTA DE REQUISICOES DO REQUISITANTE
// E METE COMO DATA DE REQUISICAO A DATA ATUAL
void AdicionarRequisicaoARequisitante(REQUISICAO *requisicao, REQUISITANTE *requisitante)
{

}




void Wizard_Requisicao()
{

}



// CALCULA A IDADE MEDIA DE TODOS OS REQUISITANTES
int CalcularIdadeMediaDosRequisitantes(LISTA_REQUISITANTES *hr)
{
    // VAI GUARDAR A SOMA DA IDADE DOS REQUISITANTES DURANTE O LOOP
    int somaIdades = 0;

    // PRIMEIRO REQUISITANTE NA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP PELOS REQUISITANTES
    while (requisitante)
    {
        // SOMA A IDADE DO REQUISITANTE
        somaIdades += CalcularIdadeDoRequisitante(requisitante);

        // SELECIONA O PROXIMO REQUISITANTE
        requisitante = requisitante->Seguinte;
    }

    return somaIdades / hr->Quantidade;
}



// PROCURA O REQUISITANTE QUE TENHA A IDADE MAIS VELHA
int CalcularIdadeMaximaDosRequisitantes(LISTA_REQUISITANTES *hr)
{
    // VARIAVEL PARA GUARDAR A IDADE MAIS ALTA ENCONTRADA
    int maxIdade = 0;

    // PRIMEIRO REQUISITANTE NA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP POR TODOS OS REQUISITANTES
    while (requisitante)
    {
        // CALCULA A IDADE DO REQUISITANTE ATUAL
        int idade = CalcularIdadeDoRequisitante(requisitante);

        // VERIFICA SE O REQUISITANTE ATUALMENTE EM LOOP TEM UMA IDADE SUPERIOR A IDADE ATUALMENTE GUARDADA NA VARIAVEL 'MAXIDADE'
        if (idade > maxIdade)
        {
            // GUARDA A IDADE DO REQUISITANTE ATUAL NA VARIAVEL PORQUE A IDADE DELE E MAIOR
            maxIdade = idade;
        }

        // SELECIONA O PROXIMO REQUISITANTE
        requisitante = requisitante->Seguinte;
    }

    // DEVOLVE A IDADE OBTIDA
    return maxIdade;
}



// CONTA TODOS OS REQUISITANTES QUE TEM UMA IDADE SUPERIOR A UM VALOR INSERIDO PELO UTILIZADOR
int ContarIdadeSuperior(LISTA_REQUISITANTES *hr, int idade)
{
    // GUARDA A QUANTIDADE DE PESSOAS QUE A IDADE E SUPERIOR AO VALOR DA VARIAVEL 'IDADE'
    int idadeSuperior = 0;

    // VAI BUSCAR O PRIMEIRO REQUISITANTE DA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP POR TODOS OS REQUISITANTES
    while (requisitante)
    {
        // COMPARA A IDADE DO REQUISITANTE ATUALMENTE EM LOOP
        // E VERIFICA SE A IDADE DELE E MAIOR QUE A IDADE NA VARIAVEL 'IDADE'
        if (CalcularIdadeDoRequisitante(requisitante) > idade)
        {
            // ADICIONA 1 A CONTAGEM
            idadeSuperior = idadeSuperior + 1;
        }

        // SELECIONA O PROXIMO REQUISITANTE
        requisitante = requisitante->Seguinte;
    }

    return idadeSuperior;
}




// CALCULA A IDADE MAIS COMUM ENTRE OS REQUISITANTES
int CalcularModaIdade(LISTA_REQUISITANTES *hr)
{
    // # PARTE 1
    // VAI GUARDAR A QUANTIDADE DE IDADES QUE EXISTE EM QUE O INDEX E A IDADE E O VALOR AS VEZES QUE ESSA IDADE APARECE
    int modaIdadeArray[200];

    // METE TODOS OS VALORES DA VARIAVEL A 0
    int loopI = 0;
    for (loopI; loopI < 200; loopI++)
    {
        modaIdadeArray[loopI] = 0;
    }



    // # PARTE 2
    // VAI BUSCAR O PRIMEIRO REQUISITANTE DA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP POR TODOS OS REQUISITANTES
    while (requisitante)
    {
        // CALCULA A IDADE DO REQUISITANTE
        int idade = CalcularIdadeDoRequisitante(requisitante);

        // ADICIONA 1 AO VALOR NA VARIAVEL COM O INDEX DA IDADE DO UTILIZADOR
        modaIdadeArray[idade] = modaIdadeArray[idade] + 1;

        // SELECIONA O REQUISITANTE SEGUINTE
        requisitante = requisitante->Seguinte;
    }



    // # PARTE 3
    // VAI GUARDAR A MODA DA IDADE
    int modaIdade = 0;

    // FAZ LOOP PARA PROCURAR O INDEX (IDADE) COM VALOR MAIS ALTO
    int loopIdade = 0;
    for (loopIdade; loopIdade < 200; loopIdade++)
    {
        // CASO A IDADE ATUAL TENHA UM VALOR MAIS ALTO QUE A
        if (modaIdadeArray[loopIdade] > modaIdadeArray[modaIdade])
        {
            // GUARDA O VALOR NA VARIAVEL
            modaIdade = loopIdade;
        }
    }

    // DEVOLVE A MODA DA IDADE
    return modaIdade;
}



#endif
