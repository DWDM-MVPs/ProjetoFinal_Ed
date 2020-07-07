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
