#ifndef _REQUISITANTES_H_
#define _REQUISITANTES_H_

struct REQUISITANTE
{
    char ID[9];
    char Nome[100];
    int DiaNascimento;
    int MesNascimento;
    int AnoNascimento;
    char ID_Freguesia[6];
};



struct NO_REQUISITANTE
{
    REQUISITANTE *Requisitante;
    struct No_Requisitante *Seguinte;
};



struct LISTA_REQUISITANTES
{
    NO_REQUISITANTE *Start;
    int Quantidade;
};



struct DATA
{
    int Dia;
    int Mes;
    int Ano;
};

#endif
