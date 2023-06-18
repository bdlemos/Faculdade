#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Pilha.hpp"

using namespace std;

int gerarAleatorio(int min, int max) {
    static bool iniciado = false;
    if (!iniciado) {
        srand(time(nullptr));
        iniciado = true;
    }
    return min + rand() % (max - min + 1);
}

int main() {
    int tamanho = 100;
    int* vetor = (int*) malloc(sizeof(int)*tamanho);
    Pilha p;
    p.CriaPilha();

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = gerarAleatorio(0, 9);
        p.Empilha(vetor[i]);
        cout << "Empilha: " << vetor[i] << " | Tamanho: " 
             << p.getTamanho()  << endl;
    }
    cout << endl;

    
    for (int i = 0; i < tamanho; i++) {
        cout << "Desempilha: " << p.Desempilha() << " | Tamanho: " 
             << p.getTamanho()  << endl;
    }

    p.DestroiPilha();
    free(vetor);
    cout << endl;

    return 0;
}
