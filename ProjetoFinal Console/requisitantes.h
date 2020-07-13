#ifndef _REQUISITANTES_H_
#define _REQUISITANTES_H_





struct DATA
{
    int Dia;
    int Mes;
    int Ano;
};





struct REQUISICAO
{
    int ID_Requisitante;
    int ISBN_Livro;
    DATA *DataRequisicao;
    REQUISICAO *Seguinte;
};

struct LISTA_REQUISICOES
{
    REQUISICAO *Inicio;
    int NumeroTotalDeRequisicoes;
    int RequisicoesAtivas;
};





struct REQUISITANTE
{
    int ID;
    char Nome[100];
    DATA *DataDeNascimento;
    char ID_Freguesia[6];
    REQUISITANTE *Seguinte;
    LISTA_REQUISICOES *ListaRequisicoes;

};

struct LISTA_REQUISITANTES
{
    REQUISITANTE *Inicio;
    int Quantidade;
};

#endif
