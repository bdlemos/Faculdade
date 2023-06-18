#include "racional.h"

#include <cmath>
#include <iostream>

void Racional::Simplificar() {
  if(denominador_ < 0){
      denominador_ *= -1;
      numerador_ *= -1;
  }
  int i = 2;
  while(true){
    if (abs(numerador_) < i || abs(denominador_) < i) break;
    if (numerador_ % i == 0 && denominador_ % i == 0){
      numerador_ /= i;
      denominador_ /= i;
    }else{
      i++;
    }
  }
}

Racional::Racional() {
  numerador_ = 0;
  denominador_ = 1;
}

Racional::Racional(int n)  {
  numerador_ = n;
  denominador_ = 1;
}

Racional::Racional(int n, int d) {
  numerador_ = n;
  denominador_ = d;
}

int Racional::numerador() const {
  return numerador_;
}

int Racional::denominador() const {
  return denominador_;
}

Racional Racional::simetrico() const {
  Racional ans(-numerador_, denominador_);
  ans.Simplificar();
  return ans;
}

Racional Racional::somar(Racional k) const {
  int num = (k.numerador() * denominador_) + (numerador_ * k.denominador());
  int den = k.denominador() * denominador_; 
  Racional ans(num, den);
  ans.Simplificar();
  return ans;
}

Racional Racional::subtrair(Racional k) const {
  int num = - (k.numerador() * denominador_) + (numerador_ * k.denominador());
  int den = k.denominador() * denominador_;
  Racional ans(num, den);
  ans.Simplificar();
  return ans;
}

Racional Racional::multiplicar(Racional k) const {
  int num = (k.numerador()* numerador_);
  int den = k.denominador() * denominador_; 
  Racional ans (num, den);
  ans.Simplificar();
  return ans;
}

Racional Racional::dividir(Racional k) const {
  Racional inverse(k.denominador(), k.numerador());
  Racional ans = multiplicar(inverse);
  ans.Simplificar();
  return ans;
}

