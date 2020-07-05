#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pesquisadores.h"

struct pesquisador *criar(char nome[], char email[], char instituicao[], Lista *publicacoes);
Arvore *menorNode(Arvore *node);
void exibirPesquisador(struct pesquisador *pesquisador);

// Funções para balanceamento da árvore
int altura(Arvore *node);
int maior(int x, int y);
int fatorBalanceamento(Arvore *node);

Arvore *rebalancear(Arvore *node, char nome[]);
Arvore *rotacaoEsq(Arvore *node);
Arvore *rotacaoDir(Arvore *node);

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

    if (stricmp(nome, node->nome) < 0)
    {
        return busca(node->esq, nome);
    }

    if (stricmp(nome, node->nome) > 0)
    {
        return busca(node->dir, nome);
    }

    return node;
}

Arvore *inserir(Arvore *node, char nome[], char email[], char instituicao[], Lista *publicacoes)
{
    if (node == NULL)
    {
        return criar(nome, email, instituicao, publicacoes);
    }

    if (stricmp(nome, node->nome) < 0)
    {
        node->esq = inserir(node->esq, nome, email, instituicao, publicacoes);
    }
    else if (stricmp(nome, node->nome) > 0)
    {
        node->dir = inserir(node->dir, nome, email, instituicao, publicacoes);
    }
    else
    {
        printf("\n > Esse pesquisador já existe na rede. Nenhuma alteração foi efetuada.");

        return node;
    }

    // atualiza a altura do nó
    node->altura = maior(altura(node->esq), altura(node->dir)) + 1;

    // determina o fator de balanceamento do nó
    int balance = fatorBalanceamento(node);

    // Rebalanceia a árvore caso necessário
    // Esquerda Esquerda
    if (balance > 1 && stricmp(nome, node->esq->nome) < 0)
    {
        return rotacaoDir(node);
    }

    // Direita Direita
    if (balance < -1 && stricmp(nome, node->dir->nome) > 0)
    {
        return rotacaoEsq(node);
    }

    // Esquerda Direita
    if (balance > 1 && stricmp(nome, node->esq->nome) > 0)
    {
        node->esq = rotacaoEsq(node->esq);
        return rotacaoDir(node);
    }

    // Direita Esquerda
    if (balance < -1 && stricmp(nome, node->dir->nome) < 0)
    {
        node->dir = rotacaoDir(node->dir);
        return rotacaoEsq(node);
    }

    // Retorna sem alterações caso árvore esteja balanceada
    return node;
}

Arvore *excluir(Arvore *node, char nome[])
{
    if (node == NULL) // definição de parada da recursão
    {
        return node;
    }

    if (stricmp(nome, node->nome) < 0) // Verifica se o nome é menor que o nó atual e procura a esquerda da árvore
    {
        node->esq = excluir(node->esq, nome);
    }
    else if (stricmp(nome, node->nome) > 0) // Verifica se o nome é maior que o nó atual e procura a direita da árvore
    {
        node->dir = excluir(node->dir, nome);
    }
    else // Se não é maior, menor ou nulo, então encontramos o nó a ser excluído
    {
        if (node->esq == NULL && node->dir == NULL) // Esse nó é folha? Se sim, simplesmente remove o nó
        {
            free(node);
            node = NULL;
        }
        else if (node->esq == NULL || node->dir == NULL) // Se o nó só tem um filho, substitue a posição do filho naquele nó
        {
            Arvore *tempNode = node->esq ? node->esq : node->dir;
            *node = *tempNode;

            free(tempNode);
        }
        else
        {
            // Nó tem dois filhos: subsitue pelo proximo nó na ordem (menor nó a direita da árvore)
            Arvore *tempNode = menorNode(node->dir);

            // Substitui os valores do node removido pelo menor nó
            strcpy(node->nome, tempNode->nome);
            strcpy(node->email, tempNode->email);
            strcpy(node->instituicao, tempNode->instituicao);
            node->publicacoes = tempNode->publicacoes;

            // Remove o proximo nó na ordem (que está duplicado)
            node->dir = excluir(node->dir, tempNode->nome);
        }
    }

    if (node == NULL) // caso o último elemento da arvore tenha sido removido
    {
        return node;
    }

    // atualiza a altura do nó
    node->altura = maior(altura(node->esq), altura(node->dir)) + 1;

    // determina o fator de balanceamento do nó
    int balance = fatorBalanceamento(node);

    // Rebalanceia a árvore caso necessário
    // Esquerda Esquerda
    if (balance > 1 && fatorBalanceamento(node->esq) >= 0)
    {
        return rotacaoDir(node);
    }

    // Esquerda Direita
    if (balance > 1 && fatorBalanceamento(node->esq) < 0)
    {
        node->esq = rotacaoEsq(node->esq);
        return rotacaoDir(node);
    }

    // Direita Direita
    if (balance < -1 && fatorBalanceamento(node->dir) >= 0)
    {
        return rotacaoEsq(node);
    }

    // Direita Esquerda
    if (balance < -1 && fatorBalanceamento(node->dir) < 0)
    {
        node->dir = rotacaoDir(node->dir);
        return rotacaoEsq(node);
    }

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

void listarParenteses(Arvore *raiz)
{
    printf("(");
    if (raiz != NULL)
    {
        printf("[%s]", raiz->nome);
        listarParenteses(raiz->esq);
        listarParenteses(raiz->dir);
    }
    printf(")");
}

struct pesquisador *criar(char nome[], char email[], char instituicao[], Lista *publicacoes)
{
    Arvore *temp = malloc(sizeof(Arvore));
    strcpy(temp->nome, nome);
    strcpy(temp->email, email);
    strcpy(temp->instituicao, instituicao);
    temp->publicacoes = publicacoes;
    temp->altura = 1;

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

int maior(int x, int y)
{
    return (x > y) ? x : y;
}

int fatorBalanceamento(Arvore *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return altura(node->esq) - altura(node->dir);
}

Arvore *rotacaoEsq(Arvore *x)
{
    Arvore *y = x->dir;
    Arvore *T2 = y->esq;

    // faz a rotação para a esquerda
    y->esq = x;
    x->dir = T2;

    x->altura = maior(altura(x->esq), altura(x->dir)) + 1;
    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;

    // retorna a nova raiz
    return y;
}

Arvore *rotacaoDir(Arvore *y)
{
    Arvore *x = y->esq;
    Arvore *T2 = x->dir;

    // faz a rotação para a direita
    x->dir = y;
    y->esq = T2;

    y->altura = maior(altura(y->esq), altura(y->dir)) + 1;
    x->altura = maior(altura(x->esq), altura(x->dir)) + 1;

    // retorna a nova raiz
    return x;
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
