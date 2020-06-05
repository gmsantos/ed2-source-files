
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pesquisadores.h"

Arvore *criar(char nome[], char email[], char instituicao[])
{
    Arvore *temp = (Arvore *)malloc(sizeof(Arvore));
    strcpy(temp->nome, nome);
    strcpy(temp->email, email);
    strcpy(temp->instituicao, instituicao);

    temp->esq = NULL;
    temp->dir = NULL;

    return temp;
}

Arvore *busca(Arvore *node, char nome[])
{
    if (node == NULL)
    {
        printf("\n\nPesquisador não foi encontrado.");

        return node;
    }

    if (strcmp(node->nome, nome) == 0)
    {
        printf("\nPesquisador encontrado:\n");
        exibirPesquisador(node);

        return node;
    }

    if (strcasecmp(node->nome, nome) > 0)
    {
        return busca(node->esq, nome);
    }

    if (strcasecmp(node->nome, nome) < 0)
    {
        return busca(node->dir, nome);
    }
}

Arvore *inserir(Arvore *node, char nome[], char email[], char instituicao[])
{
    if (node == NULL)
    {
        return criar(nome, email, instituicao);
    }

    if (strcasecmp(node->nome, nome) > 0)
    {
        node->esq = inserir(node->esq, nome, email, instituicao);
    }
    else if (strcasecmp(node->nome, nome) < 0)
    {
        node->dir = inserir(node->dir, nome, email, instituicao);
    }

    return node;
}

void exibirPesquisador(Arvore *pesquisador)
{
    printf("\nNome: %s", pesquisador->nome);
    printf("\nEmail: %s", pesquisador->email);
    printf("\nInstituição: %s", pesquisador->instituicao);
    //printf("\nPublicações: %s", pesquisador->publicoes);
}

void altera(Arvore **raiz, char *nome)
{
    if ((*raiz) != NULL)
    {
        if (strcasecmp((*raiz)->nome, nome) > 0)
        {
            altera(&(*raiz)->esq, nome);
        }
        else
        {
            if (strcasecmp((*raiz)->nome, nome) < 0)
            {
                altera(&(*raiz)->dir, nome);
            }
            else
            {
                if (strcmp((*raiz)->nome, nome) == 0)
                {
                    char email[60];
                    char instituicao[50];
                    char publicoes[100];
                    printf("REGISTRO ENCONTRADO!!\n");
                    printf("\n\nPesquisador: %s", (*raiz)->nome);
                    printf("\nNovo E-Mail: ");
                    scanf("%s", email);
                    printf("\nNova Instituição: ");
                    scanf("%s", instituicao);
                    printf("\nNovas Publicações: ");
                    scanf("%s", publicoes);

                    strcpy((*raiz)->email, email);
                    strcpy((*raiz)->instituicao, instituicao);
                    strcpy((*raiz)->publicoes, publicoes);

                    printf("| Dados alterados!! |\n");
                    getchar();
                }
            }
        }
    }
    else
    {
        printf("| nome não encontrado!! |\n");
        getchar();
    }
}

void excluir(Arvore **raiz, char nome[])
{
    Arvore **aux2, *aux3;
    if (*raiz != NULL)
    {
        if (strcasecmp((*raiz)->nome, nome) == 0)
        {
            if ((*raiz)->esq == (*raiz)->dir)
            {
                free(*raiz);
                *raiz = NULL;
            }
            else
            {
                if ((*raiz)->esq != NULL)
                {
                    aux2 = maior_esq(*raiz);
                    aux3 = *aux2;
                    (*aux2) = (*aux2)->esq;
                }
                else
                {
                    aux2 = menor_dir(*raiz);
                    aux3 = *aux2;
                    (*aux2) = (*aux2)->dir;
                }
                strcpy((*raiz)->nome, aux3->nome);
                free(aux3);
                aux3 = NULL;
            }
        }
        else
        {
            if (strcasecmp(nome, (*raiz)->nome) < 0)
            {
                excluir(&(*raiz)->esq, nome);
            }
            else
            {
                excluir(&(*raiz)->dir, nome);
            }
        }
    }
    else
    {
        printf("\n\nPesquisador não encontrado!");
        getchar();
    }
}

void ordem(Arvore *raiz)
{
    if (raiz != NULL)
    {
        ordem(raiz->esq);
        exibirPesquisador(raiz);
        printf("\n");
        ordem(raiz->dir);
    }
}

Arvore **maior_esq(Arvore *raiz)
{
    Arvore **aux = &(raiz);
    if ((*aux)->esq != NULL)
    {
        aux = &(*aux)->esq;
        while ((*aux)->dir != NULL)
        {
            aux = &(*aux)->dir;
        }
    }
    return aux;
}

Arvore **menor_dir(Arvore *raiz)
{
    Arvore **aux = &(raiz);
    if ((*aux)->dir != NULL)
    {
        aux = &(*aux)->dir;
        while ((*aux)->esq != NULL)
        {
            aux = &(*aux)->esq;
        }
    }
    return aux;
}
