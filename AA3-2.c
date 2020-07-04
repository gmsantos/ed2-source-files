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

void ler_nome(char nome[]);
void ler_email(char email[]);
void ler_instituicao(char instituicao[]);
Lista *ler_publicacoes();

void ler_titulo(char titulo[]);
void ler_ano(int *ano);
void ler_editora(char editora[]);

int main()
{
    int acao;
    char nome[90], email[60], instituicao[50];
    Lista *publicacoes;

    printf("Inserindo pesquisadores iniciais na rede...\n");
    Arvore *raiz = NULL;

    // Cria as listas de publicações
    Lista *publicacoesMarcos = novaPublicacao("Árvores e suas Aplicações", 2011, "Makron Books", NULL);
    Lista *publicacoesMarcos2 = novaPublicacao("Estruturas de Dados em Disco", 2008, "Campus", publicacoesMarcos);
    Lista *publicacoesFlavio = novaPublicacao("Aspectos Formais", 1991, "Elsevier", NULL);
    Lista *publicacoesFlavio2 = novaPublicacao("Autómatos", 1994, "ETC", publicacoesFlavio);
    Lista *publicacoesOdair = novaPublicacao("Lógica de Programação", 2002, "Elsevier", NULL);

    // Cria a raiz da Árvore
    raiz = inserir(raiz, "Marcos Teixeira", "teixeira@gmail.com", "UFSCar", publicacoesMarcos);
    inserir(raiz, "Flávio Mendes", "fm@ufrj.br", "UFRJ", publicacoesFlavio);
    inserir(raiz, "Odair Siqueira", "odair@din.uem.br", "UEM", publicacoesOdair);

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
            publicacoes = ler_publicacoes();

            if (raiz == NULL) // Caso todos os nós forem apagados, recria a raiz da arvore
            {
                raiz = inserir(raiz, nome, email, instituicao, publicacoes);
            }
            else
            {
                inserir(raiz, nome, email, instituicao, publicacoes);
            }

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

            printf("\n > Insira os novos dados para esse pesquisador\n");
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

void menu(int *acao)
{
    printf("\nCADASTRO DE PESQUISADORES\n");
    printf("1 - Inserir\n");
    printf("2 - Pesquisar\n");
    printf("3 - Alterar \n");
    printf("4 - Excluir\n");
    printf("5 - Listar\n");
    printf("6 - Sair do programa\n");

    printf("\nDigite uma opção: ");
    scanf("%d", acao);
    getchar();
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
    printf("Digite a instituiçãoo: ");
    fgets(instituicao, 50, stdin);
    instituicao[strcspn(instituicao, "\r\n")] = 0;
}

void ler_titulo(char titulo[])
{
    printf("\nDigite o título: ");
    fgets(titulo, 90, stdin);
    titulo[strcspn(titulo, "\r\n")] = 0;
}

void ler_ano(int *ano)
{
    printf("Digite o ano: ");
    scanf("%d", ano);
    getchar();
}

void ler_editora(char editora[])
{
    printf("Digite a editora: ");
    fgets(editora, 50, stdin);
    editora[strcspn(editora, "\r\n")] = 0;
}

Lista *ler_publicacoes()
{
    char titulo[90], editora[50], confirma[1];
    int ano;
    Lista *lista = NULL;
    Lista *anterior = NULL;

    // Loop para inserir as publicações do pesquisador
    // aceita os inputs de S ou N para inserir mais publicações ou prosseguir
    do
    {
        printf("\nDeseja incluir uma nova publicação para esse pesquisador? ([S]Sim/[N]Não) : ");
        scanf("%s", confirma);
        getchar();

        if (strcasecmp(confirma, "s") == 0) // Lê os dados da publicação
        {
            ler_titulo(titulo);
            ler_ano(&ano);
            ler_editora(editora);

            if (lista == NULL) // inicializa o primeiro elemento da lista
            {
                lista = novaPublicacao(titulo, ano, editora, NULL);

                // mantêm a referencia anterior para definir o pointer da proxima publicação
                anterior = lista;
            }
            else
            {
                Lista *nova = novaPublicacao(titulo, ano, editora, anterior);

                // mantêm a referencia anterior para o ultimo elemento da lista
                anterior = nova;
            }
        }
    } while (strcasecmp(confirma, "n") != 0); // Se mantem no se input for diferente de N

    return lista; // O primeiro elemento da lista ligada ou NULL Ã© retornado
}
