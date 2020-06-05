
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
        printf("\n > Pesquisador não foi encontrado.\n");

        return node;
    }

    if (strcmp(nome, node->nome) == 0)
    {
        printf("\n > Pesquisador encontrado:\n");
        exibirPesquisador(node);

        return node;
    }

    if (strcasecmp(nome, node->nome) < 0)
    {
        return busca(node->esq, nome);
    }

    if (strcasecmp(nome, node->nome) > 0)
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

    if (strcasecmp(nome, node->nome) < 0)
    {
        node->esq = inserir(node->esq, nome, email, instituicao);

        return node;
    }
    
    if (strcasecmp(nome, node->nome) > 0)
    {
        node->dir = inserir(node->dir, nome, email, instituicao);

        return node;
    }

    printf("\n > Esse pesquisador já existe na rede. Nenhuma alteração foi efetuada.");

    return node;
}

void alterarPesquisador(Arvore* pesquisador, char email[], char instituicao[])
{
    if (pesquisador == NULL) // Essa condição só é verdadeira caso tente alterar um pesquisador nulo
    {
        printf("\n > Informe um pesquisador presente na rede antes de tentar alterá-lo.");
        return;
    }
    
    strcpy(pesquisador->email, email);
    strcpy(pesquisador->instituicao, instituicao);

    printf("\n > Dados alterados com sucesso!");
    exibirPesquisador(pesquisador);
}

void exibirPesquisador(Arvore *pesquisador)
{
    printf("\nNome: %s", pesquisador->nome);
    printf("\nEmail: %s", pesquisador->email);
    printf("\nInstituição: %s", pesquisador->instituicao);
    //printf("\nPublicações: %s", pesquisador->publicoes);
    printf("\n");
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

void listarEmOrdem(Arvore* raiz)
{
    if (raiz != NULL)
    {
        listarEmOrdem(raiz->esq);
        exibirPesquisador(raiz);        
        listarEmOrdem(raiz->dir);
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
