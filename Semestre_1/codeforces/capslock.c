#include <stdio.h>
#include <string.h>

int allUpper(char *x){
    // 0 se nao for toda maiscula | 1 se for toda maiscula
    for (int i = 0 ; i < strlen(x) ; ++i){
        if (x[i] > 90){
            return 0;
        }
    }
    return 1;
}

int condition2(char *x){
    //1 - se a primeira é minusucula e as outras maiscula
    if (x[0] > 90){
        for (int i = 1 ; i < strlen(x) ; ++i){
            if (x[i] > 90) return 0;
        }
        return 1;
    }
    return 0;
}

void uppertolower(char *x, int o){
    for (int i = 0 ; i < strlen(x); ++i){
        if (x[i] <= 90)
            x[i] +=32;
    }
    if (!o) // se nao for toda maiscula
        x[0] -= 32;
    printf("%s", x);
}

int main(){
    char array[101];
    scanf("%s", array);
    if( condition2(array) || allUpper(array))
        uppertolower(array, allUpper(array));
    else
        printf("%s", array);
    return 0;
}