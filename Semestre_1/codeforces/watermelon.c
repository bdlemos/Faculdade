#include <stdio.h>

int main(){
    int peso, i, contador = 0;
    scanf("%d", &peso);
    for( i = 1 ; i <= peso/2 ; i++){
        if (i % 2 == 0 && (peso - i) % 2 ==0){
            printf("YES");
            contador++;
            break;
        }
    }
    if (contador == 0){
        printf("NO");
    }
    return 0;
}