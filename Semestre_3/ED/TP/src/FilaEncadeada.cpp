#include "FilaEncadeada.hpp"

FilaEncadeada::FilaEncadeada(){
    frente = nullptr;
    tras = nullptr;
    tamanho = 0;
}

FilaEncadeada::~FilaEncadeada(){
    Limpa();
}

void FilaEncadeada::Enfileira(std::string x) {
    Item* novo = new Item;
    novo->val = x; 
    novo->prox = frente;
    if(Vazia()){
        frente = novo;
        tras = novo;
    }else{
        tras->prox = novo;
        tras = novo;
    }
    tamanho++;
}

std::string FilaEncadeada::Desenfileira() {
    if (Vazia())
        throw "Fila está vazia!";
    
    Item* aux = frente;
    frente = frente->prox;
    std::string val = aux->val;
    delete aux;
    tamanho--;
    return val;
}


void FilaEncadeada::Limpa(){
    while (!Vazia())
        Desenfileira();
}

int FilaEncadeada::getTamanho(){
    return tamanho;
}

bool FilaEncadeada::Vazia(){
    return tamanho == 0;
}