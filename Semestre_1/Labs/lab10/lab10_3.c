#include <stdio.h>
#include <stdlib.h>

void preenche_vetor(int *v, int n){
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
}

void soma_vetor(int *v1, int *v2, int *v3, int n){
    for (int i = 0; i < n; i++)
        v3[i] = v1[i] + v2[i];
    
}

int main(){
    int *vet1, *vet2, *vet3, n;
    scanf("%d", &n);
    vet1 = (int*) malloc(n * sizeof(int));
    vet2 = (int*) malloc(n * sizeof(int));
    vet3 = (int*) malloc(n * sizeof(int));
    preenche_vetor(vet1, n);
    preenche_vetor(vet2, n);
    soma_vetor(vet1, vet2, vet3, n);
    for (int i = 0; i < n; i++)
        printf("%d\n", vet3[i]);
    free(vet1);
    free(vet2);
    free(vet3);
    return 0;
}