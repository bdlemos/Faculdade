// Copyright 2022 Universidade Federal de Minas Gerais (UFMG)

#include "complexo.h"

#include <cmath>

Complexo::Complexo() {
}

Complexo::Complexo(double a, double b) {
    this->real_ = a;
    this->imag_ = b;
}

double Complexo::real() {
  return real_;
}

double Complexo::imag() {
  return imag_;
}

bool Complexo::igual(Complexo x) {
  return x.real() == real_ && x.imag() == imag_;
}

void Complexo::Atribuir(Complexo x) {
    *this = x;
}

double Complexo::modulo() {
  return sqrt(real_ * real_ + imag_ * imag_);
}

Complexo Complexo::conjugado() {
  Complexo c;
  c.real_ = real_;
  c.imag_ = -imag_;
  return c;
}

Complexo Complexo::simetrico() {
  Complexo c;
  c.real_ = -real_;
  c.imag_ = -imag_;
  return c;
}

Complexo Complexo::inverso() {
  Complexo i = conjugado();
  double mod = modulo();
  i.real_ /= mod * mod;
  i.imag_ /= mod * mod;
  return i;
}

Complexo Complexo::somar(Complexo y) {
  Complexo s;
  s.real_ = this->real_ + y.real_;
  s.imag_ = this->imag_ + y.imag_;
  return s;
}

Complexo Complexo::subtrair(Complexo y) {
  Complexo s;
  s.real_ = this->real_ - y.real_;
  s.imag_ = this->imag_ - y.imag_;
  return s;
}

Complexo Complexo::multiplicar(Complexo y) {
  Complexo p;
  p.real_ = this->real_ *  y.real_ - this->imag_ * y.imag_;
  p.imag_ = this->real_ *  y.imag_ - this->imag_ * y.real_;
  return p;
}

Complexo Complexo::dividir(Complexo y) {
  Complexo d = multiplicar(y);
  double div = y.real_ * y.real_ + y.imag_ * y.imag_;
  d.real_ /= div;
  d.imag_ /= div;
  return d;
}
