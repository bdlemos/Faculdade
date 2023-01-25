#ifndef KNIGHTTOUR_H_
#define KNIGHTTOUR_H_

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

// Definindo as variaveis globais
int condition; // Condiçao de parada da recursao;
int rep; // Numero de repetições
int regression; // Numero de regression
int move_count; // Numero de movimentos validos
int board[SIZE][SIZE]; // Tabuleiro
int Moves[2][8] = { //Armazena Todos os movimentos possiveis onde a linha 0 é a posiçao x e a linha 1 o y
    {-1, -2, -2, -1, 1, 2, 2, 1}, 
    {2, 1, -1, -2, -2, -1, 1, 2}
}; 

// Declaraçao de Funçoes

// Retorna a quantidade de movimentos possiveis para a posição de entrada
int possible_moves(int i, int j); 
// Retorna verdadeiro se a posição for valida, caso contrario, falso.
int IsValid(int i, int j); 
// Adiciona movimento
void add_move(int i, int j); 
// Remove movimento
void remove_move(int i, int j); 
// Faz o passeio do cavalo recursivamente
void KnightTour(int i, int j); 
// Troca os valores
void swap(int* a,int* b);
// Organiza a matriz "qnt_moves" mantendo os valores fieis aos indices
void bubble_sort(int **qnt_moves); 
// Seta as variaveis para iniciar o passeio
void initialize_board(); 
// Printa o Tabuleiro
void print_board(); 
// Faz o papel de "main"
void passeio(int i, int j);



void passeio(int i, int j){
    i--;
    j--;
    initialize_board();
    KnightTour(i,j);

    FILE* f = fopen("saida.txt", "a");
    if (f == NULL) return;

    print_board(f);
    fclose(f);
}

void initialize_board(){
    condition = 0;
    rep = 0;
    regression = 0;
    move_count = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = 0;
    
}

void print_board(FILE *f){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE ; j++){
            fprintf(f, "%d", board[i][j]);
            if (j < SIZE){
                fprintf(f, " ");
            }
        }
        fprintf(f,"\n");
    }
    //Printa Casas visitadas Casas retrocedidas
    fprintf(f, "%d %d\n", rep, regression);
}

int IsValid(int i, int j){
    if ((i < SIZE && i >= 0) && (j < SIZE && j >= 0) && (board[i][j] == 0)){
        return 1;
    }
    return 0;
}

void add_move(int i, int j){
    board[i][j] = ++move_count;
}

void remove_move(int i, int j){
    regression++;
    board[i][j] = 0;
    move_count--;
}

int possible_moves(int i, int j){
    int cont = -1;
    for (int k = 0; k < 8; k++){
        if (IsValid(i + Moves[0][k], j + Moves[1][k])){
            cont++;
        }
    }
    return cont;
}

void swap(int* a, int* b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void bubble_sort(int **qnt_moves){
    for (int i = 0; i < 8 - 1; i++){
        for (int j = 0; j < 8 - 1 - i; j++){
            if (qnt_moves[0][j + 1] < qnt_moves[0][j]){
                swap(&qnt_moves[1][j], &qnt_moves[1][j + 1]);
                swap(&qnt_moves[0][j], &qnt_moves[0][j + 1]);
            }
        }
    }
}

void KnightTour(int i, int j){
    add_move(i, j);
    rep++;
    
    // qnt_moves = Armazena a quantidade de movimento futuro para cada um dos possiveis movimentos atuais, onde linha 0 é valor e a linha 1 os indices
    int **qnt_moves = (int**) malloc(2*sizeof(int*));
    for (int i = 0; i < 2; i++) qnt_moves[i] = (int*) malloc(8*sizeof(int));
    
    if (move_count == SIZE * SIZE)
        condition = 1;
    // Realiza a heuristica de prioridade de movimentos
    for (int k = 0; k < 8; k++){
        qnt_moves[0][k] = possible_moves(i + Moves[0][k], j + Moves[1][k]);
        qnt_moves[1][k] = k;
    }
    bubble_sort(qnt_moves);
    //Testa os caminhos possíveis 
    for (int k = 0; k < 8; k++){
        if (IsValid(i + Moves[0][qnt_moves[1][k]], j + Moves[1][qnt_moves[1][k]])){
            KnightTour(i + Moves[0][qnt_moves[1][k]], j + Moves[1][qnt_moves[1][k]]);
            if(condition) break;
        }

    }
    //Caso o código cheque nesse ponto e a condição seja negativa, realiza o backtracking
    if (!condition){
        remove_move(i,j);
    }
    for (int i = 0; i < 2; i++) free(qnt_moves[i]);free(qnt_moves);
    return;
}

#endif