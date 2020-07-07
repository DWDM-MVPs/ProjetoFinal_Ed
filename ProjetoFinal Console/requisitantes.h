typedef struct Requisitante
{
    char ID[9];
    char Nome[100];
    int DiaNascimento;
    int MesNascimento;
    int AnoNascimento;
    char ID_Freguesia[6];
} REQUISITANTE;



typedef struct No_Requisitante
{
    REQUISITANTE *Requisitante;
    struct No_Requisitante *Seguinte;
} NO_REQUISITANTE;



typedef struct Lista_Requisitantes
{
    NO_REQUISITANTE *Start;
    int Quantidade;
} LISTA_REQUISITANTES;
