#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int powxy(int* x, int* y){ //EX7
    if (*y == 0)
        return 1;
    *y = *y - 1;
    return *x * powxy(x, y);
}

int multiplicacao(int x, int y){ //EX8
    if (y == 1)
        return x;
    return x + multiplicacao(x, y - 1);
}

int factorial(int x){ //EX9
    if (x == 0)
        return 1;
    return x * factorial(x - 1);
}

int fibonacci(int x){ //EX10
    if (x == 1) 
        return 0;
    if (x == 2)
        return 1;
    return fibonacci(x - 2) + fibonacci(x - 1);
}

int reverse(int x){ // EX11
    if ( x / 10 == 0)
        return x;
    int i = 1, aux = x;
    while (aux/10){
        i *= 10;
        aux /= 10;
    }
    return ((x % 10) * i) + reverse(x/10);
}

void dectobin(int x){ //EX12
    if (x / 2 == 0){
        printf("%d", x % 2);
        return;
    }
    dectobin(x / 2);
    printf("%d", x % 2);
}

float series(float n){ //EX13
    if (n == 1)
        return 2;
    return (pow(n,2) + 1 ) / n + series(n - 1);
}

int min_vetor(int *vetor, int n, int aux){ // EX 14
    if (n == 0)
        return aux;
    if (aux >= vetor [n - 1])  
        aux = vetor[n - 1];
    return min_vetor(vetor, n - 1, aux);
}

float harmonico(float n){
    if ( n == 1)
        return 1;
    return (1/n) + harmonico(n - 1);
}

int main(){
    int x, y;
    scanf("%d", &x);
    int vet[] = {10,472,413,187,505,6};
    printf("%d", reverse(x));
    //dectobin(x);
    printf("\n");
    return 0;
}