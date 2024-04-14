using JuMP
using HiGHS

mutable struct EmpacotamentoData
    n::Int #numero de objetos
    c::Array{Float64} #peso
end

function readData(file)
    n = 0
    c = []
    for l in eachline(file)
        q = split(l, "\t")
        num = parse(Int64, q[2])
        if q[1] == "n"
            n = num
            c = [0.0 for i=1:n]
        elseif q[1] == "o"
            value = parse(Float64, q[3])
            c[num + 1] = value
        end
    end
    return EmpacotamentoData(n,c)
end

function printSolution(data, x, y)
    for i in 1:data.n
        aux = round(Int64, y[i])
        if aux == 0
            continue
        end
        println("CAIXA ", i, " PESO: ", sum(x[i,j]*data.c[j] for j=1:data.n))
        #print("CAIXA ", i, " : ")
        for j = 1: data.n
            if(value(x[i,j]) >= 0.5)
                print(j-1)
                print(" ")
            end
        end
        println()
    end
    println()
end

model = Model(HiGHS.Optimizer)

file = open(ARGS[1], "r")
data = readData(file)

@variable(model, y[1:data.n],Bin)
@variable(model, x[1:data.n,1:data.n] , Bin)


# cada coluna j, representa um item, deve ser empacotado em apenas um pacote
for j=1:data.n
    @constraint(model, sum(x[i,j] for i=1:data.n) == 1)
end

# cada linha i, representa um pacote, deve ter no maximo 20kg
for i=1:data.n
    @constraint(model, sum(x[i,j]*data.c[j] for j=1:data.n) <= 20*y[i])
end


@objective(model, Min, sum(y[i] for i=1:data.n))


optimize!(model)

sol = objective_value(model)
println("TP1 2022043949 = ", sol)


#printSolution(data, value.(x), value.(y))