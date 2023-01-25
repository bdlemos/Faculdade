function lucro2_otimo(isoqk,p,w,r,gridl,gridy)
  l(y)=p*y - minimum([r*isoqk(l, y) + w*l for l in gridl])
  l_aux=[l(y) for y in gridy]
  l_max=maximum(l_aux)
  y_otimo=argmax(l_aux)
  return [y_otimo,l_max]
end

println("Lucro em Dois Estágios- Executado com Sucesso");