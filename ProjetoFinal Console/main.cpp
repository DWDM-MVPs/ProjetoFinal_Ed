#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "livros.h"
#include "requisitantes.h"
#include "localidades.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;


extern void MenuRequisitantes(LISTA_REQUISITANTES *hr);
extern void MenuFicheiros(LISTA_CATEGORIAS *hl, LISTA_REQUISITANTES *hr, LISTA_LOCALIDADES *hz);

extern LISTA_CATEGORIAS *Criar_ListaCategorias();
extern LISTA_REQUISITANTES *Criar_ListaRequisitantes();
extern LISTA_REQUISICOES *Criar_ListaRequisicoes();
extern LISTA_LOCALIDADES *Criar_ListaLocalidades();



void ImprimirMenu(const char *menu)
{
    CLS;

    printf("# =============================================================== #");
    printf("\n# ============================================== > #");
    printf("\n# ========================================================================== # > %s >", menu);
    printf("\n# ============================================== > #");
    printf("\n# =============================================================== #\n\n\n\n");
}

void ImprimirFuncao(const char *funcao)
{
    printf("# ===================== # > %s < # ===================== #\n\n", funcao);
}

void ImprimirDuplo(const char *funcao, const char *menu)
{
    ImprimirMenu(menu);
    ImprimirFuncao(funcao);
}



void GuardarRequisicao(LISTA_REQUISICOES *hs, REQUISICAO *requisicao)
{
    requisicao->Seguinte = hs->Inicio;
    hs->Inicio = requisicao;

    hs->NumeroTotalDeRequisicoes = hs->NumeroTotalDeRequisicoes + 1;
    hs->RequisicoesAtivas = hs->RequisicoesAtivas + 1;
}


extern REQUISICAO *Criar_Requisicao();
extern bool ExisteISBN(LISTA_CATEGORIAS *hl, int isbn);
extern bool ExisteID(LISTA_REQUISITANTES *hr, int id);
extern DATA *Criar_Data_Preenchida(int dia, int mes, int ano);
void CriarRequisicao(LISTA_CATEGORIAS *hl, LISTA_REQUISITANTES *hr, LISTA_REQUISICOES *hs)
{
    ImprimirDuplo("Criar Requisição", "Requisições");

    int isbn = 0;
    int id = 0;

    printf("Insira o ID do Requisitante: ");
    scanf("%d", &id);

    printf("Insira o ISBN do Livro: ");
    scanf("%d", &isbn);

    if (!ExisteISBN(hl, isbn))
    {
        printf("\n\nNão existe nenhum Livro com esse ISBN.");
        PAUSE_CLS;
        return;
    }
    if (!ExisteID(hr, id))
    {
        printf("\n\nNão existe nenhum Requisitante com esse ID.");
        PAUSE_CLS;
        return;
    }

    REQUISITANTE *requisitante = hr->Inicio;

    while (requisitante)
    {
        if (requisitante->ID == id)
        {
            REQUISICAO *requisicao = Criar_Requisicao();

            time_t tempo = time(NULL);
            struct tm tm = *localtime(&tempo);

            requisicao->DataRequisicao = Criar_Data_Preenchida(tm.tm_mday, tm.tm_mon, tm.tm_year);
            requisicao->ID_Requisitante = id;
            requisicao->ISBN_Livro = isbn;

            GuardarRequisicao(hs, requisicao);
        }

        requisitante = requisitante->Seguinte;
    }

    printf("\n\nRequisição criada com sucesso.");
}








extern void LerLivros(LISTA_CATEGORIAS *hl);
extern void LerRequisitantes(LISTA_REQUISITANTES *hr);
extern void LerConcelhos(LISTA_LOCALIDADES *hz);
extern void LerDistritos(LISTA_LOCALIDADES *hz);
extern void LerFreguesias(LISTA_LOCALIDADES *hz);
extern void GravarLivros(LISTA_CATEGORIAS *hl);
extern void GravarRequisitantes(LISTA_REQUISITANTES *hr);
// MAIN
int main()
{
    setlocale(LC_ALL, "");

    LISTA_CATEGORIAS *hl = Criar_ListaCategorias();
    LISTA_REQUISITANTES *hr = Criar_ListaRequisitantes();
    LISTA_REQUISICOES *hs = Criar_ListaRequisicoes();
    LISTA_LOCALIDADES *hz = Criar_ListaLocalidades();

    LerLivros(hl);
    LerRequisitantes(hr);
    LerConcelhos(hz);
    LerDistritos(hz);
    LerFreguesias(hz);

    int escolha = 0;
    do
    {
        ImprimirMenu("Gestor de Biblioteca");

        printf("\n1. Gerir Livros");
        printf("\n2. Gerir Requisitantes");
        printf("\n3. Gerir Ficheiros");
        printf("\n4. Criar Requisição");
        printf("\n\n0. Sair");
        printf("\n\n\n\n\n »---> Escolha: ");

        scanf("%d", &escolha);

        CLS;

        switch(escolha)
        {
            extern void MenuLivros(LISTA_CATEGORIAS *hl);
            case 1: MenuLivros(hl); break;
            case 2: MenuRequisitantes(hr); break;
            case 3: MenuFicheiros(hl, hr, hz); break;
            case 4: CriarRequisicao(hl, hr, hs); break;
        }
    } while (escolha != 0);

    GravarLivros(hl);
    GravarRequisitantes(hr);

	return 0;
}
