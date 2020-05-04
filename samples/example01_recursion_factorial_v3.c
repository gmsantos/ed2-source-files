#include <stdio.h>
#include <stdlib.h>

int fact(n) {
    if (n)
       return n * fact(n-1);
    else
       return 1;
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
