#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *LerString()
{
    char input[1024];

    scanf("%s", input);
    char *texto = (char *)malloc((strlen(input)+1) * sizeof(char));
    strcpy(texto, input);

    return texto;
}

int LerInteiro()
{
    char input[9];

    bool error;
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

    return atoi(input);
}

#endif // INPUT_H_INCLUDED
