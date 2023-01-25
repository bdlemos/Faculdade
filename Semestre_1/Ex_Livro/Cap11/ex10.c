#include <stdio.h>
#include <stdlib.h>

int* aloca_vetor(int n, int val){
    int *p = (int*) malloc(n * sizeof(int));
    if (n <= 0){
        p = NULL;
    }else{
    for (int i = 0 ; i < n ; ++i)
        p[i] = val;
    }
    return p;
}

int main(){
    int n, *vet;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    vet = aloca_vetor(n, 5);
    for (int i = 0 ; i < n ; i++)
        printf("%d ", vet[i]);
    printf("\n");
    free(vet);
    return 0;
}