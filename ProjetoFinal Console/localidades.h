#ifndef _LOCALIDADES_H_
#define _LOCALIDADES_H_

struct DISTRITO
{
    int ID;
    char Nome[100];
};

struct CONCELHO
{
    int ID;
    char Nome[100];
};

struct FREGUESIA
{
    int ID;
    char Nome[100];
};





// LISTA DAS AREAS / CATEGORIAS
struct LISTA_LOCALIDADES
{
    DISTRITO *InicioDistritos;
    CONCELHO *InicioConcelhos;
    FREGUESIA *InicioFreguesias;
};

#endif
