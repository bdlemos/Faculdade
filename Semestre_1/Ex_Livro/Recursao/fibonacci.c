#include <stdio.h>

int fib[810] ={0};

int fibonacci(int x){ //EX10
    if (fib[x] != 0 || x == 0)
        return fib[x];
    fib[x] = fibonacci(x - 2) + fibonacci(x - 1);
    return fib[x];
}

int main(){
    int x;
    fib[1] = 1;
    scanf("%d", &x);
    printf("%d\n", fibonacci(x));
}