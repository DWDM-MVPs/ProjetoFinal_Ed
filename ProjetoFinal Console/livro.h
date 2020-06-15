#ifndef NEW_H_INCLUDED
#define NEW_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

struct Livro
{
    int ISBN;
    char Titulo[100];
    char Autor[100];
    char Area[100];
    int AnoDePublicacao;
};

void ApagarLivro(Livro *l)
{
    free(l);
}

Livro *CriarLivro(int isbn, char *titulo, char *autor, char *area, int anoDePublicacao)
{
    Livro *livro = (Livro *)malloc(sizeof(Livro));

    livro->ISBN = isbn;
    strcpy(livro->Titulo, titulo);
    strcpy(livro->Autor, autor);
    strcpy(livro->Area, area);
    livro->AnoDePublicacao = anoDePublicacao;

    return livro;
}

Livro *WizardCriarLivro()
{
    int isbn;
    char *titulo;
    char *autor;
    char *area;
    int anoDePublicacao;

    printf("Insira o ISBN do Livro: "); isbn = LerInteiro();
    printf("Insira o Título do Livro: "); titulo = LerString();
    printf("Insira o Autor do Livro: "); autor = LerString();
    printf("Insira a Area do Livro: "); area = LerString();
    printf("Insira o Ano de Publicação do Livro: "); anoDePublicacao = LerInteiro();

    return CriarLivro(isbn, titulo, autor, area, anoDePublicacao);
}

#endif // NEW_H_INCLUDED
