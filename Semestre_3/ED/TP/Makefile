#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa vetop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2022-04-02 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/Arvore.o $(OBJ)/FilaEncadeada.o $(OBJ)/ArvoreExpressao.o 
HDRS = $(INC)/Pilha.hpp $(INC)/Arvore.hpp $(INC)/FilaEncadeada.hpp $(INC)/ArvoreExpressao.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run:  $(EXE)
	$(BIN)/main < in.txt

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/Arvore.o: $(HDRS) $(SRC)/Arvore.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Arvore.o $(SRC)/Arvore.cpp

$(OBJ)/FilaEncadeada.o: $(HDRS) $(SRC)/FilaEncadeada.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/FilaEncadeada.o $(SRC)/FilaEncadeada.cpp

$(OBJ)/ArvoreExpressao.o: $(HDRS) $(SRC)/ArvoreExpressao.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/ArvoreExpressao.o $(SRC)/ArvoreExpressao.cpp

	
clean:
	rm -rf bin/* obj/*