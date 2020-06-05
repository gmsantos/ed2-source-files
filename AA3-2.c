/*
AA3.2 - Atividade em grupo: Trabalho Prático - Parte 1
Elaboração de um aplicativo que disponibiliza as funcionalidades de uma rede de colaboração de pesquisadores. Os dados dos
pesquisadores da rede devem ser armazenados em memória utilizando uma árvore binária de busca (ABB)

Integrantes:
Gabriel Machado Santos             RA: 581062
Thiago Andre de Oliveira Benedito  RA: 579947
Vanessa Paula Alves de Moura       RA: 580643
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "pesquisadores.c"
#include "publicacoes.c"

void menu(int *acao);
void opcao(char op[]);

void ler_nome(char nome[]);
void ler_email(char email[]);
void ler_instituicao(char instituicao[]);
void ler_public(char public[]);

void menu(int *acao)
{
    printf("\nCADASTRO DE PESQUISADORES\n");
    printf("1 - Inserção de novos pesquisadores na rede\n");
    printf("2 - Consulta de pesquisador da rede\n");
    printf("3 - Alteração dos dados de pesquisador da rede\n");
    printf("4 - Remoção de pesquisadores da rede\n");
    printf("5 - Listar os pesquisadores da rede em ordem\n");
    printf("6 - Sair do programa\n");

    printf("\nDigite uma opção: ");
    scanf("%d", acao);
    getchar();
}

void opcao(char op[])
{
    printf("\nDeseja continuar sim: s ou não: n\n");
    scanf("%s", op);
    getchar();
}

int main()
{
    int acao;
    char nome[90], email[60], instituicao[50];

    printf("Inserindo pesquisadores iniciais na rede...\n");
    Arvore *raiz = NULL;
    raiz = inserir(raiz, "Marcos Teixeira", "teixeira@gmail.com", "UFSCar");
    inserir(raiz, "Flávio Mendes", "fm@ufrj.br", "UFRJ");
    inserir(raiz, "Odair Siqueira", "odair@din.uem.br", "UEM");

    while (acao != 6)
    {
        menu(&acao);
        switch (acao)
        {
        case 1:
            printf("\nINSERIR UM NOVO PESQUISADOR");
            ler_nome(nome);
            ler_email(email);
            ler_instituicao(instituicao);
            inserir(raiz, nome, email, instituicao);

            break;

        case 2:
            printf("\nCONSULTAR UM PESQUISADOR");
            ler_nome(nome);
            busca(raiz, nome);
            break;

        case 3:
            printf("\nALTERAR UM PEQUISADOR");
            ler_nome(nome);
            Arvore *pesquisador = busca(raiz, nome);

            if (pesquisador == NULL) // Verificar se o pesquisador está na rede
            {
                break; // Encerra a ação caso aquele pesquisador não esteja na rede
            }

            printf("\nInsira os novos dados para esse pesquisador");
            ler_email(email);
            ler_instituicao(instituicao);
            alterarPesquisador(pesquisador, email, instituicao);

            break;

        case 4:
            printf("\nREMOVER PESQUISADOR");
            ler_nome(nome);
            raiz = excluir(raiz, nome);
            break;

        case 5:
            printf("\nLISTAR OS PESQUISADORES DA REDE EM ORDEM");
            listarEmOrdem(raiz);
            break;
        }
    }
}

void ler_nome(char nome[])
{
    printf("\nDigite o nome: ");
    fgets(nome, 90, stdin);
    nome[strcspn(nome, "\r\n")] = 0;
}

void ler_email(char email[])
{
    printf("Digite o email: ");
    fgets(email, 60, stdin);
    email[strcspn(email, "\r\n")] = 0;
}

void ler_instituicao(char instituicao[])
{
    printf("Digite a instituição: ");
    fgets(instituicao, 50, stdin);
    instituicao[strcspn(instituicao, "\r\n")] = 0;
}

void ler_publicacoes(char publicacoes[])
{
    printf("Digite as publicações: ");
    fgets(publicacoes, 100, stdin);
    publicacoes[strcspn(publicacoes, "\r\n")] = 0;
}
