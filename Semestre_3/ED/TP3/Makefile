CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/Huffman.o
HDRS = $(INC)/MinHeap.hpp $(INC)/Huffman.hpp
CFLAGS = -Wall -c -I $(INC)

EXE = $(BIN)/main

run:  $(EXE)
	  clear
	  $(EXE) -c bible.txt code.bin
	  $(EXE) -d code.bin decoded.txt  table.txt

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp
$(OBJ)/Huffman.o: $(HDRS) $(SRC)/Huffman.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Huffman.o $(SRC)/Huffman.cpp

	
clean:
	rm -rf bin/* obj/* decoded.txt code.bin table.txt