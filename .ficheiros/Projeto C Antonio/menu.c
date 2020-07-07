#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "hashing.h"
#include "lista.h"

/** ---------- MENU PRINCIPAL ---------- */

int menu(){

 int choice;

    do{
        printf("\n\n______________________________________________________________________________________________________________\n");
        printf("\n-                                             Menu principal                                                 -");
        printf("\n______________________________________________________________________________________________________________");
        printf("\n-                                                                                                            -");
        printf("\n- [1]  Gerir os livros                                                                                       -");
        printf("\n-                                                                                                            -");
        printf("\n- [2]  Gerir a lista de requisitantes                                                                        -");
        printf("\n-                                                                                                            -");
        printf("\n- [3]  Gerir as requisições de livros                                                                      -");
        printf("\n-                                                                                                            -");
        printf("\n- [4]  Determinar a memória ocupada por toda a Estrutura de Dados                                           -");
        printf("\n-                                                                                                            -");
        printf("\n- [5]  Gravar toda a informação para um dado ficheiro XML, cujo nome é introduzido pelo utilizador        -");
        printf("\n-                                                                                                            -");
        printf("\n- [6]  Gravar toda a informação em ficheiros .txt e .csv                                                   -");
        printf("\n-                                                                                                            -");
        printf("\n______________________________________________________________________________________________________________\n");
        printf("\n- [0]  Sair                                                                                                  -");
        printf("\n______________________________________________________________________________________________________________\n");

    printf("\n\n>> Escolha uma opção: ");
    choice = 0;
    scanf("%d",&choice);

    }while(choice<0 || choice>7);

    return choice;
}

/** ---------- SUBMENU 1 ---------- */

int submenu1(){

    int choice1;

    do{
        printf("\n\n______________________________________________________________________________________________________________\n");
        printf("\n-                                               Gerir os livros                                              -");
        printf("\n______________________________________________________________________________________________________________");
        printf("\n-                                                                                                            -");
        printf("\n- [1]  Adicionar livros à Biblioteca (na espetiva área)                                                    -");
        printf("\n-                                                                                                            -");
        printf("\n- [2]  Listar todos os livros da Biblioteca (organizados por área)                                          -");
        printf("\n-                                                                                                            -");
        printf("\n- [3]  Determinar qual a área com mais livros                                                               -");
        printf("\n-                                                                                                            -");
        printf("\n- [4]  Verificar se um dado livro existe (dado o ISBN)                                                       -");
        printf("\n-                                                                                                            -");
        printf("\n- [5]  Determinar qual(ais) os livros mais recentes (O que tiver o ano mais recente)                         -");
        printf("\n-                                                                                                            -");
        printf("\n- [6]  Determinar qual o livro mais requisitado                                                              -");
        printf("\n-                                                                                                            -");
        printf("\n- [7]  Determinar qual área mais requisitada                                                                -");
        printf("\n-                                                                                                            -");
        printf("\n______________________________________________________________________________________________________________\n");
        printf("\n- [0]  Voltar para o menu principal                                                                          -");
        printf("\n______________________________________________________________________________________________________________\n");

        printf("\n\n>> Escolha uma opção: ");
        choice1 = 0;
        scanf("%d",&choice1);

    } while(choice1<0 || choice1>8);

    return choice1;
}

/** ---------- SUBMENU 2 ---------- */

int submenu2(){

    int choice2;

    do{
        printf("\n\n______________________________________________________________________________________________________________\n");
        printf("\n-                                             Gerir os requisitantes                                         -");
        printf("\n______________________________________________________________________________________________________________");
        printf("\n-                                                                                                            -");
        printf("\n- [1]  Inclusão de novos requisitantes                                                                      -");
        printf("\n-                                                                                                            -");
        printf("\n- [2]  Verificar se um requisitante existe na lista, dando o seu nome                                        -");
        printf("\n-                                                                                                            -");
        printf("\n- [3]  Listar todos os clientes, com uma ordenação à escolha do utilizador                                -");
        printf("\n-                                                                                                            -");
        printf("\n- [4]  Determinar a idade máxima de todos os requisitantes                                                  -");
        printf("\n-                                                                                                            -");
        printf("\n- [5]  Determinar a média das idades de todos os requisitantes                                              -");
        printf("\n-                                                                                                            -");
        printf("\n- [6]  Contar o número de pessoas cuja idade é superior a um dado valor                                    -");
        printf("\n-                                                                                                            -");
        printf("\n- [7]  Determinar qual a idade com mais requisitantes                                                        -");
        printf("\n-                                                                                                            -");
        printf("\n- [8]  Mostrar as requisições de um dado requisitante                                                      -");
        printf("\n-                                                                                                            -");
        printf("\n- [9]  Devolver uma lista das pessoas que nunca requisitaram nada                                            -");
        printf("\n-                                                                                                            -");
        printf("\n- [10] Listar os requisitantes que no momento têm livros requisitados                                       -");
        printf("\n-                                                                                                            -");
        printf("\n- [11] Determinar qual o sobrenome mais usado pelos requisitantes                                            -");
        printf("\n-                                                                                                            -");
        printf("\n- [12] Determinar o número de pessoas de um dado Distrito, cujo nome contém um determinado apelido         -");
        printf("\n-                                                                                                            -");
        printf("\n- [13] Listar requisitantes que nasceram (ou cujo aniversário num determinado amo é) no Domingo            -");
        printf("\n-                                                                                                            -");
        printf("\n- [14] Listar requisitantes cujo aniversário, num determinado ano, é na quaresma                           -");
        printf("\n-                                                                                                            -");
        printf("\n______________________________________________________________________________________________________________\n");
        printf("\n- [0]  Voltar para o menu principal                                                                          -");
        printf("\n______________________________________________________________________________________________________________\n");

        printf("\n\n>> Escolha uma opção: ");
        choice2 = 0;
        scanf("%d",&choice2);

    } while(choice2<0 || choice2>15);

    return choice2;
}

