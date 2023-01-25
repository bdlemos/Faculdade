#include <stdio.h>

int bissexto(int n){
    if((!(n % 4) && (n % 100))|| !(n % 400))
        return 1;
    return 0;
}

int main(){
    int year;
    while(scanf("%d", &year) != EOF)
        printf("%d\n", bissexto(year));
    return 0;
}
