#include "japonesa.hpp"

using std::to_string;

std::string Japonesa::descricao() const {
  std::string x = to_string(m_qtd) + "X Comida japonesa - " +
                  combo_ + ", " + to_string(sushis_) + " sushis, " +
                  to_string(temakis_) + " temakis e " + to_string(hots_) +
                  " hots.";
   
  return x;
}

Japonesa::Japonesa(const std::string& combinado,
                   int sushis,
                   int temakis,
                   int hots,
                   int qtd,
                   float valor_unitario) {
  combo_ = combinado;
  sushis_ = sushis;
  temakis_ = temakis;
  hots_ = hots;
  m_qtd = qtd;
  m_valor_unitario = valor_unitario;
}