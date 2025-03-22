# Definir o compilador
CC = gcc

# Definir o nome do arquivo fonte e o binário de saída
SRC = sh.c
OUT = myshell.out

# Regra padrão para compilar e rodar
all: $(OUT) run

# Regra para compilar o código fonte
$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT)

# Regra para rodar o binário
run:
	./$(OUT)

# Limpar arquivos gerados
clean:
	rm -f $(OUT)
