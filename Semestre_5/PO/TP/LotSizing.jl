
using JuMP
using HiGHS

mutable struct LotSizingData
    n::Int #numero de periodos
    c::Array{Int} #custo de produção
    h::Array{Int} #custo de estoque
    d::Array{Int} #demandas dos clientes
    p::Array{Int} #Multa por não atender a demanda
end

function readData(file)
	n = 0
	c = []
	h = []
	d = []
    p = []
	for l in eachline(file)
		q = split(l, "\t")
		num = parse(Int64, q[2])
		if q[1] == "n"
			n = num
			c = [0 for i=1:n]
			h = [0 for i=1:n]
			d = [0 for i=1:n]
            p = [0 for i=1:n]
		elseif q[1] == "c"
			num = parse(Int64, q[2])
			c[num] = parse(Float64, q[3])
		elseif q[1] == "s"
			num = parse(Int64, q[2])
			h[num] = parse(Float64, q[3])									
		elseif q[1] == "d"
			num = parse(Int64, q[2])
			d[num] = parse(Float64, q[3])
        elseif q[1] == "p"
            num = parse(Int64, q[2])
            p[num] = parse(Float64, q[3])
		end
	end
	return LotSizingData(n,c,h,d,p)
end

function printSolution(data, x)
	println("Esquema de produção:")
	for i = 1: data.n
		println("No periodo $i é produzido $(value(x[i]))")
	end
	println()
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[i=1:data.n] >= 0) # quantidade produzida no periodo i
@variable(model, s[i=1:data.n+1]) # estoque no periodo i
@variable(model, z[i=1:data.n]) # custo extra no periodo i


for i=1:data.n
	@constraint(model, s[i+1] == s[i] + x[i] - data.d[i]) 
	@constraint(model, z[i] >= -s[i+1]*data.p[i]) #s[i+1] é o estoque do periodo i para o i+1
	@constraint(model, z[i] >= s[i+1]*data.h[i]) # por isso as penalidades sao do dia i, pq s[i+1] é o quanto sobra/falta do dia i
end

@constraint(model, s[1] == 0)
#@constraint(model, s[data.n+1] == 0)

@constraint(model, sum(x) == sum(data.d[i] for i in 1:data.n))


#						   custo de produção + custo extra
@objective(model, Min, sum((data.c[i]*x[i]) + z[i]  for i=1:data.n))

print(model)

optimize!(model)

sol = objective_value(model)
println("TP1 2022043949 = ", sol)

#printSolution(data, x)

