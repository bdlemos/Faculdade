#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, *vet;
    printf("Digite o tamanho do vetor: ");
    while(1){
        scanf("%d", &n);
        if (n >= 0)
            break;
        printf("Digite um valor valido: ");
    }
    vet = (int*) malloc(sizeof(int) * n);
    for (int i = 0 ; i < n ;){
        scanf("%d", &vet[i]);
        if (vet[i] >= 2)
            i++;
        else
            printf("Digite um valor maior ou igual a 2\n");
    }
    for (int i = 0 ; i < n ; i++)
        printf("%d ", vet[i]);
    
    free(vet);
    return 0;
}