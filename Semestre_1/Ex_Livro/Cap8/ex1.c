#include <stdio.h>
#include <string.h>

typedef struct{
    char nome[30];
    int age;
    char adress[50];
} cad;

int main(){
    cad c;
    scanf("%s %d", c.nome, &c.age);
    setbuf(stdin, NULL);
    fgets(c.adress, 50, stdin);
    printf("%s\n%d\n%s", c.nome, c.age, c.adress);
}