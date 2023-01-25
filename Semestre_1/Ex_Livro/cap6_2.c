#include <stdio.h>
#include <math.h>

void ex_1(){
    int matriz[3][3] = {{1,-2,3}, {4,25,6}, {7,8,9}};
    int min = matriz[0][0];
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ; j < 3 ; j++){
            if (matriz[i][j] < min){
                min = matriz[i][j];
            }
        }
    }
    printf("%d\n", min);
}

void ex_2(){
    int matriz[4][4] = {{1,2,3,4}, {4,25,6,5}, {7,8,9,10}, {56,41,147,9}};
    int max = matriz[0][0];
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (matriz[i][j] > max){
                max = matriz[i][j];
            }
        }
    }
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++){
            if (matriz[i][j] == max){
                printf("%d e esta na posicao [%d][%d]\n", max, i, j);
            }
        }
    }
}

void ex_3(){
    int matriz[5][5] = {};
    for (int i = 0 ; i < 5 ; i++){
        for (int j = 0 ; j < 5 ; j++){
            if (i == j){
                matriz[i][j] = 1;
                printf("%d ", matriz[i][j]);
            }else{
                matriz[i][j] = 0;
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

void ex_7(){
    //Soma a diagonal secundaria
    int matriz[3][3] = {{1,-2,3}, {4,25,6}, {7,8,9}};
    int countline = 0, countcol = 2, soma = 0;
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 2 ; j >= 0 ; j--){
            if (countline == i && countcol == j){
                soma += matriz[i][j];
                countline++; // garante q some apenas um valor por linha
                countcol--; // garante q pegue o termo da coluna certa
            }
        }
    }
    printf("%d\n", soma);
}

void ex_8(){
    int m[10][10] = {};
    for (int i = 0 ; i < 3 ; i++){
        for (int j = 0 ;  j < 3 ; j++){
            if (i < j){
                m[i][j] = (2*i) + (7*j);
            } else if (i == j){
                m[i][j] = (3 * pow(i,2)) - 1;
            } else {
                m[i][j] = (4 * pow(i,3)) + (5 * pow(j,5)) + 1;
            }
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

void ex_9(){
    int i, j, soma[3] = {};
    int m[3][3] = {};
    for (i = 0 ; i < 3 ; i++){
        for (j = 0 ; j < 3 ; j++){
            scanf("%d", &m[i][j]);
        }
    }
    for (j = 0 ; j < 3 ; j++){
        for (i = 0 ; i < 3 ; i++){
            soma[j] += m[i][j];
        }
        printf("Soma da coluna[%d] = %d\n", j, soma[j]);
    }
}

void ex_10(){
    float M[10][3] = {};
    int i, j; 
    int prova_1, prova_2, prova_3;
    prova_1 = prova_2 = prova_3 = 0;
    //Preencher a matriz
    for (i = 0 ; i < 10 ; i++){
        for (j = 0 ; j < 3 ; j++){
            scanf("%f", &M[i][j]);
        }
    }
    //verificar as notas
    for (i = 0 ; i < 10 ; i++){
        if (M[i][0] < M[i][1] && M[i][0] < M[i][2]){
            prova_1++;
        }
        if (M[i][1] < M[i][0] && M[i][1] < M[i][2]){
            prova_2++;
        }
        if (M[i][2] < M[i][0] && M[i][2] < M[i][1]){
            prova_3++;
        }
    }
    printf("Pior na prova 1 = %d\nPior na prova 2 = %d\nPior na prova 3 = %d\n", prova_1, prova_2, prova_3);
}

void ex_11(){
    //soma accma da principal
    int M[5][5] = {};
    int i, j;
    int soma = 0;
    for (i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            M[i][j] = i + j;
        }
    }
    for (i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            if ( j > i){
                soma += M[i][j];
            }
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    printf("%d\n", soma);
}

void ex_12(){
    //soma abaixo da principal
    int M[5][5] = {};
    int i, j;
    int soma = 0;
    for (i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            M[i][j] = i + j;
        }
    }
    for (i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            if ( j < i){
                soma += M[i][j];
            }
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    printf("%d\n", soma);
}

void ex_15(){
    //Calcula matriz ao quadrado
    int M[5][5] = {};
    int B[5][5] = {};
    int i, j;
    int soma = 0;
    for (i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            M[i][j] = i + j;
            B[i][j] = 0;

        }
    }
    for (i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            for (int z = 0; z < 5 ; z++){
                B[i][j] += M[i][z]*M[z][j];
            }
        }
    }
    for (i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
}

int main (){
    ex_15();
    return 0;
}