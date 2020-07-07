typedef struct Livro
{
    int ISBN;
    char Titulo[100];
    char Autor[100];
    char Area[100];
    int AnoDePublicacao;
} LIVRO;



typedef struct No_Livro
{
    LIVRO *Livro;
    struct No_Livro *Seguinte;
} NO_LIVRO;



typedef struct Lista_Livros
{
    NO_LIVRO *Inicio;
    int Quantidade;
} LISTA_LIVROS;



typedef struct No_Hashing_Livro
{
    LISTA_LIVROS ListaLivros;
    struct No_Hashing_Livro *Seguinte;
    int Requisicoes;
    char Nome[100];
} NO_HASHING_LIVRO;



typedef struct Hashing_Livros
{
    NO_HASHING_LIVRO *Inicio;
    int Quantidade;
} HASHING_LIVROS;
