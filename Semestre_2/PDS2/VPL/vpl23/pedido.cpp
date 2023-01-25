#include "pedido.hpp"


Pedido::~Pedido() {
  for (auto &&i : m_produtos)
    delete i;
}

void Pedido::setEndereco(const std::string& endereco) {
  m_endereco = endereco;
}

float Pedido::calculaTotal() const {
  float total = 0;
  for (auto &&i : m_produtos)
    total += i->getValor();
  
  return total;
}

void Pedido::adicionaProduto(Produto* p) {
  m_produtos.push_back(p);
}

std::string Pedido::resumo() const {
  std::string resumo;
  for (auto &&i : m_produtos)
    resumo += i->descricao() + "\n";
  resumo += "Endereco: " + m_endereco;
  return resumo;
}