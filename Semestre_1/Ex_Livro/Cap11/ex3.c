#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[30], endereco[50];
    int idade;
}pessoa;

pessoa* funcao(int n){
    pessoa *p = (pessoa*) malloc(n * sizeof(pessoa));
    for(int i = 0 ; i < n ; ++i){
        setbuf(stdin, NULL);
        printf("Digite seu nome: ");
        fgets(p[i].nome, 30, stdin);
        printf("Digite sua idade: ");
        scanf("%d", &p[i].idade);
        setbuf(stdin, NULL);
        printf("Digite seu endereco: ");
        fgets(p[i].endereco,50, stdin);
    }
    return p;
}

int main(){
    int n;
    scanf("%d", &n);
    printf("%p\n", funcao(n));
    return 0;
}