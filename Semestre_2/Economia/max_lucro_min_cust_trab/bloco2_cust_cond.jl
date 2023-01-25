function dem_cond(y,isoqk,w,r,gridl)
  custo(l)=r*isoqk(l, y) + w*l
  c_aux=[custo(x...) for x in Iterators.product(gridl)]
  l_otimo=argmax(c_aux)
  k_otimo=isoqk(l_otimo, y)
  return [k_otimo,l_otimo]
end
function cust_min(y,isoqk,w,r,gridl)
  custo(l)=r*isoqk(l, y) + w*l
  c_aux=[custo(x...) for x in Iterators.product(gridl)]
  c_min=minimum(c_aux)
  return c_min
end

println("Custo Condicional - Executado com Sucesso");