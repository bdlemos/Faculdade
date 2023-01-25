#include <stdio.h>
#include <stdlib.h>

int main(){
    int line, col, **matrix;
    scanf("%d %d", &line, &col);
    matrix = (int**) malloc(line * sizeof(int*));
    for (int i = 0; i < line; i++)
        matrix[i] = (int*) malloc(col * sizeof(int));
    
    for (int i = 0; i < line; i++)
        for (int j = 0; j < col; j++)
            scanf("%d", &matrix[i][j]);
        
    for (int i = 0; i < line; i++){
        for (int j = 0; j < col; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    for(int i = 0; i < line; i++)
        free(matrix[i]);
    free(matrix);
    
    return 0;
}