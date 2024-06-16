#= 

A-COLORAÇÃO
Nome: Antônio Caetano Neves Neto
Matrícula: 2022043698

=#

using JuMP
using HiGHS

# Definindo a estrutura de dados do problema.
mutable struct ProblemData
    n::Int
    edges::Array{Array{Int}}
end

function readData(file)
    n = 0
    edges = []

    for line in eachline(file)
        q = split(line, "\t")

        if q[1] == "n"
            n = parse(Int, q[2])

            # Criando a matriz de adjacência nula para ser preenchida posteriormente.
            for i=1:n
                push!(edges, [])
            end
        else
            # Preenchendo a matriz de adjacência.
            push!(edges[parse(Int, q[2])], parse(Int, q[3]))
            push!(edges[parse(Int, q[3])], parse(Int, q[2]))
        end
    end

    return ProblemData(n, edges)
end

# Lendo o arquivo de entrada.
file = open(ARGS[1], "r")
data = readData(file)

# Criando o modelo de programação linear.
model = Model(HiGHS.Optimizer)

@variable(model, z[1:data.n, 1:data.n, 1:data.n, 1:data.n], Bin)

# A variável é uma matriz que informa se o vértice i é da cor j
@variable(model, x[1:data.n, 1:data.n], Bin)

# Indica se a cor i está ativa ou não
@variable(model, y[1:data.n], Bin)

# Vértices adjacentes não podem ter a mesma cor
for i=1:data.n
    for j in data.edges[i]
        for k=1:data.n
            @constraint(model, x[i, k] + x[j, k] <= y[k])
        end
    end
end

# Nenhum vértice pode ter mais de uma cor.
for i=1:data.n
    @constraint(model, sum(x[i, j] for j=1:data.n) == 1)
end

# Se um vértice i é da cor k, então a matriz z deve obedecer a condição.
for k=1:data.n
    for l=k+1:data.n
        for i=1:data.n
            for j in data.edges[i]
                @constraint(model, z[i, j, k, l] <= x[i, k])
                @constraint(model, z[i, j, k, l] <= x[j, l])
            end
        end
    end
end

# Para cada opção de cor, deve existir pelo menos um par de vértices adjacentes com esse par cor.
for k=1:data.n
    for l=k+1:data.n
        @constraint(model, sum(z[i, j, k, l] for i=1:data.n, j in data.edges[i]) >= y[k] + y[l] - 1)
    end
end

# Queremos minimizar o número de cores, logo, a soma de todas as colunas que tem vértice
@objective(model, Max, sum(y[i] for i=1:data.n))

# Resolvendo o modelo.
optimize!(model)

sol = objective_value(model)
println("TP1 2022043698 = ", sol)