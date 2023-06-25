CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/ArvoreB.o
HDRS = 
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/arvexp

run:  $(EXE)
	(BIN)/arvexp

$(BIN)/arvexp: $(OBJS)
	$(CC) -o $(BIN)/arvexp $(OBJS) $(LIBS)

$(OBJ)/ArvoreB.o: $(HDRS) $(SRC)/ArvoreB.c
	$(CC) $(CFLAGS) -o $(OBJ)/ArvoreB.o $(SRC)/ArvoreB.c
#-Dm=2 -DCARGA=100 -o arvexp arvexp.c -lm
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
