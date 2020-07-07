/** ---------- INCLUDES ---------- */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "hashing.h"

extern void destruirRequisitante(void *requisitante);
extern void destruirLivro(void *livro);

/** ---------- MAIN ---------- */

int main()
{
    setlocale(LC_ALL, ""); // caracteres acentuados

    HASHING *hashingDist = criarHashing();
    HASHING *hashingLivro = criarHashing();

    printf("\n______________________________________________________________________________________________________________\n\n");
    printf("-                                          Gestão da biblioteca - ED                                        -");
    printf("\n______________________________________________________________________________________________________________\n\n");

    printf("\n>> Aguarde o carregamento dos dados...\n");

    int *ultimoId = lerFicheiroReq(hashingDist, "requisitantes.txt");
    printf("\n>> [%d] requisitantes carregados\n", contaReq(hashingDist));

    int livrosCount = lerFicheiroLivro(hashingLivro);
    printf("\n>> [%d] livros carregados\n", livrosCount);


    int requisicoesCount = lerFicheiroRequisicoesTXT(hashingDist, hashingLivro);
    printf("\n>> [%d] requisições carregadas\n", requisicoesCount);

    int choice;
    int choice1;
    int choice2;
    int choice3;

    do
    {
        choice = menu();

        switch(choice)
        {
            case 1:
            {
                funcaosubmenu1(hashingLivro);
                break;
            }

            case 2:
            {
                funcaosubmenu2(hashingDist, ultimoId);
                break;
            }

            case 3:
            {
                funcaosubmenu3(hashingDist, hashingLivro);
                break;
            }

            case 4:
            {
                int totalMem = MemoriaTotalEstrutura(hashingLivro, hashingDist);
                printf("\n>> Tamanho total da estrutura: %d bytes\n", totalMem);
                pressioneQualquerTecla();
                break;
            }

            case 5:
            {
                break;
            }

            case 6:
            {
                break;
            }

            case 0:
                break;

            default:
            {
                printf("\n>> Introduza um número válido\n");
                break;
            }
        }
    } while(choice != 0);
}




