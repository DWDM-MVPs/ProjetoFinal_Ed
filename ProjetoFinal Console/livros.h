#ifndef _LIVROS_H_
#define _LIVROS_H_

// LISTA_CATEGORIAS -> CATEGORIA -> LIVRO





// LIVRO
struct LIVRO
{
    int ISBN;
    char Titulo[100];
    char Autor[100];
    char Area[100];
    int AnoDePublicacao;
    int NumeroDeRequisicoes;
    LIVRO *Seguinte;
    bool Disponivel;
};



// AREA / CATEGORIA
struct CATEGORIA
{
    char Nome[100];
    int NumeroDeRequisicoes;
    int QuantidadeDeLivros;
    LIVRO *Inicio;
    CATEGORIA *Seguinte;
};



// LISTA DAS AREAS / CATEGORIAS
struct LISTA_CATEGORIAS
{
    CATEGORIA *Inicio;
    int QuantidadeDeLivros;
    int NumeroDeRequisicoes;
};

#endif
