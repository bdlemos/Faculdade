#include <stdio.h>


int Primo(int n){
    for(int i = 2 ; i * i <= n ; ++i)
        if (!(n % i))
            return 0;
    return 1;
}

void primos(int m, int *p1, int *p2){
    for (int i = m + 1; ; i++){
        if (Primo(i)){
            *p1 = i;
            break;
        }
    }
    for (int i = m - 1; i >= 2; i--){
        if (Primo(i)){
            *p2 = i;
            break;
        }
    }
    return;
}

int main(){
    int val, prox, antes;
    scanf("%d", &val);
    primos(val, &prox, &antes);
    printf("%d\n%d", antes, prox);
    return 0;
}