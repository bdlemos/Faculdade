#include "Pilha.hpp"

Pilha :: Pilha(){
}

Pilha :: ~Pilha(){
    DestroiPilha();
    delete pilha;
}

void Pilha :: CriaPilha(){
    pilha = new FilaEncadeada();
}

bool Pilha :: PilhaVazia(){
    return pilha->getTamanho() == 0;
}

void Pilha :: Empilha(int x){
    pilha->Enfileira(x);
}

int Pilha :: Desempilha(){
    if (PilhaVazia())
        throw "Pilha está vazia!";
        
    int size = pilha->getTamanho();
    for (int i = 0; i < size - 1; i++)
        pilha->Enfileira(pilha->Desenfileira());
    return pilha->Desenfileira();
}

void Pilha :: DestroiPilha(){
    pilha->~FilaEncadeada();
}

int Pilha :: getTamanho(){
    return pilha->getTamanho();
}