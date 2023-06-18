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
OBJS = $(OBJ)/vetop.o $(OBJ)/vet.o  $(OBJ)/memlog.o
HDRS = $(INC)/vet.h $(INC)/msgassert.h $(INC)/memlog.h
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/vetop

all:  $(EXE)
	$(EXE) -d 100 -s
	$(EXE) -d 100 -i
	$(EXE) -d 100 -n
mem: $(EXE)
	$(EXE) -d 100 -s -p /tmp/somalog.out -l
	$(EXE) -d 100 -i -p /tmp/prodlog.out -l
	$(EXE) -d 100 -n -p /tmp/normlog.out -l

$(BIN)/vetop: $(OBJS)
	$(CC) -o $(BIN)/vetop $(OBJS) $(LIBS)

$(OBJ)/vetop.o: $(HDRS) $(SRC)/vetop.c
	$(CC) $(CFLAGS) -o $(OBJ)/vetop.o $(SRC)/vetop.c 

$(OBJ)/vet.o: $(HDRS) $(SRC)/vet.c
	$(CC) $(CFLAGS) -o $(OBJ)/vet.o $(SRC)/vet.c

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
