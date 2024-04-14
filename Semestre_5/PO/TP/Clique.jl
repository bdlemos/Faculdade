
using JuMP
using HiGHS

mutable struct CliqueData
    n::Int #numero de vertices
    ng::Array{Array{Int}} #vizinhancas
end

function readData(file)
	n = 0
	ng=[[]]
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


function adjMatrix(data)
	m = zeros(Int64, data.n, data.n)
	for i=1:data.n
		for j in data.ng[i]
			m[i,j] = 1
		end
	end
	return m
end

function printSolution(data, x)
	println("Uma clique maxima:")
	for i = 1: data.n
		if value(x[i]) > 0.5
			println("$i")
		end
	end
	println()
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")

data = readData(file)
adj = adjMatrix(data)


@variable(model, y[i=1:data.n], Bin)

for i = 1:data.n
    for j = i+1:data.n
        @constraint(model, y[j] + y[i] <= adj[i,j] + 1)
    end
end


@objective(model, Max, sum(y[i] for i=1:data.n))

print(model)

optimize!(model)

sol = objective_value(model)
println("TP1 2022043949 = ", sol)

#printSolution(data, value.(y))

