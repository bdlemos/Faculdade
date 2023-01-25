CC=g++
CFLAGS=-std=c++11 -Wall

BIN     := build
SRC     := src
INCLUDE := include
ENTITIES	:= $(SRC)/entidades
LIB     := lib
LIBRARIES   := 
EXECUTABLE  := vpl_execution


all: $(EXECUTABLE)

run: clean all
	clear
	./$(EXECUTABLE)

$(EXECUTABLE): $(BIN)/Funcionario.o $(BIN)/Pessoa.o $(BIN)/Professor.o $(BIN)/main.o
	${CC} ${CFLAGS} $(BIN)/*.o -o $(EXECUTABLE) 


##$(BIN)/%.o: $(ENTITIES)/%.cpp $(INCLUDE)/%.hpp #ESSAS DUAS LINHAS FAZEM O MESMO
##	${CC} ${CFLAGS} -I ${INCLUDE}/ -c $< -o $@   #QUE A LINHA 26 A 33.

$(BIN)/Pessoa.o: $(ENTITIES)/Pessoa.cpp $(INCLUDE)/Pessoa.hpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c $(ENTITIES)/Pessoa.cpp -o $(BIN)/Pessoa.o

$(BIN)/Professor.o: $(ENTITIES)/Professor.cpp $(INCLUDE)/Professor.hpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c $(ENTITIES)/Professor.cpp -o $(BIN)/Professor.o

$(BIN)/Funcionario.o: $(ENTITIES)/Funcionario.cpp $(INCLUDE)/Funcionario.hpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c $(ENTITIES)/Funcionario.cpp -o $(BIN)/Funcionario.o

$(BIN)/main.o: $(INCLUDE)/Pessoa.hpp $(INCLUDE)/Professor.hpp $(INCLUDE)/Funcionario.hpp $(SRC)/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE}/ -c $(SRC)/main.cpp -o $(BIN)/main.o

clean:
	-rm $(BIN)/*