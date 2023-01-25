#include "vetor.h"

Vetor::Vetor(int inicio, int fim){
    if(inicio > fim) 
        throw IntervaloVazio{inicio, fim};
    inicio_ = inicio;
    fim_ = fim;
    int size = fim - inicio + 1;
    elementos_= new string[size];
    inicializadas_= new bool[size];
}

void Vetor::atribuir(int i, string valor){
    if(i > fim_ || i < inicio_){
        throw IndiceInvalido{inicio_, fim_, i};
    }
    int real_i = i - inicio_;
    elementos_[real_i] = valor;
    inicializadas_[real_i] = true;
}
string Vetor::valor(int i) const{
    if(i > fim_ || i < inicio_){
        throw IndiceInvalido{inicio_, fim_, i};
    }
    int real_i = i - inicio_;
    if(!inicializadas_[real_i]){
        throw IndiceNaoInicializado{i};
    }
    return elementos_[real_i];
}
Vetor::~Vetor(){
    delete[] elementos_;
}
