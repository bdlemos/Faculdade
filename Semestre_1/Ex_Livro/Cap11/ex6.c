#include <stdio.h>
#include <stdlib.h>

int isValInMatriz(int **vet, int val, int line, int col){
    for(int i = 0 ; i < line ; ++i)
        for(int j = 0 ; j < col ; ++j)
            if (vet[i][j] == val)
                return 1;
    return 0;
}

int main(){
    int col, lines, **vet, val;
    printf("Digite o numero de linhas: ");
    scanf("%d", &lines);
    printf("Digite o numero de colunas: ");
    scanf("%d", &col);
    
    vet = (int**) calloc(lines ,sizeof(int));
    for (int i = 0 ; i < lines ; ++i)
        vet[i] = (int*) malloc(col * sizeof(int));
    printf("%d\n", isValInMatriz(vet, 0, lines, col));
    
    free(vet);
    return 0;
}