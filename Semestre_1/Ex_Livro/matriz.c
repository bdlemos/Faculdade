#include <stdio.h>
#include <stdlib.h>

int main(){
    int **ptr;
    int i, j, linha, coluna;
    scanf("%d%d", &linha, &coluna);
    ptr = (int**) malloc(linha*sizeof(int)); //aloca espaço para as linhas
    for (i = 0; i < linha; i++){
        ptr[i] = (int*)malloc(coluna*sizeof(int)); // "estica" as linhas para o tamanho determinado
        for(j = 0; j < coluna; j++){
            ptr[i][j] = i+j;
            printf("%d ", ptr[i][j]);
        }
        printf("\n");
    }
    return 0;
}