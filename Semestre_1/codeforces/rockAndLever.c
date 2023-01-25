#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int llu;

void rockandlever(llu *bit){
    llu pos = 0, val_pos, analise = 0;
    for (int i = 0 ; i < 32 ; ++i){
        if (bit[i] > 1){
            analise += bit[i]*(bit[i] - 1 )/2;
        }
    }
    for (int i = 0 ; i < 32 ; ++i){
        bit[i] = 0;
    }
    printf("%lld\n", analise);

}

int main(){
    llu t, n, x, contador_bits;
    llu bit[32] ={ 0 };
    scanf("%lld", &t);
    for (int i = 0 ; i < t ; ++i){
        scanf("%lld", &n);
            for (int j = 0 ; j < n ; ++j){
                scanf("%lld", &x);
                contador_bits = 0;
                for (int k = x ; k > 0 ; k = k >> 1){
                    contador_bits++;
                }
                bit[contador_bits - 1] += 1;
            }
            rockandlever(bit);
    }
    return 0;
}