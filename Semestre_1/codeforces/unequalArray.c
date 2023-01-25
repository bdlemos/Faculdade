#include <stdio.h>
#include <stdlib.h>

typedef long long unsigned int llu;

int unequalArray(llu* array, llu n){
    int contador_iguais = 0, first = 0, last = 0 ;
    for(int i = 0 ; i < n - 1 ; ++i){
        if (array[i] == array[i+1]){
            if (contador_iguais == 0)
                first = i;
            contador_iguais++;
            last = i;
        }
    }
    if ((last - first) > 1)
        return (last - first) - 1;
    return (last - first);
}

int main(){
    llu t, n, x;
    llu *array;
    array = (llu*) malloc(1 * sizeof(llu));
    scanf("%lld", &t);
    for (int i = 0 ; i < t ; ++i){
        scanf("%lld", &n);
        array = realloc(array, n * sizeof(llu));
            for (int j = 0 ; j < n ; ++j){
                scanf("%lld", &array[j]);
            }
        printf("%d\n", unequalArray(array, n));
    }
    free(array);
    return 0;
}