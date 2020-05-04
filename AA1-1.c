/*
 ============================================================================
 Name        : ED2 - AA1.1
 Author      : Gabriel Machado
 Description : Criação e simulação de execução de programas
 ============================================================================
 */

#include <stdio.h>

int potencia(int n1, int n2);

int main()
{
    // Execução no windows :)
    setbuf(stdout, NULL);

    // Declaração de variaveis
    int base, exp;
    printf("Entre com a base: ");
    scanf("%d", &base);
    printf("Entre com o expoente (numero positivo): ");
    scanf("%d", &exp);

    // Loop de validação do expoente
    while (exp <= 0)
    {
        printf("Expoente precisa ser um inteiro positivo: ");
        scanf("%d", &exp);
    }

    // Impressao do resultado com a chamada do metodo recursivo
    printf("%d^%d = %d", base, exp, potencia(base, exp));
    return 0;
}

int potencia(int base, int exp)
{
    // condição de parada da recursão
    if (exp == 1)
    {
        return base;
    }

    // Retorno da recursão, decrementando o expoente
    return (base * potencia(base, exp - 1));
}

/*
 *
 * 2. Tabela de execução recursiva utilizando os valores 4 ^ 4
 *
+-----------------+--------------------+-------------------+-------------------+-----------------------------------+----------+
| Linha 42        |                    |                   | Linha 47          |                                   |          |
+-----------------+--------------------+-------------------+-------------------+-----------------------------------+----------+
| Numero execucao | Parametro recebido | Condição (n == 1) | Executa a chamada | Valor Retornado                   | Subtotal |
+-----------------+--------------------+-------------------+-------------------+-----------------------------------+----------+
| 1               | 4                  | FALSO             | 2                 | 4 * Valor Retornado de Execução_2 | 256      |
+-----------------+--------------------+-------------------+-------------------+-----------------------------------+----------+
| 2               | 3                  | FALSO             | 3                 | 4 * Valor Retornado de Execução_3 | 64       |
+-----------------+--------------------+-------------------+-------------------+-----------------------------------+----------+
| 3               | 2                  | FALSO             | 4                 | 4 * Valor Retornado de Execução_4 | 16       |
+-----------------+--------------------+-------------------+-------------------+-----------------------------------+----------+
| 4               | 1                  | VERDADEIRO        | -                 | 4                                 | 4        |
+-----------------+--------------------+-------------------+-------------------+-----------------------------------+----------+
*/
