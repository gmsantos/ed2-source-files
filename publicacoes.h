#ifndef FUNCTIONS_PUBLICACOES_INCLUDED
#define FUNCTIONS_PUBLICACOES_INCLUDED

struct publicacao
{
    char titulo[90];
    int ano;
    char editora[50];
    struct publicacao *proximo;
};

#endif
