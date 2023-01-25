#include <string>
#include <iostream>
#include "Estoque.hpp"

void Estoque::add_mercadoria(const std::string& mercadoria, unsigned int qtd) {
    mercadorias_[mercadoria] += qtd;
}

void Estoque::sub_mercadoria(const std::string& mercadoria, unsigned int qtd) {
  if(mercadorias_.find(mercadoria) == mercadorias_.end())
    throw std::string(mercadoria) + " inexistente\n";
  if(mercadorias_[mercadoria] < qtd)
    throw std::string(mercadoria) + " insuficiente\n";
  mercadorias_[mercadoria] -= qtd;
}

unsigned int Estoque::get_qtd(const std::string& mercadoria) const {
  if(mercadorias_.find(mercadoria) != mercadorias_.end()){
    return mercadorias_.at(mercadoria);
  }
  return 0;
}

void Estoque::imprime_estoque() const {
  for (auto &&i : mercadorias_)
    std::cout << i.first << ", " << i.second << std::endl;
  
}

Estoque& Estoque::operator += (const Estoque& rhs) {
  for (auto &&i : rhs.mercadorias_)
    this->add_mercadoria(i.first, i.second);
  return *this;
}

Estoque& Estoque::operator -= (const Estoque& rhs) {
  for (auto &&i : rhs.mercadorias_)
    this->sub_mercadoria(i.first, i.second);
  return *this;
}

bool operator < (Estoque& lhs, Estoque& rhs) {
  for (auto &&i : lhs.mercadorias_){
    if(rhs.mercadorias_.find(i.first) == rhs.mercadorias_.end()) return false;
    if(rhs.get_qtd(i.first) <= i.second) return false;
  }
  return true;;
}

bool operator > (Estoque& lhs, Estoque& rhs) {
  for (auto &&i : rhs.mercadorias_){
    if(lhs.mercadorias_.find(i.first) == lhs.mercadorias_.end()) return false;
    if(lhs.get_qtd(i.first) <= i.second) return false;
  }
  return true;
}