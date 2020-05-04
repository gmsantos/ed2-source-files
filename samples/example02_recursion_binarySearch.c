#include <stdio.h>
#include <stdlib.h>

// Função recursiva para busca binária em vetor
// 'A' é o vetor
// 'x' é o elemento procurado
// 'comeco' é o elemento inicial do vetor
// 'fim' é o elemento final do vetor

int binarySearch(int A[], int x, int comeco, int fim) {
    int k;
    if ( comeco > fim )  // condição de parada
       return -1;
    k = (comeco + fim)/2;  // encontra o elemento médio
    
    if ( x == A[k] )
       return k;  // encontrou, então retorna o índice do elemento no vetor
       
    if ( x < A[k] )
       return binarySearch( A, x, comeco, k-1); // busca na metade inicial
    return binarySearch( A, x, k+1, fim);
}


int main ( int argc, char *argv[] ) {
 
    int *vetor, // vetor de elementos
        tamanho,  // tamanho do vetor
        i,  // contador
        x,  // elemento a procurar
        p;  // posição do elemento no vetor (se existir)
    

    // definindo o tamanho do vetor e alocando memória
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    if ( ( vetor = (int *)malloc(tamanho) ) == NULL ) {
       printf("Memória insuficiente!!! encerrando o programa...");     
       system("PAUSE");
       return EXIT_FAILURE;    
    }
    
    // carregando o vetor
    printf("Digite os %d elementos do vetor: \n", tamanho);
    for ( i = 0 ; i < tamanho ; i++ ) {
        scanf("%d", &vetor[i] );
    }
    
    // informando o elemento a ser procurado
    printf("Digite o elemento a ser procurado no vetor: ");
    scanf("%d", &x);
    
    // realizando a busca utilizando a Função recursiva
    p = binarySearch(vetor, x, 0, tamanho-1);
    
    // exibindo a posição do elemento no vetor ( -1 caso não exista)
    printf("Posicao do elemento %d no vetor: %d\n", x, p);
    
    system("PAUSE");
    return EXIT_SUCCESS;    
} // fim do programa
