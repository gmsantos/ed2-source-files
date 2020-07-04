#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pesquisadores.h"

struct pesquisador *criar(char nome[], char email[], char instituicao[], Lista *publicacoes);
Arvore *menorNode(Arvore *node);
void exibirPesquisador(struct pesquisador *pesquisador);

// Fun��es para balanceamento da �rvore
int altura(Arvore *node);
int maior(int x, int y);
int fatorBalanceamento(Arvore *node);

void rotacaoEsq(Arvore *root);
void rotacaoDir(Arvore *root);
void rotacaoEsqDir(Arvore *root);
void rotacaoDirEsq(Arvore *root);

Arvore *busca(Arvore *node, char nome[])
{
    if (node == NULL)
    {
        printf("\n > Pesquisador n�o foi encontrado.\n");

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

    node->altura = maior(altura(node->esq), altura(node->dir)) + 1;
    printf("\n > Esse pesquisador j� existe na rede. Nenhuma altera��o foi efetuada.");

    return node;
}

Arvore *excluir(Arvore *node, char nome[])
{
    Arvore *tempNode = NULL;

    if (node == NULL) // defini��o de parada da recurs�o
    {
        return node;
    }

    if (strcasecmp(nome, node->nome) < 0) // Verifica se o nome � menor que o n� atual e procura a esquerda da �rvore
    {
        node->esq = excluir(node->esq, nome);

        return node;
    }

    if (strcasecmp(nome, node->nome) > 0) // Verifica se o nome � maior que o n� atual e procura a direita da �rvore
    {
        node->dir = excluir(node->dir, nome);

        return node;
    }

    // Se n�o � maior, menor ou nulo, ent�o encontramos o n� a ser exclu�do

    if (node->esq == NULL && node->dir == NULL) // Esse n� � folha? Se sim, simplesmente remove o n�
    {
        free(node);
        node = NULL;

        return node;
    }

    if (node->esq == NULL || node->dir == NULL) // Se o n� s� tem um filho, substitue a posi��o do filho naquele n�
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

    // N� tem dois filhos: subsitue pelo proximo n� na ordem (menor n� a direita da �rvore)
    tempNode = menorNode(node->dir);

    // Substitui os valores do node removido pelo menor n�
    strcpy(node->nome, tempNode->nome);
    strcpy(node->email, tempNode->email);
    strcpy(node->instituicao, tempNode->instituicao);
    node->publicacoes = tempNode->publicacoes;

    // Remove o proximo n� na ordem (que est� duplicado)
    node->dir = excluir(node->dir, tempNode->nome);

    return node;
}

void alterarPesquisador(struct pesquisador *pesquisador, char email[], char instituicao[])
{
    if (pesquisador == NULL) // Essa condi��o s� � verdadeira caso tente alterar um pesquisador nulo
    {
        printf("\n > Informe um pesquisador presente na rede antes de tentar alter�-lo.");
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
    printf("\nInstitui��o: %s", pesquisador->instituicao);
    if (pesquisador->publicacoes != NULL)
    {
        printf("\nLista de Publica��es:");
        exibirPublicacoes(pesquisador->publicacoes);
    }
    printf("\n");
}

Arvore *menorNode(Arvore *node)
{
    Arvore *nodeAtual = node;

    // Procura o n� mais a esquerda o poss�vel
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
    return altura(node->esq) - altura(node->dir);
}

void rotacaoEsq(Arvore *root)
{
    Arvore *node = root->esq;
    root->esq = node->dir;
    node->dir = root;

    root->altura = maior(altura(root->esq), altura(root->dir)) + 1;
    node->altura = maior(altura(node->esq), root->altura) + 1;

    root = node;
}

void rotacaoDir(Arvore *root)
{
    Arvore *node = root->dir;
    root->dir = node->esq;
    node->esq = root;

    root->altura = maior(altura(root->esq), altura(root->dir)) + 1;
    node->altura = maior(altura(node->dir), root->altura) + 1;

    root = node;
}

void rotacaoEsqDir(Arvore *root)
{
    rotacaoDir(root->esq);
    rotacaoEsq(root);
}

void rotacaoDirEsq(Arvore *root)
{
    rotacaoEsq(root->dir);
    rotacaoDir(root);
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
