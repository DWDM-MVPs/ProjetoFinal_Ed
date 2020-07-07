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
