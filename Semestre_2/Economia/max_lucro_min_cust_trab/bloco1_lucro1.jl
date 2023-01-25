function lucro1_otimo(f,p,w,r,gridk,gridl)
  l(k,l)=p*f(k,l) - (r*k + w*l)
  l_aux=[l(x...) for x in Iterators.product(gridk, gridl)]
  l_max=maximum(l_aux)
  kl_otimo=argmax(l_aux)
  k_otimo=gridk[kl_otimo[1]]
  l_otimo=gridl[kl_otimo[2]]
  y_otimo=f(k_otimo, l_otimo)
  return [k_otimo,l_otimo,y_otimo,l_max]
end

println("Lucro em um Estágio - Executado com Sucesso");