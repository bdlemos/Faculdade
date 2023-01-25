function max_func(func,gridk,gridl)
  matriz_func=[func(x...) for x in Iterators.product(gridk,gridl)]
  func_max=maximum(matriz_func)
  kl_otimo=argmax(matriz_func)
  k_otimo=gridk[kl_otimo[1]]
  l_otimo=gridl[kl_otimo[2]]
  prod_otima=func_max
  return [k_otimo,l_otimo,prod_otima]
end

#Dados de Entrada

luc(k,l)=8k^(0.3)*l^(1/2)-4l-k
precis_deriv=10^(-12);precis_grid=0.005
gridk=0:precis_grid:10
gridl=0:precis_grid:10

result_otimo=max_func(luc,gridk,gridl)

println("")

println("Alocação Ótima (cap,trab,luc) = ",round.(result_otimo; digits = 3))

