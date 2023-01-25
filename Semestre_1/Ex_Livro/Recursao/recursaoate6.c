#include <stdio.h>
#include <math.h>

int soma_de_cubos(int n){ // EX1
    if (n == 1)
        return 1;
    return pow(n,3) + soma_de_cubos(n-1);
}

int somatorio_n(int n){ // EX2
    if (n == 1)
        return 1;
    return n + somatorio_n(n - 1);
}

int print_n(int n){ // EX3
    if (n == -1)
        return 0;
    print_n(n - 1);
    printf("%d ", n );
}

int print_decres(int n){ //EX4
    if (n == -1)
        return 0;
    printf("%d ", n );
    print_decres(n - 1);
}

int soma_vetor(int *vetor, int n){ // EX 5
    if (n == 1)
        return vetor[0];
    return vetor[n - 1] + soma_vetor(vetor, n - 1);
}

float media_vetor(int *vetor, int n, int aux){ // EX7
    if (n == 1)
        return vetor[0];
    float soma =  vetor[n - 1] + media1(vetor, n - 1, aux);
    if(n==aux)
        return soma/aux;
    else
        return soma;
}

int main(){
    int vet[] = {1,2,3,4,5,6};
    printf("%f\n", media_vetor(vet, 6, 6));
    //print_decres(3);
    return 0;
}