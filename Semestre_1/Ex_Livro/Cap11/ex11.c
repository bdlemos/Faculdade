#include <stdio.h>
#include <stdlib.h>

int** matriz_identidade(int n){
    int **p = (int**) calloc(n, sizeof(int*));
    for (int i = 0 ; i < n ; ++i){
        p[i] = (int*) calloc(n, sizeof(int));
        for (int j = 0 ; j < n ; ++j)
            if (i == j)
                p[i][j] = 1;
    }
    return p;
}

void LiberaMatriz(int **M, int m){
    for(int i = 0 ; i < m ; i++)
        free(M[i]);
    free(M);
}

int main(){
    int n, **vet;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    vet = matriz_identidade(n);
    printf("\n");
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++)
            printf("%d ", vet[i][j]);
        printf("\n");
    }
    printf("\n");
    LiberaMatriz(vet, n);
    return 0;
}