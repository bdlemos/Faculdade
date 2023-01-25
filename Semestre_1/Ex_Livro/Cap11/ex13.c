#include <stdio.h>
#include <stdlib.h>

int** fill_matrix(int n){
    int **p = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++){
        p[i] = (int*) calloc(n, sizeof(int)); // p[i] já é um ponteiro.
        for (int j = 0; j < n; j++){
            if (j > i)
                p[i][j] = 1;
            if (i > j)
                p[i][j] = -1;
        }
    }
    return p;
}

int main(){
    int n, **m;
    scanf("%d", &n);
    m = fill_matrix(n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
            printf("%d ", m[i][j]);
        printf("\n");  
    }
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
    
    return 0;
}