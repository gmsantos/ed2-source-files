#include <stdio.h>
#include <stdlib.h>

// n deve ser um número inteiro maior ou igual a zero
int fact(int n) {
    int i, fatorial = 1;
    if (n == 0)
       return (1);
    else {
       for ( i = n ; i > 0 ; i-- ) {
           fatorial = fatorial * i;
       }
    }
    return fatorial;
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
