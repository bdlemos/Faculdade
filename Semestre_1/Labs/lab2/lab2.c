#include <stdio.h>

void ex1(){
    int num1, num2, num3;
    scanf("%d%d%d", &num1, &num2, &num3);
    if (num1 > num2 && num1 > num3){
        printf("%d",num1);
    }else if (num2 > num1 && num2 > num3){
        printf("%d",num2);
    }else{
        printf("%d", num3);
    }
}

void ex2(){
    int num1, num2, num3;
    scanf("%d%d%d", &num1, &num2, &num3);
    if (num1 % num2 == 0 && num1 % num3 == 0){
        printf("O número é divisível");
    }else{
        printf("O número não é divisível");
    }
}

void ex3(){
    int dinheiro;
    scanf("%d", &dinheiro);
    if (dinheiro >= 100){
        printf("100: %d\n", dinheiro/100);
        dinheiro = dinheiro - 100*(dinheiro/100);
    }else{
        printf("100: 0\n");
    }
    if (dinheiro >= 50){
        printf("50: %d\n", dinheiro/50);
        dinheiro = dinheiro - 50*(dinheiro/50);
    }
    else{
        printf("50: 0\n");
    }
    if (dinheiro >= 20){
        printf("20: %d\n", dinheiro/20);
        dinheiro = dinheiro - 20*(dinheiro/20);
    }else{
        printf("20: 0\n");
    }
    if (dinheiro >= 10){
        printf("10: %d\n", dinheiro/10);
        dinheiro = dinheiro - 10*(dinheiro/10);
    }else{
        printf("10: 0\n");
    }
    if (dinheiro >= 5){
        printf("5: %d\n", dinheiro/5);
        dinheiro = dinheiro - 5*(dinheiro/5);
    }else{
        printf("5: 0\n");
    }
    if (dinheiro >= 2){
        printf("2: %d\n", dinheiro/2);
        dinheiro = dinheiro - 2*(dinheiro/2);
    }else{
        printf("2: 0\n");
    }
    if (dinheiro >= 1){
        printf("1: %d\n", dinheiro/1);
        dinheiro = dinheiro - 1*(dinheiro/1);
    }else{
        printf("1: 0\n");
    }
}

int main(){
    ex2();
    return 0;
}