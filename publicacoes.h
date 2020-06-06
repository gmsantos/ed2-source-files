#ifndef FUNCTIONS_PUBLICACOES_INCLUDED
#define FUNCTIONS_PUBLICACOES_INCLUDED

struct publicacao
{
    char titulo[90];
    int ano;
    char editora[50];
    struct publicacao *proximo;
};

typedef struct publicacao Lista;

Lista *novaPublicacao(char titulo[], int ano, char editora[], Lista *anterior);
void exibirPublicacoes(Lista *publicacoes);

#endif
