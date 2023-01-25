#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;
    int soma = 0;
    fp = fopen("teste1.txt", "r");
    if (fp == NULL){
        printf("Erro\n");
        exit(1);
    }
    while (!feof(fp))
        if (fgetc(fp) == '\n')
            soma++;
    
    printf("A numero de linha desse arquivo eh %d\n", soma);
    
    fclose(fp);
    return 0;
}