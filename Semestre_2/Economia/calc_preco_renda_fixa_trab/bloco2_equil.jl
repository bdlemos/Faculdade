function price(u11,u12,u21,u22,e1,e2,bt1,bt2,r,grida,precis)
p1=
p2=
ngp=max(p1,p2)
gridp=precis:precis:ngp
abs_exc_dem(preco)=abs(exc_demand(preco,u11,u12,u21,u22,e1,e2,bt1,bt2,r,grida))
erro_exc_dem=
eq=
a1=
a2=
erro=minimum(erro_exc_dem)
return [eq,a1,a2,erro]
end
println("Função de preço executada com sucesso")