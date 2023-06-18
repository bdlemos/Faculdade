CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/Graham.o $(OBJ)/FechoConvexo.o $(OBJ)/Jarvis.o
HDRS = $(INC)/Graham.hpp $(INC)/Pilha.hpp $(INC)/Ponto.hpp  $(INC)/FechoConvexo.hpp $(INC)/Jarvis.hpp
CFLAGS = -Wall -c -I $(INC)

EXE = $(BIN)/main

run:  $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/Graham.o: $(HDRS) $(SRC)/Graham.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Graham.o $(SRC)/Graham.cpp

$(OBJ)/FechoConvexo.o: $(HDRS) $(SRC)/FechoConvexo.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/FechoConvexo.o $(SRC)/FechoConvexo.cpp

$(OBJ)/Jarvis.o: $(HDRS) $(SRC)/Jarvis.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Jarvis.o $(SRC)/Jarvis.cpp
	
clean:
	rm -rf bin/* obj/*