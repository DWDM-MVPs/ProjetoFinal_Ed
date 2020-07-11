// HASING_LIVROS    -> NO_HASING_LIVRO  -> LISTA_LIVROS -> LIVRO
// LISTA_CATEGORIAS -> INDEX_CATEGORIAS -> LISTA_LIVROS -> LIVRO





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
};



// LISTA DE LIVROS
struct LISTA_LIVROS
{
    LIVRO *Inicio;
    int QuantidadeDeLivros;
};



// AREA / CATEGORIA
struct CATEGORIA
{
    char Nome[100];
    int NumeroDeRequisicoes;
    LISTA_LIVROS *ListaDeLivros;
    CATEGORIA *Seguinte;
};



// LISTA DAS AREAS / CATEGORIAS
struct LISTA_CATEGORIAS
{
    CATEGORIA *Inicio;
    int Quantidade;
};
