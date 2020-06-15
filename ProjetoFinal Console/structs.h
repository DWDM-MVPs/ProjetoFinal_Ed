#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

struct Livro
{
    int ISBN;
    char Titulo[100];
    char Autor[100];
    char Area[100];
    int AnoDePublicacao;
};

struct Concelho
{
    int ID;
    char *Nome;
};

struct Distrito
{
    int ID;
    char *Nome;
};

struct Data
{
    int Dia;
    int Mes;
    int Ano;
};

struct Requisitante
{
    int ID;
    char Nome[100];
    Data DataDeNascimento;
    char ID_Freguesia[6];
};

#endif // STRUCTS_H_INCLUDED
