using JuMP
using HiGHS

function printSolution(x)
	println("Objetos na Solução:")
	for i in x
		print(i)
		print(";")
	end
	println()
end

model = Model(HiGHS.Optimizer)

@variable(model, x[i=1:4])

@constraint(model, 12*x[1] + 10*x[2] + 8x[3] + 6x[4] <= 13)

@objective(model, Max, 18*x[1] + 10*x[2] + 6x[3] + 4x[4])

print(model)

optimize!(model)

sol = objective_value(model)
println("Valor otimo= ", sol)

printSolution(x)