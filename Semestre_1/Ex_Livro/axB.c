#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int **matrizA, *vetorB, *vetorX, *result;
    int size, contador = 0;
    scanf("%d", &size);
    matrizA = (int**) malloc(size*sizeof(int));
    vetorB = (int*) calloc(size, sizeof(int));
    vetorX = (int*) calloc(size, sizeof(int));
    result = (int*) malloc(size * sizeof(int));
    
    printf("Digite a matriz A\n");
    for (int i = 0 ; i < size ; ++i){
        matrizA[i] = (int*) malloc(size * sizeof(int));
        for (int j = 0 ; j < size ; ++j)
            scanf("%d", &matrizA[i][j]);
    }

    printf("Digite o Vetor X\n");
    for (int i = 0 ; i < size ; ++i)
        scanf("%d", &vetorX[i]);
    printf("Digite o Vetor B\n");
    for (int i = 0 ; i < size ; ++i)
        scanf("%d", &vetorB[i]);
    
    printf("Vetor AX\n");
    for (int i = 0 ; i < size ; ++i){
        for (int j = 0 ; j < size ; ++j){
            result[i] += matrizA[i][j] * vetorX[j];
        }
        printf("%d\n", result[i]);
    }
    
    for (int i = 0; i < size ; ++i){
        if (result[i] != vetorB[i])
            contador++;
    }
    printf("%s", (contador == 0) ? "AX = B\n" : "AX != B\n");

    
    free(matrizA); free(vetorB); free(vetorX); free(result);
    return 0;
}