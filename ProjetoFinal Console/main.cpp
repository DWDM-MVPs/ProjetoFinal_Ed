#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

//Guarda cenas no ficheiro
int SaveInFile()
{
   char nome[50];
   int numCon, i, num;

   printf("Numero de concelhos: ");
   scanf("%d", &num);

   FILE *fptr;
   fptr = (fopen("C:\\Users\\Jak\\Desktop\\ProjetoFinal2\\test.txt", "w"));
   if(fptr == NULL)
   {
       printf("Error!");
       getch();
   }

   for(i = 0; i < num; ++i)
   {
      printf("Concelho %d\nIntroduza o nome: ", i+1);
      scanf("%s", nome);

      printf("Introduza o numero do concelho: ");
      scanf("%d", &numCon);

      fprintf(fptr,"\nNome: %s \nNumeroConcelho: %d \n", nome, numCon);
   }

   fclose(fptr);
   return 0;
}

//Abre e le as cenas no ficheiro
int LerFicheiro(){
	int c;
	FILE *file;
	file = fopen("C:\\Users\\Jak\\Desktop\\ProjetoFinal2\\test.txt", "r");
	if (file) {
    while ((c = getc(file)) != EOF)
        putchar(c);
    	fclose(file);
	}
}
char* ReadFile(char *filename)
{
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       fseek(handler, 0, SEEK_END);
       string_size = ftell(handler);
       rewind(handler);
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
       read_size = fread(buffer, sizeof(char), string_size, handler);
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           free(buffer);
           buffer = NULL;
       }
       fclose(handler);
    }

    return buffer;
}

int main()
{
	SaveInFile();
    char *string = ReadFile((char *)"C:\\Users\\Jak\\Desktop\\ProjetoFinal2\\test.txt");
    if (string)
    {
        puts(string);
        free(string);
    }
    return 0;
}

