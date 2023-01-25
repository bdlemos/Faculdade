# Dados de entrada

e1=[19,0];
e2=[15,0];
bt1=0.8+n/100;
bt2=0.5+n/100;
r=1.5;
grida=1/200:1/200:1
precis=1/200

u11(c)=log(c);
u12(c)=(c)^(1/2);
u21(c)=log(c);
u22(c)=(c)^(1/2);

#Arquivos de Execução

module principal
include("bloco1_demanda.jl")
include("bloco2_equil.jl")         
end

#Comando Principal Extraído do Módulo Principal
prec_func=principal.price
(eq,a1,a2,erro)=prec_func(u11,u12,u21,u22,e1,e2,bt1,bt2,r,grida,precis)

println("Preço = ",eq)
println("Demanda Investidor 1 = ",a1)
println("Demanda Investidor 2 = ",a2)
println("Erro = ",erro)