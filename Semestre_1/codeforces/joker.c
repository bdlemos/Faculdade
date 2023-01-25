#include <stdio.h>
#include <stdlib.h>

int elementsOdd(int * array, int n, int x){
    int even = 0, odd = 0;
    if ((x == 1 || n == 1) && array[0] % 2) return 1;
    for (int i = 0; i < n ; ++i){
        if (array[i] % 2)
            even++;
    }
    if (even % 2)
        return 1; 

    return 0;
}

int main(){
    int t, n, x;
    int *array;
    array = (int*) malloc(1 * sizeof(int));
    scanf("%d", &t);
    for (int i = 0 ; i < t ; ++i){
        scanf("%d %d", &n, &x);
        array = realloc(array, n * sizeof(int));
            for (int j = 0 ; j < n ; ++j){
                scanf("%d", &array[j]);
            }
            if (elementsOdd(array, n, x))
                printf("Yes\n");
            else
                printf("No\n");
    }
    return 0;
}