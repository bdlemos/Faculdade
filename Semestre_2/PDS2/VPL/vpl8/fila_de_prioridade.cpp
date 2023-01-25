#include "fila_de_prioridade.h"

#include <list>
#include <string>
#include <vector>

using std::string;
using std::vector;

void FilaDePrioridade::Adicionar(Pessoa p) {
  if(lista_.size() == 0){
    lista_.push_back(p);
  }else{
    for (auto it = lista_.begin(); it != lista_.end(); it++){
      if(it->prioridade < p.prioridade){
        lista_.insert(it, p);
        return;
      }
    }
    lista_.push_back(p);
  }
}

string FilaDePrioridade::RemoverMaiorPrioridade() {  
  string nome;
  list<Pessoa>::iterator it, greater;
  int maior = 0;
  for (it = lista_.begin() ; it != lista_.end() ; it++){
    if(it->prioridade > maior){
      maior = it->prioridade;
      nome = it->nome;
      greater = it;
    }
  }
  lista_.erase(greater);
  return nome;
}

void FilaDePrioridade::Remover(string nome) {
  list<Pessoa>::iterator it;
  for (it = lista_.begin() ; it != lista_.end() ; it++){
    if(nome == it->nome){
      lista_.erase(it);
      return;
    }
  }
}

int FilaDePrioridade::tamanho() {
  int size = lista_.size();
  return size;
}

vector<string> FilaDePrioridade::listar() {
  vector<string> v;
  for (auto it = lista_.begin() ; it != lista_.end() ; it++)
      v.push_back(it->nome);
  return v; 
}