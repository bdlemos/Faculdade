#include "venda.hpp"

#include <iomanip>

Venda::~Venda() {
  for (auto &&i : m_pedidos)
    delete i;
}

void Venda::adicionaPedido(Pedido* p) {
  m_pedidos.push_back(p);
}

void Venda::imprimeRelatorio() const {
  float tv = 0;
  int cont = 1;
  for (auto &&i : m_pedidos){
    std::cout << "Pedido " << cont++ << std::endl<< i->resumo() << std::endl;
    tv += i->calculaTotal();
  }
  std::cout << "Relatorio de Vendas" << std::endl 
            <<"Total de vendas: R$ " << std::fixed << std::setprecision(2)<< tv << std::endl
            <<  "Total de pedidos: " << m_pedidos.size() << std::endl;
}