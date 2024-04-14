using JuMP
using HiGHS

mutable struct AColoracao
    n::Int
    vizinhos::Array{Array{Int}}
    vizinhos_m::Matrix{Int64}
end

function LerArquivo(arquivo)
    n = 0
    vizinhos = [[]]
    vizinhos_m = zeros(Int64, n, n)
    for l in eachline(arquivo)
        q = split(l, "\t")
        if q[1] == "n"
            n = parse(Int64, q[2])
            vizinhos = [[] for i=1:n]
			vizinhos_m = zeros(Int64, n, n)
        elseif q[1] == "e"
            v = parse(Int64, q[2])
            u = parse(Int64, q[3])
            push!(vizinhos[v], u)
            push!(vizinhos[u], v)
            vizinhos_m[v, u] = 1
            vizinhos_m[u, v] = 1
        end
    end
    return AColoracao(n,vizinhos,vizinhos_m)
end

modelo = Model(HiGHS.Optimizer)
#set_silent(modelo)
arquivo = open(ARGS[1], "r")
dados = LerArquivo(arquivo)

@variable(modelo, y[i=1:dados.n], Bin)
# i vertice, j cor
@variable(modelo, x[i=1:dados.n, j=1:dados.n], Bin)
# i j cores, k l vertices
@variable(modelo, z[i=1:dados.n, j=(i+1):dados.n, k=1:dados.n, l=1:dados.n], Bin)

# fazendo a coloracao normal
for v = 1:dados.n
	@constraint(modelo, sum(x[v, k] for k=1:dados.n) == 1)
	for k = 1:dados.n
		for u in dados.vizinhos[v]
			@constraint(modelo, x[v, k] + x[u, k]<= y[k])
		end
		@constraint(modelo, x[v,k] <= y[k])
	end
end

for k = 1:dados.n
	@constraint(modelo, sum(x[v, k] for v=1:dados.n) >= y[k])
end

# se l for vizinho de k, queremos que i e j tenham conexao
for i = 1:dados.n
    for j = (i+1):dados.n
        for k = 1:dados.n
            for l = 1:dados.n
                if dados.vizinhos_m[k, l] == 1
                    @constraint(modelo, z[i,j,k,l] <= x[k, i])
                    @constraint(modelo, z[i,j,k,l] <= x[l, j])
                else
                    @constraint(modelo, z[i,j,k,l] <= 0)
                end
            end
        end
        @constraint(modelo, sum(sum(z[i,j,k,l] for l=1:dados.n) for k=1:dados.n) >= y[i] + y[j] - 1)
    end
end

@objective(modelo, Max, sum(y[i] for i=1:dados.n))

optimize!(modelo)
sol = objective_value(modelo)
println("TP1 2022043485 = ", sol)