/** ---------- SUBMENU 3 ---------- */

int submenu3(){

    int choice3;

    do{
        printf("\n\n______________________________________________________________________________________________________________\n");
        printf("\n-                                           Gerir as requisições                                           -");
        printf("\n______________________________________________________________________________________________________________");
    printf("\n-                                                                                                            -");
        printf("\n- [1]  Efetuar uma requisição de um livro por parte de um requisitante;                                    -");
        printf("\n-                                                                                                            -");
        printf("\n- [2]  Devolver um livro que anteriormente estava requisitado;                                               -");
        printf("\n-                                                                                                            -");
        printf("\n- [3]  Listar os livros atualmente requisitados (organizados por área);                                     -");
        printf("\n-                                                                                                            -");
        printf("\n______________________________________________________________________________________________________________\n");
        printf("\n- [0]  Voltar para o menu principal                                                                          -");
        printf("\n______________________________________________________________________________________________________________\n");

        printf("\n\n>> Escolha uma opção: ");
        choice3 = 0;
        scanf("%d",&choice3);

    } while(choice3<0 || choice3>4);

    return choice3;
}

/** ---------- FUNÇÃO SUBMENU 1 ---------- */

int funcaosubmenu1(HASHING *hashingLiv)
{
    int choice1 = 0;

    do
    {
        choice1 = submenu1();

        switch(choice1)
        {

            case 1:
            {
                NODO *nodoLivro = criarNodo();
                nodoLivro->info = criarLiv();
                preencherLivro((LIVRO *)nodoLivro->info);
                inserirLivro(hashingLiv, nodoLivro);
                printf("\n\n>> Livro registado com sucesso\n");
                pressioneQualquerTecla();
                break;
            }

            case 2:
            {
                mostrarArea(hashingLiv);
                pressioneQualquerTecla();
                break;
            }

            case 3:
            {
                NODO_HASHING *area = areaComMaisLivros(hashingLiv);

                if(area)
                    printf("\n>> Area com mais livros: %s (%d livros)\n", area->nome, area->lista->nel);

                pressioneQualquerTecla();
                break;
            }

            case 4:
            {
                LIVRO *liv = existeLiv(hashingLiv);

                if(liv)
                    mostrarLivros(liv);

                else
                    printf("\n>> Não foi encontrado nenhum livro\n");

                pressioneQualquerTecla();
                break;
            }

            case 5:
            {
                LivMaisRecentes(hashingLiv);
                pressioneQualquerTecla();
                break;
            }

            case 6:
            {
                LIVRO *liv = livMaisRequisitado(hashingLiv);

                if(liv)
                {
                    printf("\n");
                    mostrarLivros(liv);
                }else
                    printf("\nNão existe livros com requisições.");


                pressioneQualquerTecla();
                break;
            }

            case 7:
            {
                NODO_HASHING *area = areaMaisRequisitada(hashingLiv);

                if(area)
                    printf("\n>> Area com mais requisições: %s", area->nome);
                else
                    printf("\nNão existe areas com livros com requisições.");

                pressioneQualquerTecla();
                break;
            }

            case 0:
                return;

            default:
            {
                printf("\n>> Introduza um número válido\n");
                break;
            }
        }

    } while (choice1 !=0);
}

/** ---------- FUNÇÃO SUBMENU 2 ---------- */

