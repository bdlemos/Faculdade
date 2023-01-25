/*Crie uma estrutura capaz de armazenar o nome e a data de nascimento de uma
pessoa. Agora, escreva um programa que leia os dados de seis pessoas. Calcule e
exiba os nomes da pessoa mais nova e da mais velha.*/

#include <stdio.h>
#include <string.h>

typedef struct{
    int d, m, y;
    char nome[30];
} ficha;

int main(){
    ficha pessoa[6];
    ficha older = {31, 12, 10000};
    ficha younger = {0,0,0};
    for (int i = 0 ;  i < 6 ; ++i){
        setbuf(stdin, NULL);
        fgets(pessoa[i].nome, 30, stdin);
        scanf("%d/%d/%d", &pessoa[i].d, &pessoa[i].m, &pessoa[i].y);
        if (younger.y < pessoa[i].y){
            younger = pessoa[i];
        }else if (younger.y == pessoa[i].y && younger.m < pessoa[i].m){
            younger = pessoa[i];
        }else if (younger.y == pessoa[i].y && younger.m == pessoa[i].m && younger.d < pessoa[i].d){
            younger = pessoa[i];
        }
        if (older.y > pessoa[i].y){
            older = pessoa[i];
        }else if (older.y == pessoa[i].y && older.m > pessoa[i].m){
            older = pessoa[i];
        }else if (older.y == pessoa[i].y && older.m == pessoa[i].m && older.d > pessoa[i].d){
            older = pessoa[i];
        }
    }
    printf("A mais velho eh : %s", older.nome);
    printf("A mais novo eh : %s", younger.nome);
}