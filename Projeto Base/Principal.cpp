
#include "Lista.h"
#include "Hashing.h"


extern Hashing *CriarHashing_PRO();
extern void Destruir_Hashing_PRO(Hashing *H);
extern void Add_Hashing_PRO(Hashing *H, Virus *X);
extern void Mostrar_Hashing_PRO(Hashing *H);
extern int ContarVirusCidade(Hashing *H, const char *nome_cid);
extern int LerInteiro(const char *msg);
extern Lista *CriarLista();
extern void Inserir_Lista(Lista *L, Virus *V);
extern void Destruir_Lista(Lista *L);
extern void Mostrar_Lista(Lista *L);
//----------------------------------------
Virus *CriarVirus(int cod, const char *nome, const char *cid )
{
    Virus *X = (Virus *)malloc(sizeof(Virus));
    X->CODIGO = cod;
    strcpy(X->NOME, nome);
    strcpy(X->CIDADE, cid);
    return X;
}
//----------------------------------------
void MostrarVirus(Virus *V)
{
    printf("VIRUS:%d [%s] [%s] \n", V->CODIGO, V->NOME, V->CIDADE);
}
//----------------------------------------
void DestruirVirus(Virus *V)
{
    // pode ser necessário destruir mais informação que está dentro do Virus
    free(V);
}
//----------------------------------------
//----------------------------------------

typedef struct
{
    Hashing *H_LIVROS;
    Lista *LPESSOAS;
    char LOGS[10];
    // Requisições..........
}Mochila;
//----------------------------------------
Mochila *CriarMochila()
{
    printf("Funcao <%s>\n", __FUNCTION__);
    Mochila *M = (Mochila *)malloc(sizeof(Mochila));
    M->H_LIVROS = CriarHashing_PRO();
    M->LPESSOAS = CriarLista();
    strcpy(M->LOGS, "logs.txt");
    return M;
}
//----------------------------------------
void Mostrar_Mochila(Mochila *M)
{
    printf("Funcao <%s>\n", __FUNCTION__);
    if (!M) return;
    Mostrar_Hashing_PRO(M->H_LIVROS);
    Mostrar_Lista(M->LPESSOAS);
}
//----------------------------------------
void GravarXML(Mochila *M)
{
    printf("Funcao <%s>\n", __FUNCTION__);

}
//----------------------------------------
void MostrarAreaMaisLivros(Mochila *M)
{
    printf("Funcao <%s>\n", __FUNCTION__);

}
//----------------------------------------
void DeterminarPessoasMaisRequisicoes(Mochila *M)
{
    printf("Funcao <%s>\n", __FUNCTION__);

}
//----------------------------------------
void PesquisarLivroISBN(Mochila *M)
{
    // Estrategia
    printf("Funcao <%s>\n", __FUNCTION__);
    int ISBN = LerInteiro("QUak o livro que queres ISBN? ");
    // lfkdslfkdslfdslf

}
//----------------------------------------
void DeterminarSobreNomeMaisUsado(Mochila *M)
{
    // Estrategia
    printf("Funcao <%s>\n", __FUNCTION__);

}
void DestruirMochila(Mochila *M)
{
    printf("Funcao <%s>\n", __FUNCTION__);
    if (!M) return;
    Destruir_Hashing_PRO(M->H_LIVROS);
    Destruir_Lista(M->LPESSOAS);
    free(M);
}
//----------------------------------------
void Load(Mochila *M)
{
    if (!M) return;

    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(123, "V. Ja Foste!", "VISEU"));
    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(123, "V. Ja Foste!", "VISEU"));
    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(1235, "V. Ja yuyu!", "VISEU"));
    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(19, "V. Ja ghgh!", "COVILHA"));
    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(15, "V. Ja 15!", "COVILHA"));
    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(1455, "V. Ja 1erwr5!", "COVILHA"));
    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(14545, "V. Ja 1ewrewr5!", "COIMBRA"));
    Add_Hashing_PRO(M->H_LIVROS, CriarVirus(14549, "CoSAD-V2vid-21", "FUNDAO"));
}
//----------------------------------------
int Menu()
{
    printf("1- Opcao 1\n");
    printf("2- Opcao 2\n");
    printf("3- Opcao 3\n");
    printf("4- Opcao 4\n");
    int N = LerInteiro("Opcao ?");
    return N;
}

int main()
{
    printf("INICIO: Pratico \n\n");
    Mochila *Sacola_TimTim = CriarMochila();
    Load(Sacola_TimTim);
    int OP = 0;
    do
    {
        OP = Menu();
        switch(OP)
        {
            case 1: Mostrar_Mochila(Sacola_TimTim); break;
            case 2: GravarXML(Sacola_TimTim); break;
            case 3: MostrarAreaMaisLivros(Sacola_TimTim); break;
            case 4: DeterminarPessoasMaisRequisicoes(Sacola_TimTim); break;
            case 5: DeterminarSobreNomeMaisUsado(Sacola_TimTim); break;
            case 6: PesquisarLivroISBN(Sacola_TimTim); break;
        }
    }while (OP != 0);
    DestruirMochila(Sacola_TimTim);

    printf("FIM: Pratico \n\n");
    return 0;
}









/*
int main()
{
   printf("INICIO: HASHING \n\n");

   Hashing*HV = CriarHashing_PRO();

   Add_Hashing_PRO(HV, CriarVirus(123, "V. Ja Foste!", "VISEU"));
   Add_Hashing_PRO(HV, CriarVirus(1235, "V. Ja yuyu!", "VISEU"));
   Add_Hashing_PRO(HV, CriarVirus(19, "V. Ja ghgh!", "COVILHA"));
   Add_Hashing_PRO(HV, CriarVirus(15, "V. Ja 15!", "COVILHA"));
   Add_Hashing_PRO(HV, CriarVirus(1455, "V. Ja 1erwr5!", "COVILHA"));
   Add_Hashing_PRO(HV, CriarVirus(14545, "V. Ja 1ewrewr5!", "COIMBRA"));
   Add_Hashing_PRO(HV, CriarVirus(14549, "CoSAD-V2vid-21", "FUNDAO"));

   Mostrar_Hashing_PRO(HV);
   int N = ContarVirusCidade(HV, "COVILHA");
   printf("N = %d\n", N);

   Destruir_Hashing_PRO(HV);

   printf("FIM: HASHING \n\n");
   return 1;
}
*/
