#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, *vet;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    vet = (int*) malloc(sizeof(int) * n);
    for (int i = 0 ; i < n ; i++)
        scanf("%d", &vet[i]);
    for (int i = 0 ; i < n ; i++)
        printf("%d ", vet[i]);
    free(vet);
    return 0;
}