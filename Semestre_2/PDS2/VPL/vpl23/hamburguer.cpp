#include "hamburguer.hpp"

using std::to_string;

std::string Hamburguer::descricao() const {
  std::string x;
  x = to_string(m_qtd) + "X Hamburguer " + tipo_;
  if(artesanal_) x += " artesanal.";
  else x += " simples.";
  return x;
}

Hamburguer::Hamburguer(const std::string& tipo,
                       bool artesanal,
                       int qtd,
                       float valor_unitario) {
  tipo_ = tipo;
  artesanal_ = artesanal;
  m_qtd = qtd;
  m_valor_unitario = valor_unitario;
}