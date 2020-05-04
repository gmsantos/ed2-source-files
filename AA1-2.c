/*
 ============================================================================
 Name        : ED2 - AA2.1
 Author      : Gabriel Machado
 Description : Discussão sobre algoritmos recursivos
 ============================================================================
 
 Analise do código 

 Aqui temos a implementação da sequencia de Fibonacci utilizando uma 
 abordagem recursiva e outra iterativa.

 Na abordagem iterativa, precisamos uma quantidade maior de código para
 implementar a sequencia de fibonacci até o termo necessário. A vantagem
 dessa abordagem é uma implementação mais simples e não requer o entendimento
 de recursão.

 Na abordagem recursiva, temos uma menor quantidade de código executado,
 pois a função consiste em executar a mesma função com os dois termos anteriores
 até atingir a codição de parada. Isso resulta num grande número de chamadas
 da mesma função, o que é menos eficiente que a abordagem interativa e
 pode causar um estouro de pilha em termos em maiores termos da sequencia.
 Além disso, o código não é tão claro e simples se comparado com a 
 abordagem iterativa.

 Nesse caso a abordagem iterativa se mostra mais eficiente. Abordagens recursivas
 geralmente tem uma complexidade maior de serem resolvidos e para casos
 que podem ser resolvidos aplicando um único laço de repetição, como
 Fibonacci e cálculos fatorias, seu uso pode ser. Podemos avaliar sua eficiência 
 com o exemplo de execução com o termo 30 da sequencia:
 
 Entre com o termo da sequencia desejado:30

 Fibonacci Iterativo:
 832040 
 
 Executado em: 0.000006 segundos
 
 Fibonacci Recursivo:
 832040 

 Executado em: 0.005638 segundos

*/

#include <stdio.h>
#include <time.h>

// Definição dos métodos
// n -> enésimo termo na sequencia de Fibonacci
int fibonacci_iteractive(int n);
int fibonacci_recursive(int n);

// A função principal executa ambas implementação de Fibonacci,
// medindo o tempo de execução de cada implementação.
int main()
{
    // Declara variáveis para medir o tempo de execução
    // e o enésimo termo que será exibido.
    int n;
    clock_t start;

    printf("Entre com o termo da sequencia desejado:");
    scanf("%d", &n);

    // Executa a abordagem iterativa e mede seu tempo de execução
    printf("\nFibonacci Iterativo:\n");
    start = clock();
    printf("%d ", fibonacci_iteractive(n));
    printf("\n\nExecutado em: %f segundos\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    // Executa a abordagem recursiva e mede seu tempo de execução
    printf("\nFibonacci Recursivo:\n");
    start = clock();
    printf("%d ", fibonacci_recursive(n));
    printf("\n\nExecutado em: %f segundos\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}

// Algoritmo Iterativo
int fibonacci_iteractive(int n)
{
    int i;
    int termo_anterior = 0; // Termos iniciais da sequencia de fibonacci
    int termo_atual = 1;
    int proximo_termo; // incializa com o primeiro termo

    if (n == 0)
    {
        return termo_anterior; // Retorna 0 se enviado a posição zero
    }

    for (i = 2; i <= n; i++) // começa a contagem em 2, para n = 1 retornar
    {
        // o termo seguinte é a soma dos dois termos anteriores
        proximo_termo = termo_anterior + termo_atual;
        // troca os termos anteriores para a proxima interação
        termo_anterior = termo_atual;
        termo_atual = proximo_termo;
    }

    return termo_atual; // retorna o enésimo termo
}

// Algoritmo Recursivo
int fibonacci_recursive(int n)
{
    if (n < 2)
    { // definição do critério de parada
        return n;
    }

    // Soma recursivamente os termos anteriores
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}
