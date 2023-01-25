#include <stdio.h>

#define SIZE 8

// Definindo as variaveis globais
int rep = 0;
int retrocessos = 0;
int move_count = 0;
int board[SIZE][SIZE];
int moves[2][SIZE * SIZE];
int qnt_moves[][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 2, 3, 4, 5, 6, 7}};
int Moves[2][8] = {
    {-1, -2, -2, -1, 1, 2, 2, 1},
    {2, 1, -1, -2, -2, -1, 1, 2}};

void add_move(int i, int j);
void remove_move(int i, int j);
int possible_moves(int i, int j);
int IsValid(int i, int j);
void game(int i, int j);
void bubble_sort();

int main()
{

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = 0;
    game(0, 0);
    printf("O numero de casas visitadas foi %d \nO numero de movimentos retrocedidos foi %d\n", rep, retrocessos);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] < 10)
            {
                printf("0%d ", board[i][j]);
            }
            else
            {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}

void bubble_sort()
{ // Faz a ordenaçao por valor e organiza os indez tambem
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (qnt_moves[0][i] > qnt_moves[0][j])
            {
                int aux = qnt_moves[1][j];
                qnt_moves[1][j] = qnt_moves[1][i];
                qnt_moves[1][i] = aux;
                int aux2 = qnt_moves[0][j];
                qnt_moves[0][j] = qnt_moves[0][i];
                qnt_moves[0][i] = aux2;
            }
        }
    }
}

void add_move(int i, int j)
{
    board[i][j] = move_count + 1;
    // moves[0][move_count] = i;
    // moves[1][move_count] = j;
    move_count++;
}

void remove_move(int i, int j)
{
    retrocessos++;
    board[i][j] = 0;
    moves[0][move_count] = 0;
    moves[1][move_count] = 0;
    move_count--;
}
int IsValid(int i, int j)
{
    if ((i >= SIZE || i < 0) && (j >= SIZE || j < 0) && (board[i][j] != 0))
    {
        return 1;
    }
    return 0;
}

int possible_moves(int i, int j)
{
    rep++;
    int cont = 0;
    for (int i = 0; i < 8; i++)
    {
        if (IsValid(Moves[0][i], Moves[1][i]))
            cont++;
    }
    return cont++;
}
void game(int i, int j)
{
    add_move(i, j);
    for (int k = 0; k < 8; k++)
        qnt_moves[0][k] = possible_moves(i, j);

    bubble_sort();
    for (int k = 0; k < 8; k++)
    {
        int num_mov = Moves[qnt_moves[1][k]][qnt_moves[1][k]];
        if (num_mov != 0)
            add_move(num_mov, num_mov);
    }
}