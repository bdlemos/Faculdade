#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa vetop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2022-04-02 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/fibFact.o $(OBJ)/operations.o 
HDRS = $(INC)/fibFact.h $(INC)/operations.h 
CFLAGS = -Wall -c -ftest-coverage -I$(INC)

EXE = $(BIN)/main

run:  $(EXE)
	$(BIN)/main 1
	gprof $(BIN)/main gmon.out > analise.txt
	$(BIN)/main 2
	gprof $(BIN)/main gmon.out > analise2.txt

$(BIN)/main: $(OBJS)
	$(CC) -pg -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.c
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.c 

$(OBJ)/fibFact.o: $(HDRS) $(SRC)/fibFact.c
	$(CC) $(CFLAGS) -o $(OBJ)/fibFact.o $(SRC)/fibFact.c

$(OBJ)/operations.o: $(HDRS) $(SRC)/operations.c
	$(CC) $(CFLAGS) -o $(OBJ)/operations.o $(SRC)/operations.c
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
