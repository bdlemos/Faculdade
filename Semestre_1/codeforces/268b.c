#include <stdio.h>

int main(){
    int n, x, i = 1, toques = 0;
    scanf("%d", &n);
    while ( i < n ){
        toques += (n - i) * i;
        i++;
    }
    toques += n;
    printf("%d", toques);
    return 0;
}
