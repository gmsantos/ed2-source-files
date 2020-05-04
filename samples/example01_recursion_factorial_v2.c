#include <stdio.h>
#include <stdlib.h>

int fact(n) {
    int x, y;
    if (n == 0)   // condição de parada
       return (1);
    x = n - 1;
    y = fact (x);
    return (n * y);
}

int main ( int argc, char *argv[] ) {
    int numero, fatorial;
    
    printf("Digite o numero para calcular o fatorial: ");
    scanf("%d", &numero);

    // calculando o fatorial utilizando a função recursiva
    fatorial = fact(numero);
    
    printf("O fatorial de %d eh: %d\n", numero, fatorial);

    system("PAUSE");
    return EXIT_SUCCESS;    
} // fim do programa
