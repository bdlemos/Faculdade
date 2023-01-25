#include <stdio.h>
typedef long long unsigned int llu;

int main(){
    llu number_tests, number_wheels, max, min, rest;
    scanf("%llu", &number_tests);
    while(number_tests--){
        max = min = rest = 0;
        scanf("%llu", &number_wheels);
        max = number_wheels / 4;
        min = number_wheels / 6;
        if (number_wheels % 4 && number_wheels % 6){
            printf("-1\n");
        }else{
            if(max * 6 - number_wheels == 0){
                printf("%d", max);
            }
        }
    }
    
    return 0;
}