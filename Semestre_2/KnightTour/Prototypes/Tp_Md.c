#include <stdio.h>

#define SIZE 8

// Definindo as variaveis globais
int condition; // Condiçao de parada da recursao;
int rep; // Numero de repetições
int regression; // Numero de regression
int move_count; // Numero de movimentos validos
int board[SIZE][SIZE]; // Tabuleiro
int qnt_moves[2][8];// Armazena a quantidade de movimento futuro para cada um dos possiveis movimentos atuais, onde linha 0 é valor e a linha 1 os indices
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
//Troca os valores
void swap(int* a,int* b);
// Organiza a matriz "qnt_moves" mantendo os valores fieis aos indices
void bubble_sort(); 
// Seta as variaveis para iniciar o passeio
void initialize_board(); 
// Printa o Tabuleiro
void print_board(); 



int main(){
    
    initialize_board();
    KnightTour(0,0);

    
    print_board();
    printf("O numero de casas visitadas foi %d \nO numero de movimentos retrocedidos foi %d\n", rep, regression);
    printf("\n\n");

    initialize_board();
    KnightTour(1,3);

    print_board();
    printf("O numero de casas visitadas foi %d \nO numero de casas retrocedidas foi %d\n", rep, regression);
    

    return 0;
}

void initialize_board(){
    condition = 0;
    rep = 0;
    regression = 0;
    move_count = 0;
    for (int i = 0; i < 8; i++){
        qnt_moves[0][i] = 0;
        qnt_moves[1][i] = i;
    }
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = 0;
    
}

void print_board(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE ; j++){
            if(board[i][j] < 10){
                printf("0%d ", board[i][j]);
            }else{
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
}

int IsValid(int i, int j){
    if ((i < SIZE && i >= 0) && (j < SIZE && j >= 0) && (board[i][j] == 0)){
        return 1;
    }
    return 0;
}

void add_move(int i, int j){
    board[i][j] = move_count + 1;
    move_count++;
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

void bubble_sort(){
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
    if (move_count == SIZE * SIZE)
        condition = 1;

    for (int k = 0; k < 8; k++){
        qnt_moves[0][k] = possible_moves(i + Moves[0][k], j + Moves[1][k]);
        qnt_moves[1][k] = k;
    }
    bubble_sort();
    for (int k = 0; k < 8; k++){
        if (IsValid(i + Moves[0][qnt_moves[1][k]], j + Moves[1][qnt_moves[1][k]])){
            KnightTour(i + Moves[0][qnt_moves[1][k]], j + Moves[1][qnt_moves[1][k]]);
            if(condition) return;
        }

    }
    
    if (!condition)
        remove_move(i,j);
    return;
}