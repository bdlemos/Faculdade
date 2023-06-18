#include "fibFact.h"
#include <math.h>
unsigned long long int Rfact(int n){
    if (n < 1) return 1;
    for (int i = 0; i < 10e6; i++) i = i;
    return n * Rfact(n-1);
}

unsigned long long int fact(int n){
    unsigned long long int ans = 1;
    while(n - 1) ans *= n--;
    return ans;
}

unsigned long long int Rfib(int n){
    if(n <= 2) return 1;
    for (int i = 0; i < 10e4; i++) i = i;
    
    return Rfib(n-1) + Rfib(n-2);
}
unsigned long long int fib(int n){
    if(n <= 2) return 1;
    int pre = 1, atual = 1;
    for (int i = 3; i <= n; i++){
        int aux = atual;
        atual += pre;
        pre = aux;
    }
    return atual;
}