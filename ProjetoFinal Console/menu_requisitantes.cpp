#ifndef _MENU_REQUISITANTES_CPP_
#define _MENU_REQUISITANTES_CPP_

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

extern void ImprimirMenu(const char *titulo);
extern void ImprimirFuncao(const char *titulo);
extern void ImprimirDuplo(const char *funcao, const char *menu);

void MensagemNaoExistemRequisitantes()
{
    printf("Não existem Requisitantes.");
    PAUSE_CLS;
}


















// FAZ O PRINTF DE TODAS AS INFORMACOES DO LIVRO
void MostrarRequisitante(REQUISITANTE *requisitante)
{
    printf("ID: %d", requisitante->ID);
    printf("\nNome: %s", requisitante->Nome);
    printf("\nID da Freguesia: %d", requisitante->ID_Freguesia);
    printf("\nData de Nascimento: %d/%d/%d", requisitante->DataDeNascimento->Dia, requisitante->DataDeNascimento->Mes, requisitante->DataDeNascimento->Ano);
    printf("\nNúmero de Requisições: %d", requisitante->ListaRequisicoes->NumeroTotalDeRequisicoes);
}

void MostrarData(DATA *data)
{
    printf("%02d/%02d/%04d", data->Dia, data->Mes, data->Ano);
}

// FAZ PRINTD DE TODAS AS INFORMACOES DE UMA REQUISICAO
void MostrarRequisicao(REQUISICAO *requisicao)
{
    printf("ISBN do Livro: %d", requisicao->ISBN_Livro);
    printf("\nData de Requisição: "); MostrarData(requisicao->DataRequisicao);
    printf("\nID do Requisitante: %d", requisicao->ID_Requisitante);
}



// MOSTRA A LISTA DE REQUISITANTES
void ListarRequisitantes(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Listar Requisitantes", "Requisitantes");

    // VERIFICA SE HA REQUISITANTES REGISTADOS
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // GUARDA O PRIMEIRO REQUISITANTE NA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP PELOS REQUISITANTES
    while (requisitante)
    {
        // MOSTRA AS INFORMACOES DO REQUISITANTE
        MostrarRequisitante(requisitante);

        // SELECIONA O REQUISITANTE SEGUINTE
        requisitante = requisitante->Seguinte;
    }

    PAUSE_CLS;
}




extern REQUISITANTE *Wizard_Requisitante(LISTA_REQUISITANTES *hr);
// MOSTRA O MENU PARA CRIAR UM NOVO REQUISITANTE
void CriarRequisitante(LISTA_REQUISITANTES *hr)
{
    // MOSTRA AO UTILIZADOR O ECRA PARA CRIAR UM NOVO REQUISITANTE
    ImprimirDuplo("WIZARD: Criar novo Requisitante", "Requisitantes");
    REQUISITANTE *r = Wizard_Requisitante(hr);
    CLS;

    // MOSTRA AS INFORMACOES GUARDADAS DO REQUISITANTE QUE O UTILIZADOR ACABOU DE CRIAR
    ImprimirFuncao("Requisitante criado com sucesso!");
    MostrarRequisitante(r);
    PAUSE_CLS;
}




// PESQUISA UM REQUISITANTE POR UM NOME INTRODUZIDO PELO UTILIZADOR
void PesquisarRequisitantePorNome(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Pesquisar Requisitante por Nome", "Requisitantes");

    // VERIFICA SE HA REQUISITANTES REGISTADOS
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // GUARDA INPUT DO UTILIZADOR
    char nome[100];
    char temp;

    // LE UM NOME DE REQUISITANTE DO UTILIZADOR
    printf("Insira o Nome do Requisitante a pesquisar: ");
    scanf("%c",&temp);
    scanf("%[^\n]", nome);

    // GUARDA O PRIMEIRO REQUISITANTE DA LISTA
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP PELOS REQUISITANTES
    while (requisitante)
    {
        // VERIFICA SE O NOME DO REQUISITANTE NO LOOP CORRESPONDE AO NOME A PROCURAR INTRODUZIDO PELO UTILIZADOR
        // E SE CORRESPONDER MOSTRA AS INFORMACOES DO REQUISITANTE ENCONTRADO
        if (requisitante->Nome == nome)
        {
            printf("\nRequisitante encontrado!\n\n\n\nInformações do Requisitante encontrado:\n\n");
            MostrarRequisitante(requisitante);
            PAUSE_CLS;
            return;
        }

        // SELECIONA O PROXIMO REQUISITANTE
        requisitante = requisitante->Seguinte;
    }

    // MOSTRA UMA MENSAGEM A DIZER QUE NENHUM REQUISITATE COM O NOME INTRODUZIDO PELO UTILIZADOR FOI ENCONTRADO
    printf("Não foi encontrado nenhum Requisitante com o Nome %s", nome);
    PAUSE_CLS;
}




