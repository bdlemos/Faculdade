#include <stdio.h>
#define max 10000

void primo(int a, int b){
    int contador;
    while (a <= b){
        contador = 0;
        for (int i = 2 ; i*i <= a ; ++i)
            if (a % i == 0){
                contador++;
                break;
            }
        if (contador == 0)
            printf("%d ", a);
        a++;
    }
}

int main(){
    int a, b;
    scanf("%d%d", &a, &b);
    primo(a,b);
    return 0;
}