#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    int matricula;
    float n1, n2, n3;
}aluno;


int main(){
    printf("Struct = %ld bytes \n", sizeof(aluno));
    return 0;
}