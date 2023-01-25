#include <stdio.h>
#include <stdlib.h>

void preenche_vetor(int *v, int n){
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
}

int main(){
    int *vet, n;
    scanf("%d", &n);
    vet = (int*) malloc(n * sizeof(int));
    preenche_vetor(vet, n);
    for (int i = 0; i < n; i++)
        printf("%d\n", vet[i]);
    free(vet);
    return 0;
}