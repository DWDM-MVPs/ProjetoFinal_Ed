
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------------
int LerInteiro(const char *msg)
{
    printf("[%s] ", msg);
    int X;
    scanf("%d", &X);
    return X;
}
//--------------------------------
double LerDouble(const char *msg)
{
    printf("[%s] ", msg);
    double X;
    scanf("%f", &X);
    return X;
}
//--------------------------------
char *LerString(const char *msg)
{
    printf("[%s] ", msg);
    char X[200];
    scanf("%s", X);
    char *Y = (char *)malloc((strlen(X)+1) * sizeof(char));
    strcpy(Y, X);
    return Y;
}
//--------------------------------
char *LerFrase(const char *msg, int TAM_MAXIMO)
{
    printf("[%s] ", msg);
    char *X = (char *)malloc(TAM_MAXIMO * sizeof(char));
    //scanf("%s", X);
    return NULL;
}
