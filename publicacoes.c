#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "publicacoes.h"

Lista *novaPubicacao(char titulo[], int ano, char editora[], Lista *anterior)
{
    Lista *novo = malloc(sizeof(Lista));

    strcpy(novo->titulo, titulo);
    novo->ano = ano;
    strcpy(novo->editora, editora);
    novo->proximo = NULL;

    if (anterior != NULL)
    {
        anterior->proximo = novo;
    }

    return novo;
}

void exibirPublicacoes(Lista *publicacoes)
{
    while (publicacoes != NULL)
    {
        printf(
            "\n - %s, %d - %s",
            publicacoes->titulo,
            publicacoes->ano,
            publicacoes->editora);

        publicacoes = publicacoes->proximo;
    }
}
