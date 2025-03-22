CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o
HDRS = $(INC)/dense.h $(INC)/inverse.h $(INC)/level1.h  $(INC)/level2.h $(INC)/level1.h
CFLAGS = -c -I $(INC)

EXE = $(BIN)/tp2virtual

# Regra principal
run:  $(EXE)

# Regras para criar o executável
$(BIN)/tp2virtual: $(OBJS)
	$(CC) -o $(BIN)/tp2virtual $(OBJS) $(LIBS)

# Regras para gerar o objeto main.o
$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c
	
clean:
	rm -rf bin/* obj/*
