#include <stdio.h>
#include <stdlib.h>

// Função iterativa para busca binária em vetor
// 'n' é o tamanho do vetor
// 'x' é o elemento procurado

int binarySearch(int A[], int n, int x) {
    
	int comeco, fim, k, achou;

	comeco = 0;
	fim = n-1;
	achou = 0;   //achou fica falso

	while( comeco <= fim && !achou )
	{
		 k = ( comeco + fim )/2;         //pega o meio do vetor
		 if( x == A[k] )
			 achou = !achou;   //achou fica verdadeiro
		 else if( x < A[k] )
			 fim = k-1;
		 else
			 comeco = k+1;
	}
	if( achou )
		return k;
	return -1;
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
    
    // realizando a busca utilizando a função recursiva
    p = binarySearch(vetor, tamanho, x);
    
    // exibindo a posição do elemento no vetor ( -1 caso não exista)
    printf("Posicao do elemento %d no vetor: %d\n", x, p);
    
    system("PAUSE");
    return EXIT_SUCCESS;    
} // fim do programa
