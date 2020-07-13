#ifndef _LOCALIDADES_H_
#define _LOCALIDADES_H_

struct DISTRITO
{
    int ID;
    char Nome[100];
    DISTRITO *Seguinte;
};

struct CONCELHO
{
    int ID;
    char Nome[100];
    CONCELHO *Seguinte;
};

struct FREGUESIA
{
    int ID;
    char Nome[100];
    FREGUESIA *Seguinte;
};





// LISTA DAS AREAS / CATEGORIAS
struct LISTA_LOCALIDADES
{
    DISTRITO *InicioDistritos;
    CONCELHO *InicioConcelhos;
    FREGUESIA *InicioFreguesias;
};

#endif
