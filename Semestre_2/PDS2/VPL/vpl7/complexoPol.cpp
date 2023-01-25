// Copyright 2022 Universidade Federal de Minas Gerais (UFMG)

#include "complexo.h"

#include <cmath>

Complexo::Complexo() {
}

Complexo::Complexo(double a, double b) {
    modulo_ = sqrt(a*a + b*b);
    angulo_ = atan(b/a);
}

double Complexo::real() {
  return modulo_*cos(angulo_);
}

double Complexo::imag() {
  return modulo_*sin(angulo_);
}

bool Complexo::igual(Complexo x) {
  return x.real() == real() && x.imag() == imag();
}

void Complexo::Atribuir(Complexo x) {
    *this = x;
}

double Complexo::modulo() {
  return modulo_;
}

Complexo Complexo::conjugado() {
  float a = this->real();
  float b = -(this->imag());
  Complexo c(a,b);
  return c;
}

Complexo Complexo::simetrico() {
  Complexo c(-real(), -imag());
  return c;
}

Complexo Complexo::inverso() {
  Complexo i = conjugado();
  double a = i.real() / (modulo_* modulo_);
  double b = i.imag() / (modulo_* modulo_);
  Complexo k(a,b);
  return k;
}

Complexo Complexo::somar(Complexo y) {
  Complexo s;
  s.modulo_ = this->modulo_ + y.real();
  s.angulo_ = this->angulo_ + y.imag();
  return s;
}

Complexo Complexo::subtrair(Complexo y) {
  float a = real() - y.real();
  float b = imag() - y.imag();
  Complexo s(a,b);
  return s;
}

Complexo Complexo::multiplicar(Complexo y) {
  Complexo p;
  p.modulo_ = this->modulo() *  y.modulo();
  p.angulo_ = this->angulo_ + y.angulo_;
  return p;
}

Complexo Complexo::dividir(Complexo y) {
  Complexo p;
  p.modulo_ = this->modulo() /  y.modulo();
  p.angulo_ = this->angulo_ - y.angulo_;
  return p;
}