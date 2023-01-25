#include <stdio.h>
#include <math.h>

int main(){
    float n, m, flag, qtd1, qtd2, soma = 0;
    scanf("%f%f%f", &n, &m, &flag);
    if (n > flag && m > flag){
        qtd1 = ceil(n/flag);
        qtd2 = ceil(m/flag);
        soma = qtd1 * qtd2;
    }else if (n >= flag && m <= flag){
        qtd1 = ceil(n/flag);
        soma = qtd1;
    }else if (n <= flag && m >= flag){
        qtd2 = ceil(m/flag);
        soma = qtd2;
    }else if( n <= flag && m <= flag){
        soma = 1;
    }
    printf("%.0lf", soma);
    return 0;
}