#include "pizza.hpp"
using std::to_string;

std::string Pizza::descricao() const {
  std::string x;
  x = to_string(m_qtd) + "X Pizza " + sabor_ + ", " + 
                 to_string(pedacos_) + " pedacos";
  if(borda_) x += " e borda recheada.";
  else x += " e sem borda recheada.";
  return x;
}

Pizza::Pizza(const std::string& sabor,
             int pedacos,
             bool borda_recheada,
             int qtd,
             float valor_unitario) {
  sabor_ = sabor;
  pedacos_ = pedacos;
  borda_ = borda_recheada;
  m_qtd = qtd;
  m_valor_unitario = valor_unitario;
}