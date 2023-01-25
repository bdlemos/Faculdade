#include <stdio.h>
#include <stdlib.h>

int PlusOne(int * array, int n){
    int maior = 0, menor = array[0];
    for (int i = 0 ; i < n ; ++i){
        if (maior < array[i]) 
            maior = array[i];
        if (menor > array[i]) 
            menor = array[i];
    }
    return maior - menor;
}

int main(){
    int t, n;
    int *array;
    array = (int*) malloc(1 * sizeof(int));
    scanf("%d", &t);
    for (int i = 0 ; i < t ; ++i){
        scanf("%d", &n);
        array = realloc(array, n * sizeof(int));
            for (int j = 0 ; j < n ; ++j){
                scanf("%d", &array[j]);
            }
            printf("%d\n", PlusOne(array, n));
    }
    return 0;
}