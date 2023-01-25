# Dados de entrada

n=30
a=(1/4+n/1000);b=(1/2+n/1000)
f(k,l)=k^a*l^b
isoqk(l,y)=y^(1/a)/l^(b/a)
precis_deriv=10^(-12);precis_grid=0.005
p=8;w=4;r=1;
gridk=0:precis_grid:10
gridl=0:precis_grid:10
gridy=precis_grid:precis_grid:f(10,10)


#Arquivos de Execução

module principal
include("bloco0_derivada.jl")
include("bloco1_lucro1.jl")
include("bloco2_cust_cond.jl")  
include("bloco3_lucro2.jl")       
end

#Comandos Extraídos do Módulo Principal
lucro_1estagio=principal.lucro1_otimo
lucro_2estagios=principal.lucro2_otimo
dem_cond=principal.dem_cond
custo_minimo=principal.cust_min
deriv=principal.derivada

#Execução dos Comandos
l1=lucro_1estagio(f,p,w,r,gridk,gridl)
l2=lucro_2estagios(isoqk,p,w,r,gridl,gridy)

(cap_otimo,trab_otimo,prod_otima,luc_max_1est)=l1

(prod_otima_1est,luc_max_2est)=l2

pmgk_otimo=deriv(f,[cap_otimo,trab_otimo],[precis_deriv,0])
pmgl_otimo=deriv(f,[cap_otimo,trab_otimo],[0,precis_deriv])

(dem_cond_cap,dem_cond_trab)=dem_cond(prod_otima,isoqk,w,r,gridl)
custo_min_func(y)=custo_minimo(y,isoqk,w,r,gridl)
custo_min_otimo=custo_min_func(prod_otima)
custo_marg=deriv(custo_min_func,prod_otima,precis_deriv)

#Exibição dos Resultados
println("")

println("Capital Ótimo = ",round(cap_otimo; digits = 3))
println("Trabalho Ótimo = ",round(trab_otimo; digits = 3))
println("Produção Ótima = ",round(prod_otima; digits = 3))
println("Produto Marginal do Capital = ",round(pmgk_otimo; digits = 3))
println("Produto Marginal do Trabalho = ",round(pmgl_otimo; digits = 3))
println("Custo Marginal Ótimo = ",round(custo_marg; digits = 3))

println("")

println("Lucro Máximo da Firma Estabelecida = ",round(luc_max_1est; digits = 3))
println("Lucro Máximo da Firma Entrante = ",round(luc_max_2est; digits = 3))

println("")

println("Demanda por Capital = ",round(dem_cond_cap; digits = 3))
println("Demanda por Trabalho  = ",round(dem_cond_trab; digits = 3))