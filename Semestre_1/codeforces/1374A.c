//https://codeforces.com/problemset/problem/1374/A

#include <stdio.h>
typedef long long unsigned llu;

int main(){
    llu x, y, n, times;
    scanf("%llu", &times);
    while (times--){
        scanf("%llu %llu %llu",&x, &y, &n);
        int mod = n % x;
        if (mod >= y){
            printf("%llu\n", n - mod + y );
        }else{
            int z = x * (n / x);
            printf("%llu\n", z - x + y);
        }
    }
    return 0;
}