int funcaosubmenu2(HASHING *hashingDist, int *ultimoId)
{
    int choice2 = 0;

    do
    {
        choice2 = submenu2();

        switch(choice2)
        {

            case 1:
            {
                NODO *nodoReq = criarNodo();
                nodoReq->info = criarReq();
                int idUtilizado = preencherReq((REQUISITANTE *)nodoReq->info, ultimoId);
                ultimoId = idUtilizado;
                inserirReq(hashingDist, nodoReq);
                printf("\n\n>> Requisitante registado com sucesso\n");
                pressioneQualquerTecla();
                break;
            }

            case 2:
            {
                REQUISITANTE *req = existeReq(hashingDist);

                if(req)
                    mostrarReq(req);
                else
                    printf("\n>> O requisitante que procura não foi encontrado\n");

                pressioneQualquerTecla();
                break;
            }

            case 3:
            {
                int escolha;

                do{
                    /* Pedimos ao utilizador para escolher o tipo de ordenação que deseja */

                    printf("\n\n__________________________________________________\n\n");
                    printf("-             Escolha uma ordenação            -");
                    printf("\n__________________________________________________");
                    printf("\n-                                                -");
                    printf("\n- [1] Ordem alfabética do nome                  -");
                    printf("\n-                                                -");
                    printf("\n- [2] Ordem do campo ID de freguesia             -");
                    printf("\n-                                                -");
                    printf("\n- [3] Ordem alfabética do apelido               -");
                    printf("\n-                                                -");
                    printf("\n__________________________________________________\n");

                    printf("\n\n>> Escolha: ");
                    scanf("%d",&escolha);

                }while(escolha < 1 || escolha > 3);

                ordenarListaRequisitantes(hashingDist, escolha);
                pressioneQualquerTecla();
                break;
            }

            case 4:
            {
                REQUISITANTE *req = idadeMax(hashingDist);

                if(req)
                    printf("\n>> Idade máxima de todos os requisitantes: %d anos", calcularIdade(req));

                pressioneQualquerTecla();
                break;
            }

            case 5:
            {
                int idadeMed = idadeMedia(hashingDist);

                if(idadeMed)
                    printf("\n>> Idade média de todos os requisitantes: %d anos", idadeMed);

                pressioneQualquerTecla();
                break;
            }

            case 6:
            {
                printf("\n>> Total de requisitantes: %d", idadeSup(hashingDist));
                pressioneQualquerTecla();
                break;
            }

            case 7:
            {
                IdadeComMaisResquesitantes(hashingDist);
                pressioneQualquerTecla();
                break;
            }

            case 8:
            {
                REQUISITANTE *req = existeReq(hashingDist);

                if(req)
                    mostrarRequisicoesDoRequisitante(req);

                else
                    printf("\n>> Não foi encontrado nenhum requisitante\n");

                pressioneQualquerTecla();
                break;
            }

            case 9:
            {
                listaReqSemRequisicoes(hashingDist);
                pressioneQualquerTecla();
                break;
            }

            case 10:
            {

                listarReqComRequisicaoAtiva(hashingDist);
                pressioneQualquerTecla();
                break;
            }

            case 11:
            {
                SOBRENOME *sobreN = determinarSobrenomeMaisUsado(hashingDist);

                if(sobreN)
                    printf("\n>> Sobrenome mais usado: %s (x %d)", sobreN->sobrenome, sobreN->nel);

                pressioneQualquerTecla();
                break;
            }

            case 12:
            {
                int existe = existeReqDistNome(hashingDist);
                printf("\n>> Total de requisitantes: %d\n", existe);
                pressioneQualquerTecla();
                break;
            }

            case 13:
            {
                break;
            }

            case 14:
            {
                break;
            }

            case 0:
                return;

            default:
            {
                printf("\n>> Introduza um número válido\n");
                break;
            }
        }

    } while (choice2 !=0);
}

/** ---------- FUNÇÃO SUBMENU 3 ---------- */

int funcaosubmenu3(HASHING *hashingDist, HASHING *hashingLiv)
{
    int choice3 = 0;

    do
    {
        choice3 = submenu3();

        switch(choice3)
        {

            case 1:
            {
                LIVRO *livro;
                REQUISITANTE *req;

                req = existeReq(hashingDist);

                if(req) /* Encontrou o requisitante */
                {
                    livro = existeLiv(hashingLiv);

                    if(livro) /* Encontrou o livro */
                        CriarEpreencherRequisicao(livro, req);

                    else /* O livro não foi encontrado */
                    {
                        printf("\n>> O livro não foi encontrado, não é possivel realizar uma requisição\n");
                        pressioneQualquerTecla();
                        return;
                    }
                }

                else /* O requisitante não foi encontrado */
                {
                    printf("\n>> O requisitante não foi encontrado, não é possivel realizar uma requisição\n");
                    pressioneQualquerTecla();
                    return;
                }
                pressioneQualquerTecla();
                break;
            }

            case 2:
            {
                LIVRO *liv = existeLiv(hashingLiv);

                if(liv) /* A devolução pode-se realizar, porque o livro existe */
                    devolverLivroRequisitado(liv, hashingDist);

                else
                    printf("\n>> Impossivel devolver o livro\n");

                pressioneQualquerTecla();
                break;
            }

            case 3:
            {
                ListarLivRequisitados(hashingLiv);
                pressioneQualquerTecla();
                break;
            }

            case 0:
                return;

            default:
            {
                printf("\n>> Introduza um número válido\n");
                break;
            }
        }

    } while (choice3 !=0);
}

#endif
