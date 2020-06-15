#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structs.h"

char *LerString()
{
    char input[1024];

    scanf("%s", input);
    char *texto = (char *)malloc((strlen(input)+1) * sizeof(char));
    strcpy(texto, input);

    return texto;
}

int LerInteiro(int min, int max)
{
    char input[9];

    bool error;
    while (true)
    {
        do
        {
            error = false;

            scanf("%s", input);

            int i;
            for (i=0; i<strlen(input); i++)
            {
                if (!isdigit(input[i]))
                {
                    printf("Dados incorretos inseridos. Tente novamente: ");

                    error = true;
                    break;
                }
            }
        } while (error);

        int num = atoi(input);

        if (min != NULL && num >= min ||  max != NULL && num <= max)
        {
            return atoi(input);
        }
    }
}

bool AnoBissexto(int ano)
{
     return ano%4==0 && ano%100!=0 || ano%400==0;
}

bool DataValida(Data *data)
{
    // Verificar valores máximos para dias e mêses
    if (data->Dia < 1 || data->Dia > 31)
    {
        return false;
    }
    if (data->Mes < 1 || data->Mes > 12)
    {
        return false;
    }
    // Ano Bissexto (Fevereiro)
    if (data->Mes == 2)
    {
        if (AnoBissexto(data->Ano))
        {
            return (data->Dia <= 29);
        }
        else
        {
            return (data->Dia <= 28);
        }
    }
    // Mêses que só têm 30 dias
    if (data->Mes == 4 || data->Mes == 6 || data->Mes == 9 || data->Mes == 11)
    {
        return (data->Dia <= 30);
    }
    // Default return: true
    return true;
}

int AnoAtual()
{
   printf("\n[%s]\n", __FUNCTION__);

    time_t s = time(NULL);
    struct tm* current_time = localtime(&s);

    return current_time->tm_year + 1900;
}

#endif // FUNCOES_H_INCLUDED
