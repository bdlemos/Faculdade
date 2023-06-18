#include "Sorts.hpp"
#include <iostream>

Sorts::Sorts(){}
Sorts::~Sorts(){}

void Sorts::Faz(int A[], int n, int i){
    int maior = i; 
    int Esq = 2 * i + 1; 
    int Dir = 2 * i + 2; 
 
    if (Esq < n && A[Esq] > A[maior])
        maior = Esq;
 
    if (Dir < n && A[Dir] > A[maior])
        maior = Dir;
 
    if (maior != i) {
        Troca(A + i, A + maior);
        Faz(A, n, maior);
    }
}

void Sorts::HeapSort(int *A, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Faz(A, n, i);
 
    for (int i = n - 1; i >= 0; i--) {
        Troca(A, A + i);
        Faz(A, i, 0);
    }
}

void Sorts::ShellSort(int *vet, int n) {
    int i, j, value;
 
    int h = 1;
    while(h < n) {
        h = 2*h+1;
    }
    while (h > 0) {
        for(i = h; i < n; i++) {
            value = vet[i];
            j = i;
            while (j > h-1 && value <= vet[j - h]) {
                vet[j] = vet[j - h];
                j = j - h;
            }
            vet[j] = value;
        }
        float t = 2.5;
        if (h == 1) break;
        else if (int(h/t) == 0) h = (h/t) + 1;
        else h = h/t;
    }
}

double Sorts::getTimeHeap(int *A, int n){
    clock_t t;
    t = clock();
    HeapSort(A, n);
    t = clock() - t;
    return (double)t/(CLOCKS_PER_SEC);
}

double Sorts::getTimeShell(int* v, int n){
    clock_t t;
    t = clock();
    ShellSort(v, n);
    t = clock() - t;
    return (double)t/(CLOCKS_PER_SEC);
}

void Sorts::Troca(int* a, int* b){
    int aux = *a;
    *a = *b;
    *b = aux;
}