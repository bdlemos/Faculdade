#include <stdio.h>
#include <stdlib.h>


void imprime(int *v, int n){
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
    return;
}

void multiplica(int *v, int n, double x){
    for (int i = 0; i < n; i++)
        v[i] *= x;
    return;
}

int main(){
    int n, *vetor;
    double val;
    scanf("%d", &n);
    vetor = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &vetor[i]);
    imprime(vetor, n);
    
    scanf("%lf", &val);
    multiplica(vetor, n, val);
    imprime(vetor, n);

    multiplica(vetor, n, 1/val);
    imprime(vetor, n);

    free(vetor);
    return 0;
}