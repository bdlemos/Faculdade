#include <stdio.h>
#include <math.h>

void ex1(){
    int vetor[6] = {};
    int val;
    for (int i = 0 ; i < 6; i++){
        scanf("%d", &val);
        vetor[i] = val;
    }
    for (int i = 0 ; i < 6; i++){
        printf("%d ", vetor[i]);
    }
}

void ex2(){
    int vetor[6] = {};
    int val;
    for (int i = 0 ; i < 6; i++){
        scanf("%d", &val);
        vetor[i] = val;
    }
    for (int i = 5 ; i >= 0; i--){
        printf("%d ", vetor[i]);
    }
}

void ex3(){
    int vetor[6] = {}, val;
    float soma = 0;
    for (int i = 0 ; i < 6; i++){
        scanf("%d", &val);
        soma += val;
        vetor[i] = val;
    }
    for (int i = 0 ; i < 6; i++){
        printf("%d ", vetor[i]);
    }
    printf ("\nA media eh %.2f\n", soma/6);
}

void ex4(){
    int vetor[] = {1, 0, 5, -2, -5, 7};
    int soma = vetor[0]+ vetor[1] + vetor[5];
    vetor[4] = 100;
    printf("%d\n",soma);
    for (int i = 0 ; i < 6; i++){
        printf("%d\n", vetor[i]);
    }
}

void ex5(){
    int vetor[8] = {};
    int val, x, y;
    for (int i = 0 ; i < 8; i++){
        scanf("%d ", &val);
        vetor[i] = val;
    }
    printf("x e y:");
    scanf("%d%d", &x, &y);
    printf("%d", vetor[x] + vetor[y]);
}

void ex9(){
    int A[] = {1, 2, 3, 4, 5, 6, 7, 8 ,9 , 10};
    int B[] = {1, 2, 3, 4, 5, 6, 7, 8 ,9 , 11};
    int C[10] = {};
    for (int i = 0 ; i < 10; i++){
        C[i] = A[i] - B[i];
        printf("%d ", C[i]);
    }
    printf("\n");
}

void ex10(){
    int vetor[100] = {};
    int val = 1;
    for (int i = 0 ; i < 100; i++, val++){
        if (val % 7 != 0){
            vetor[i] = val;
        }else{
            i--;
        }
    }
    for (int i = 0 ; i < 100; i++){
        printf("%d ", vetor[i]);
    }
}

void ex13(){}  

void ex14(){
    float vetor[10] = {1.80, 1.70, 1.90};
    float desvio_padrao, somatorio = 0,  media = 0; 
    for (int i = 0 ; i < 3 ; i++){
        media += vetor[i]/3.0;
    }
    for (int i = 0 ; i < 3 ; i++){
        somatorio += (vetor[i] - media);
    }
    desvio_padrao = ((1/(3-1)) +  somatorio);
    printf("%f\n", sqrt(desvio_padrao));
}

void ex15(){
    float a[10] = {};
    float val, t;
    for (int i = 0 ; i < 10; i++){
        scanf("%f", &val);
        a[i] = val;
    }
    // bubblesort
    for (int i = 0; i < 10 - 1; i++){
      for (int j = i + 1 ; j < 10; j++){
         if (a[i] > a[j]){
            t = a[i];
            a[i] = a[j];
            a[j] = t;
         }
      }
   }
    for (int i = 0 ; i < 10; i++){
        printf("%.0f ", a[i]);
    }
}

int main(){
    ex15();
    return 0;
}