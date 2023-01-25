#include "dicionario.h"
#include "dicionario.h"

Dicionario::Dicionario(){
    elementos_ = list<Elemento>();
    inicializado = true;
}

int Dicionario::tamanho(){
    return elementos_.size();
}

bool Dicionario::pertence(string key){
    for (auto i = elementos_.begin(); i != elementos_.end(); i++){
        if(i->chave == key){
            return true;
        }
    }
    return false;
}

string Dicionario::menor(){
    if(tamanho() == 0 || !inicializado) throw DicionarioVazio{};
    string menor = elementos_.begin()->chave;
    for (auto i = elementos_.begin(); i != elementos_.end(); i++){
        if(i->chave <  menor){
            menor = i->chave;
        }
    }
    return menor;
}

string Dicionario::valor(string key){
    if(!pertence(key)) {throw ChaveInexistente{key};}
    string val;
    for (auto i = elementos_.begin(); i != elementos_.end(); i++){
        if(i->chave == key){
            val = i-> valor;
        }
    }
    return val;
}

void Dicionario::Inserir(string key, string valor){
    if(pertence(key)) {throw ChaveRepetida{key};}
    elementos_.push_back(Elemento{key, valor});
    return;
}

void Dicionario::Remover(string key){
    if(!pertence(key)) {throw ChaveInexistente{key};}
    for (auto i = elementos_.begin(); i != elementos_.end(); i++){
        if(i->chave == key){
            elementos_.erase(i);
            return;
        }
    }
}

void Dicionario::Alterar(string key, string valor){
    if(!pertence(key)) {throw ChaveInexistente{key};}
    for (auto &i : elementos_){
        if(i.chave == key){
            i.chave = key;
            i.valor = valor;
        }
    }
}

Dicionario::~Dicionario(){}