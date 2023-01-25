#include "vetor.h"

Vetor::Vetor(int inicio, int fim){
    inicio_ = inicio;
    int size = fim - inicio;
    elementos_= new string[size + 1];
}

void Vetor::atribuir(int i, string valor){
    int real_i = i - inicio_;
    elementos_[real_i] = valor;
}
string Vetor::valor(int i) const{
    int real_i = i - inicio_;
    return elementos_[real_i];
}
Vetor::~Vetor(){
    delete[] elementos_;
}
