#ifndef LIVROS_H_INCLUDED
#define LIVROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"
#include "structs.h"

int ApagarLivro(Livro *l)
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

    printf("Insira o ISBN do Livro: "); isbn = LerInteiro(NULL, NULL);
    printf("Insira o Título do Livro: "); titulo = LerString();
    printf("Insira o Autor do Livro: "); autor = LerString();
    printf("Insira a Area do Livro: "); area = LerString();
    printf("Insira o Ano de Publicação do Livro: "); anoDePublicacao = LerInteiro(NULL, AnoAtual());

    return CriarLivro(isbn, titulo, autor, area, anoDePublicacao);
}

#endif // LIVROS_H_INCLUDED
