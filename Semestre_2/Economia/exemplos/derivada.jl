function derivada(f,ponto,precisao)
  variacao=abs(sum(precisao))
  quociente_de_newton=(f(ponto+precisao...)-f(ponto...))/variacao
  return quociente_de_newton
end

f(x)=x^3+2x+1
#f(x)=log(x)

x=4

valor_deriv=derivada(f,x,0.000001)

println("")

println("Valor da Derivada de f no Ponto ",x," = ",round.(valor_deriv; digits = 3))