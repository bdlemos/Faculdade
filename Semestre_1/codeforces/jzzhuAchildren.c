#include <stdio.h>
#include <stdlib.h>

//x[i]/m || x[i] % m !=

int main(){
    int *a, n, m, maior = 0, posMaior = 0;
    scanf("%d%d", &n, &m);
    a = (int*) malloc(n * sizeof(int));
    for (int i = 0 ; i < n ; ++i){
        scanf("%d", &a[i]);
        if (a[i] % m == 0)
            a[i] = a[i] / m;
        else
            a[i] = (a[i] / m) + 1;
        
        if (a[i] >= maior && i >= posMaior){
            maior = a[i];
            posMaior = i;
        }
    }
    printf("%d\n", posMaior + 1);
    return 0;
}