
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** ---------- LER UM INTEIRO DO TECLADO ---------- */

int LerInteiro(const char *msg)
{
    printf("[%s] ", msg);
    int X;
    scanf("%d", &X);
    return X;
}

/** ---------- LER UM DOUBLE DO TECLADO ---------- */

double LerDouble(const char *msg)
{
    printf("[%s] ", msg);
    double X;
    scanf("%f", &X);
    return X;
}

/** ---------- LER UMA STRING DO TECLADO ---------- */

char *LerString(const char *msg)
{
    printf("[%s] ", msg);
    char X[200];
    scanf("%s", X);
    char *Y = (char *)malloc((strlen(X)+1) * sizeof(char));
    strcpy(Y, X);
    return Y;
}

/** ---------- LER UMA FRASE DO TECLADO ---------- */

char *LerFrase(const char *msg, int TAM_MAXIMO)
{
    printf("[%s] ", msg);
    char *X = (char *)malloc(TAM_MAXIMO * sizeof(char));
    //scanf("%s", X);
    return NULL;
}

/** ---------- CONCATENAR DOIS INTEGERS ---------- */

int concatInteger(int a, int b)
{

    char s1[20];
    char s2[20];

    // Convert both the integers to string
    sprintf(s1, "%02d", a);
    sprintf(s2, "%02d", b);

    // Concatenate both strings
    strcat(s1, s2);

    // Convert the concatenated string
    // to integer
    int c = atoi(s1);

    // return the formed integer
    return c;
}

/** ---------- SOMAR OS 8 DIGITOS DE UM DADO NUMERO ---------- */

int somarDigitos(int num)
{
    if(!num)
    {
        printf("\n>> Ocorreu um erro na leitura do número\n");
        return 0;
    }

    int i, soma = 0;

    for(i = 0; i < 9; i++)
    {
      soma +=  num % 10;
      num = num / 10;
    }
    return soma;
}

/** ---------- PAUSA NO PROGRAMA QUE PEDE AO UTILIZADOR PARA PRESSIONAR UMA TECLA ---------- */

void pressioneQualquerTecla(){

    printf("\n\n______________________________________________\n");
    printf("\n-  Pressione qualquer tecla para continuar   -");
    printf("\n______________________________________________\n");

    while(!kbhit())
    {

    }
    getch();

    return;
}

