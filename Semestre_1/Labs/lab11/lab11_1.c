#include <stdio.h>
#include <stdlib.h>

void preenche_vetor(int *v, int n){
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
}

int soma_vet(int *v, int n){
    int aux = n - 1;
    if (aux == 0)
        return v[aux];
    return v[aux] + soma_vet(v, n - 1);
}

int main(){
    int *vet, n;
    scanf("%d", &n);
    vet = (int*) malloc(n * sizeof(int));
    preenche_vetor(vet, n);
    printf("%d\n", soma_vet(vet, n));
    free(vet);
    return 0;
}