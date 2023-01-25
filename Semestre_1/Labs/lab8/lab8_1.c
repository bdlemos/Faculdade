#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void media(double *vet, int n, int *pos){
    double media = 0, diff;
    for (int i = 0; i < n; i++)
        media += vet[i] / n;
    diff = fabs(media - vet[0]);
    for (int i = 0; i < n; i++)
        if (fabs(media - vet[i]) <= diff){
            *pos = i;
            diff = fabs(media - vet[i]);
        }
}

int main(){
    int size, pos;
    double *v;
    scanf("%d", &size);
    v = (double*) malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
        scanf("%lf", &v[i]);
    media(v, size, &pos);
    printf("%d", pos);
    return 0;
}