#ifndef NEW_H_INCLUDED
#define NEW_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro
{
    int ISBN;
    char Titulo[100];
    char Autor[100];
    char Area[100];
    int AnoDePublicacao;
} Livro;

void ApagarLivro(Livro *l)
{
    free(l);
}

Livro *CriarLivro(int isbn, const char *titulo, const char *autor, const char *area, int anoDePublicacao)
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
    char titulo[100];
    char autor[100];
    char area[100];
    int anoDePublicacao;

    printf("Insira o ISBN do Livro: "); scanf("%d", &isbn);
    printf("Insira o Título do Livro: "); scanf("%c", &titulo);
    printf("Insira o Autor do Livro: "); scanf("%c", &autor);
    printf("Insira a Area do Livro: "); scanf("%c", &area);
    printf("Insira o Ano de Publicação do Livro: "); scanf("%i", &anoDePublicacao);

    return CriarLivro(isbn, titulo, autor, area, anoDePublicacao);
}

#endif // NEW_H_INCLUDED
