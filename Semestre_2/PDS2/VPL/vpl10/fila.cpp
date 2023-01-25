#include "fila.h"

Fila::Fila(){
    primeiro_ = ultimo_ = nullptr;
}

string Fila::primeiro(){
    return primeiro_->chave;
}

string Fila::ultimo(){
    return ultimo_->chave;
}

bool Fila::vazia(){
    return primeiro_== nullptr;
}

void Fila::Inserir(string k){
    No* novo = new No();
    novo->chave = k;
    novo->proximo = nullptr;
    if (vazia()){
        primeiro_ = ultimo_ = novo;
    }else{
        ultimo_->proximo = novo;
        ultimo_ = novo;
    }
}

void Fila::Remover(){
    No* aux = primeiro_;
    primeiro_ = primeiro_->proximo;
    delete aux;
}

int Fila::tamanho(){
    int contador = 0;
    No* NoAtual = primeiro_;
    while (NoAtual != nullptr){
        contador++;
        NoAtual = NoAtual->proximo;
    }
    return contador;
}
Fila::~Fila(){
    No* NoAtual = primeiro_;
    while (NoAtual != nullptr){
        No* aux = NoAtual;
        NoAtual = NoAtual->proximo;
        delete aux;
    }
}