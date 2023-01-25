#include <stdio.h>

int lucky(int i){
    int d1, d2, d3;
    //verifica os algarismos
    if (i > 99 && i < 1000){
        d1 = i/100;
        d2 = (i % 100) / 10;
        d3 = (i % 100) % 10;
    }else if (i < 100){
        d1 = i/10;
        d2 = i % 10;
        d3 = 7;
    }else return i;

    if ((d1 == 4 || d1 == 7) && (d2 == 4 || d2 == 7) && (d3 == 4 || d3 == 7)) return i;
    return 0;

}

int almostlucky(int i){
    if (i % 4 == 0 || i % 7 == 0) 
        return 1;
    for(int j = 0 ; j < 1000 ; ++j){
        if (lucky(j) && i % lucky(j) == 0) 
            return 1;
    }
    return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    if (lucky(n) || almostlucky(n)) 
        printf("YES");
    else
        printf("NO");
    return 0;

}