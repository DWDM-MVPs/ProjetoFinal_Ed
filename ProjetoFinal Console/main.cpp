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
        }
    } while (escolha != 0);

    GravarLivros(hl);
    GravarRequisitantes(hr);

	return 0;
}
