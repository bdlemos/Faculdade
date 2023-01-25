#include <stdio.h>
#include <string.h>
#define SIZE 5

typedef long long unsigned llu;

int main (int argc, char *argv[]){
    FILE *f;
    int M[SIZE][SIZE],
    M2[SIZE][SIZE], 
    M3[SIZE][SIZE];
    int cont = 0;
    char s[300000];

    scanf("%s", s);
    f = fopen(s, "r");
    if (f == NULL) return 1;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE;j++)
            fscanf(f, "%u", &M[i][j]);
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE;j++)
            fscanf(f, "%u", &M2[i][j]);
    
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE;j++)
            printf("%u ", M[i][j] + M2[i][j]);
        printf("\n");
    }
    fclose(f);
    return 0;
}