extern int CalcularIdadeMediaDosRequisitantes(LISTA_REQUISITANTES *hr);
// MOSTRA A IDADE MEDIA DE TODOS OS REQUISITANTES
void IdadeMediaDosRequisitantes(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Idade média dos Requisitantes", "Requisitantes");

    // VERIFICA SE HA REQUISITANTES REGISTADOS
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // IMPRIME A MEDIA DAS IDADES
    printf("Média das Idades dos Requisitantes: %d", CalcularIdadeMediaDosRequisitantes(hr));
    PAUSE_CLS;
}





extern int CalcularIdadeMaximaDosRequisitantes(LISTA_REQUISITANTES *hr);
// MOSTRA A IDADE DO CLIENTE MAIS VELHO
void IdadeMaximaDosRequisitantes(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Idade máxima dos Requisitantes", "Requisitantes");

    // NAO EXISTEM REQUISITANTES
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // MOSTRA A IDADE MAXIMA DOS REQUISITANTES (NESTE CASO A IDADE DO REQUISITANTE MAIS VELHO)
    printf("Idade máxima dos Requisitantes: %d", CalcularIdadeMaximaDosRequisitantes(hr));
    PAUSE_CLS;
}





extern int ContarIdadeSuperior(LISTA_REQUISITANTES *hr, int idade);
// MOSTRA A CONTAGEM DE REQUISITANTES QUE TEM A IDADE SUPERIOR A UM VALOR INSERIDO PELO UTILIZADOR
void ContagemIdadeSuperior(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Contagem Idade superior", "Requisitantes");

    // VERIFICA SE EXISTEM REQUISITANTES
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    int valor;
    printf("Insira o valor a verificar: "); scanf("%d", &valor);

    printf("\n\nNúmero de Requisitantes com Idade superior a '%d': %d", valor, ContarIdadeSuperior(hr, valor));
    PAUSE_CLS;
}






extern int CalcularModaIdade(LISTA_REQUISITANTES *hr);
// MOSTRA A MODA DAS IDADES DOS REQUISITANTES
void ModaDasIdades(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Moda das Idades", "Requisitantes");

    // VERIFICA SE EXISTEM REQUISITANTES
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // IMPRIME O VALOR DA MODA DAS IDADES
    printf("Moda das Idades dos Requisitantes: %d", CalcularModaIdade(hr));
    PAUSE_CLS;
}






// FAZ UMA LISTAGEM DE TODOS OS REQUISITANTES QUE NUNCA FIZERAM UMA REQUISICAO
void MostrarSemRequisicoes(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Mostrar Requisitantes com nenhuma Requisição", "Requisitantes");

    // VERIFICA SE HA REQUISITANTES
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // PARA MOSTRAR UMA MENSAGEM CASO NAO HAJA REQUISITANTES SEM REQUISICOES
    bool encontrado = false;

    // SELECIONA O PRIMEIRO REQUISITANTE
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP POR TODOS OS REQUISITANTES
    while (requisitante)
    {
        // VERIFICA SE O REQUISITANTE NUNCA FEZ NENHUMA REQUISICAO
        if (requisitante->ListaRequisicoes->NumeroTotalDeRequisicoes == 0)
        {
            // IMPRIME AS INFORMACOES DO REQUISITANTE
            MostrarRequisitante(requisitante);
            printf("\n\n");

            // DESATIVAR A MENSAGEM
            encontrado = true;
        }

        requisitante = requisitante->Seguinte;
        // SELECIONA O PROXIMO REQUISITANTE
    }

    // MOSTRA UMA MENSAGEM A DIZER QUE NAO FOI ENCONTRADO NENHUM REQUISITANTE SEM REQUISICOES
    if (!encontrado)
    {
        printf("Não foram encontrados Requisitantes com nenhuma Requisição.");
    }

    PAUSE_CLS;
}





