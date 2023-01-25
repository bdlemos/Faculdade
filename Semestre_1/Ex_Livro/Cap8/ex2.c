#include <stdio.h>
#include <math.h>

typedef struct{
    float x, y, d;
} pos;

int main(){
    pos ponto;
    scanf("%f %f", &ponto.x, &ponto.y);
    ponto.d = sqrt((pow(ponto.x,2) + (pow(ponto.y,2))));
    printf("A distancia do ponto ate a origem eh %.1f\n", ponto.d);
    return 0;
}