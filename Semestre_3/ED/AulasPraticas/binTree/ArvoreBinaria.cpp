#include "ArvoreBinaria.hpp"
#include <iostream>
#include <stack>
Arvore::Arvore(){
    Raiz = nullptr;
}

Arvore::~Arvore(){
    Limpa();
}

void Arvore::Insere(int item){
    InsereRecursivo(Raiz, item);
}

void Arvore::InsereRecursivo(node* &p, int item){
    if(p==NULL){
        p = new node(item);
    }
    else{
        if(item < p->item)
            InsereRecursivo(p->esq, item);
        else
            InsereRecursivo(p->dir, item);
    }
}

// void Arvore::PreOrdem(node *p){
//     if(p != NULL){
//         std::cout << p->item << ' ';
//         PreOrdem(p->esq);
//         PreOrdem(p->dir);
//     }
// }

// void Arvore::InOrdem(node *p){
//     if(p != NULL){
//         InOrdem(p->esq);
//         std::cout << p->item << ' ';
//         InOrdem(p->dir);
//     }
// }

// void Arvore::PosOrdem(node *p){
//     if(p != NULL){
//         PosOrdem(p->esq);
//         PosOrdem(p->dir);
//         std::cout << p->item << ' ';
//     }
// }


void Arvore::PreOrdem(node *p){
    std::stack<node*> S;
    S.push(p);
    while (!S.empty()){
        node* aux = S.top();
        std::cout<< aux->item << ' ';
        S.pop();
        if(aux->dir != NULL) S.push(aux->dir);
        if(aux->esq != NULL) S.push(aux->esq);
    }
}

void Arvore::InOrdem(node *p){
    std::stack<node*> S;
    node* atual = p;
    while (atual != NULL || !S.empty()){
        while (atual != NULL){
            S.push(atual);
            atual = atual->esq;
        }
        atual = S.top();
        S.pop();
        std::cout << atual->item << ' ';
        atual = atual->dir;
    }
}

void Arvore::PosOrdem(node *p){
    std::stack<node*> S,S2;
    S.push(p);
    while (!S.empty()){
        node* aux = S.top();
        S2.push(aux);
        S.pop();
        if(aux->esq != NULL) S.push(aux->esq);
        if(aux->dir != NULL) S.push(aux->dir);
    }
    while (!S2.empty()){
        std::cout << S2.top()->item << ' ';
        S2.pop();
    }
}


void Arvore::Caminha(int x){
    if(x == 1) PreOrdem(Raiz);
    else if (x == 2) InOrdem(Raiz);
    else PosOrdem(Raiz);
}

void Arvore::ApagaRecursivo(node* p){
    if(p != NULL){
        ApagaRecursivo(p->esq);
        ApagaRecursivo(p->dir);
        delete p;
    }
}

void Arvore::Limpa(){
    ApagaRecursivo(Raiz);
    Raiz = NULL;
}