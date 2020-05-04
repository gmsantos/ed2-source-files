/*
 ============================================================================
 Name        : ED2 - AA2.1
 Author      : Gabriel Machado
 Description : Discussão sobre algoritmos recursivos
 ============================================================================
 */

#include <stdio.h>
#include <time.h>

// Definição dos métodos
// n -> enésimo termo na sequencia de Fibonacci 
int fibonacci_interactive(int n);
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

    printf("\nFibonacci Iterativo:\n");
    start = clock();
    printf("%d ", fibonacci_interactive(n));
    printf("\n\nExecutado em: %f segundos\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    printf("\nFibonacci Recursivo:\n");
    start = clock();
    printf("%d ", fibonacci_recursive(n));
    printf("\n\nExecutado em: %f segundos\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}

// Algoritmo Iterativo
//
// Contras: Código mais longo
int fibonacci_interactive(int n)
{
    int i;
    int termo_anterior = 0; // Termos iniciais da sequencia de fibonacci
    int termo_atual = 1;
    int proximo_termo; // incializa com o primeiro termo

    if (n == 0) {
        return termo_anterior; // Retorna 0 se enviado a posição zero
    }

    for (i = 2; i <= n; i++) // começa a contagem em 2, para n = 1 retornar 
    {
        proximo_termo = termo_anterior + termo_atual; // o termo seguinte é a soma dos dois termos anteriores
        termo_anterior = termo_atual; // troca os termos anteriores para a proxima interação
        termo_atual = proximo_termo;
    }

    return termo_atual; // retorna o enésimo termo
}

// Algoritmo Recursivo
// Prós: código mais curto
//
// Contras: Maior uso de memória
// Requer um ponto de parada (return == 0 e return == 1)
// Complexidade algorimica maior O(2^n)
int fibonacci_recursive(int n)
{
    if (n < 2) {
        return n;
    }

    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2); // Soma recursivamente 
}

// Conclusão
//
// Nesse caso não vejo uma justificativa em implementar o algorítimo usando recursão.
// Algoritomos que podem ser resolvidos aplicando um único laço de repetição, como
// Fibocacci e cálculos fatorias tem uma complexidade algorítmica maior se resolvidos
// utilizando.
//
// A recursão se mostra mais eficiente com estruturas mais complexas, como o caso
// de um algoritmo de busca binaria.
