#ifndef FUNCTIONS_PESQUISADORES_INCLUDED
#define FUNCTIONS_PESQUISADORES_INCLUDED

#include "pesquisadores.h"

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

Arvore* busca(Arvore* node, char nome[]);
Arvore* inserir(Arvore* node, char nome[], char email[], char instituicao[]);

void exibirPesquisador(Arvore *pesquisador);

//void altera(Arvore **raiz, char nome[], char email[], char instituicao[]);
void altera(Arvore **raiz, char nome[]);
void excluir(Arvore **raiz, char nome[]);
void ordem(Arvore *raiz);
Arvore **menor_dir(Arvore *raiz);
Arvore **maior_esq(Arvore *raiz);

#endif
