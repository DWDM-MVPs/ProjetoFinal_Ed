#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LerConcelhos()
{
    FILE *ficheiroConcelhos = fopen("dados\\concelhos.txt", "r");

    printf("cheguei");

    if (ficheiroConcelhos == NULL)
    {
        perror("Houve um problema ao abrir o ficheiro.");
    }
    else
    {
        int MAX_ITEM = 5;

        char linha[512];
        int i, parsedData;

        int id;
        char *nome;

        while (fgets(linha, sizeof(linha), ficheiroConcelhos) != NULL && i < MAX_ITEM)
        {
            parsedData = sscanf(linha, "%d\t%s", id, nome);
            if (parsedData == 3)
            {
                printf("deve ter lido");
                printf("%d", id);
            }
        }
    }
}