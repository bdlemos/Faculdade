#include <stdio.h>
#include <stdlib.h>

int* aloca_vetor(int n){
    int *p = (int*) malloc(n * sizeof(int));
    for (int i = 0 ; i < n ; ++i)
        p[i] = i;
    return p;
}

int main(){
    int n, *vet;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    vet = aloca_vetor(n);
    for (int i = 0 ; i < n ; i++)
        printf("%d ", vet[i]);
    
    free(vet);
    return 0;
}