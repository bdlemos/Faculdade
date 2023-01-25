#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    float comS, larS, comP, larP;
    char tipo[50];
}Iris;

void classificar(Iris nao_identificada, Iris registros_identificados[], int n){
    float *euclidian =(float*) calloc(n, sizeof(float));
    float menor;
    int pos;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 4; j++)
            euclidian[i] += pow(*(&nao_identificada.comS + j) - *(&registros_identificados[i].comS + j), 2);
        euclidian[i] = sqrt(euclidian[i]);
    }
    menor = euclidian[0];
    for (int i = 0; i < n; i++){
        if (euclidian[i] <= menor){
            pos = i;
            menor = euclidian[i];
        }
    }
    printf("%s", registros_identificados[pos].tipo);
    return;
}


int main(){
    int n;
    Iris *flores, flor;
    scanf("%d", &n);
    flores = (Iris*) malloc (n * sizeof(Iris));
    for (int i = 0; i < n; i++)
    {
        scanf("%f %f %f %f", &flores[i].comS, &flores[i].larS, &flores[i].comP, &flores[i].larP);
        getchar();
        scanf("%s", flores[i].tipo);
    }
    scanf("%f %f %f %f", &flor.comS, &flor.larS, &flor.comP, &flor.larP);
    classificar(flor, flores, n);
    return 0;
}
