#include <stdio.h>
#include <math.h>

int main(){
    int n, t;
    scanf("%d", &t);
    for (int i = 0 ; i < t ; ++i){
        scanf("%d", &n);
        printf("%.0f\n", pow(2,n) - 1);
    }
    return 0;
}