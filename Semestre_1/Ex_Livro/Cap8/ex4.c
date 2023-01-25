#include <stdio.h>
#include <math.h>

typedef struct{
    int x, y;
} ponto;

typedef struct{
    ponto p1, p2;
} retangulo;

int main(){
    float area, diagonal, perimetro;
    retangulo ret;
    scanf("%d %d", &ret.p1.x, &ret.p1.y);
    scanf("%d %d", &ret.p2.x, &ret.p2.y);
    area = (ret.p1.x - ret.p2.x) * (ret.p1.y - ret.p2.y);
    diagonal = sqrt((pow(ret.p1.x - ret.p2.x, 2)) + (pow(ret.p1.y - ret.p2.y, 2)));
    perimetro = (ret.p1.x - ret.p2.x) * 2 + (ret.p1.y - ret.p2.y) * 2;
    printf("A area eh %.1f\n", (area < 0) ? -area : area);
    printf("A diagonal eh %.1f\n", diagonal);
    printf("O perimetro eh %.1f\n", perimetro);
    
    return 0;
}