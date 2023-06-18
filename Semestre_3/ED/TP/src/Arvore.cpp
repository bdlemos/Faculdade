#include"Arvore.hpp"

int isoperator(std::string x){
    if (x == "+") return 1;
    if (x == "-") return 2;
    if (x == "*") return 3;
    if (x == "/") return 4;
    return 0;
}


Arvore::Arvore(){
    Raiz = nullptr;
}

Arvore::~Arvore(){
    Limpa();
}

void Arvore::Insere(std::string item){
    InsereRecursivo(Raiz, item);
}

void Arvore::InsereRecursivo(node* &p, std::string item){
    if(p==NULL){
        for (auto &&i : item) if(i == ',') i = '.';
        p = new node(item);
    }else if(isoperator(p->item) and isValid(p->esq)){
        InsereRecursivo(p->esq, item);
    }else if(isoperator(p->item) and isValid(p->dir)){
        InsereRecursivo(p->dir, item);
    }else{
        Limpa();
        throw EXPINVALIDA{};
    }
}

float Arvore::PreOrdem(node *p){ // RESULTADO
    if(p!=NULL){
        if(!isoperator(p->item)) return stof(p->item);
        if(isoperator(p->item) == 4) {
            float den = float(PreOrdem(p->esq));
            if(!den) throw DIVPOR0{};
            return float(PreOrdem(p->dir)) / den;
        }
        if(isoperator(p->item) == 3) return float(PreOrdem(p->esq)) * float(PreOrdem(p->dir));
        if(isoperator(p->item) == 2) return float(PreOrdem(p->dir)) - float(PreOrdem(p->esq));
        if(isoperator(p->item) == 1) return float(PreOrdem(p->esq)) + float(PreOrdem(p->dir));
    }
    return 0;
}

void Arvore::InOrdem(node *p){ //INFIXA
    if(p!=NULL){
        if(isoperator(p->item)){
            std::cout << "( ";
            InOrdem(p->dir);
            std:: cout << p->item << ' ';
            InOrdem(p->esq);
            std::cout << ") ";
        }else{
            std:: cout << p->item << ' ';
        }
        
    }
}

void Arvore::PosOrdem(node *p){ // POSFIXA
    if(p!=NULL){
        PosOrdem(p->dir);
        PosOrdem(p->esq);
        std:: cout << p->item << ' ';
    }
}

void Arvore::Limpa(){
    ApagaRecursivo(Raiz);
    Raiz = nullptr;
}
void Arvore::ApagaRecursivo(node *p){
    if(p!=NULL){
        ApagaRecursivo(p->esq);
        ApagaRecursivo(p->dir);
        delete p;
    }
}
void Arvore::Caminha(int x){
    if(x == 1){
        float ans = PreOrdem(Raiz);
        std::cout << "VAL: " << ans;
    }
    else if(x == 2)
        InOrdem(Raiz);
    else
        PosOrdem(Raiz);
}

bool Arvore::isValid(node *p){
    if (p == nullptr) return true;
    else if (!isoperator(p->item)) return false;
    return isValid(p->dir) or isValid(p->esq);
    
}

bool Arvore::ExpressaoValida(){
    return !isValid(Raiz);
}
bool Arvore::Vazia(){
    return Raiz == nullptr;
}