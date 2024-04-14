
using JuMP
using HiGHS

mutable struct CliqueData
    n::Int #numero de vertices
    ng::Array{Array{Int}} #vizinhancas
end

function readData(file)
	n = 0
	ng = [[]]
	for l in eachline(file)
		q = split(l, "\t")

		if q[1] == "n"
			n = parse(Int64, q[2])
			ng = [[] for i=1:n]
		elseif q[1] == "e"
			v = parse(Int64, q[2])
			u = parse(Int64, q[3])
			push!(ng[v], u)
			push!(ng[u], v)
		end
	end
	return CliqueData(n,ng)
end


function printSolution(data, y, x)
	for i in 1:data.n
		if y[i] == 1
			print("Cor ", i, ": ")
			for j=1:data.n
				if x[i,j] == 1
					print(j, " ")
				end
			end
			println()
		end
	end
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)
#adj = adjMatrix(data)


@variable(model, y[i=1:data.n],Bin)
@variable(model, x[i=1:data.n,j=1:data.n], Bin) #Cada linha representa uma cor e cada coluna um vertice

#Cada vertice pode ter apenas uma cor
for j=1:data.n
	@constraint(model, sum(x[i,j] for i=1:data.n) == 1)
end


# Para cada par de vertices adjacentes, eles nao podem ter a mesma cor ativa
# A matriz x na posição i,j representa a cor i no vertice j
for i = 1:data.n
	for j in data.ng[i]
		for z = 1:data.n
			@constraint(model, x[z,i] + x[z,j] <= y[z]) # Caso a cor z esteja ativa, os vertices i e j nao podem ter a mesma cor, caso contrario, a soma sera menor igual a 0
		end
    end
end


@objective(model, Min, sum(y[i] for i=1:data.n))

print(model)

optimize!(model)

sol = objective_value(model)
println("TP1 2022043949 = ", sol)

#print x
# for i=1:data.n
# 	for j=1:data.n
# 		print(Int(value(x[i,j])), " ")
# 	end
# 	println()
# end

# printSolution(data, value.(y), value.(x))

