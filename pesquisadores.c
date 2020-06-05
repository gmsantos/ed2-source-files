
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pesquisadores.h"

Arvore* criar(char nome[], char email[], char instituicao[])
{
    Arvore *temp = (Arvore *)malloc(sizeof(Arvore));
    strcpy(temp->nome, nome);
    strcpy(temp->email, email);
    strcpy(temp->instituicao, instituicao);

    temp->esq = NULL;
    temp->dir = NULL;

    return temp;
}

Arvore* busca(Arvore *node, char nome[])
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

Arvore* inserir(Arvore *node, char nome[], char email[], char instituicao[])
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

Arvore* excluir(Arvore *node, char nome[])
{
    Arvore *tempNode;

    if (node == NULL) // definição de parada da recursão
    { 
        return node;
    }

    if (strcasecmp(nome, node->nome) < 0) // Verifica se o nome é menor que o nó atual e procura a esquerda da árvore
    {
        excluir(node->esq, nome);
        return node;
    }

    if (strcasecmp(nome, node->nome) > 0) // Verifica se o nome é maior que o nó atual e procura a direita da árvore
    {
        excluir(node->dir, nome);
        return node;
    }

    // Se não é maior, menor ou nulo, então encontramos o nó a ser excluído

    if (node->esq == NULL && node->dir == NULL) // Esse nó é folha? Se sim, simplesmente remove o nó
    {
        free(node);
        node = NULL;

        return node;
    }

    if (node->esq == NULL || node->dir == NULL) // Se o nó só tem um filho, substitue a posição do filho naquele nó
    {
        if (node->esq == NULL)
        {
            tempNode = node->dir;
        }
        else
        {
            tempNode = node->esq;
        }

        free(node);
        node = NULL;

        return tempNode;
    }


/*
        if (node->esq != NULL) // 
        {
            aux2 = maior_esq(node);
            aux3 = aux2;
            aux2 = aux2->esq;
        }
        else
        {
            aux2 = menor_dir(node);
            aux3 = aux2;
            aux2 = aux2->dir;
        }
        strcpy(node->nome, aux3->nome);
        free(aux3);
        aux3 = NULL;

        return node;
*/

}


void alterarPesquisador(Arvore *pesquisador, char email[], char instituicao[])
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

void listarEmOrdem(Arvore *raiz)
{
    if (raiz != NULL)
    {
        listarEmOrdem(raiz->esq);
        exibirPesquisador(raiz);
        listarEmOrdem(raiz->dir);
    }
}

void exibirPesquisador(Arvore *pesquisador)
{
    printf("\nNome: %s", pesquisador->nome);
    printf("\nEmail: %s", pesquisador->email);
    printf("\nInstituição: %s", pesquisador->instituicao);
    //printf("\nPublicações: %s", pesquisador->publicoes);
    printf("\n");
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
