#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pesquisadores.h"

struct pesquisador *criar(char nome[], char email[], char instituicao[], Lista *publicacoes);
Arvore *menorNode(Arvore *node);
void exibirPesquisador(struct pesquisador *pesquisador);

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

<<<<<<< HEAD
Arvore *inserir(Arvore *node, char nome[], char email[], char instituicao[], Lista *publicacoes)
=======
Arvore *inserir(Arvore *node, char nome[], char email[], char instituicao[])
>>>>>>> format code
{
    if (node == NULL)
    {
        return criar(nome, email, instituicao, publicacoes);
    }

    if (strcasecmp(nome, node->nome) < 0)
    {
        node->esq = inserir(node->esq, nome, email, instituicao, publicacoes);

        return node;
    }

    if (strcasecmp(nome, node->nome) > 0)
    {
        node->dir = inserir(node->dir, nome, email, instituicao, publicacoes);

        return node;
    }

    printf("\n > Esse pesquisador já existe na rede. Nenhuma alteração foi efetuada.");

    return node;
}

Arvore *excluir(Arvore *node, char nome[])
{
    Arvore *tempNode = NULL;

    if (node == NULL) // definição de parada da recursão
    {
        return node;
    }

    if (strcasecmp(nome, node->nome) < 0) // Verifica se o nome é menor que o nó atual e procura a esquerda da árvore
    {
        node->esq = excluir(node->esq, nome);

        return node;
    }

    if (strcasecmp(nome, node->nome) > 0) // Verifica se o nome é maior que o nó atual e procura a direita da árvore
    {
        node->dir = excluir(node->dir, nome);

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

    // Nó tem dois filhos: subsitue pelo proximo nó na ordem (menor nó a direita da árvore)
    tempNode = menorNode(node->dir);

    // Substitui os valores do node removido pelo menor nó
    strcpy(node->nome, tempNode->nome);
    strcpy(node->email, tempNode->email);
    strcpy(node->instituicao, tempNode->instituicao);
    node->publicacoes = tempNode->publicacoes;

    // Remove o proximo nó na ordem (que está duplicado)
    node->dir = excluir(node->dir, tempNode->nome);

    return node;
}

void alterarPesquisador(struct pesquisador *pesquisador, char email[], char instituicao[])
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

<<<<<<< HEAD
struct pesquisador *criar(char nome[], char email[], char instituicao[], Lista *publicacoes)
=======
struct pesquisador *criar(char nome[], char email[], char instituicao[])
>>>>>>> format code
{
    Arvore *temp = malloc(sizeof(Arvore));
    strcpy(temp->nome, nome);
    strcpy(temp->email, email);
    strcpy(temp->instituicao, instituicao);
    temp->publicacoes = publicacoes;

    temp->esq = NULL;
    temp->dir = NULL;

    return temp;
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

void exibirPesquisador(struct pesquisador *pesquisador)
{
    printf("\nNome: %s", pesquisador->nome);
    printf("\nEmail: %s", pesquisador->email);
    printf("\nInstituição: %s", pesquisador->instituicao);
    if (pesquisador->publicacoes != NULL)
    {
        printf("\nLista de Publicações:");
        exibirPublicacoes(pesquisador->publicacoes);
    }
    printf("\n");
}

Arvore *menorNode(Arvore *node)
{
    Arvore *nodeAtual = node;

    // Procura o nó mais a esquerda o possível
    while (nodeAtual && nodeAtual->esq != NULL)
    {
        nodeAtual = nodeAtual->esq;
    }

    return nodeAtual;
}
