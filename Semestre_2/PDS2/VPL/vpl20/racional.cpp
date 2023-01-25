#include "racional.h"

#include <cmath>
#include <bits/stdc++.h>

void Racional::Simplificar() {
  if(denominador_ < 0){
      denominador_ *= -1;
      numerador_ *= -1;
  }
  int mdc = std::__gcd(numerador(),denominador());
  denominador_ /= mdc;
  numerador_ /= mdc;
}

Racional::Racional() {
  numerador_ = 0;
  denominador_ = 1;
  Simplificar();
}

Racional::Racional(int n)  {
  numerador_ = n;
  denominador_ = 1;
  this->Simplificar();
}

Racional::Racional(int n, int d) {
  if(d == 0) throw ExcecaoDivisaoPorZero{};
  numerador_ = n;
  denominador_ = d;
  this->Simplificar();
}

int Racional::numerador() const {
  return numerador_;
}

int Racional::denominador() const {
  return denominador_;
}

Racional Racional::operator-() const {
  Racional ans(-numerador_, denominador_);
  return ans;
}

Racional Racional::operator+(Racional k) const {
  int num = (k.numerador() * denominador()) + (numerador() * k.denominador());
  int den = k.denominador() * denominador(); 
  Racional ans(num, den);
  return ans;
}

Racional Racional::operator-(Racional k) const {
  int num = - (k.numerador() * denominador()) + (numerador() * k.denominador());
  int den = k.denominador() * denominador();
  Racional ans(num, den);
  return ans;
}

Racional Racional::operator*(Racional k) const {
  int num = (k.numerador()* numerador());
  int den = k.denominador() * denominador(); 
  Racional ans (num, den);
  return ans;
}

Racional Racional::operator/(Racional k) const {
  Racional inverse(k.denominador(), k.numerador());
  Racional ans = (*this)*(inverse);
  return ans;
}

Racional::operator float() const{
    float num = float(numerador());
    float dem = float(denominador());
    return num/dem;
}

Racional::operator string() const{
    string num = std::to_string(numerador());
    string dem = std::to_string(denominador());
    return num + '/' + dem;
}

ostream& operator<<(ostream& out, Racional r){
    out << string(r);
    return out;
}

istream& operator>>(istream& in, Racional& r){
    in >> r.numerador_;
    in >> r.denominador_;
    r.Simplificar();
    return in;
}