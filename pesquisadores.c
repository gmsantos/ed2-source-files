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

Arvore *rebalancear(Arvore *node, char nome[]);
Arvore *rotacaoEsq(Arvore *node);
Arvore *rotacaoDir(Arvore *node);

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
        printf("\n > Esse pesquisador j� existe na rede. Nenhuma altera��o foi efetuada.");

        return node;
    }

    // atualiza a altura do n�
    node->altura = maior(altura(node->esq), altura(node->dir)) + 1;

    // determina o fator de balanceamento do n�
    int balance = fatorBalanceamento(node);

    // Rebalanceia a �rvore caso necess�rio
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

    // Retorna sem altera��es caso �rvore esteja balanceada
    return node;
}

Arvore *excluir(Arvore *node, char nome[])
{
    if (node == NULL) // defini��o de parada da recurs�o
    {
        return node;
    }

    if (stricmp(nome, node->nome) < 0) // Verifica se o nome � menor que o n� atual e procura a esquerda da �rvore
    {
        node->esq = excluir(node->esq, nome);
    }
    else if (stricmp(nome, node->nome) > 0) // Verifica se o nome � maior que o n� atual e procura a direita da �rvore
    {
        node->dir = excluir(node->dir, nome);
    }
    else // Se n�o � maior, menor ou nulo, ent�o encontramos o n� a ser exclu�do
    {
        if (node->esq == NULL && node->dir == NULL) // Esse n� � folha? Se sim, simplesmente remove o n�
        {
            free(node);
            node = NULL;
        }
        else if (node->esq == NULL || node->dir == NULL) // Se o n� s� tem um filho, substitue a posi��o do filho naquele n�
        {
            Arvore *tempNode = node->esq ? node->esq : node->dir;
            *node = *tempNode;

            free(tempNode);
        }
        else
        {
            // N� tem dois filhos: subsitue pelo proximo n� na ordem (menor n� a direita da �rvore)
            Arvore *tempNode = menorNode(node->dir);

            // Substitui os valores do node removido pelo menor n�
            strcpy(node->nome, tempNode->nome);
            strcpy(node->email, tempNode->email);
            strcpy(node->instituicao, tempNode->instituicao);
            node->publicacoes = tempNode->publicacoes;

            // Remove o proximo n� na ordem (que est� duplicado)
            node->dir = excluir(node->dir, tempNode->nome);
        }
    }

    if (node == NULL) // caso o �ltimo elemento da arvore tenha sido removido
    {
        return node;
    }

    // atualiza a altura do n�
    node->altura = maior(altura(node->esq), altura(node->dir)) + 1;

    // determina o fator de balanceamento do n�
    int balance = fatorBalanceamento(node);

    // Rebalanceia a �rvore caso necess�rio
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

    // faz a rota��o para a esquerda
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

    // faz a rota��o para a direita
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