// LISTAR COM REQUISICOES ATIVAS
void MostrarRequisicoesAtivas(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Mostrar Requisitantes com Requisições ativas", "Requisitantes");

    // VERIFICA SE HA REQUISITANTES
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // PARA MOSTRAR UMA MENSAGEM CASO NAO HAJA REQUISITANTES COM REQUISICOES ATIVAS
    bool encontrado = false;

    // SELECIONA O PRIMEIRO REQUISITANTE
    REQUISITANTE *requisitante = hr->Inicio;

    // FAZ LOOP POR TODOS OS REQUISITANTES
    while (requisitante)
    {
        // VERIFICA SE O REQUISITANTE TEM ALGUMA REQUISICAO ATIVA
        if (requisitante->ListaRequisicoes->RequisicoesAtivas == 0)
        {
            // IMPRIME AS INFORMACOES DO REQUISITANTE
            MostrarRequisitante(requisitante);
            printf("\n\n");

            // DESATIVAR A MENSAGEM
            encontrado = true;
        }

        requisitante = requisitante->Seguinte;
        // SELECIONA O PROXIMO REQUISITANTE
    }

    // MOSTRA UMA MENSAGEM A DIZER QUE NAO FOI ENCONTRADO NENHUM REQUISITANTE SEM REQUISICOES
    if (!encontrado)
    {
        printf("Não foram encontrados Requisitantes com Requisições ativas.");
    }

    PAUSE_CLS;
}







extern REQUISITANTE *PesquisarRequisitantePorId(LISTA_REQUISITANTES *hr, int id);
// PEDE AO UTILIZADOR UM ID PARA PROCURAR UM REQUISITANTE
// PESQUISA UM REQUISITANTE PELO ID FORNECIDO
// E MOSTRA AS REQUISICOES PARA ESSE REQUISITANTE
void MostrarRequisicoesDeRequisitante(LISTA_REQUISITANTES *hr)
{
    ImprimirDuplo("Ver Requisições de um Requisitante", "Requisitantes");

    // VERIFICA SE HA REQUISITANTES
    if (hr->Quantidade == 0)
    {
        MensagemNaoExistemRequisitantes();
        return;
    }

    // # PARTE 1
    // PEDE UM ID DE REQUISITANTE AO UTILIZADOR
    int id = 0;
    printf("Insira o ID do Requisitante a pesquisar: ");
    scanf("%d", &id);

    // # PARTE 2
    // PROCURA O REQUISITANTE PELO ID DADO PELO UTILIZADOR
    REQUISITANTE *requisitante = PesquisarRequisitantePorId(hr, id);

    // VERIFICA SE O REQUISITANTE FOI ENCONTRADO
    if (!requisitante)
    {
        printf("Não foi encontrado nenhum Requisitante com o ID '%d'.", id);
        PAUSE_CLS;
        return;
    }

    // # PARTE 3
    // VERIFICA SE O REQUISITANTE TEM ALGUMA REQUISICAO
    if (requisitante->ListaRequisicoes->RequisicoesAtivas == 0)
    {
        printf("O Requisitante com o ID '%d' não tem Requisições ativas.", id);
        PAUSE_CLS;
        return;
    }

    // SELECIONA A PRIMEIRA REQUISICAO DO REQUISITANTE
    REQUISICAO *requisicao = requisitante->ListaRequisicoes->Inicio;

    // FAZ LOOP PELAS REQUISICOES ATIVAS DO REQUISITANTE
    while (requisicao)
    {
        // MOSTRA AS REQUISICOES DO REQUISITANTE ENCONTRADO
        MostrarRequisicao(requisicao);

        // SELECIONA A REQUISICAO SEGUINTE
        requisicao = requisicao->Seguinte;
    }

    PAUSE_CLS;
    return;
}




void MenuRequisitantes(LISTA_REQUISITANTES *hr)
{
    int escolha = 0;
    do
    {
        ImprimirMenu("Gerir Requisitantes");

        printf("\n1. Criar Requisitante");
        printf("\n2. Listar Requisitantes");
        printf("\n3. Pesquisar Requisitante por Nome");
        printf("\n4. Idade Média dos Requisitantes");
        printf("\n5. Idade Máxima dos Requisitantes");
        printf("\n6. Contagem Idade superior");
        printf("\n7. Moda das Idades");
        printf("\n8. Mostrar Requisitantes com nenhuma Requisição");
        printf("\n9. Mostrar Requisitantes com Requisições ativas");
        printf("\n10. Ver Requisições de um Requisitante");
        printf("\n\n0. Voltar");
        printf("\n\n\n\n\n »---> Escolha: ");

        scanf("%d", &escolha);

        CLS;

        switch(escolha)
        {
            case 1: CriarRequisitante(hr); break;
            case 2: ListarRequisitantes(hr); break;
            case 3: PesquisarRequisitantePorNome(hr); break;
            case 4: IdadeMediaDosRequisitantes(hr); break;
            case 5: IdadeMaximaDosRequisitantes(hr); break;
            case 6: ContagemIdadeSuperior(hr); break;
            case 7: ModaDasIdades(hr); break;
            case 8: MostrarSemRequisicoes(hr); break;
            case 9: MostrarRequisicoesAtivas(hr); break;
            case 10: MostrarRequisicoesDeRequisitante(hr); break;
        }
    } while (escolha != 0);
}


#endif
