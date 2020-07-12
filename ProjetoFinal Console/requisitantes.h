#ifndef _REQUISITANTES_H_
#define _REQUISITANTES_H_





struct DATA
{
    int Dia;
    int Mes;
    int Ano;
};





struct REQUISITANTE
{
    int ID;
    char Nome[100];
    DATA *DataDeNascimento;
    int NumeroRequisicoes;
    int ID_Freguesia;
    REQUISITANTE *Seguinte;
};



struct LISTA_REQUISITANTES
{
    REQUISITANTE *Inicio;
    int Quantidade;
};





struct REQUISICAO
{
    char IdRequisitante[9];
    char IsbnLivro;
    DATA *DataRequisicao;
    REQUISICAO *Seguinte;
};



struct LISTA_REQUISICOES
{
    REQUISICAO *Inicio;
    int QuantidadeRequisicoes;
};

#endif
