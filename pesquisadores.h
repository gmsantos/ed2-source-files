#ifndef FUNCTIONS_PESQUISADORES_INCLUDED
#define FUNCTIONS_PESQUISADORES_INCLUDED

#include "publicacoes.h"

struct pesquisador
{
    char nome[90];
    char email[60];
    char instituicao[50];
    char publicoes[100];
    //struct publicacao *publicacoes;
    struct pesquisador *esq, *dir;
};

typedef struct pesquisador Arvore;

Arvore* busca(Arvore *node, char nome[]);
Arvore* inserir(Arvore *node, char nome[], char email[], char instituicao[]);
void alterarPesquisador(struct pesquisador *pesquisador, char email[], char instituicao[]);
Arvore* excluir(Arvore *node, char nome[]);
void listarEmOrdem(Arvore *node);

#endif
