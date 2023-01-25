#include <stdio.h>
#include <stdlib.h>

int** preenche_matriz(int linha, int col){
    int **p = (int**) malloc(linha* sizeof(int*));
    for (int i = 0 ; i < linha ; ++i){
        p[i] = (int*) malloc(col * sizeof(int));
        for (int j = 0 ; j < col ; ++j)
            scanf("%d", &p[i][j]);
    }
    return p;
}

int** aloca_matriz(int linha, int col){
    int **p = (int**) calloc(linha, sizeof(int*));
    for (int i = 0 ; i < linha ; ++i)
        p[i] = (int*) calloc(col, sizeof(int));
    return p;
}

int** mult_matriz(int** m1, int lines1, int col1,int** m2, int lines2, int col2){
    int** p;
    if(col1 != lines2){
        p = NULL;
        return p;
    }else{
        p = aloca_matriz(lines1, col2);
    }
    for (int i = 0; i < lines1; i++){
        for (int j = 0; j < col2; j++)
            for (int k = 0; k < col1; k++)
                p[i][j] += m1[i][k] * m2[k][j];
    }
    return p;
}

void LiberaMatriz(int **M, int m){
    for(int i = 0 ; i < m ; i++)
        free(M[i]);
    free(M);
}

int main(){
    int line1, col1, line2, col2, **mat1, **mat2, **mat3;
    
    printf("Digite o numero de linhas e de colunas da matriz: ");
    scanf("%d%d", &line1, &col1);
    mat1 = preenche_matriz(line1, col1);
    
    printf("Digite o numero de linhas e de colunas da matriz: ");
    scanf("%d%d", &line2, &col2);
    mat2 = preenche_matriz(line2, col2);

    printf("\n");
    mat3 = mult_matriz(mat1, line1, col1, mat2, line2, col2);
    if(mat3 == NULL){
        printf("Multiplicção impossivel\n");
        LiberaMatriz(mat1, line1);
        LiberaMatriz(mat2, line2);
        return 0;
    }
    printf("Multiplicação das matrizes é: \n");
    for (int i = 0 ; i < line1 ; i++){
        for (int j = 0 ; j < col2 ; j++)
            printf("%d ", mat3[i][j]);
        printf("\n");
    }
    printf("\n");
    LiberaMatriz(mat1, line1);
    LiberaMatriz(mat2, line2);
    LiberaMatriz(mat3, line1);
    return 0;
}