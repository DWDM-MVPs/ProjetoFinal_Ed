#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#include "structs.h"
#include "funcoes.h"
#include "livros.h"

// Guarda cenas no ficheiro
void GuardarNoFicheiro()
{
   char nome[50];
   int numCon, i, num;

   printf("Número de concelhos: ");
   scanf("%d", &num);

   FILE *file = (fopen("dados\\test.txt", "w"));
   if(file == NULL)
   {
       printf("Error! File not found.");
       getch();
   }

   for(i = 0; i < num; ++i)
   {
      printf("Concelho %d\nIntroduza o nome: ", i+1);
      scanf("%s", nome);

      printf("Introduza o numero do concelho: ");
      scanf("%d", &numCon);

      fprintf(file,"\nNome: %s \nNumeroConcelho: %d \n", nome, numCon);
   }

   fclose(file);
}

// Abre e lê as cenas do ficheiro
void LerFicheiro()
{
	int c;
	FILE *file = fopen("dados\\test.txt", "r");

	if (file)
    {
        while ((c = getc(file)) != EOF)

        putchar(c);
    	fclose(file);
	}
}

void Testing()
{
    Livro *l = WizardCriarLivro();

	GuardarNoFicheiro();
	LerFicheiro();
}

int main()
{
    // Imprimir chars portuguêses como 'ç', 'á', ...
    setlocale(LC_ALL, "Portuguese");

    Testing();

	return 0;
}
