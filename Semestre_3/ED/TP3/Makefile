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
OBJS = $(OBJ)/main.o $(OBJ)/Huffman.o
HDRS = $(INC)/Pilha.hpp $(INC)/MinHeap.hpp $(INC)/Huffman.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run:  $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp
$(OBJ)/Huffman.o: $(HDRS) $(SRC)/Huffman.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Huffman.o $(SRC)/Huffman.cpp

	
clean:
	rm -rf bin/* obj/*