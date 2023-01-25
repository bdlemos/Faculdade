all: build main

run: all clean
	clear
	./main.out

teste_unidade: build teste clean
	clear
	./teste.out

build:
	mkdir build

teste: ./build/indexacao.o ./build/teste.o 
	g++ -w ./build/*  -o teste.out

main: ./build/indexacao.o ./build/main.o 
	g++ -w ./build/*  -o main.out

./build/teste.o: ./include/indexacao.h ./src/main.cpp
	g++ -w -I ./include/ -c ./src/indexacao_teste.cpp -o ./build/teste.o

./build/indexacao.o: ./src/entidades/indexacao.cpp ./include/indexacao.h
	g++ -w -I ./include/ -c ./src/entidades/indexacao.cpp -o ./build/indexacao.o

./build/main.o: ./include/indexacao.h ./src/main.cpp
	g++ -w -I ./include/ -c ./src/main.cpp -o ./build/main.o

clean:
	-rm ./build/*
	-rmdir ./build