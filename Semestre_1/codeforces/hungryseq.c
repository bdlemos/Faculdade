#include <stdio.h>

typedef long long unsigned int llu;

/*llu primo(llu number, llu* vetor){
    llu contador = 0, prox_pos_vetor;
    for (llu j = 0 ;  vetor[j] != 0; ++j){
        if (number % vetor[j] == 0 || vetor[j] == 0)
            return primo(number+1, vetor);
        prox_pos_vetor = j + 1;
    }
    vetor[prox_pos_vetor] = number;
    return number;
}*/

int main(){
    llu t;
    scanf("%lld", &t);
    for (llu j = t + 1 ; j < (2 * t) + 1 ; ++j){
        printf("%lld ", j);
    }
    return 0;
}