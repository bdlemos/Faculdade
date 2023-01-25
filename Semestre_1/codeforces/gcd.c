#include <stdio.h>

int main(){
    int n, contador = 0;
    int v[] = {1,1,1,1};
    scanf("%d", &n);
    while (contador < n){
        int valor;
        scanf("%d", &valor);
        v[0] = valor - 3;
        for (int j = 0 ; j < 4 ; ++j){
            printf("%d ", v[j]);
        }
        contador += 1;
    }
    return 0;
}