#include <stdio.h>
#include <math.h>
typedef struct{
    int x, y;
} ponto;

typedef struct{
    ponto p1, p2;
} retangulo;

int main(){
    ponto point;
    retangulo ret;
    scanf("%d %d", &ret.p1.x, &ret.p1.y);
    scanf("%d %d", &ret.p2.x, &ret.p2.y);
    scanf("%d %d", &point.x, &point.y);
    if ((point.x >=  ret.p1.x && point.x <=  ret.p2.x) || (point.x >=  ret.p2.x && point.x <=  ret.p1.x)){
        if ((point.y >=  ret.p1.y && point.y <=  ret.p2.y) || (point.y >=  ret.p2.y && point.y <=  ret.p1.y)){
            printf("O ponto ta dentro do retangulo\n");
            return 0;
        }
    }
    printf("O ponto nao ta dentro do retangulo\n");
    
    return 0;
}