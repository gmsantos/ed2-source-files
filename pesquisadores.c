#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pesquisadores.h"

struct pesquisador *criar(char nome[], char email[], char instituicao[], Lista *publicacoes);
Arvore *menorNode(Arvore *node);
void exibirPesquisador(struct pesquisador *pesquisador);

// Funções para balanceamento da árvore
int altura(Arvore *node);
int maiorInt(int x, int y);
int fatorBalanceamento(Arvore *node);

void rotacaoEsq(Arvore *raiz);
void rotacaoDir(Arvore *raiz);
void rotacaoEsqDir(Arvore *raiz);
void rotacaoDirEsq(Arvore *raiz);

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

Arvore *inserir(Arvore *node, char nome[], char email[], char instituicao[], Lista *publicacoes)
{
    if (node == NULL)
    {
        return criar(nome, email, instituicao, publicacoes);
    }

    if (strcasecmp(nome, node->nome) < 0)
    {
        node->esq = inserir(node->esq, nome, email, instituicao, publicacoes);
        if (fatorBalanceamento(node->esq) >= 2)
        {
            if (nome < node->esq->nome)
            {
                rotacaoEsq(node);
            }
            else
            {
                rotacaoEsqDir(node);
            }
        }
        return node;
    }

    if (strcasecmp(nome, node->nome) > 0)
    {
        node->dir = inserir(node->dir, nome, email, instituicao, publicacoes);
        if (fatorBalanceamento(node->dir) >= 2)
        {
            if (node->dir->nome < nome)
            {
                rotacaoDir(node);
            }
            else
            {
                rotacaoDirEsq(node);
            }
        }

        return node;
    }

    node->altura = maiorInt(altura(node->esq), altura(node->dir)) + 1;
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

    if (strcasecmp(nome, node->nome) > 0) // Verifica se o nome é maiorInt que o nó atual e procura a direita da árvore
    {
        node->dir = excluir(node->dir, nome);

        return node;
    }

    // Se não é maiorInt, menor ou nulo, então encontramos o nó a ser excluído

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

void listarEmOrdem(Arvore *raiz)
{
    if (raiz != NULL)
    {
        listarEmOrdem(raiz->esq);
        exibirPesquisador(raiz);
        listarEmOrdem(raiz->dir);
    }
}

void listar(Arvore *raiz)
{
    if (raiz != NULL)
    {
        exibirPesquisador(raiz);
        listarEmOrdem(raiz->esq);
        listarEmOrdem(raiz->dir);
    }
}

struct pesquisador *criar(char nome[], char email[], char instituicao[], Lista *publicacoes)
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

int altura(Arvore *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return node->altura;    
}

int maiorInt(int x, int y)
{
    return (x > y) ? x : y;
}

int fatorBalanceamento(Arvore *node)
{
    return altura(node->esq) - altura(node->dir);
}

void rotacaoEsq(Arvore *raiz)
{
    Arvore *node;
    node = raiz->esq;
    raiz->esq = node->dir;
    node->dir = raiz;

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
    node->altura = maior(altura(node->esq), raiz->altura) + 1;

    raiz = node;
}

void rotacaoDir(Arvore *raiz)
{
    Arvore *node;
    node = raiz->dir;
    raiz->dir = node->esq;
    node->esq = raiz;
    raiz->altura = maior(altura(raiz->esq),
                         altura(raiz->dir)) +
                   1;

    node->altura = maior(altura(node->dir), raiz->altura) + 1;
    raiz = node;
}

void rotacaoEsqDir(Arvore *raiz)
{
    RotacaoRR(raiz->esq);
    RotacaoLL(raiz);
}

void rotacaoDirEsq(Arvore *raiz)
{
    RotacaoLL(raiz->dir);
    RotacaoRR(raiz);
}

Arvore *procuraMenor(Arvore *nodeAtual)
{
    Arvore *no1 = nodeAtual;
    Arvore *no2 = nodeAtual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

