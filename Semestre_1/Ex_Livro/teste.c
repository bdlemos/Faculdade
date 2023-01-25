#include <stdio.h>
#include <math.h>

void ex2_1(){
    int n, x0, x1, xn;
    scanf("%d%d%d", &n, &x0, &x1);
    printf("X0 = %d\nX1 = %d\n", x0, x1);
    for (int i = 1 ; i < n ; i++){
        printf("X%d = %d\n", i+1, 4*x1 - 2*x0);
        xn = x1;
        x1 = 4*xn - 2*x0;
        x0 = xn;
    }
}

void ex2_2(){
    double max_dif, pi_prox = 0, dem = 1, teste;
    int i = 0;
    scanf("%lf", &max_dif);
    while (1){
        i++;
        if (i % 2 == 0){
            pi_prox -= (4/dem);
        }
        else{
            pi_prox += (4/dem);
        }
        dem += 2;
        teste = pi_prox - M_PI;
        teste = (teste < 0) ? -teste : teste;
        if ( teste < max_dif){
            break;
        }
    }
    printf("%d\n", i);
}

int main(){
    ex2_1();
}