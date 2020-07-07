#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LIVRO *Criar_Livro()
{
    LIVRO *livro = (LIVRO *)malloc(sizeof(LIVRO));

    livro->ISBN = 0;
    livro->AnoDePublicacao = 0;

    return livro;
}

LIVRO *Criar_Livro_Preenchido(int isbn, char *titulo, char *autor, char *area, int anoDePublicacao)
{
    LIVRO *livro = Criar_Livro();

    livro->ISBN = isbn;
    strcpy(livro->Titulo, titulo);
    strcpy(livro->Autor, autor);
    strcpy(livro->Area, area);
    livro->AnoDePublicacao = anoDePublicacao;

    return livro;
}

LIVRO *Wizard_Livro()
{
    int isbn;
    char *titulo;
    char *autor;
    char *area;
    int anoDePublicacao;

    printf("Insira o ISBN do Livro: "); isbn = LerInteiro(NULL, NULL);
    printf("Insira o T�tulo do Livro: "); titulo = LerString();
    printf("Insira o Autor do Livro: "); autor = LerString();
    printf("Insira a Area do Livro: "); area = LerString();
    printf("Insira o Ano de Publica��o do Livro: "); anoDePublicacao = LerInteiro(NULL, AnoAtual());

    return Criar_Livro_Preenchido(isbn, titulo, autor, area, anoDePublicacao);
}





NO_LIVRO *Criar_NoLivro()
{
    NO_LIVRO *no_livro = (NO_LIVRO *)malloc(sizeof(NO_LIVRO));

    no_livro->Livro = NULL;
    no_livro->Seguinte = NULL;

    return no_livro;
}
