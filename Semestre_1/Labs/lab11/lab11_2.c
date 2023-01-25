#include <stdio.h>
#include <stdlib.h>

int fib(int n){
    if (n == 1 || n == 0)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main(){
    int *vet, n;
    scanf("%d", &n);
    printf("%d\n", fib(n));
    return 0;
}