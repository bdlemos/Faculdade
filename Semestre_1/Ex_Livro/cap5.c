#include <stdio.h>
#include <stdlib.h>

void ex1(){
    int n, i;
    scanf("%d", &n);
    for (i = 0 ; i <= n ; i++){
        printf("%d\n", i);
    }
}

void ex2(){
    int n, i;
    scanf("%d", &n);
    for (i = n ; i >= 0 ; i--){
        printf("%d\n", i);
    }
}

void ex3(){
    int n, i;
    scanf("%d", &n);
    for (i = 1 ; i < n*2 ; ){
        printf("%d\n", i);
        i += 2;
    }
}

void ex4(){
    int n = 5, i = 1;
    while (i <= n){
        printf("%d\n", 3*i);
        i++;
    }
}

void ex5(){
    int i = 0, num_par = 0, soma = 0;
    loop:
    if (i < 50){
        soma += num_par;
        i++;
        num_par += 2;
        goto loop;
    }
    printf("%d", soma);
}

void ex6(){
    int i = 10;
    do{
        printf("%d\n", i);
        i--;
    }while(i >= 0);
    printf("FIM!\n");
}

void ex11(){
    int num;
    scanf("%d", &num);
    for (int i = 1; i < num + 1; i++){
        if (num % i == 0){
            printf("%d ", i);
        }
    }
}

void ex12(){
    int num, sum = 0;
    scanf("%d", &num);
    for (int i = 1; i < num ; i++){
        if (num % i == 0){
            sum += i;
        }
    }
    printf("%d\n", sum);
}

void ex13(){
    int sum = 0;
    for (int i = 1; i < 1000 ; i++){
        if (i % 3 == 0 || i % 5 == 0){
            sum += i;
        }
    }
    printf("%d\n", sum);
}

void ex14(){
    int* vetor;
    int size, termo = 0;
    scanf("%d", &size);
    vetor = (int *) malloc(size*sizeof(int));
    for (int i = 0; i < size; i++){
        if (i == 0 || i == 1){
            vetor[i] = i;
            printf("%d ", vetor[i]);
        }else{
            vetor[i] = vetor[i-1] + vetor[i-2];
            printf("%d ", vetor[i]);
        }
    }
    free(vetor);
}

void ex15(){
    int max ,min, x;
    scanf("%d", &x);
    max = min = x;
    while(x >= 0){
        max = (x > max) ? max = x : max;
        min = (x < min) ? min = x : min;
        scanf("%d", &x);
    }
    printf("Maior: %d Menor:%d\n", max, min);
}

void ex16(){
    float n, sum = 0;
    scanf("%f", &n);
    for (float i = 1; i <= n ; i++){
        sum += 1/i;
    }
    printf("%f\n", sum);
}

void ex17(){
    int n, i, j, cont = 1;
    scanf("%d", &n);
    printf("\n");
    for (i= 0 ; i < n; i++){
        for(j = 0 ; j <= i ; j++){
            printf("%d ", cont);
            cont++;
        }
        printf("\n");
    }
}

void ex18(){
    //Verifica Primos
    int valor, contador = 0;
    scanf("%d", &valor);
    for (int i = 1; i <= valor ; i++){
        if (valor % i == 0){
            contador++;
        }
    }
    (contador > 2) ? printf("%d nao eh primo\n", valor): printf("%d eh primo\n", valor);
}

void ex19(){
    float den, num, somatorio = 0;
    num = 1;
    for (den = 1 ; den < 56 ; den++, num + 2){
        somatorio += num/den;
    }
    printf("%f\n", somatorio);   
}

float fatorial(int numero){
    float fat = 1;
    for (int i = 1 ; i <= numero ; i++){
        fat = fat *i;
    }
}

void ex20(){
    float valor, soma = 0;
    fatorial(5);
    scanf("%f", &valor);
    for (float i = 1; i <= valor ; i++){
        soma += 1/fatorial(i);
    }
    printf("%f", soma);
}

void ex21(){
    int quantidade, valor ,contador, maximo;
    scanf("%d", &quantidade);
    scanf("%d", &valor);
    for (int i = 1; i < quantidade ; i++){
        if (valor > maximo){
            maximo = valor;
            contador = 1;
        }else if (valor == maximo){
            contador++;
        }
        scanf("%d", &valor);
    }
    printf("O maior numero foi %d e foi lido %d vez!\n", maximo, contador);
}

int main(){
    ex16();
}