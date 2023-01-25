#include <stdio.h>
#include <string.h>

void ex1(){
    int x, y;
    printf("%s", (&x > &y) ? "O endereço x é maior" : "O endereço x é maior");
}

void ex2(){
    int x, y;
    scanf("%d%d", &x, &y);
    printf("%d", (&x > &y) ? x : y);
}

void ex3(){
    double x[10];
    for (int i = 0 ; i < 10 ; ++i)
        printf("%p\n", x + i);
}

void ex4(){
    float x[3][3] = {0}, *p;
    p = &x[0][0];
    for (int i = 0 ; i < 9 ; ++i)
        printf("%p\n", p + i);
}

void ex5(){
    int vetor[] = {1, 2, 3, 4, 5}, *p;
    p = vetor;
    for (int i = 0 ; i < 5 ; i++)
        printf("%d", *(p + i) * 2);
}

void ex6(){
    int vetor[] = {1, 2, 3, 4, 5}, *p;
    p = vetor;
    for (int i  = 0 ; i < 5 ; i++)
        if (!(*(p + i) % 2))
            printf("%p\n", p + i);
}

int ex7(char *str1, char *str2){
    int len1 = strlen(str1), len2 = strlen(str2), cont;
    for (int i = 0 ; i < len1 ; ++i)
        if (*(str1 + i) == *(str2)){
            cont = 1;
            for (int j = 1, w = i + 1 ; j < len2 ; ++j, ++w)
                if(*(str2 + j) == *(str1 + w))
                    cont++;
            if (cont == len2)
                return 1;
        }
        return 0;
}

void ex8(int* vetor, int* p, int n){
    for (int i = 0 ; i < n ; ++i)
        *(vetor + i) = *p;
}

void ex9(int* vetor, int n){
    for (int i = 0 ; i < n ; ++i)
        printf("%d ", *(vetor + i));
}

void ex10(){
    int a, *b, **c, ***d;
    scanf("%d", &a);
    b = &a;
    c = &b;
    d = &c;
    printf("Dobro: %d\n", *b * 2);
    printf("Triplo: %d\n", **c * 3);
    printf("Quadruplo: %d\n", ***d * 4);
}

int main(){
    //printf("%s",(ex7("Bernardo", "Ber")) ? "É substring\n" : "Não é substring\n");
    //int x = 18, vet[6] = {1,2,3,4,5,6}, *p;
    //ex9(vet, 6);
    ex10();
    return 0;
}