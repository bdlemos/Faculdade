#include <stdio.h>

int main(){
    int n, count, p1, p2, p3;
    count = 0;
    scanf("%d", &n);
    for (int i = 0; i < n;i++){
        scanf("%d %d %d", &p1, &p2, &p3);
        if (p1 == 1 && p2 == 1 || p1 == 1 && p3 == 1 || p2 == 1 && p3 == 1 ){
            count++;
        }
    }
    printf("%d",count);
    return 0;
}