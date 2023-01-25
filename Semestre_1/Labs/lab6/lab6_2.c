#include <stdio.h>
typedef long long unsigned int llu;

int Primo(llu n){
    if (n < 2) return -1;
    for(llu i = 2 ; i * i <= n ; ++i)
        if (!(n % i)) return 0;
    return 1;
}

int main(){
    llu val;
    while(scanf("%lld", &val) != EOF)
        printf("%d\n", Primo(val));
    return 0;
}