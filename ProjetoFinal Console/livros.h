// LIVRO
struct LIVRO
{
    int ISBN;
    char Titulo[100];
    char Autor[100];
    char Area[100];
    int AnoDePublicacao;
    int NumeroDeRequisicoes;
};



// ELEMENTOS DA LISTA DE LIVROS
struct NO_LIVRO
{
    LIVRO *Livro;
    NO_LIVRO *Seguinte;
};



// LISTA DE LIVROS
struct LISTA_LIVROS
{
    NO_LIVRO *Inicio;
    int QuantidadeDeLivros;
};



// AREA / CATEGORIA
struct NO_HASHING_LIVRO
{
    char Nome[100];
    int NumeroDeRequisicoes;
    LISTA_LIVROS *ListaDeLivros;
    NO_HASHING_LIVRO *Seguinte;
};



// LISTA DAS AREAS / CATEGORIAS
struct HASHING_LIVROS
{
    NO_HASHING_LIVRO *Inicio;
    int Quantidade;
};
