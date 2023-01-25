/* Crie uma estrutura representando uma hora. Essa estrutura deve conter os campos
hora, minuto e segundo. Agora, escreva um programa que leia um vetor de cinco
posições dessa estrutura e imprima a maior hora.*/

#include <stdio.h>

typedef struct{
    unsigned int h, m, s;
} hora;

int main(){
    hora maiorHora = {0, 0, 0};
    hora horas[5];
    for (int i = 0; i < 5 ; ++i){
        scanf("%d:%d:%d", &horas[i].h, &horas[i].m, &horas[i].s);
        if (maiorHora.h < horas[i].h){
            maiorHora = horas[i];
        }else if (maiorHora.h == horas[i].h && maiorHora.m < horas[i].m){
            maiorHora = horas[i];
        }else if (maiorHora.h == horas[i].h && maiorHora.m == horas[i].m && maiorHora.s < horas[i].s){
            maiorHora = horas[i];
        }
    }
    printf("A maior hora eh : %d:%d:%d\n", maiorHora.h, maiorHora.m, maiorHora.s);
    
    return 0;
}