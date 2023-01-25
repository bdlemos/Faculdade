#include <stdio.h>
#include <math.h>

typedef struct{
    float x, y;
} pos;

int main(){
    float distancia;
    pos ponto, ponto2;
    scanf("%f %f", &ponto.x, &ponto.y);
    scanf("%f %f", &ponto2.x, &ponto2.y);
    distancia = sqrt((pow(ponto.x - ponto2.x, 2)) + (pow(ponto.y - ponto2.y, 2)));
    printf("A distancia entre os pontos eh %.1f\n", distancia);
    return 0;
}