#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "livros.h"
#include "requisitantes.h"

#define PAUSE printf("\n\n\n\n\n"); system("PAUSE");
#define CLS system("CLS");
#define PAUSE_CLS PAUSE CLS;

extern LISTA_CATEGORIAS *Criar_ListaCategorias();
extern void MenuLivros(LISTA_CATEGORIAS *hl);

extern LISTA_REQUISITANTES *Criar_ListaRequisitantes();
extern void MenuRequisitantes(LISTA_REQUISITANTES *hr);



void ImprimirMenu(const char *menu)
{
    CLS;

    printf("# =============================================================== #");
    printf("\n# ============================================== > #");
    printf("\n# ======================= # > %s >", menu);
    printf("\n# ============================================== > #");
    printf("\n# =============================================================== #\n\n\n\n");
}

void ImprimirFuncao(const char *funcao)
{
    printf("# ===================== # > %s < # ===================== #\n\n", funcao);
}

void ImprimirDuplo(const char *funcao, const char *menu)
{
    CLS;

    printf("# =============================================================== #");
    printf("\n# ============================================== > #");
    printf("\n# ======================= # > %s >", menu);
    printf("\n# ============================================== > #");
    printf("\n# =============================================================== #\n\n\n\n");

    printf("# ===================== # > %s < # ===================== #\n\n", funcao);
}












int main()
{
    setlocale(LC_ALL, "");

    LISTA_CATEGORIAS *hl = Criar_ListaCategorias();
    LISTA_REQUISITANTES *hr = Criar_ListaRequisitantes();

    MenuRequisitantes(hr);
    MenuLivros(hl);

	return 0;
}
